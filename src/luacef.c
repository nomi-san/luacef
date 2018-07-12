#include "luacef.h"

void* luacef_newuserdata(lua_State* L, size_t sz)
{
	void **ud = (void**)lua_newuserdata(L, 4u);
	*ud = calloc(1, sz);
	return *ud;
}

void* luacef_checkudata(lua_State* L, int i, const char* s)
{
	void **ud = (void**)luaL_checkudata(L, i, s);
	if (!ud || !*ud) return NULL;
	return *ud;
}

void* luacef_touserdata(lua_State* L, int i)
{
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

void luacef_error_index(lua_State* L, const char* index)
{
	luaL_error(L, "cannot get member '%s'", index);
}

// ==============================
/*
	<str>, <str> version() 
					|-> <CEF version>
					|-> <Chromium version>
*/
static int luacef_version(lua_State* L)
{
	lua_pushstring(L, CEF_VERSION);
	lua_pushfstring(L, "%d.%d", CHROME_VERSION_MAJOR, CHROME_VERSION_MINOR);

	return 2;
}

/*
	<void> printversion()
	-->	CEF: <version>
	--> Chromium: <version>
*/
static int luacef_print_version(lua_State* L)
{
	lua_getglobal(L, "print");
	lua_pushvalue(L, -1);
	if (lua_isnil(L, -1)) return 0; // for not print

	lua_pushstring(L, "CEF: " CEF_VERSION);
	lua_pushfstring(L, "\nChromium: %d.%d\n", CHROME_VERSION_MAJOR, CHROME_VERSION_MINOR);
	
	lua_pcall(L, 2, 0, 8);
	return 0;
}
// ==============================


static void luacef_handler_reg(lua_State* L)
{
	luacef_life_span_handler_reg(L);
	luacef_keyboard_handler_reg(L);
}

static void luacef_api_reg(lua_State *L)
{
	luacef_v8_reg(L);
}

//====================

/*
	<table> require "luacef"
*/
int LUACEF_API luaopen_luacef(lua_State* L)
{
	HINSTANCE ins = GetModuleHandleA(NULL);
	if (ins == GetModuleHandleA("lua.exe") || 
		ins == GetModuleHandleA("luajit.exe"))
		__interpreter = 1;

	//__mainState = L;

	lua_newtable(L);
	lua_pushcfunction(L, luacef_version);
	lua_setfield(L, -2, "version");

	lua_pushcfunction(L, luacef_print_version);
	lua_setfield(L, -2, "printversion");
		
	luacef_client_reg(L);
	luacef_app_reg(L);
	luacef_handler_reg(L);
	luacef_types_reg(L);
	luacef_funcs_reg(L);

	luacef_browser_reg(L);

	luacef_api_reg(L);

	// ptr
	luacef_ptr_reg(L);

	return 1;
}


