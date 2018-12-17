#include "../luacef.h"

#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_life_span_handler_capi.h"

//  _ _ ___                           _             _ _         
// | |_|  _|___    ___ ___ ___ ___   | |_ ___ ___ _| | |___ ___ 
// | | |  _| -_|  |_ -| . | .'|   |  |   | .'|   | . | | -_|  _|
// |_|_|_| |___|  |___|  _|__,|_|_|  |_|_|__,|_|_|___|_|___|_|  
//====================|_|========================================
/*
	<LifeSpanHandler> {
		<int>	
			OnBeforePopup(<Browser>, <Frame>, <str>, <str>, <int>, <int>,
							<PopupFeatures>, <WindowInfo>, <Client>, <BrowserSettings>, <int>)
		<int>
			OnBeforeClose(<Browser>)
		<void>
			OnAfterCreated(<Browser>)
		<void>
			OnBeforeClose(<Browser>)
	}

	<LifeSpanHandler> newLifeSpanHandler(
		<table: LifeSpanHandler>
	)

	<void> LifeSpanHandler:release() -- for created from newLifeSpanHandler()

*/

typedef struct luacef_LifeSpanHandler {

	cef_life_span_handler_t self;

	lua_State *L; // state
	int ref; // table ref

} luacef_LifeSpanHandler;

#define API(fn) \
	LCEF_API(LifeSpanHandler, fn)

#define API_N(fn) \
	LCEF_API_N(LifeSpanHandler, fn)

#define API_M(mname) \
	LCEF_M(LifeSpanHandler, mname)

#define SELF luacef_LifeSpanHandler

/*
	<int> CefLifeSpanHandler:OnBeforePopup(
		<CefBrowser>			browser
		<CefFrame>				frame
		<str>				target_url
		<str>				target_frame_name
		<int>				target_disposition
		<int>				user_gesture
		<CefPopupFeatures>		popupFeatures
		<CefWindowInfo>		windowInfo
		<CefClient>			client
		<CefBrowserSettings>	settings
		<int>				no_javascript_access
	)
*/
int CEF_CALLBACK API_N(OnBeforePopup)(
	SELF*	self,
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
	if (lua_getfield(self->L, -1, __OnBeforePopup)) {

		luacef_pushuserdata(self->L, self, __CefLifeSpanHandler); // self, first arg

		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2

		luacef_pushuserdata(self->L, frame, __CefFrame); //3

		cef_string_utf8_t s1 = { 0 };
		cef_string_to_utf8(target_url->str, target_url->length, &s1);
		lua_pushstring(self->L, s1.str); // 4

		cef_string_utf8_t s2 = { 0 };
		cef_string_to_utf8(target_frame_name->str, target_frame_name->length, &s2);
		lua_pushstring(self->L, s2.str); // 5

		lua_pushinteger(self->L, target_disposition); // 6

		lua_pushinteger(self->L, user_gesture); // 7

		luacef_pushuserdata(self->L, popupFeatures, __popup_features__); // 8

		luacef_pushuserdata(self->L, windowInfo, __CefWindowInfo); // 9
		
		luacef_pushuserdata(self->L, *client, __CefClient); // 10

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
int CEF_CALLBACK API_N(DoClose)(
	SELF*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __DoClose)) {
			
		luacef_pushuserdata(self->L, self, __CefLifeSpanHandler);

		lua_pushlightuserdata(self->L, browser);
		luaL_setmetatable(self->L, __CefBrowser);

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
void CEF_CALLBACK API_N(OnAfterCreated)(
	SELF*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnAfterCreated)) {

		luacef_pushuserdata(self->L, self, __CefLifeSpanHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<void> LifeSpanHandler:OnBeforeClose(
		<Browser>	browser
	)
*/
void CEF_CALLBACK API_N(OnBeforeClose)(
	SELF*	self,
	struct _cef_browser_t*				browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeClose)) {

		luacef_pushuserdata(self->L, self, __CefLifeSpanHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);

		lua_pcall(self->L, 2, 0, -8);
	}
}

//===================================================

API(new)
{
	size_t sz = sizeof(SELF);
	SELF* lsh = luacef_alloc(sz);
	lsh->self.base.size = sz;
	lsh->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		lsh->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnAfterCreated))
			lsh->self.on_after_created = (void*)API_N(OnAfterCreated);

		if (lua_getfield(L, 1, __OnBeforeClose))
			lsh->self.on_before_close = (void*)API_N(OnBeforeClose);

		if (lua_getfield(L, 1, __DoClose))
			lsh->self.do_close = (void*)API_N(DoClose);

		if (lua_getfield(L, 1, __OnBeforePopup))
			lsh->self.on_before_popup = (void*)API_N(OnBeforePopup);
	}
	else {
		lua_newtable(L);
		lsh->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, lsh, __CefLifeSpanHandler);
	return 1;
}

API(index)
{
	SELF* lsh = luacef_touserdata(L, 1);
	if (!lsh || !lsh->L) return 0;

	const char* id = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, lsh->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(id, __OnAfterCreated))
		lua_getfield(L, -1, __OnAfterCreated);

	else if (!strcmp(id, __OnBeforeClose))
		lua_getfield(L, -1, __OnBeforeClose);

	else if (!strcmp(id, __OnBeforePopup))
		lua_getfield(L, -1, __OnBeforePopup);

	else if (!strcmp(id, __DoClose))
		lua_getfield(L, -1, __DoClose);

	else return 0;

	return 1;
}

API(newindex)
{
	SELF* lsh = luacef_touserdata(L, 1);
	if (!lsh || !lsh->L) return 0;

	const char* id = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, lsh->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(id, __OnAfterCreated)) {
		lua_setfield(L, -2, __OnAfterCreated);
		lsh->self.on_after_created = (void*)API_N(OnAfterCreated);
	}

	else if (!strcmp(id, __OnBeforeClose)) {
		lua_setfield(L, -2, __OnBeforeClose);
		lsh->self.on_before_close = (void*)API_N(OnBeforeClose);
	}

	else if (!strcmp(id, __OnBeforePopup)) {
		lua_setfield(L, -2, __OnBeforePopup);
		lsh->self.on_before_popup = (void*)API_N(OnBeforePopup);
	}

	else if (!strcmp(id, __DoClose)) {
		lua_setfield(L, -2, __DoClose);
		lsh->self.do_close = (void*)API_N(DoClose);
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
		LUAREGEND
};

void API_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, __CefLifeSpanHandler);
	luaL_setfuncs(L, API_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, API_N(new));
	lua_setfield(L, -2, "newLifeSpanHandler");
}