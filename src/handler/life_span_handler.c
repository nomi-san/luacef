#include "../luacef.h"
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
	int ref; // table ref

} luacef_life_span_handler;

/*
	<int> LifeSpanHandler:OnBeforePopup(
		<Browser>			browser
		<Frame>				frame
		<str>				target_url
		<str>				target_frame_name
		<int>				target_disposition
		<int>				user_gesture
		<PopupFeatures>		popupFeatures
		<WindowInfo>		windowInfo
		<Client>			client
		<BrowserSettings>	settings
		<int>				no_javascript_access
	)
*/
int CEF_CALLBACK life_span_handler_on_before_popup(
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
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_before_popup)) {

		luacef_pushuserdata(self->L, self, __life_span_handler__); // self, first arg

		luacef_pushuserdata(self->L, browser, __browser__); // 2

		luacef_pushuserdata(self->L, frame, __frame__); //3

		cef_string_utf8_t s1 = { 0 };
		cef_string_to_utf8(target_url->str, target_url->length, &s1);
		lua_pushstring(self->L, s1.str); // 4

		cef_string_utf8_t s2 = { 0 };
		cef_string_to_utf8(target_frame_name->str, target_frame_name->length, &s2);
		lua_pushstring(self->L, s2.str); // 5

		lua_pushinteger(self->L, target_disposition); // 6

		lua_pushinteger(self->L, user_gesture); // 7

		luacef_pushuserdata(self->L, popupFeatures, __popup_features__); // 8

		luacef_pushuserdata(self->L, windowInfo, __window_info__); // 9
		
		luacef_pushuserdata(self->L, *client, __client__); // 10

		luacef_pushuserdata(self->L, settings, __browser_settings__); // 11
		
		lua_pushinteger(self->L, *no_javascript_access); // 12

		lua_pcall(self->L, 12, 1, -8);
		return lua_tointeger(self->L, -1);
	}
	return 0;
}

/*
	<int> LifeSpanHandler:OnBeforeClose(
		<Browser>	browser
	)
*/
int CEF_CALLBACK life_span_handler_do_close(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __do_close)) {
			
		luacef_pushuserdata(self->L, self, __life_span_handler__);

		lua_pushlightuserdata(self->L, browser);
		luaL_setmetatable(self->L, __browser__);

		lua_pcall(self->L, 2, 1, -8);
		return lua_tointeger(self->L, -1);
	}
	return 0;
}

/*
	<void> LifeSpanHandler:OnAfterCreated(
		<Browser>	browser
	)
*/
void CEF_CALLBACK life_span_handler_on_after_created(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_after_created)) {

		luacef_pushuserdata(self->L, self, __life_span_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<void> LifeSpanHandler:OnBeforeClose(
		<Browser>	browser
	)
*/
void CEF_CALLBACK life_span_handler_on_before_close(
	struct luacef_life_span_handler*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_before_close)) {

		luacef_pushuserdata(self->L, self, __life_span_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);

		lua_pcall(self->L, 2, 0, -8);
	}
}

//===================================================

/*
	<LifeSpanHandler> newLifeSpanHandler 
	{
		<int>	OnBeforePopup(<Browser>, <Frame>, <str>, <str>, <int>, <int>,
							<PopupFeatures>, <WindowInfo>, <Client>, <BrowserSettings>, <int>)

		<int>	OnBeforeClose(<Browser>)

		<void>	OnAfterCreated(<Browser>)

		<void>	OnBeforeClose(<Browser>)
	}
*/
static int luacef_life_span_handler_new(lua_State* L)
{
	size_t sz = sizeof(luacef_life_span_handler);
	luacef_life_span_handler* lsh = luacef_alloc(sz);
	lsh->base.size = sz;
	lsh->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		lsh->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __on_after_created))
			lsh->on_after_created = life_span_handler_on_after_created;

		if (lua_getfield(L, 1, __on_before_close))
			lsh->on_before_close = life_span_handler_on_before_close;

		if (lua_getfield(L, 1, __do_close))
			lsh->do_close = life_span_handler_do_close;

		if (lua_getfield(L, 1, __on_before_popup))
			lsh->on_before_popup = life_span_handler_on_before_popup;
	}
	else {
		lua_newtable(L);
		lsh->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, lsh, __life_span_handler__);
	return 1;
}

static int luacef_lifespan_handler_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_life_span_handler*)*ud)->ref); //
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

	lua_rawgeti(L, LUA_REGISTRYINDEX, lsh->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(id, __release__)) // release method
		lua_pushcfunction(L, luacef_lifespan_handler_release);

	else if (!strcmp(id, __on_after_created))
		lua_getfield(L, -1, __on_after_created);

	else if (!strcmp(id, __on_before_close))
		lua_getfield(L, -1, __on_before_close);

	else if (!strcmp(id, __on_before_popup))
		lua_getfield(L, -1, __on_before_popup);

	else if (!strcmp(id, __do_close))
		lua_getfield(L, -1, __do_close);

	else return 0;

	return 1;
}

static int luacef_life_span_handler_newindex(lua_State* L)
{
	luacef_life_span_handler* lsh = luacef_touserdata(L, 1);
	if (!lsh || !lsh->L) return 0;

	const char* id = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, lsh->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(id, __on_after_created)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_after_created);
		lsh->on_after_created = life_span_handler_on_after_created;
	}

	else if (!strcmp(id, __on_before_close)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_before_close);
		lsh->on_before_close = life_span_handler_on_before_close;
	}

	else if (!strcmp(id, __on_before_popup)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_before_popup);
		lsh->on_before_popup = life_span_handler_on_before_popup;
	}

	else if (!strcmp(id, __do_close)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __do_close);
		lsh->do_close = life_span_handler_do_close;
	}

	else return 0;

	return 1;
}

static const luaL_Reg luacef_life_span_handler_m[] = {
	//{ "__gc", luacef_lifespan_handler_release },
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