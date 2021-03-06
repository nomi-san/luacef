#include "luacef.h"

static int luacef_bmp(lua_State *L)
{
	unsigned char *p = lua_touserdata(L, 1);
	int i = lua_tointeger(L, 2);

	lua_pushnumber(L, (double)(p[i]/255));
	lua_pushnumber(L, (double)(p[i+1]/255));
	lua_pushnumber(L, (double)(p[i+2]/255));
	lua_pushnumber(L, (double)(p[i+3]/255));

	return 4;
}

#if LUA_VERSION_NUM == 501
int lua_isinteger(lua_State *L, int i)
{
	double n = lua_tonumber(L, i);
	return n == (int)n;
}

void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup) {
	luaL_checkstack(L, nup + 1, "too many upvalues");
	for (; l->name != NULL; l++) {  /* fill the table with given functions */
		int i;
		lua_pushstring(L, l->name);
		for (i = 0; i < nup; i++)  /* copy upvalues to the top */
			lua_pushvalue(L, -(nup + 1));
		lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
		lua_settable(L, -(nup + 3)); /* table must be below the upvalues, the name and the closure */
	}
	lua_pop(L, nup);  /* remove upvalues */
}

void luaL_setmetatable(lua_State *L, const char *tname) {
	luaL_checkstack(L, 1, "not enough stack slots");
	luaL_getmetatable(L, tname);
	lua_setmetatable(L, -2);
}

#undef lua_getfield
int _lua_getfield(lua_State *L, int i, const char *k)
{
#if LUA_VERSION_NUM > 501
	return lua_getfield(L, i, k);
#else
	lua_getfield(L, i, k);
	return !lua_isnil(L, -1);
#endif
}
#define lua_getfield _lua_getfield
#endif

typedef struct luacef_base {

	cef_base_ref_counted_t base;
	void *p;

} luacef_base;

void* luacef_newuserdata(lua_State* L, size_t sz)
{
	void **ud = (void**)lua_newuserdata(L, sizeof(void*));
	*ud = calloc(1, sz);
	return *ud;
}

void* luacef_checkudata(lua_State* L, int i, const char* s)
{
	if (lua_isnoneornil(L, i)) return NULL;
	void **ud = (void**)luaL_checkudata(L, i, s);
	if (!ud || !*ud) return NULL;
	return *ud;
}

void* luacef_touserdata(lua_State* L, int i)
{
	if (lua_isnoneornil(L, i)) return NULL;
	void **ud = (void**)lua_touserdata(L, i);
	if (!ud || !*ud) return NULL;
	return *ud;
}

void luacef_pushuserdata(lua_State* L, void* udata, const char* meta)
{
	if (!udata) return;
	void** ud = (void**)lua_newuserdata(L, sizeof(void*));
	*ud = udata;
	luaL_setmetatable(L, meta);
}

// luacef metatable //===========================

// release, __gc
int luacef_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

// __index
int luacef_index(lua_State* L)
{
	return 1;
}

// __newindex
int luacef_newindex(lua_State *L)
{
	lua_getuservalue(L, -3);
	lua_pushvalue(L, -3);
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	return 0;
}

// __eq
int luacef_eq(lua_State *L)
{
	void *p1 = luacef_touserdata(L, 1);
	void *p2 = luacef_touserdata(L, 2);

	lua_pushboolean(L, p1 == p2);
	return 1;
}

// __len, for some struct has base member
int luacef_len(lua_State *L)
{
	luacef_base *p = luacef_touserdata(L, 1);
	if (p->base.size) 
		lua_pushinteger(L, p->base.size);
	else
		lua_pushinteger(L, 0);
	return 1;
}

void luacef_error_index(lua_State* L, const char* index)
{
	luaL_error(L, "cannot get member '%s'", index);
}

/*
	<bool> cef.bool(<any> [, <func>() ])

	-- check expression
	-- if true, execute function and return nil
	# '' (empty string), 0 (zero number)
		-> false, unlike default
	# nil, none
		-> false
	# 'a' (valid string), {} (table), fn (function)
		-> true
*/
static int luacef_bool(lua_State *L) {
	int b = false;

	if (!lua_isnoneornil(L, 1))
		switch (lua_type(L, 1)) {
			case LUA_TSTRING: {
				int len = 0;
				const char *s = lua_tolstring(L, 1, &len);
				b = ((len != 0) || (s[0] != '\0'))
					? 1 : 0;
			}	break;

			case LUA_TTABLE:
			case LUA_TFUNCTION:
				b = true;
				break;

			case LUA_TBOOLEAN:
				b = lua_tointeger(L, 1) != 0;
				break;

			case LUA_TNUMBER:
				b = lua_tonumber(L, 1) != 0;
				break;

			case LUA_TUSERDATA:
				b = lua_touserdata(L, 1) != NULL;
				break;

			default:
				b = true;
		}

	if (b != 0 && lua_type(L, 2) == LUA_TFUNCTION) {
		lua_pushvalue(L, 2);
		lua_call(L, 0, 0);
		return 0;
	}

	lua_pushboolean(L, b);
	return 1;
}

// trycatch ==============================
/*
	cef.try {
		func(),
		catch = func(<str> err)
	}
*/
static int luacef_try(lua_State *L)
{
	if (!lua_istable(L, 1)) return 0;

    // Get function expr
	lua_rawgeti(L, 1, 1);
	if (!lua_isfunction(L, -1)) return 0;

    // Call
	int err = lua_pcall(L, 0, 1, 0);
    const char *msg = lua_tostring(L, -1);

    // Check result
	if (err != LUA_OK) {
        // Get catch
		if (!lua_getfield(L, 1, "catch"))
			lua_rawgeti(L, -1, 2);
		if (!lua_isfunction(L, -1))
			return 0;

        // Push err message
        lua_pushstring(L, msg);
		lua_call(L, 1, 0);

        return 1;
    }

    return 0;
}

// ==============================
/*
	<str>, <str> getv()
	-> value 1: CEF version
	-> value 2: Chromium version
*/
static int luacef_getv(lua_State* L)
{
	lua_pushstring(
		L, 
		CEF_VERSION
	);

	lua_pushfstring(
		L, "%d.%d.%d", 
		CHROME_VERSION_MAJOR, 
		CHROME_VERSION_MINOR, 
		CHROME_VERSION_BUILD
	);

	return 2;
}

/*
	<void> printv()
	// CEF: <version>
	// Chromium: <version>
*/
static int luacef_printv(lua_State* L)
{
	printf("CEF: %d.%d.%d\nChromium: %d.%d.%d\n", 
		CEF_VERSION_MAJOR, CHROME_VERSION_BUILD, CEF_COMMIT_NUMBER,
		CHROME_VERSION_MAJOR, CHROME_VERSION_MINOR, CHROME_VERSION_BUILD
	);
	fflush(stdout);
	return 0;
}

static int luacef_print(lua_State *L)
{
	const char *s = lua_tostring(L, 1);
	puts(s);
	fflush(stdout);
	return 0;
}

// ==============================

static void luacef_handler_reg(lua_State* L)
{
	LCEF_API_N(LifeSpanHandler, reg)(L);
	LCEF_API_N(RenderHandler, reg)(L);
	luacef_keyboard_handler_reg(L);
	luacef_LoadHandler_reg(L);
	luacef_ContextMenuHandler_reg(L);
	luacef_JSDialogHandler_reg(L);
	luacef_DragHandler_reg(L);
	luacef_RenderProcessHandler_reg(L);
}

static void luacef_api_reg(lua_State *L)
{
	luacef_MenuModel_reg(L);
	luacef_CompletionCallback_reg(L);

	luacef_V8_reg(L);
	luacef_Time_reg(L);
}

//====================

/*
	<table> require "luacef"
*/
int DLL_PUBLIC luaopen_luacef(lua_State* L)
{
	//__mainState = L;

	lua_newtable(L); // return of require('luacef');

	lua_pushcfunction(L, luacef_bmp);
	lua_setfield(L, -2, "bmp");

	lua_pushcfunction(L, luacef_bool);
	lua_setfield(L, -2, "bool");

	lua_pushcfunction(L, luacef_getv);
	lua_setfield(L, -2, "getv");

	lua_pushcfunction(L, luacef_printv);
	lua_setfield(L, -2, "printv");
	
	lua_pushcfunction(L, luacef_print);
	lua_setfield(L, -2, "print");

    lua_pushcfunction(L, luacef_try);
    lua_setfield(L, -2, "try");
		
	luacef_Client_reg(L);
	luacef_app_reg(L);
	luacef_handler_reg(L);
	luacef_types_reg(L);
	luacef_funcs_reg(L);
	
	luacef_Browser_reg(L);
	luacef_Frame_reg(L);

	luacef_api_reg(L);

	luacef_types_os_reg(L);

	// ptr
	luacef_ptr_reg(L);

	return 1;
}


