#include "../luacef.h"
#include "include/capi/cef_find_handler_capi.h"

typedef struct luacef_FindHandler {

	cef_find_handler_t self;

	lua_State *L;
	int ref;

} luacef_FindHandler;

#define API(fn) \
	LCEF_API(FindHandler, fn)

#define API_N(fn) \
	LCEF_API_N(FindHandler, fn)

#define API_M(mname) \
	LCEF_M(FindHandler, mname)

#define SELF luacef_FindHandler

/*
	<void> FindHandler:OnFindResult(
		<CefBrowser>	browser,
		<int>		identifier,
		<int>		count,
		<Rect>		selectionRect,
		<int>		activeMatchOrdinal,
		<int>		finalUpdate
	)
*/
void CEF_CALLBACK API_N(OnFindResult)(SELF* self,
	struct _cef_browser_t* browser,
	int identifier,
	int count,
	const cef_rect_t* selectionRect,
	int activeMatchOrdinal,
	int finalUpdate)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnFindResult)) {

		luacef_pushuserdata(self->L, self, __CefFindHandler); // self

		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2

		lua_pushinteger(self->L, identifier); // 3

		lua_pushinteger(self->L, identifier); // 4

		luacef_pushuserdata(self->L, selectionRect, __rect__); // 5

		lua_pushinteger(self->L, activeMatchOrdinal); // 6

		lua_pushinteger(self->L, finalUpdate); // 7

		lua_pcall(self->L, 7, 0, 8); // call, no return
	}
}

/*
	<CefFindHandler> newFindHandler {
		OnFindResult = <void> func(self, <CefBrowser>, <int>, <int>, <Rect>, <int>, <int>)
	}
*/
API(new)
{
	size_t sz = sizeof(SELF);
	SELF *p = luacef_alloc(sz);
	p->self.base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnFindResult))
			p->self.on_find_result = (void*)API_N(OnFindResult);
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __CefFindHandler);
	return 1;
}

API(index)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __OnFindResult))
		lua_getfield(L, -1, __OnFindResult);

	else return 0;

	return 1;
}

API(newindex)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnFindResult)) {
		lua_setfield(L, -2, __OnFindResult);
		p->self.on_find_result = (void*)API_N(OnFindResult);
	}
		
	return 0;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

API_M(meta)
{
	{ "__len", API_N(len) },
	{ "__unm", API_N(unm) },
	{ "__index", API_N(index) },
	{ "__newindex", API_N(newindex) },
	{ NULL, NULL }
};

void API_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, __CefFindHandler);
	luaL_setfuncs(L, API_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, API_N(new));
	lua_setfield(L, -2, "newFindHandler");
}