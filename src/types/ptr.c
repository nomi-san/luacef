#include "../luacef.h"

static const char *__val = "val";
static const char *__ptr = "ptr";
static const char *__new = "new";

#define luacef_int long
#define luacef_bool int

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
static int luacef_int_ptr_new(lua_State *L)
{
	luacef_int *p = calloc(1, sizeof(long));
	*p = lua_tointeger(L, 1);

	luacef_pushuserdata(L, p, __int_ptr__);
	return 1;
}

static int luacef_int_ptr_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_int_ptr_index(lua_State *L)
{
	luacef_int *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		lua_pushinteger(L, *p);

	else if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_int_ptr_release);

	else if (!strcmp(i, __new))
		lua_pushcfunction(L, luacef_int_ptr_new);

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

static const luaL_Reg luacef_int_ptr_m[] = {
	{ "__index", luacef_int_ptr_index },
	{ "__newindex", luacef_int_ptr_newindex },
	{ NULL, NULL}
};

// =============================

/*
	<BoolPtr> newBoolPtr(<bool> value)
	<BoolPtr> BoolPtr.new(<bool> value)
	-- create new BoolPtr

	<void> BoolPtr:release()
	-- release, only use when itself created by newBoolPtr() or self.new()

	<udata> BoolPtr.ptr
	-- get pointer

	<bool> BoolPtr.val
	-- set/get value
*/
static int luacef_bool_ptr_new(lua_State *L)
{
	luacef_bool *p = calloc(1, sizeof(long));
	*p = lua_tointeger(L, 1);
	//*p = lua_toboolean(L, 1);
	
	luacef_pushuserdata(L, p, __bool_ptr__);
	return 1;
}

static int luacef_bool_ptr_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_bool_ptr_index(lua_State *L)
{
	luacef_bool *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		lua_pushboolean(L, *p);

	else if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_bool_ptr_release);

	else if (!strcmp(i, __new))
		lua_pushcfunction(L, luacef_bool_ptr_new);

	else if (!strcmp(i, __ptr))
		lua_pushlightuserdata(L, p);

	else return 0;

	return 1;
}

static int luacef_bool_ptr_newindex(lua_State *L)
{
	luacef_bool *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __val))
		*p = lua_tointeger(L, 3);
		//*p = lua_toboolean(L, 3);

	return 0;
}

static const luaL_Reg luacef_bool_ptr_m[] = {
	{ "__index", luacef_bool_ptr_index },
	{ "__newindex", luacef_bool_ptr_newindex },
	{ NULL, NULL}
};


// =================================

void luacef_ptr_reg(lua_State *L)
{
	luaL_newmetatable(L, __int_ptr__);
	luaL_setfuncs(L, luacef_int_ptr_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_int_ptr_new);
	lua_setfield(L, -2, "newIntPtr");
	
	// ==============

	luaL_newmetatable(L, __bool_ptr__);
	luaL_setfuncs(L, luacef_bool_ptr_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_bool_ptr_new);
	lua_setfield(L, -2, "newBoolPtr");

}