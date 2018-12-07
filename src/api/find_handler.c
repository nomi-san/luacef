#include "../luacef.h"


typedef struct luacef_find_handler {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_find_result)(struct luacef_find_handler* self,
		struct _cef_browser_t* browser,
		int identifier,
		int count,
		const cef_rect_t* selectionRect,
		int activeMatchOrdinal,
		int finalUpdate);

	lua_State *L;
	int ref;

} luacef_find_handler;

/*
	<void> OnFindResult(
		<Browser>	browser,
		<int>		identifier,
		<int>		count,
		<Rect>		selectionRect,
		<int>		activeMatchOrdinal,
		<int>		finalUpdate
	)
*/
void CEF_CALLBACK fh_on_find_result(struct luacef_find_handler* self,
	struct _cef_browser_t* browser,
	int identifier,
	int count,
	const cef_rect_t* selectionRect,
	int activeMatchOrdinal,
	int finalUpdate)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_find_result)) {

		luacef_pushuserdata(self->L, self, __find_handler__); // self

		luacef_pushuserdata(self->L, browser, __browser__); // 2

		lua_pushinteger(self->L, identifier); // 3

		lua_pushinteger(self->L, identifier); // 4

		luacef_pushuserdata(self->L, selectionRect, __rect__); // 5

		lua_pushinteger(self->L, activeMatchOrdinal); // 6

		lua_pushinteger(self->L, finalUpdate); // 7

		lua_pcall(self->L, 7, 0, 8); // call, no return
	}
}

/*
	<FindHandler> newFindHandler
	{
		<void>	
			OnFindResult(self, <Browser>, <int>, <int>, <Rect>, <int>, <int>)
	}
*/
static int luacef_find_handler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_find_handler);
	luacef_find_handler *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __on_find_result))
			p->on_find_result = fh_on_find_result;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __find_handler__);
	return 1;
}

static int luacef_find_handler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_find_handler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_find_handler_index(lua_State *L)
{
	luacef_find_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_find_handler_release);

	else if (!strcmp(i, __on_find_result))
		lua_getfield(L, -1, __on_find_result);

	else return 0;

	return 1;
}

static int luacef_find_handler_newindex(lua_State *L)
{
	luacef_find_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __on_find_result)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_find_result);
		p->on_find_result = fh_on_find_result;
	}
		
	return 0;
}

static const luaL_Reg luacef_find_handler_m[] = {
	{ "__index", luacef_find_handler_index },
	{ "__newindex", luacef_find_handler_newindex },
	{ NULL, NULL}
};

void luacef_find_handler_reg(lua_State *L)
{
	luaL_newmetatable(L, __find_handler__);
	luaL_setfuncs(L, luacef_find_handler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_find_handler_new);
	lua_setfield(L, -2, "newFindHandler");
}