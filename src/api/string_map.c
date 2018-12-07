#include "../luacef.h"
#include "include/internal/cef_string_map.h"

static const char __string_map__[] = "CefStringMap";

typedef struct {
	cef_string_map_t self;
	int ref;
} CefStringMap;

static int luacef_StringMap_totable(lua_State *L)
{
	CefStringMap *map = luacef_alloct(CefStringMap);
	map->self = cef_string_map_alloc();

	lua_newtable(L);

	return 1;
}


int luacef_StringMap_new(lua_State *L)
{
	CefStringMap *map = luacef_alloct(CefStringMap);
	map->self = cef_string_map_alloc();

	cef_string_map_alloc;


	luacef_pushudata(L, map, __string_map__);
	return 1;
}



int luacef_StringMap_index(lua_State *L)
{
	cef_string_map_t map = luacef_toudata(L, 1);

	if (lua_isinteger(L, 2)) {



	}
	else if (lua_isstring(L, 2)) {



	}

	return 1;
}

int luacef_StringMap_unm(lua_State *L)
{
	cef_string_map_t map = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, map);
	return 1;
}




// ==================================================

static const luaL_Reg luacef_StringMap_meta[] = {
	{ "__index", luacef_StringMap_index },
	{ "__call", luacef_StringMap_index },
	{ "__unm", luacef_StringMap_unm },
	{ NULL, NULL }
};

void luacef_StringMap_reg(lua_State *L)
{
	luaL_newmetatable(L, __string_map__);
	luaL_setfuncs(L, luacef_StringMap_meta, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_StringMap_new);
	lua_setfield(L, -2, "newStringMap");
}