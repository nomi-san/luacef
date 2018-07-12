#include "../luacef.h"

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

	luacef_pushuserdata(L, b, __browser__);
	return 1;
}

/*
	<Browser> Browser:GetHost()
*/
static int 	luacef_browser_get_host(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	cef_browser_host_t *host = b->get_host(b);

	luacef_pushuserdata(L, host, __browser_host__);
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
	<void> Browser:GoBack()
*/
static int 	luacef_browser_go_back(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->go_back(b);

	return 0;
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
	<void> Browser:GoForward()
*/
static int 	luacef_browser_go_forward(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->go_forward(b);

	return 0;
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
	<void> Browser:StopLoad()
*/
static int 	luacef_browser_stop_load(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	b->stop_load(b);

	return 0;
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
	<bool> Browser:IsPopup()
*/
static int 	luacef_browser_is_popup(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	lua_pushboolean(L, b->is_popup(b));

	return 1;
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
	<int> Browser:GetFrameCount()
*/
static int 	luacef_browser_get_frame_count(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);

	size_t c = b->get_frame_count(b);

	lua_pushinteger(L, c);
	return 1;
}

///////////////////////////
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
	return 1;
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

static int luacef_browser_host_new(lua_State* L)
{
	size_t sz = sizeof(cef_browser_host_t);
	cef_browser_host_t *h = calloc(1, sz);
	h->base.size = sz;

	//
	h->add_word_to_dictionary;
	h->close_browser;
	h->close_dev_tools;
	h->download_image;
	h->drag_source_ended_at;
	h->drag_source_system_drag_ended;
	h->drag_target_drag_enter;
	h->drag_target_drag_leave;
	h->drag_target_drag_over;
	h->drag_target_drop;
	h->find;
	h->get_browser;
	h->get_client;
	h->get_navigation_entries;
	//h->get_nstext_input_context;
	h->get_opener_window_handle;
	h->get_request_context;
	h->get_windowless_frame_rate;
	h->get_window_handle;
	h->get_zoom_level;
	//h->handle_key_event_after_text_input_client;
	//h->handle_key_event_before_text_input_client;
	h->has_dev_tools;
	h->has_view;
	h->invalidate;
	h->is_mouse_cursor_change_disabled;
	h->is_window_rendering_disabled;
	h->notify_move_or_resize_started;
	h->notify_screen_info_changed;
	h->print;
	h->print_to_pdf;
	h->replace_misspelling;
	h->run_file_dialog;
	h->send_capture_lost_event;
	h->send_focus_event;
	h->send_key_event;
	h->send_mouse_click_event;
	h->send_mouse_move_event;
	h->send_mouse_wheel_event;
	h->set_focus;
	h->set_mouse_cursor_change_disabled;
	h->set_windowless_frame_rate;
	h->set_zoom_level;
	h->show_dev_tools;
	h->start_download;
	h->stop_finding;
	h->try_close_browser;
	h->was_hidden;
	h->was_resized;

	luacef_pushuserdata(L, h, __browser_host__);
	return 1;
}

/*
	<void> BrowserHost:AddWordToDictionary(
		<str> word
	)
*/
static int luacef_browser_host_add_word_to_dictionary(lua_State* L)
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
static int luacef_browser_host_close_browser(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int force_close = lua_tointeger(L, 2);

	h->close_browser(h, force_close);

	return 0;
}

/*
	<void> BrowserHost:CloseDevTools()
*/
static int luacef_browser_host_close_dev_tools(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->close_dev_tools(h);

	return 0;
}

/*
	<> BrowserHost:DownloadImage()
*/
static int luacef_browser_host_download_image(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo

	//h->download_image(h, );

	return 0;
}

/*
	<> BrowserHost:DragSourceEndedAt()
*/
static int luacef_browser_host_drag_source_ended_at(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo
	//h->drag_source_ended_at()

	return 0;
}

/*
	<> BrowserHost:DragSourceSystemDragEnded()
*/
static int luacef_browser_host_drag_source_system_drag_ended(lua_State* L)
{

	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDragEnter()
*/
static int luacef_browser_host_drag_target_drag_enter(lua_State* L)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDragLeave()
*/
static int luacef_browser_host_drag_target_drag_leave(lua_State* L)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDragOver()
*/
static int luacef_browser_host_drag_target_drag_over(lua_State* L)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:DragTargetDrop()
*/
static int luacef_browser_host_drag_target_drop(lua_State* L)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:Find()
*/
static int luacef_browser_host_find(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo
	//h->find(h, )

	return 0;
}

/*
	<Browser> BrowserHost:GetBrowser()
*/
static int luacef_browser_host_get_browser(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_browser_t *b = h->get_browser(h);

	luacef_pushuserdata(L, b, __browser__);
	return 1;
}

/*
	<Client> BrowserHost:GetClient()
*/
static int luacef_browser_host_get_client(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_client_t *c = h->get_client(h);

	luacef_pushuserdata(L, c, __client__);
	return 1;
}

/*
	<void> Browser:GetNavigationEntries()
*/
static int luacef_browser_host_get_navigation_entries(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	// todo
	//h->get_navigation_entries(j. )

	return 0;
}

/*
	<void> Browser:GetNSTextInputContext()
*/
static int luacef_browser_host_get_nstext_input_context(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	//h->get_nstext_input_context(h);

	return 0;
}

/*
	<udata> Browser:GetOpenerWindowHandle()
	-> HWND
*/
static int luacef_browser_host_get_opener_window_handle(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	HWND handle = h->get_opener_window_handle(h);

	lua_pushlightuserdata(L, handle);
	return 1;
}

/*
	<RequestContext> Browser:GetRequestContext()
*/
static int luacef_browser_host_get_request_context(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	cef_request_context_t *rq = h->get_request_context(h);

	luacef_pushuserdata(L, rq, __request_context__);
	return 1;
}

/*
	<int> Browser:GetWindowlessFrameRate()
*/
static int luacef_browser_host_get_windowless_frame_rate(lua_State* L)
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
static int luacef_browser_host_get_window_handle(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	HWND handle = h->get_window_handle(h);

	lua_pushlightuserdata(L, handle);
	return 1;
}

/*
	<num> BrowserHost:GetZoomLevel()
*/
static int luacef_browser_host_get_zoom_level(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	double zl = h->get_zoom_level(h);

	lua_pushnumber(L, zl);
	return 1;
}

/*
	<> BrowserHost:HandleKeyEventAfterTextInputClient()
*/
static int luacef_browser_host_handle_key_event_after_text_input_client(lua_State* L)
{
	// todo
	return 0;
}

/*
	<> BrowserHost:HandleKeyEventBeforeTextInputClient()
*/
static int luacef_browser_host_handle_key_event_before_text_input_client(lua_State* L)
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
static int luacef_browser_host_has_dev_tools(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->has_dev_tools(h));
	return 1;
}

/*
	<bool> BrowserHost:HasView()
*/
static int luacef_browser_host_has_view(lua_State* L)
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
static int luacef_browser_host_invalidate(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int type = lua_tointeger(L, 2);

	h->invalidate(h, type);

	return 0;
}

/*
	<bool> BrowserHost:IsMouseCursorChangeDisabled()
*/
static int luacef_browser_host_is_mouse_cursor_change_disabled(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->is_mouse_cursor_change_disabled(h));
	return 1;
}

/*
	<bool> BrowserHost:IsWindowRenderingDisabled()
*/
static int luacef_browser_host_is_window_rendering_disabled(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	lua_pushboolean(L, h->is_window_rendering_disabled(h));
	return 1;
}

/*
	<void> BrowserHost:NotifyMoveOrResizeStarted()
*/
static int luacef_browser_host_notify_move_or_resize_started(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->notify_move_or_resize_started(h);

	return 0;
}

/*
	<void> BrowserHost:NotifyScreenInfoChanged()
*/
static int luacef_browser_host_notify_screen_info_changed(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->notify_screen_info_changed(h);

	return 0;
}

/*
	<void> BrowserHost:Print()
*/
static int luacef_browser_host_print(lua_State* L)
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
static int luacef_browser_host_print_to_pdf(lua_State* L)
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
static int luacef_browser_host_replace_misspelling(lua_State* L)
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
static int luacef_browser_host_run_file_dialog(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	//h->run_file_dialog()
	// todo

	return 0;
}

/*
	<void> BrowserHost:SendCaptureLostEvent()
*/
static int luacef_browser_host_send_capture_lost_event(lua_State* L)
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
static int luacef_browser_host_send_focus_event(lua_State* L)
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
static int luacef_browser_host_send_key_event(lua_State* L)
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
static int luacef_browser_host_send_mouse_click_event(lua_State* L)
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
static int luacef_browser_host_send_mouse_move_event(lua_State* L)
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
static int luacef_browser_host_send_mouse_wheel_event(lua_State* L)
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
static int luacef_browser_host_set_focus(lua_State* L)
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
static int luacef_browser_host_set_mouse_cursor_change_disabled(lua_State* L)
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
static int luacef_browser_host_set_windowless_frame_rate(lua_State* L)
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
static int luacef_browser_host_set_zoom_level(lua_State* L)
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
static int luacef_browser_host_show_dev_tools(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	cef_window_info_t *wi = luacef_checkudata(L, 2, __window_info__);
	cef_client_t *c = luacef_checkudata(L, 3, __client__);
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
static int luacef_browser_host_start_download(lua_State* L)
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
static int luacef_browser_host_stop_finding(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int clr_slt = lua_tointeger(L, 2);

	h->stop_finding(h, clr_slt);

	return 0;
}

/*
	<int> BrowserHost:TryCloseBrowser()
*/
static int luacef_browser_host_try_close_browser(lua_State* L)
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
static int luacef_browser_host_was_hidden(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);
	int hidden = lua_tointeger(L, 2);

	h->was_hidden(h, hidden);

	return 0;
}

/*
	<void> BrowserHost:WasResized()
*/
static int luacef_browser_host_was_resized(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	h->was_resized(h);

	return 0;
}

static const luaL_Reg luacef_browser_host_m[] = {
	{ "AddWordToDictionary", luacef_browser_host_add_word_to_dictionary },
	{ "CloseBrowser", luacef_browser_host_close_browser },
	{ "CloseDevTools", luacef_browser_host_close_dev_tools },
	{ "DownloadImage", luacef_browser_host_download_image },
	{ "DragSourceEndedAt", luacef_browser_host_drag_source_ended_at },
	{ "DragSourceSystemDragEnded", luacef_browser_host_drag_source_system_drag_ended },
	{ "DragTargetDragEnter", luacef_browser_host_drag_target_drag_enter },
	{ "DragTargetDragLeave", luacef_browser_host_drag_target_drag_leave },
	{ "DragTargetDragOver", luacef_browser_host_drag_target_drag_over },
	{ "DragTargetDrop", luacef_browser_host_drag_target_drop },
	{ "Find", luacef_browser_host_find },
	{ "GetBrowser", luacef_browser_host_get_browser },
	{ "GetClient", luacef_browser_host_get_client },
	{ "GetNavigationEntries", luacef_browser_host_get_navigation_entries },
	{ "GetNSTextInputContext", luacef_browser_host_get_nstext_input_context },
	{ "GetOpenerWindowHandle", luacef_browser_host_get_opener_window_handle },
	{ "GetRequestContext", luacef_browser_host_get_request_context },
	{ "GetWindowlessFrameRate", luacef_browser_host_get_windowless_frame_rate },
	{ "GetWindowHandle", luacef_browser_host_get_window_handle },
	{ "GetZoomLevel", luacef_browser_host_get_zoom_level },
	{ "HandleKeyEventAfterTextInputClient", luacef_browser_host_handle_key_event_after_text_input_client },
	{ "HandleKeyEventBeforeTextInputClient", luacef_browser_host_handle_key_event_before_text_input_client },
	{ "HasDevTools", luacef_browser_host_has_dev_tools },
	{ "HasView", luacef_browser_host_has_view },
	{ "Invalidate", luacef_browser_host_invalidate },
	{ "IsMouseCursorChangeDisabled", luacef_browser_host_is_mouse_cursor_change_disabled },
	{ "IsWindowRenderingDisabled", luacef_browser_host_is_window_rendering_disabled },
	{ "NotifyMoveOrResizeStarted", luacef_browser_host_notify_move_or_resize_started },
	{ "NotifyScreenInfoChanged", luacef_browser_host_notify_screen_info_changed },
	{ "Print", luacef_browser_host_print },
	{ "PrintToPDF", luacef_browser_host_print_to_pdf },
	{ "ReplaceMisspelling", luacef_browser_host_replace_misspelling },
	{ "RunFileDialog", luacef_browser_host_run_file_dialog },
	{ "SendCaptureLostEvent", luacef_browser_host_send_capture_lost_event },
	{ "SendFocusEvent", luacef_browser_host_send_focus_event },
	{ "SendKeyEvent", luacef_browser_host_send_key_event },
	{ "SendMouseClickEvent", luacef_browser_host_send_mouse_click_event },
	{ "SendMouseMoveEvent", luacef_browser_host_send_mouse_move_event },
	{ "SendMouseWheelEvent", luacef_browser_host_send_mouse_wheel_event },
	{ "SetFocus", luacef_browser_host_set_focus },
	{ "SetMouseCursorChangeDisabled", luacef_browser_host_set_mouse_cursor_change_disabled },
	{ "SetWindowlessFrameRate", luacef_browser_host_set_windowless_frame_rate },
	{ "SetZoomLevel", luacef_browser_host_set_zoom_level },
	{ "ShowDevTools", luacef_browser_host_show_dev_tools },
	{ "StartDownload", luacef_browser_host_start_download },
	{ "StopFinding", luacef_browser_host_stop_finding },
	{ "TryCloseBrowser", luacef_browser_host_try_close_browser },
	{ "WasHidden", luacef_browser_host_was_hidden },
	{ "WasResized", luacef_browser_host_was_resized },
	{ NULL, NULL }
};

// functions

/*
	<int> CreateBrowser(
		<WindowInfo>		info,
		<Client>			client,
		<str>				url,
		<BrowserSettings>	settings
	)
*/
static int luacef_create_browser(lua_State* L)
{
	cef_window_info_t *winfo = luacef_checkudata(L, 1, __window_info__);
	if (!winfo) return 0;

	cef_client_t *client = luacef_checkudata(L, 2, __client__);
	if (!client) return 0;

	const char *cs_url = lua_tostring(L, 3);

	cef_string_t url = { 0 };
	cef_string_from_utf8(cs_url, strlen(cs_url), &url);

	cef_browser_settings_t *bs = luacef_checkudata(L, 4, __browser_settings__);
	if (!bs) return 0;

	int ret = cef_browser_host_create_browser(
		winfo,
		client,
		&url,
		bs,
		NULL
	);

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<Browser> CreateBrowserSync(
		<WindowInfo>		info,
		<Client>			client,
		<str>				url,
		<BrowserSettings>	settings
	)
*/
static int luacef_create_browser_sync(lua_State* L)
{
	cef_window_info_t *winfo = luacef_checkudata(L, 1, __window_info__);
	if (!winfo) return 0;

	cef_client_t *client = luacef_checkudata(L, 2, __client__);
	if (!client) return 0;

	cef_string_t url = luacef_tostring(L, 3);

	cef_browser_settings_t *bs = luacef_checkudata(L, 4, __browser_settings__);
	if (!bs) return 0;

	cef_browser_t *browser = cef_browser_host_create_browser_sync(
		winfo,
		client,
		&url,
		bs,
		NULL
	);
	
	luacef_pushuserdata(L, browser, __browser__);
	return 1;
}

// register

void luacef_browser_reg(lua_State* L)
{
	luaL_newmetatable(L, __browser__);
	luaL_setfuncs(L, luacef_browser_m, 0);
	lua_setfield(L, -1, __index__);

	//

	luaL_newmetatable(L, __browser_host__);
	luaL_setfuncs(L, luacef_browser_host_m, 0);
	lua_setfield(L, -1, __index__);

	//

	lua_pushcfunction(L, luacef_create_browser);
	lua_setfield(L, -2, "CreateBrowser");

	lua_pushcfunction(L, luacef_create_browser_sync);
	lua_setfield(L, -2, "CreateBrowserSync");
}