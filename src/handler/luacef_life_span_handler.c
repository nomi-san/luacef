#include "luacef_handler.h"
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_life_span_handler_capi.h"

typedef struct luacef_life_span_handler {

	cef_base_t base; // base

	int (CEF_CALLBACK *on_before_popup)(
		struct luacef_life_span_handler*	self,
		struct _cef_browser_t*				browser,
		struct _cef_frame_t*				frame,
		const cef_string_t*					target_url,
		const cef_string_t*					target_frame_name,
		cef_window_open_disposition_t		target_disposition,
		int									user_gesture,
		const struct _cef_popup_features_t* popupFeatures,
		struct _cef_window_info_t*			windowInfo,
		struct _cef_client_t**				client,
		struct _cef_browser_settings_t*		settings,
		int*								no_javascript_access);

	void (CEF_CALLBACK *on_after_created)(
		struct luacef_life_span_handler*	self,
		struct _cef_browser_t*				browser);

	int (CEF_CALLBACK *do_close)(
		struct luacef_life_span_handler*	self,
		struct _cef_browser_t*				browser);

	void (CEF_CALLBACK *on_before_close)(
		struct luacef_life_span_handler*	self,
		struct _cef_browser_t*				browser);

	lua_State *L; // state
	void *self;
	int objectRef; // table ref

} luacef_life_span_handler;

const char	
	*_lsh_on_before_popup	= "OnBeforePopup",
	*_lsh_do_close			= "DoClose",
	*_lsh_on_after_created	= "OnAfterCreated",
	*_lsh_on_before_close	= "OnBeforeClose";

/*
	function <LifeSpanHandler>:OnBeforePopup(<Browser>, <Frame>, <str>, <str>, <int>, <int>, 
		<PopupFeatures>, <WindowInfo>, <Client>, <BrowserSettings>, <int>)
		-- do something
	end -> <int>
*/
int CEF_CALLBACK lsh_on_before_popup(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser,
	struct _cef_frame_t*				frame,
	const cef_string_t*					target_url,
	const cef_string_t*					target_frame_name,
	cef_window_open_disposition_t		target_disposition,
	int									user_gesture,
	const struct _cef_popup_features_t* popupFeatures,
	struct _cef_window_info_t*			windowInfo,
	struct _cef_client_t**				client,
	struct _cef_browser_settings_t*		settings,
	int*								no_javascript_access)
{
	return 0;
}

/*
	function <LifeSpanHandler>:DoClose(<Browser>)
		-- do something
	end -> <int>
*/
int CEF_CALLBACK lsh_do_close(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->objectRef);
	if (lua_getfield(self->L, -1, _lsh_do_close)) {
			
		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __life_span_handler__);

		lua_pushlightuserdata(self->L, browser);
		luaL_setmetatable(self->L, __browser__);

		lua_pcall(self->L, 2, 0, -8);
		return lua_tointeger(self->L, -1);
	}
	return 0;
}

/*
	function <LifeSpanHandler>:OnAfterCreated(<Browser>)
		-- do something
	end
*/
void CEF_CALLBACK lsh_on_after_created(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->objectRef);
	if (lua_getfield(self->L, -1, _lsh_on_after_created)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __life_span_handler__);
		//luacef_pushuserdata(self->L, self, __life_span_handler__);

		//lua_pushlightuserdata(self->L, browser);
		luacef_pushuserdata(self->L, browser, __browser__);

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	function <LifeSpanHandler>:OnBeforeClose(<Browser>)
		-- do something
	end
*/
void CEF_CALLBACK lsh_on_before_close(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->objectRef);
	if (lua_getfield(self->L, -1, _lsh_on_before_close)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __life_span_handler__);
		//luacef_pushuserdata(self->L, self, __life_span_handler__);

		//lua_pushlightuserdata(self->L, browser);
		//luaL_setmetatable(self->L, __life_span_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);

		lua_pcall(self->L, 2, 0, -8);
	}
}

//===================================================

/*
	newLifeSpanHandler {

		<func>(<Browser>, <Frame>, <str>, <str>, <int>, <int>, 
			<PopupFeatures>, <WindowInfo>, <Client>, <BrowserSettings>, <int>) -> <int>
				OnBeforePopup;

		<func>(<Browser>)
				OnAfterCreated;

		<func>(<Browser>) -> <int>
				DoClose;

		<func>(<Browser>)
				OnBeforeClose;

	} -> <LifeSpanHandler>
*/
static int luacef_life_span_handler_new(lua_State* L)
{
	size_t sz = sizeof(luacef_life_span_handler);
	luacef_life_span_handler* lsh = calloc(1, sz);
	lsh->base.size = sz;

	if (lua_istable(L, 1)) {
		lsh->L = L;
		lua_pushvalue(L, 1);
		lsh->objectRef = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, _lsh_on_after_created))
			lsh->on_after_created = lsh_on_after_created;

		if (lua_getfield(L, 1, _lsh_on_before_close))
			lsh->on_before_close = lsh_on_before_close;

		if (lua_getfield(L, 1, _lsh_do_close))
			lsh->do_close = lsh_do_close;

		if (lua_getfield(L, 1, _lsh_on_before_popup))
			lsh->on_before_popup = lsh_on_before_popup;
	}

	lsh->self = luacef_pushuserdata(L, lsh, __life_span_handler__);
	return 1;
}

static int luacef_lifespan_handler_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_life_span_handler*)*ud)->objectRef); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_life_span_handler_index(lua_State* L)
{
	luacef_life_span_handler* lsh = luacef_touserdata(L, 1);
	if (!lsh || !lsh->L) return 0;

	const char* id = lua_tostring(L, 2);

	lua_rawgeti(lsh->L, LUA_REGISTRYINDEX, lsh->objectRef);
	
	if (!strcmp(id, __release__)) // release method
		lua_pushcfunction(L, luacef_lifespan_handler_release);

	else if (!strcmp(id, _lsh_on_after_created))
		lua_getfield(L, -1, _lsh_on_after_created);

	else if (!strcmp(id, _lsh_on_before_close))
		lua_getfield(L, -1, _lsh_on_before_close);

	else if (!strcmp(id, _lsh_on_before_popup))
		lua_getfield(L, -1, _lsh_on_before_popup);

	else if (!strcmp(id, _lsh_do_close))
		lua_getfield(L, -1, _lsh_do_close);

	else return 0;

	return 1;
}

static int luacef_life_span_handler_newindex(lua_State* L)
{
	luacef_life_span_handler* lsh = luacef_touserdata(L, 1);
	if (!lsh || !lsh->L) return 0;

	const char* id = lua_tostring(L, 2);

	lua_rawgeti(lsh->L, LUA_REGISTRYINDEX, lsh->objectRef);
	lua_pushvalue(L, -1);

	if (!strcmp(id, _lsh_on_after_created)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, _lsh_on_after_created);
		lsh->on_after_created = lsh_on_after_created;
	}

	else if (!strcmp(id, _lsh_on_before_close)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, _lsh_on_before_close);
		lsh->on_before_close = lsh_on_before_close;
	}

	else if (!strcmp(id, _lsh_on_before_popup)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, _lsh_on_before_popup);
		lsh->on_before_popup = lsh_on_before_popup;
	}

	else if (!strcmp(id, _lsh_do_close)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, _lsh_do_close);
		lsh->do_close = lsh_do_close;
	}

	else return 0;

	return 1;
}

static const luaL_Reg luacef_life_span_handler_m[] = {
	{ "__gc", luacef_lifespan_handler_release },
	{ "__index", luacef_life_span_handler_index },
	{ "__newindex", luacef_life_span_handler_newindex },
	{ NULL, NULL }
};

void luacef_life_span_handler_reg(lua_State* L)
{
	luaL_newmetatable(L, __life_span_handler__);
	luaL_setfuncs(L, luacef_life_span_handler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_life_span_handler_new);
	lua_setfield(L, -2, "newLifeSpanHandler");
}