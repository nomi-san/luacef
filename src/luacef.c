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

void* luacef_pushuserdata(lua_State* L, void* udata, const char* meta)
{
	if (!udata) return NULL;
	void** ud = (void**)lua_newuserdata(L, 4u);
	*ud = udata;
	luaL_setmetatable(L, meta);

	return ud;
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

//==============================

/*
	cef = require "luacef"
*/
int LUACEF_API luaopen_luacef(lua_State* L)
{
	HINSTANCE ins = GetModuleHandleA(NULL);
	if (ins == GetModuleHandleA("lua.exe") || 
		ins == GetModuleHandleA("luajit.exe"))
		__interpreter = 1;

	//__mainState = L;

	lua_newtable(L);

	luacef_client_reg(L);
	luacef_app_reg(L);
	luacef_handler_reg(L);
	luacef_types_reg(L);
	luacef_funcs_reg(L);

	luacef_browser_reg(L);

	return 1;
}


