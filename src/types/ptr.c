#include "../luacef.h"

static const char *__val = "val";
static const char *__ptr = "ptr";
static const char *__new = "new";

/*
	<IntPtr> newIntPtr(<int> value)
	<IntPtr> IntPtr.new(<int> value)
	-- create new IntPtr

	<void> IntPtr:release()
	-- release, only use when itself created by newIntPtr() or self.new()

	<udata> IntPtr.ptr
	-- get pointer

	<int> IntPtr.val
	-- set/get value
*/
static int luacef_IntPtr_new(lua_State *L)
{
	luacef_int *p = calloc(1, sizeof(luacef_int));
	*p = lua_tointeger(L, 1);

	luacef_pushuserdata(L, p, __int_ptr__);
	return 1;
}

static int luacef_IntPtr_index(lua_State *L)
{
	luacef_int *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		lua_pushinteger(L, *p);

	else if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __new))
		lua_pushcfunction(L, luacef_IntPtr_new);

	else if (!strcmp(i, __ptr))
		lua_pushlightuserdata(L, p);

	else return 0;

	return 1;
}

static int luacef_int_ptr_newindex(lua_State *L)
{
	luacef_int *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		*p = lua_tointeger(L, 3);

	return 0;
}

static const luaL_Reg luacef_IntPtr_m[] = {
	{ "__index", luacef_IntPtr_index },
	{ "__newindex", luacef_int_ptr_newindex },
	{ NULL, NULL}
};

// ==================================

/*
	<DoublePtr> newDoublePtr(<double> value)
	<DoublePtr> DoublePtr.new(<double> value)
	-- create new DoublePtr

	<void> DoublePtr:release()
	-- release, only use when itself created by newDoublePtr() or self.new()

	<udata> IntDouble.ptr
	-- get pointer

	<double> DoublePtr.val
	-- set/get value
*/
static int luacef_DoublePtr_new(lua_State *L)
{
	luacef_double *p = calloc(1, sizeof(luacef_double));
	*p = lua_tonumber(L, 1);

	luacef_pushuserdata(L, p, __double_ptr__);
	return 1;
}

static int luacef_DoublePtr_index(lua_State *L)
{
	luacef_double *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		lua_pushnumber(L, *p);

	else if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __new))
		lua_pushcfunction(L, luacef_DoublePtr_new);

	else if (!strcmp(i, __ptr))
		lua_pushlightuserdata(L, p);

	else return 0;

	return 1;
}

static int luacef_DoublePtr_newindex(lua_State *L)
{
	luacef_double *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		*p = lua_tonumber(L, 3);

	return 0;
}

static const luaL_Reg luacef_DoublePtr_m[] = {
	{ "__index", luacef_DoublePtr_index },
	{ "__newindex", luacef_DoublePtr_newindex },
	{ NULL, NULL}
};

// =================================

void luacef_ptr_reg(lua_State *L)
{
	luaL_newmetatable(L, __int_ptr__);
	luaL_setfuncs(L, luacef_IntPtr_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_IntPtr_new);
	lua_setfield(L, -2, "newIntPtr");
	
	// ==============

	luaL_newmetatable(L, __double_ptr__);
	luaL_setfuncs(L, luacef_DoublePtr_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_DoublePtr_new);
	lua_setfield(L, -2, "newDoublePtr");

}

// =================================