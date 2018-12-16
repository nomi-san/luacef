#include "../luacef.h"

//  _                             
// | |_ ___ ___ _ _ _ ___ ___ ___ 
// | . |  _| . | | | |_ -| -_|  _|
// |___|_| |___|_____|___|___|_|  
//=================================                               

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

#define SELF luacef_Browser

typedef cef_browser_t SELF;

#define API(fn) \
	LCEF_API(Browser, fn)

#define API_N(fn) \
	LCEF_API_N(Browser, fn)

#define API_M(mname) \
	LCEF_M(Browser, mname)

/*
	<BrowserHost> Browser:GetHost()
*/
static int 	luacef_Browser_GetHost(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_browser_host_t *host = b->get_host(b);

	luacef_pushuserdata(L, host, __CefBrowserHost);
	return 1;
}

/*
	<bool> Browser:CanGoBack()
*/
static int 	luacef_Browser_CanGoBack(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	lua_pushboolean(L, b->can_go_back(b));

	return 1;
}

/*
	<void> Browser:GoBack()
*/
static int 	luacef_Browser_GoBack(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->go_back(b);

	return 0;
}

/*
	<bool> Browser:CanGoForward()
*/
static int 	luacef_Browser_CanGoForward(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->can_go_forward(b));

	return 1;
}

/*
	<void> Browser:GoForward()
*/
static int 	luacef_Browser_GoForward(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->go_forward(b);

	return 0;
}

/*
	<bool> Browser:IsLoading()
*/
static int 	luacef_Browser_IsLoading(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->is_loading(b));

	return 1;
}

/*
	<void> Browser:Reload()
*/
static int 	luacef_Browser_Reload(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->reload(b);

	return 0;
}

/*
	<void> Browser:ReloadIgnoreCache()
*/
static int 	luacef_Browser_ReloadIgnoreCache(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->reload_ignore_cache(b);

	return 0;
}

/*
	<void> Browser:StopLoad()
*/
static int 	luacef_Browser_StopLoad(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->stop_load(b);

	return 0;
}

/*
	<int> Browser:GetIdentifier()
*/
static int 	luacef_Browser_GetIdentifier(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	int id = b->get_identifier(b);

	lua_pushinteger(L, id);
	return 1;
}

/*
	<bool> Browser:IsSame(
		<Browser> that
	)
*/
static int 	luacef_Browser_IsSame(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	cef_browser_t *b2 = luacef_checkudata(L, 2, __CefBrowser);

	lua_pushboolean(L, b->is_same(b, b2));

	return 1;
}

/*
	<bool> Browser:IsPopup()
*/
static int 	luacef_Browser_IsPopup(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->is_popup(b));

	return 1;
}

/*
	<bool> Browser:HasDocument()
*/
static int 	luacef_Browser_HasDocument(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	lua_pushboolean(L, b->has_document(b));

	return 1;
}

/*
	<Frame> Browser:GetMainFrame()
*/
static int 	luacef_Browser_GetMainFrame(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_frame_t *f = b->get_main_frame(b);

	luacef_pushuserdata(L, f, __CefFrame);
	return 1;
}

/*
	<Frame> Browser:GetFocusedFrame()
*/
static int 	luacef_Browser_GetFocusedFrame(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_frame_t *f = b->get_focused_frame(b);

	luacef_pushuserdata(L, f, __CefFrame);
	return 1;
}

/*
	<Frame> Browser:GetFrame(
		<str> name
	)

	<Frame> Browser:GetFrame(
		<int> identifier
	)
*/
static int 	luacef_Browser_GetFrame(lua_State* L)
{
	cef_browser_t *p = luacef_touserdata(L, 1);

	cef_frame_t *r = NULL;

	if (lua_isstring(L, 1)) {
		const cef_string_t name = luacef_tostring(L, 1);

		r = p->get_frame(p, &name);
	}
	else if (lua_isinteger(L, 1)) {
		int id = lua_tointeger(L, 1);

		r = p->get_frame_byident(p, id);
	}

	luacef_pushuserdata(L, r, __CefFrame);
	return 1;
}

/*
	<int> Browser:GetFrameCount()
*/
static int 	luacef_Browser_GetFrameCount(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	size_t c = b->get_frame_count(b);

	lua_pushinteger(L, c);
	return 1;
}

/*
	<void> Browser:GetFrameIdentifiers(
		<int*> identifiers
	)
*/
static int 	luacef_Browser_GetFrameIdentifiers(lua_State* L)
{
	cef_browser_t *p = luacef_touserdata(L, 1);
	luacef_int *id = luacef_checkudata(L, 2, __IntPtr__);

	size_t c = p->get_frame_count(p);
	p->get_frame_identifiers(
		p,
		&c,
		id
	);

	return 0;
}

/*
	<void> Browser:GetFrameNames(
		<udata> name
	)
*/
static int 	luacef_Browser_GetFrameNames(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	

	//b->get_frame_names(b, )
	// todo

	return 1;
}

/*
	<int> Browser:SendProcessMessage(
		<int>				target_process,
		<ProcessMessage>	message
	)
*/
static int 	luacef_Browser_SendProcessMessage(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	int p_id = lua_tointeger(L, 2);
	cef_process_message_t *pm = luacef_checkudata(L, 3, __CefProcessMessage);

	int ret = b->send_process_message(b, p_id, pm);
	
	lua_pushinteger(L, ret);
	return 1;
}

static int luacef_Browser_unm(lua_State *L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	lua_pushlightuserdata(L, b);
	return 1;
}

static const luaL_Reg luacef_Browser_m[] = {
	{ "__unm", luacef_Browser_unm},
	{ "CanGoBack", luacef_Browser_CanGoBack },
	{ "CanGoForward", luacef_Browser_CanGoForward },
	{ "GetFocusedFrame", luacef_Browser_GetFocusedFrame },
	{ "GetFrame", luacef_Browser_GetFrame },
	{ "GetFrameCount", luacef_Browser_GetFrameCount },
	{ "GetFrameIdentifiers", luacef_Browser_GetFrameIdentifiers },
	{ "GetFrameNames", luacef_Browser_GetFrameNames },
	{ "GetHost", luacef_Browser_GetHost },
	{ "GetIdentifier", luacef_Browser_GetIdentifier },
	{ "GetMainFrame", luacef_Browser_GetMainFrame },
	{ "GoBack", luacef_Browser_GoBack },
	{ "GoForward", luacef_Browser_GoForward },
	{ "HasDocument", luacef_Browser_HasDocument },
	{ "IsLoading", luacef_Browser_IsLoading },
	{ "IsPopup", luacef_Browser_IsPopup },
	{ "IsSame", luacef_Browser_IsSame },
	{ "Reload", luacef_Browser_Reload },
	{ "ReloadIgnoreCache", luacef_Browser_ReloadIgnoreCache },
	{ "SendProcessMessage", luacef_Browser_SendProcessMessage },
	{ "StopLoad", luacef_Browser_StopLoad },
	{ NULL, NULL }
};

#undef SELF
#undef API
#undef API_N
#undef API_M

// BrowserHost =========================
// ==================================================

#define SELF luacef_BrowserHost

typedef cef_browser_host_t SELF;

#define API(fn) \
	LCEF_API(BrowserHost, fn)

#define API_N(fn) \
	LCEF_API_N(BrowserHost, fn)

#define API_M(mname) \
	LCEF_M(BrowserHost, mname)

/*
	<void> BrowserHost:AddWordToDictionary(
		<str> word
	)
*/
API(AddWordToDictionary)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	const char* cs = lua_tostring(L, 2);

	cef_string_t word = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &word);
	h->add_word_to_dictionary(h, &word);

	return 0;
}

/*
	<void> BrowserHost:CloseBrowser(
		<int> force_close
	)
*/
API(CloseBrowser)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int force_close = lua_tointeger(L, 2);

	h->close_browser(h, force_close);

	return 0;
}

/*
	<void> BrowserHost:CloseDevTools()
*/
API(CloseDevTools)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->close_dev_tools(h);

	return 0;
}

/*
	<> BrowserHost:DownloadImage()
*/
API(DownloadImage)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo

	//h->download_image(h, );

	return 0;
}

/*
	<> BrowserHost:DragSourceEndedAt()
*/
API(DragSourceEndedAt)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo
	//h->drag_source_ended_at()

	return 0;
}

/*
	<> BrowserHost:DragSourceSystemDragEnded()
*/
API(DragSourceSystemDragEnded)
{

	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDragEnter()
*/
API(DragTargetDragEnter)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDragLeave()
*/
API(DragTargetDragLeave)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDragOver()
*/
API(DragTargetDragOver)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDrop()
*/
API(DragTargetDrop)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:Find()
*/
API(Find)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo
	//h->find(h, )

	return 0;
}

/*
	<Browser> BrowserHost:GetBrowser()
*/
API(GetBrowser)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_browser_t *b = h->get_browser(h);

	luacef_pushuserdata(L, b, __CefBrowser);
	return 1;
}

/*
	<Client> BrowserHost:GetClient()
*/
API(GetClient)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_client_t *c = h->get_client(h);

	luacef_pushuserdata(L, c, __CefClient);
	return 1;
}

/*
	<void> Browser:GetNavigationEntries()
*/
API(GetNavigationEntries)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo
	//h->get_navigation_entries(j. )

	return 0;
}

/*
	<void> Browser:GetNSTextInputContext()
*/
API(GetNSTextInputContext)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	//h->get_nstext_input_context(h);

	return 0;
}

/*
	<udata> Browser:GetOpenerWindowHandle()
	-> HWND
*/
API(GetOpenerWindowHandle)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_window_handle_t handle = h->get_opener_window_handle(h);

	lua_pushlightuserdata(L, handle);
	return 1;
}

/*
	<RequestContext> Browser:GetRequestContext()
*/
API(GetRequestContext)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_request_context_t *rq = h->get_request_context(h);

	luacef_pushuserdata(L, rq, __CefRequestContext);
	return 1;
}

/*
	<int> Browser:GetWindowlessFrameRate()
*/
API(GetWindowlessFrameRate)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	int frame_rate = h->get_windowless_frame_rate(h);

	lua_pushinteger(L, frame_rate);
	return 1;
}

/*
	<udata> BrowserHost:GetWindowHandle()
	-> HWND
*/
API(GetWindowHandle)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_window_handle_t handle = h->get_window_handle(h);

	lua_pushlightuserdata(L, handle);
	return 1;
}

/*
	<num> BrowserHost:GetZoomLevel()
*/
API(GetZoomLevel)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	double zl = h->get_zoom_level(h);

	lua_pushnumber(L, zl);
	return 1;
}

/*
	<> BrowserHost:HandleKeyEventAfterTextInputClient()
*/
API(HandleKeyEventAfterTextInputClient)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:HandleKeyEventBeforeTextInputClient()
*/
API(HandleKeyEventBeforeTextInputClient)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	//MSG *msg = 
	// #ifdef WIN32 //


	//h->handle_key_event_before_text_input_client(h, )
	// todo
	return 0;
}

/*
	<bool> BrowserHost:HasDevTools()
*/
API(HasDevTools)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->has_dev_tools(h));
	return 1;
}

/*
	<bool> BrowserHost:HasView()
*/
API(HasView)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->has_view(h));
	return 1;
}

/*
	<void> BrowserHost:Invalidate(
		<int>	paint_element_type
	)
*/
API(Invalidate)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int type = lua_tointeger(L, 2);

	h->invalidate(h, type);

	return 0;
}

/*
	<bool> BrowserHost:IsMouseCursorChangeDisabled()
*/
API(IsMouseCursorChangeDisabled)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->is_mouse_cursor_change_disabled(h));
	return 1;
}

/*
	<bool> BrowserHost:IsWindowRenderingDisabled()
*/
API(IsWindowRenderingDisabled)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->is_window_rendering_disabled(h));
	return 1;
}

/*
	<void> BrowserHost:NotifyMoveOrResizeStarted()
*/
API(NotifyMoveOrResizeStarted)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->notify_move_or_resize_started(h);

	return 0;
}

/*
	<void> BrowserHost:NotifyScreenInfoChanged()
*/
API(NotifyScreenInfoChanged)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->notify_screen_info_changed(h);

	return 0;
}

/*
	<void> BrowserHost:Print()
*/
API(Print)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->print(h);

	return 0;
}

/*
	<void> BrowserHost:PrintToPDF(
		<str>				path,
		<PDFPrintSettings>	settings,
		<PDFPrintCallback>	callback
	)
*/
API(PrintToPDF)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	const char *cs_path = lua_tostring(L, 2);
	cef_pdf_print_settings_t *pdf_s = NULL;
	cef_pdf_print_callback_t *pdf_cb = NULL;

	cef_string_t path = { 0 };
	cef_string_from_utf8(cs_path, strlen(cs_path), &path);

	h->print_to_pdf(h, &path, pdf_s, pdf_cb);

	return 0;
}

/*
	<void> BrowserHost:ReplaceMisspelling(
		<str> word
	)
*/
API(ReplaceMisspelling)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	const char *cs = lua_tostring(L, 2);

	cef_string_t word = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &word);
	h->replace_misspelling(h, &word);

	return 0;
}

/*
	<void> BrowserHost:RunFileDialog()
*/
API(RunFileDialog)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	//h->run_file_dialog()
	// todo

	return 0;
}

/*
	<void> BrowserHost:SendCaptureLostEvent()
*/
API(SendCaptureLostEvent)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->send_capture_lost_event(h);

	return 0;
}

/*
	<void> BrowserHost:SendFocusEvent(
		<int> set_foccus
	)
*/
API(SendFocusEvent)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int setfocus = lua_tointeger(L, 2);

	h->send_focus_event(h, setfocus);

	return 0;
}

/*
	<void> BrowserHost:SendKeyEvent(
		<KeyEvent>	event
	)
*/
API(SendKeyEvent)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	cef_key_event_t *ke = luacef_checkudata(L, 2, __key_event__);

	h->send_key_event(h, ke);

	return 0;
}

/*
	<void> BrowserHost:SendMouseClickEvent(
		<MouseEvent>	event,
		<int>			button_type,
		<int>			mouse_up
		<int>			click_count
	)
*/
API(SendMouseClickEvent)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	cef_mouse_event_t *me = luacef_checkudata(L, 2, __mouse_event__);
	int type = lua_tointeger(L, 3);
	int up = lua_tointeger(L, 4);
	int count = lua_tointeger(L, 5);

	h->send_mouse_click_event(h, me, type, up, count);

	return 0;
}

/*
	<void> BrowserHost:SendMouseMoveEvent(
		<MouseEvent>	event,
		<int>			mouse_leave,
	)
*/
API(SendMouseMoveEvent)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	cef_mouse_event_t *me = luacef_checkudata(L, 2, __mouse_event__);
	int leave = lua_tointeger(L, 3);

	h->send_mouse_move_event(h, me, leave);

	return 0;
}

/*
	<void> BrowserHost:SendMouseWheelEvent(
		<MouseEvent>	event,
		<int>			deltaX,
		<int>			deltaY
	)
*/
API(SendMouseWheelEvent)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	cef_mouse_event_t *me = luacef_checkudata(L, 2, __mouse_event__);
	int dx = lua_tointeger(L, 3);
	int dy = lua_tointeger(L, 4);

	h->send_mouse_wheel_event(h, me, dx, dy);

	return 0;
}

/*
	<void> BrowserHost:SetFocus(
		<bool> focus
	)
*/
API(SetFocus)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int focus = lua_toboolean(L, 2);

	h->set_focus(h, focus);

	return 0;
}

/*
	<void> BrowserHost:SetMouseCursorChangeDisabled(
		<bool> disabled
	)
*/
API(SetMouseCursorChangeDisabled)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int disabled = lua_toboolean(L, 2);

	h->set_mouse_cursor_change_disabled(h, disabled);

	return 0;
}

/*
	<void> BrowserHost:SetWindowlessFrameRate(
		<int> frame_rate
	)
*/
API(SetWindowlessFrameRate)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int frame_rate = lua_tointeger(L, 2);

	h->set_windowless_frame_rate(h, frame_rate);

	return 0;
}

/*
	<void> BrowserHost:SetZoomLevel(
		<num>	zoom_level
	)
*/
API(SetZoomLevel)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	double zl = lua_tonumber(L, 2);

	h->set_zoom_level(h, zl);

	return 0;
}

/*
	<void> BrowserHost:ShowDevTools(
		<WindowInfo>		window_info,
		<Client>			client,
		<BrowserSettings>	settings,
		<Point>				inspect_element_at	
	)
*/
API(ShowDevTools)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	cef_window_info_t *wi = luacef_checkudata(L, 2, __CefWindowInfo);
	cef_client_t *c = luacef_checkudata(L, 3, __CefClient);
	cef_browser_settings_t *bs = luacef_checkudata(L, 4, __browser_settings__);
	cef_point_t *pt = luacef_checkudata(L, 5, __point__);

	h->show_dev_tools(h, wi, c, bs, pt);

	return 0;
}

/*
	<void> BrowserHost:StartDownload(
		<str> url
	)
*/
API(StartDownload)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	const char* cs = lua_tostring(L, 2);

	cef_string_t url = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &url);
	h->start_download(h, &url);

	return 0;
}

/*
	<void> BrowserHost:StopFinding(
		<int> clearSelection
	)
*/
API(StopFinding)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int clr_slt = lua_tointeger(L, 2);

	h->stop_finding(h, clr_slt);

	return 0;
}

/*
	<int> BrowserHost:TryCloseBrowser()
*/
API(TryCloseBrowser)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	int ret = h->try_close_browser(h);

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<void> BrowserHost:WasHidden(
		<int> hidden
	)
*/
API(WasHidden)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int hidden = lua_tointeger(L, 2);

	h->was_hidden(h, hidden);

	return 0;
}

/*
	<void> BrowserHost:WasResized()
*/
API(WasResized)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->was_resized(h);

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

// meta =========================

static const luaL_Reg luacef_Browser_Host_m[] = {
	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },

	{ "AddWordToDictionary",		API_N(AddWordToDictionary) },
	{ "CloseBrowser",				API_N(CloseBrowser) },
	{ "CloseDevTools",				API_N(CloseDevTools) },
	{ "DownloadImage",				API_N(DownloadImage) },
	{ "DragSourceEndedAt",			API_N(DragSourceEndedAt) },
	{ "DragSourceSystemDragEnded",	API_N(DragSourceSystemDragEnded) },
	{ "DragTargetDragEnter",		API_N(DragTargetDragEnter) },
	{ "DragTargetDragLeave",		API_N(DragTargetDragLeave) },
	{ "DragTargetDragOver",			API_N(DragTargetDragOver) },
	{ "DragTargetDrop",				API_N(DragTargetDrop) },
	{ "Find",						API_N(Find) },
	{ "GetBrowser",					API_N(GetBrowser) },
	{ "GetClient",					API_N(GetClient) },
	{ "GetNavigationEntries",		API_N(GetNavigationEntries) },
	{ "GetNSTextInputContext",		API_N(GetNSTextInputContext) },
	{ "GetOpenerWindowHandle",		API_N(GetOpenerWindowHandle) },
	{ "GetRequestContext",			API_N(GetRequestContext) },
	{ "GetWindowlessFrameRate",		API_N(GetWindowlessFrameRate) },
	{ "GetWindowHandle",			API_N(GetWindowHandle) },
	{ "GetZoomLevel",				API_N(GetZoomLevel) },
	{ "HandleKeyEventAfterTextInputClient",		API_N(HandleKeyEventAfterTextInputClient) },
	{ "HandleKeyEventBeforeTextInputClient",	API_N(HandleKeyEventBeforeTextInputClient) },
	{ "HasDevTools",				API_N(HasDevTools) },
	{ "HasView",					API_N(HasView) },
	{ "Invalidate",					API_N(Invalidate) },
	{ "IsMouseCursorChangeDisabled",	API_N(IsMouseCursorChangeDisabled) },
	{ "IsWindowRenderingDisabled",	API_N(IsWindowRenderingDisabled) },
	{ "NotifyMoveOrResizeStarted",	API_N(NotifyMoveOrResizeStarted) },
	{ "NotifyScreenInfoChanged",	API_N(NotifyScreenInfoChanged) },
	{ "Print",						API_N(Print) },
	{ "PrintToPDF",					API_N(PrintToPDF) },
	{ "ReplaceMisspelling",			API_N(ReplaceMisspelling) },
	{ "RunFileDialog",				API_N(RunFileDialog) },
	{ "SendCaptureLostEvent",		API_N(SendCaptureLostEvent) },
	{ "SendFocusEvent",				API_N(SendFocusEvent) },
	{ "SendKeyEvent",				API_N(SendKeyEvent) },
	{ "SendMouseClickEvent",		API_N(SendMouseClickEvent) },
	{ "SendMouseMoveEvent",			API_N(SendMouseMoveEvent) },
	{ "SendMouseWheelEvent",		API_N(SendMouseWheelEvent) },
	{ "SetFocus",					API_N(SetFocus) },
	{ "SetMouseCursorChangeDisabled",	API_N(SetMouseCursorChangeDisabled) },
	{ "SetWindowlessFrameRate",		API_N(SetWindowlessFrameRate) },
	{ "SetZoomLevel",				API_N(SetZoomLevel) },
	{ "ShowDevTools",				API_N(ShowDevTools) },
	{ "StartDownload",				API_N(StartDownload) },
	{ "StopFinding",				API_N(StopFinding) },
	{ "TryCloseBrowser",			API_N(TryCloseBrowser) },
	{ "WasHidden",					API_N(WasHidden) },
	{ "WasResized",					API_N(WasResized) },
	
	LUAREGEND
};

// static vfunctions ================================================

/*
	<bool> CreateBrowser(
		<WindowInfo> info,
		<Client> client,
		<str> url,
		<BrowserSettings> settings,
		<RequestContext> request_context
	)
*/
static int luacef_CreateBrowser(lua_State* L)
{
	cef_window_info_t *info = luacef_checkudata(L, 1, __CefWindowInfo);
	cef_client_t *client = luacef_checkudata(L, 2, __CefClient);
	cef_string_t url = luacef_tostring(L, 3);
	cef_browser_settings_t *settings = luacef_checkudata(L, 4, __browser_settings__);
	cef_request_context_t *request_context = luacef_checkudata(L, 5, __CefRequestContext);

	int r = cef_browser_host_create_browser(
		info,
		client,
		&url,
		settings,
		request_context
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<Browser> CreateBrowserSync(
		<WindowInfo> info,
		<Client> client,
		<str> url,
		<BrowserSettings> settings,
		<RequestContext> request_context
	)
*/
static int luacef_CreateBrowserSync(lua_State* L)
{
	cef_window_info_t *info = luacef_checkudata(L, 1, __CefWindowInfo);
	cef_client_t *client = luacef_checkudata(L, 2, __CefClient);
	cef_string_t url = luacef_tostring(L, 3);
	cef_browser_settings_t *settings = luacef_checkudata(L, 4, __browser_settings__);
	cef_request_context_t *request_context = luacef_checkudata(L, 5, __CefRequestContext);

	cef_browser_t *browser = cef_browser_host_create_browser_sync(
		info,
		client,
		&url,
		settings,
		request_context
	);
	
	luacef_pushuserdata(L, browser, __CefBrowser);
	return 1;
}

// =====================================

void luacef_Browser_reg(lua_State* L)
{
	luaL_newmetatable(L, __CefBrowser);
	luaL_setfuncs(L, luacef_Browser_m, 0);
	lua_setfield(L, -1, __index__);

	//

	luaL_newmetatable(L, __CefBrowserHost);
	luaL_setfuncs(L, luacef_Browser_Host_m, 0);
	lua_setfield(L, -1, __index__);

	//

	lua_pushcfunction(L, luacef_CreateBrowser);
	lua_setfield(L, -2, "CreateBrowser");

	lua_pushcfunction(L, luacef_CreateBrowserSync);
	lua_setfield(L, -2, "CreateBrowserSync");
}