#include "../luacef.h"

#define IP(fn) \
	LCEF_API(IntPtr, fn)

#define IP_N(fn) \
	LCEF_API_N(IntPtr, fn)

#define IP_M(mname) \
	LCEF_M(IntPtr, mname)

#define NP(fn) \
	LCEF_API(NumPtr, fn)

#define NP_N(fn) \
	LCEF_API_N(NumPtr, fn)

#define NP_M(mname) \
	LCEF_M(NumPtr, mname)

// IntPtr
// =========================
/*
	-- new IntPtr
	<IntPtr> cef.newIntPtr(<int> value)

	-- set value
	<nil> IntPtr(<int> value)

	-- get value
	<int> IntPtr()

	-- get sizeof
	<int> #IntPtr

	-- get pointer
	<udata> -IntPtr
*/

IP(new)
{
	IntPtr p = calloc(1, sizeof(IntPtr));
	*p = lua_tointeger(L, 1);

	luacef_pushuserdata(L, p, __IntPtr__);
	return 1;
}

IP(call)
{
	IntPtr p = luacef_touserdata(L, 1);

	if (lua_isnoneornil(L, 2))
		lua_pushinteger(L, *p);
	else {
		*p = lua_tointeger(L, 2);
		lua_pushnil(L);
	}

	return 1;
}

IP(unm)
{
	IntPtr p = luacef_touserdata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

IP(len)
{
	lua_pushinteger(L, sizeof(IntPtr));
	return 1;
}

IP_M(meta)
{
	{ "__len", IP_N(len) },
	{ "__call", IP_N(call) },
	{ "__unm", IP_N(unm) },

    { NULL, NULL }
};

// NumPtr
// =========================
/*
	-- new NumPtr
	<NumPtr> cef.newNumPtr(<num> value)

	-- set value
	<nil> NumPtr(<num> value)

	-- get value
	<num> NumPtr()

	-- get sizeof
	<int> #NumPtr

	-- get pointer
	<udata> -NumPtr
*/

NP(new)
{
	NumPtr p = calloc(1, sizeof(NumPtr));
	*p = lua_tonumber(L, 1);

	luacef_pushuserdata(L, p, __NumPtr__);
	return 1;
}

NP(call)
{
	NumPtr p = luacef_touserdata(L, 1);

	if (lua_isnoneornil(L, 2))
		lua_pushnumber(L, *p);
	else {
		*p = lua_tonumber(L, 2);
		lua_pushnil(L);
	}

	return 1;
}

NP(unm)
{
	NumPtr p = luacef_touserdata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

NP(len)
{
	lua_pushinteger(L, sizeof(NumPtr));
	return 1;
}

NP_M(meta)
{
	{ "__len", NP_N(len) },
	{ "__call", NP_N(call) },
	{ "__unm", NP_N(unm) },

    { NULL, NULL }
};
// =================================

void luacef_ptr_reg(lua_State *L)
{
	// IntPtr
	luaL_newmetatable(L, __IntPtr__);
	luaL_setfuncs(L, IP_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, IP_N(new));
	lua_setfield(L, -2, "newIntPtr");
	
	// NumPtr
	luaL_newmetatable(L, __NumPtr__);
	luaL_setfuncs(L, NP_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, NP_N(new));
	lua_setfield(L, -2, "newNumPtr");
}

// =================================