#include "luacef.h"

typedef struct luacef_base {

	cef_base_ref_counted_t base;
	void *p;

} luacef_base;

void* luacef_newuserdata(lua_State* L, size_t sz)
{
	void **ud = (void**)lua_newuserdata(L, 4u);
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
	void** ud = (void**)lua_newuserdata(L, 4u);
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
// ==============================

static void luacef_handler_reg(lua_State* L)
{
	luacef_life_span_handler_reg(L);
	luacef_keyboard_handler_reg(L);
	luacef_LoadHandler_reg(L);
	luacef_ContextMenuHandler_reg(L);
	luacef_JSDialogHandler_reg(L);
	luacef_DragHandler_reg(L);
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
EXPORT(int) luaopen_luacef(lua_State* L)
{
	//__mainState = L;

	lua_newtable(L); // return of require('luacef');

	lua_pushcfunction(L, luacef_getv);
	lua_setfield(L, -2, "getv");

	lua_pushcfunction(L, luacef_printv);
	lua_setfield(L, -2, "printv");
		
	luacef_Client_reg(L);
	luacef_app_reg(L);
	luacef_handler_reg(L);
	luacef_types_reg(L);
	luacef_funcs_reg(L);

	luacef_Browser_reg(L);

	luacef_api_reg(L);

	// ptr
	luacef_ptr_reg(L);

	return 1;
}


