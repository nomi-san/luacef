#include "../luacef.h"

//  _           _    _             _ _         
// | |___ ___ _| |  | |_ ___ ___ _| | |___ ___ 
// | | . | .'| . |  |   | .'|   | . | | -_|  _|
// |_|___|__,|___|  |_|_|__,|_|_|___|_|___|_|  
//==============================================
/*
	<LoadHandler> {
		<void>
			OnLoadingStateChange(self, <Browser>, <bool>, <bool>, <bool>);
		<void>
			OnLoadStart(self, <Broser>, <Frame>, <int>);
		<void>
			OnLoadEnd(self, <Broser>, <Frame>, <int>);
		<void>
			OnLoadError(self, <Broser>, <Frame>, <int>, <str>, <str>);
	}

	<LoadHandler> newLoadHandler(
		<table: LoadHandler>
	)

	<void> LoadHandler:release() -- for created from newLoadHandler()

*/

// implement

typedef struct luacef_load_handler {

	cef_base_t base;

	void (CEF_CALLBACK *on_loading_state_change)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		int							isLoading,
		int							canGoBack,
		int							canGoForward);

	void (CEF_CALLBACK *on_load_start)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		struct _cef_frame_t*		frame,
		cef_transition_type_t		transition_type);

	void (CEF_CALLBACK *on_load_end)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		struct _cef_frame_t*		frame,
		int							httpStatusCode);

	void (CEF_CALLBACK *on_load_error)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		struct _cef_frame_t*		frame,
		cef_errorcode_t				errorCode,
		const cef_string_t*			errorText,
		const cef_string_t*			failedUrl);

	lua_State* L;
	int ref;

} luacef_load_handler;

static const char  
	*__on_loading_state_change	= "OnLoadingStateChange",
	*__on_load_start			= "OnLoadStart",
	*__on_load_end				= "OnLoadEnd",
	*__on_load_error			= "OnLoadError";

void CEF_CALLBACK lh_on_loading_state_change(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	int							isLoading,
	int							canGoBack,
	int							canGoForward)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_loading_state_change)) {

		luacef_pushuserdata(self->L, self, __load_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		lua_pushboolean(self->L, isLoading);
		lua_pushboolean(self->L, canGoBack);
		lua_pushboolean(self->L, canGoForward);

		lua_pcall(self->L, 5, 0, 8);
	}
}

void CEF_CALLBACK lh_on_load_start(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	struct _cef_frame_t*		frame,
	cef_transition_type_t		transition_type)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_load_start)) {

		luacef_pushuserdata(self->L, self, __load_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		lua_pushinteger(self->L, transition_type);

		lua_pcall(self->L, 4, 0, 8);
	}
}

void CEF_CALLBACK lh_on_load_end(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	struct _cef_frame_t*		frame,
	int							httpStatusCode)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_load_end)) {

		luacef_pushuserdata(self->L, self, __load_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		lua_pushinteger(self->L, httpStatusCode);

		lua_pcall(self->L, 4, 0, 8);
	}
}

void CEF_CALLBACK lh_on_load_error(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	struct _cef_frame_t*		frame,
	cef_errorcode_t				errorCode,
	const cef_string_t*			errorText,
	const cef_string_t*			failedUrl)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_load_error)) {

		luacef_pushuserdata(self->L, self, __load_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		lua_pushinteger(self->L, errorCode);
		luacef_pushstring(self->L, errorText);
		luacef_pushstring(self->L, failedUrl);

		lua_pcall(self->L, 6, 0, 8);
	}
}

static int luacef_LoadHandler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_load_handler);
	luacef_load_handler *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __on_loading_state_change))
			p->on_loading_state_change = !lua_isfunction(L, -1) ? NULL : lh_on_loading_state_change;

		if (lua_getfield(L, 1, __on_load_start))
			p->on_load_start = !lua_isfunction(L, -1) ? NULL : lh_on_load_start;

		if (lua_getfield(L, 1, __on_load_end))
			p->on_load_end = !lua_isfunction(L, -1) ? NULL : lh_on_load_end;

		if (lua_getfield(L, 1, __on_load_error))
			p->on_load_error = !lua_isfunction(L, -1) ? NULL : lh_on_load_error;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __load_handler__);
	return 1;
}

static int luacef_LoadHandler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_load_handler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_LoadHandler_index(lua_State *L)
{

	luacef_load_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_LoadHandler_release);

	else if (!strcmp(i, __on_loading_state_change))
		lua_getfield(L, -1, __on_loading_state_change);

	else if (!strcmp(i, __on_load_start))
		lua_getfield(L, -1, __on_load_start);

	else if (!strcmp(i, __on_load_end))
		lua_getfield(L, -1, __on_load_end);

	else if (!strcmp(i, __on_load_error))
		lua_getfield(L, -1, __on_load_error);

	else return 0;

	return 1;
}

static int luacef_LoadHandler_newindex(lua_State *L)
{
	luacef_load_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __on_loading_state_change)) {
		lua_setfield(L, -2, __on_loading_state_change);
		p->on_loading_state_change = !lua_isfunction(L, 3) ? NULL : lh_on_loading_state_change;
	}

	else if (!strcmp(i, __on_load_start)) {
		lua_setfield(L, -2, __on_load_start);
		p->on_load_start = !lua_isfunction(L, 3) ? NULL : lh_on_load_start;
	}

	else if (!strcmp(i, __on_load_end)) {
		lua_setfield(L, -2, __on_load_end);
		p->on_load_end = !lua_isfunction(L, 3) ? NULL : lh_on_load_end;
	}

	else if (!strcmp(i, __on_load_error)) {
		lua_setfield(L, -2, __on_load_error);
		p->on_load_error = !lua_isfunction(L, 3) ? NULL : lh_on_load_error;
	}

	return 0;
}

static const luaL_Reg luacef_LoadHandler_m[] = {
	{ "__index", luacef_LoadHandler_index },
	{ "__newindex", luacef_LoadHandler_newindex },
	{ NULL, NULL }
};

// ===================================================

void luacef_LoadHandler_reg(lua_State *L)
{
	luaL_newmetatable(L, __load_handler__);
	luaL_setfuncs(L, luacef_LoadHandler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_LoadHandler_new);
	lua_setfield(L, -2, "newLoadHandler");
}