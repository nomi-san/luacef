#include "luacef_types.h"

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
	h->get_nstext_input_context;
	h->get_opener_window_handle;
	h->get_request_context;
	h->get_windowless_frame_rate;
	h->get_window_handle;
	h->get_zoom_level;
	h->handle_key_event_after_text_input_client;
	h->handle_key_event_before_text_input_client;
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
	<> Browser:GetNavigationEntries()
*/
static int luacef_browser_host_get_navigation_entries(lua_State* L)
{
	cef_browser_host_t *h = luacef_touserdata(L, 1);

	return 0;
}

/*
	<> Browser:GetNstextInputContext()
*/
static int luacef_browser_host_get_nstext_input_context(lua_State* L)
{

	return 0;
}

/*
	<> Browser:GetOpenerWindowHandle()
*/
static int luacef_browser_host_get_opener_window_handle(lua_State* L)
{

	return 0;
}

/*
	<> Browser:GetRequestContext()
*/
static int luacef_browser_host_get_request_context(lua_State* L)
{

	return 0;
}

/*
	<> Browser:GetWindowlessFrameRate()
*/
static int luacef_browser_host_get_windowless_frame_rate(lua_State* L)
{

	return 0;
}

/*
	<> Browser:GetWindowHandle()
*/
static int luacef_browser_host_get_window_handle(lua_State* L)
{

	return 0;
}

/*
	<> Browser:GetZoomLevel()
*/
static int luacef_browser_host_get_zoom_level(lua_State* L)
{

	return 0;
}

/*
	<> Browser:HandleKeyEventAfterTextInputClient()
*/
static int luacef_browser_host_handle_key_event_after_text_input_client(lua_State* L)
{

	return 0;
}

/*
	<> Browser:HandleKeyEventBeforeTextInputClient()
*/
static int luacef_browser_host_handle_key_event_before_text_input_client(lua_State* L)
{

	return 0;
}

/*
	<bool> Browser:HasDevTools()
*/
static int luacef_browser_host_has_dev_tools(lua_State* L)
{

	return 0;
}

/*
	<bool> Browser:HasView()
*/
static int luacef_browser_host_has_view(lua_State* L)
{

	return 0;
}

/*
	<> Browser:Invalidate()
*/
static int luacef_browser_host_invalidate(lua_State* L)
{

	return 0;
}

/*
	<> Browser:IsMouseCursorChangeDisabled()
*/
static int luacef_browser_host_is_mouse_cursor_change_disabled(lua_State* L)
{

	return 0;
}

/*
	<> Browser:IsWindowRenderingDisabled()
*/
static int luacef_browser_host_is_window_rendering_disabled(lua_State* L)
{

	return 0;
}

/*
	<> Browser:NotifyMoveOrResizeStarted()
*/
static int luacef_browser_host_notify_move_or_resize_started(lua_State* L)
{

	return 0;
}

/*
	<> Browser:NotifyScreenInfoChanged()
*/
static int luacef_browser_host_notify_screen_info_changed(lua_State* L)
{

	return 0;
}

/*
	<> Browser:Print()
*/
static int luacef_browser_host_print(lua_State* L)
{

	return 0;
}

/*
	<> Browser:PrintToPDF()
*/
static int luacef_browser_host_print_to_pdf(lua_State* L)
{

	return 0;
}

/*
	<> Browser:ReplaceMisspelling()
*/
static int luacef_browser_host_replace_misspelling(lua_State* L)
{

	return 0;
}

/*
	<> Browser:RunFileDialog()
*/
static int luacef_browser_host_run_file_dialog(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SendCaptureLostEvent()
*/
static int luacef_browser_host_send_capture_lost_event(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SendFocusEvent()
*/
static int luacef_browser_host_send_focus_event(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SendKeyEvent()
*/
static int luacef_browser_host_send_key_event(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SendMouseClickEvent()
*/
static int luacef_browser_host_send_mouse_click_event(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SendMouseMoveEvent()
*/
static int luacef_browser_host_send_mouse_move_event(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SendMouseWheelEvent()
*/
static int luacef_browser_host_send_mouse_wheel_event(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SetFocus()
*/
static int luacef_browser_host_set_focus(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SetMouseCursorChangeDisabled()
*/
static int luacef_browser_host_set_mouse_cursor_change_disabled(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SetWindowlessFrameRate()
*/
static int luacef_browser_host_set_windowless_frame_rate(lua_State* L)
{

	return 0;
}

/*
	<> Browser:SetZoomLevel()
*/
static int luacef_browser_host_set_zoom_level(lua_State* L)
{

	return 0;
}

/*
	<> Browser:ShowDevTools()
*/
static int luacef_browser_host_show_dev_tools(lua_State* L)
{

	return 0;
}

/*
	<> Browser:StartDownload()
*/
static int luacef_browser_host_start_download(lua_State* L)
{

	return 0;
}

/*
	<> Browser:StopFinding()
*/
static int luacef_browser_host_stop_finding(lua_State* L)
{

	return 0;
}

/*
	<> Browser:TryCloseBrowser()
*/
static int luacef_browser_host_try_close_browser(lua_State* L)
{

	return 0;
}

/*
	<> Browser:WasHidden()
*/
static int luacef_browser_host_was_hidden(lua_State* L)
{

	return 0;
}

/*
	<> Browser:WasResized()
*/
static int luacef_browser_host_was_resized(lua_State* L)
{

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
	{ "GetNstextInputContext", luacef_browser_host_get_nstext_input_context },
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

void luacef_browser_host_reg(lua_State* L)
{
	luaL_newmetatable(L, __browser_host__);
	luaL_setfuncs(L, luacef_browser_host_m, 0);
	lua_setfield(L, -1, __index__);

	//
}