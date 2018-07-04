#include "luacef_types.h"

static const char *_b_can_go_back = "CanGoBack";
static const char *_b_can_go_forward = "CanGoForward";
static const char *_b_get_focused_frame = "GetFocusedFrame";
static const char *_b_get_frame = "GetFrame";
static const char *_b_get_frame_byident = "GetFrameByident";
static const char *_b_get_frame_count = "GetFrameCount";
static const char *_b_get_frame_identifiers = "GetFrameIdentifiers";
static const char *_b_get_frame_names = "GetFrameNames";
static const char *_b_get_host = "GetHost";
static const char *_b_get_identifier = "GetIdentifier";
static const char *_b_get_main_frame = "GetMainFrame";
static const char *_b_go_back = "GoBack";
static const char *_b_go_forward = "GoForward";
static const char *_b_has_document = "HasDocument";
static const char *_b_is_loading = "IsLoading";
static const char *_b_is_popup = "IsPopup";
static const char *_b_is_same = "IsSame";
static const char *_b_reload = "Reload";
static const char *_b_reload_ignore_cache = "ReloadIgnoreCache";
static const char *_b_send_process_message = "SendProcessMessage";
static const char *_b_stop_load = "StopLoad";

/*
	Browser {
		<bool>		CanGoBack();
		<bool>		can_go_forward;
		<Frame>		GetFocusedFrame();
		<Frame>		GetFrame(<str>);
		<Frame>		GetFrameByident(<int>);
		<int>		GetFrameCount();
		//<void>		GetFrameIdentifiers;
		//<void>		GetFrameNames(<str>);
		<BrowserHost>
					GetHost();
		<int>		GetIdentifier();
		<Frame>		GetMainFrame();
		<void>		GoBack();
		<void>		GoForward();
		<bool>		HasDocument();
		<bool>		IsLoading();
		<bool>		IsPopup();
		<bool>		IsSame(<Browser>);
		<void>		Reload();
		<void>		ReloadIgnoreCache();
		<int>		SendProcessMessage(<int>, <ProcessMessage>);
		<void>		StopLoad();
*/



static int luaecf_browser_new(lua_State* L)
{
	size_t sz = sizeof(cef_browser_t);
	cef_browser_t *b = calloc(1, sz);
	b->base.size = sz;

	/*
	b->can_go_back;
	b->can_go_forward;
	b->get_focused_frame;
	b->get_frame;
	b->get_frame_byident;
	b->get_frame_count;
	b->get_frame_identifiers;
	b->get_frame_names;
	b->get_host;
	b->get_identifier;
	b->get_main_frame;
	b->go_back;
	b->go_forward;
	b->has_document;
	b->is_loading;
	b->is_popup;
	b->is_same;
	b->reload;
	b->reload_ignore_cache;
	b->send_process_message;
	b->stop_load;
	*/

	luacef_pushuserdata(L, b, __browser__);
	return 1;
}

/*
	<bool> Browser:CanGoBack()
*/
static int 	luacef_browser_can_go_back(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	lua_pushboolean(L, b->can_go_back(b));
	
	return 1;
}

/*
	<bool> Browser:CanGoForward()
*/
static int 	luacef_browser_can_go_forward(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->can_go_forward(b));

	return 1;
}

/*
	<Frame> Browser:GetFocusedFrame()
*/
static int 	luacef_browser_get_focused_frame(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_frame_t *f = b->get_focused_frame(b);

	luacef_pushuserdata(L, f, __frame__);
	return 1;
}

/*
	<Frame> Browser:GetFrame(
		<str> name
	)
*/
static int 	luacef_browser_get_frame(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	const char* cs_name = lua_tostring(L, 2);

	cef_string_t name = { 0 };
	cef_string_from_utf8(cs_name, strlen(cs_name), &name);
	cef_frame_t *f = b->get_frame(b, &name);

	luacef_pushuserdata(L, f, __frame__);
	return 1;
}

/*
	<Frame> Browser:GetFrameByIdentifier(
		<int> id
	)
*/
static int 	luacef_browser_get_frame_byident(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	int id = lua_tointeger(L, 2);

	cef_frame_t *f = b->get_frame_byident(b, id);

	luacef_pushuserdata(L, f, __frame__);
	return 1;
}

/*
	<int> Browser:GetFrameCount()
*/
static int 	luacef_browser_get_frame_count(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	size_t c = b->get_frame_count(b);

	lua_pushinteger(L, c);
	return 1;
}

//
static int 	luacef_browser_get_frame_identifiers(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	//b->get_frame_identifiers(b, )
	// todo

	return 1;
}

/*
	<void> Browser:GetFrameNames(
		<udata> name
	)
*/
static int 	luacef_browser_get_frame_names(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	//b->get_frame_names(b, )
	// todo

	return 1;
}

/*
	<BrowserHost> Browser:GetHost()
*/
static int 	luacef_browser_get_host(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_browser_host_t *host = b->get_host(b);

	luacef_pushuserdata(L, host, __browser_host__);
	return 1;
}

/*
	<int> Browser:GetIdentifier()
*/
static int 	luacef_browser_get_identifier(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	int id = b->get_identifier(b);

	lua_pushinteger(L, id);
	return 1;
}

/*
	<Frame> Browser:GetMainFrame()
*/
static int 	luacef_browser_get_main_frame(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_frame_t *f = b->get_main_frame(b);

	luacef_pushuserdata(L, f, __frame__);
	return 1;
}

/*
	<void> Browser:GoBack()
*/
static int 	luacef_browser_go_back(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->go_back(b);

	return 0;
}

/*
	<void> Browser:GoForward()
*/
static int 	luacef_browser_go_forward(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->go_forward(b);

	return 0;
}

/*
	<bool> Browser:HasDocument()
*/
static int 	luacef_browser_has_document(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	lua_pushboolean(L, b->has_document(b));

	return 1;
}

/*
	<bool> Browser:IsLoading()
*/
static int 	luacef_browser_is_loading(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->is_loading(b));

	return 1;
}

/*
	<bool> Browser:IsPopup()
*/
static int 	luacef_browser_is_popup(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->is_popup(b));

	return 1;
}

/*
	<bool> Browser:IsSame(
		<Browser> that
	)
*/
static int 	luacef_browser_is_same(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	cef_browser_t *b2 = luacef_checkudata(L, 2, __browser__);

	lua_pushboolean(L, b->is_same(b, b2));

	return 1;
}

/*
	<void> Browser:Reload()
*/
static int 	luacef_browser_reload(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->reload(b);

	return 0;
}

/*
	<void> Browser:ReloadIgnoreCache()
*/
static int 	luacef_browser_reload_ignore_cache(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->reload_ignore_cache(b);

	return 0;
}

/*
	<int> Browser:SendProcessMessage(
		<int>				target_process,
		<ProcessMessage>	message
	)
*/
static int 	luacef_browser_send_process_message(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	int p_id = lua_tointeger(L, 2);
	cef_process_message_t *pm = luacef_checkudata(L, 3, __process_message__);

	int ret = b->send_process_message(b, p_id, pm);
	
	lua_pushinteger(L, ret);
	return 0;
}

/*
	<void> Browser:StopLoad()
*/
static int 	luacef_browser_stop_load(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->stop_load(b);

	return 0;
}

static const luaL_Reg luacef_browser_m[] = {
	{ "release", luacef_release },
	{ "CanGoBack", luacef_browser_can_go_back },
	{ "CanGoForward", luacef_browser_can_go_forward },
	{ "GetFocusedFrame", luacef_browser_get_focused_frame },
	{ "GetFrame", luacef_browser_get_frame },
	{ "GetFrameByIdentifier", luacef_browser_get_frame_byident },
	{ "GetFrameCount", luacef_browser_get_frame_count },
	{ "GetFrameIdentifiers", luacef_browser_get_frame_identifiers },
	{ "GetFrameNames", luacef_browser_get_frame_names },
	{ "GetHost", luacef_browser_get_host },
	{ "GetIdentifier", luacef_browser_get_identifier },
	{ "GetMainFrame", luacef_browser_get_main_frame },
	{ "GoBack", luacef_browser_go_back },
	{ "GoForward", luacef_browser_go_forward },
	{ "HasDocument", luacef_browser_has_document },
	{ "IsLoading", luacef_browser_is_loading },
	{ "IsPopup", luacef_browser_is_popup },
	{ "IsSame", luacef_browser_is_same },
	{ "Reload", luacef_browser_reload },
	{ "ReloadIgnoreCache", luacef_browser_reload_ignore_cache },
	{ "SendProcessMessage", luacef_browser_send_process_message },
	{ "StopLoad", luacef_browser_stop_load },
	{ NULL, NULL }
};

void luacef_browser_reg(lua_State* L)
{
	luaL_newmetatable(L, __browser__);
	luaL_setfuncs(L, luacef_browser_m, 0);
	lua_setfield(L, -1, __index__);
}