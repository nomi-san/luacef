#include "../luacef.h"

#include "include/capi/cef_base_capi.h"

//          _ _ _           _   
//  ___ ___| | | |_ ___ ___| |_ 
// |  _| .'| | | . | .'|  _| '_|
// |___|__,|_|_|___|__,|___|_,_|
//===============================

// callback

static int luacef_Callback_Continue(lua_State *L)
{
	cef_callback_t *p = luacef_touserdata(L, 1);

	p->cont(p);

	return 0;
}

static int luacef_Callback_Cancel(lua_State *L)
{
	cef_callback_t *p = luacef_touserdata(L, 1);

	p->cancel(p);

	return 0;
}

static int luacef_Callback_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(cef_callback_t));
	return 1;
}

static const luaL_Reg luacef_Callback_m[] = {
	{ "Continue", luacef_Callback_Continue },
	{ "Cancel", luacef_Callback_Cancel },
	{ "__len", luacef_Callback_len },
	{ NULL, NULL }
};

// completion_callback =======================================

typedef struct luacef_CompletionCallback {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_complete)(struct luacef_CompletionCallback* self);

	lua_State *L;
	int ref;

} luacef_CompletionCallback;

void CEF_CALLBACK luacef_CompletionCallback_OnComplete(
	struct luacef_CompletionCallback* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnComplete)) {

		luacef_pushuserdata(self->L, self, __completion_callback__);

		lua_pcall(self->L, 1, 0, 0);
	}
}

static int luacef_CompletionCallback_new(lua_State *L)
{
	size_t sz = sizeof(luacef_CompletionCallback);
	luacef_CompletionCallback *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnComplete))
			p->on_complete = !lua_isfunction(L, -1) ? NULL : luacef_CompletionCallback_OnComplete;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __completion_callback__);
	return 1;
}

static int luacef_CompletionCallback_release(lua_State *L)
{

	return 0;
}

static int luacef_CompletionCallback_index(lua_State *L)
{
	luacef_CompletionCallback *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_CompletionCallback_release);

	else if (!strcmp(i, __OnComplete))
		lua_getfield(L, -1, __OnComplete);

	else return 0;

	return 1;
}

static int luacef_CompletionCallback_newindex(lua_State *L)
{
	luacef_CompletionCallback *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnComplete)) {
		lua_setfield(L, -2, __OnComplete);
		p->on_complete = luacef_CompletionCallback_OnComplete;
	}

	return 0;
}

static int luacef_CompletionCallback_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(luacef_CompletionCallback));
	return 1;
}

static const luaL_Reg luacef_CompletionCallback_m[] = {
	{ "__index", luacef_CompletionCallback_index },
	{ "__newindex", luacef_CompletionCallback_newindex },
	{ "__len", luacef_CompletionCallback_len },
	{ "__eq", luacef_eq },
	{ NULL, NULL }
};

// register =================================================

void luacef_CompletionCallback_reg(lua_State *L)
{
	luaL_newmetatable(L, __callback__);
	luaL_setfuncs(L, luacef_Callback_m, 0);
	lua_setfield(L, -1, __index__);

	luaL_newmetatable(L, __completion_callback__);
	luaL_setfuncs(L, luacef_CompletionCallback_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_CompletionCallback_new);
	lua_setfield(L, -2, "newCompletionCallback");
}