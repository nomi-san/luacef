#ifndef LUACEF_INCLUDE_API_H_
#define LUACEF_INCLUDE_API_H_
#pragma once

/*
	lua:newuuserdata <- alloc [4-byte]
	~~~~~~~~~~~~~~~~
	       |
	       v
	    <ptr**> -> <ptr*> = <udata*> <- alloc [n-byte]
	       |                   |---> ::free
	       v                   |---> ::set, get
	    <self**>  <------------|      ~~~~~~~~
	    ~~~~~~~~                          ^
	       |                               \
	       v                             ~~~~~~~~~
	[method, property] <- <metatable> -> references
	       |
	       v
	     return

	  __LUA_side__
*/

// app
static const char *__app__ = "App";
static const char *__on_before_command_line_processing = "OnBeforeCommandLineProcessing";
static const char *__on_register_custom_schemes = "OnRegisterCustomSchemes";
static const char *__get_resource_bundle_handler = "GetResourceBundleHandler";
static const char *__get_browser_process_handler = "GetBrowserProcessHandler";
static const char *__get_render_process_handler = "GetRenderProcessHandler";

// base
static const char *__base__ = "Base";

// client
static const char *__client__ = "Client";
static const char *__get_context_menu_handler = "GetContextMenuHandler";
static const char *__get_dialog_handler = "GetDialogHandler";
static const char *__get_display_handler = "GetDisplayHandler";
static const char *__get_download_handler = "GetDownloadHandler";
static const char *__get_drag_handler = "GetDragHandler";
static const char *__get_find_handler = "GetFindHandler";
static const char *__get_focus_handler = "GetFocusHandler";
static const char *__get_geolocation_handler = "GetGeolocationHandler";
static const char *__get_jsdialog_handler = "GetJSDialogHandler";
static const char *__get_keyboard_handler = "GetKeyboardHandler";
static const char *__get_life_span_handler = "GetLifeSpanHandler";
static const char *__get_load_handler = "GetLoadHandler";
static const char *__get_render_handler = "GetRenderHandler";
static const char *__get_request_handler = "GetRequestHandler";
static const char *__on_process_message_received = "OnProcessMessageReceived";

// find_handler
static const char *__find_handler__ = "FindHandler";
static const char *__on_find_result = "OnFindResult";

// request
static const char *__post_data__ = "PostData";
static const char *__post_data_element__ = "PostData";

// life_span_handler
static const char *__do_close = "DoClose";
static const char *__on_before_popup = "OnBeforePopup";
static const char *__on_after_created = "OnAfterCreated";
static const char *__on_before_close = "OnBeforeClose";

// rect
static const char *__rect__ = "Rect";

// download_handler
static const char *__download_handler__ = "DownloadHandler";
static const char *__before_download_callback__ = "BeforeDownloadCallback";
static const char *__download_item_callback__ = "DownloadItemCallback";

static const char *__cont = "Cont";
static const char *__pause = "Pause";
static const char *__resume = "Resume";
static const char *__on_before_download = "OnBeforeDownload";
static const char *__on_download_updated = "OnDownloadUpdated";

// download_item
static const char *__download_item__ = "DownloadItem";

static const char *__get_resource_handler = "GetResourceHandler";
static const char *__get_auth_credentials = "GetAuthCredentials";
static const char *__on_before_browse =				"OnBeforeBrowse";
static const char *__on_open_urlfrom_tab =			"OnOpenURLFromTab";
static const char *__on_before_resource_load =		"OnBeforeResourceLoad";
static const char *__on_resource_redirect =			"OnResourceRedirect";
static const char *__on_resource_response =			"OnResourceResponse";
static const char *__get_resource_response_filter =	"GetResourceResponseFilter";
static const char *__on_resource_load_complete =		"OnResourceLoadComplete";
static const char *__on_quota_request =				"OnQuotaRequest";
static const char *__on_protocol_execution =			"OnProtocolExecution";
static const char *__on_certificate_error =			"OnCertificateError";
static const char *__on_plugin_crashed =				"OnPluginCrashed";
static const char *__on_render_view_ready =			"OnRenderViewReady";
static const char *__on_render_process_terminated =	"OnRenderProcessTerminated";


// dom
static const char *__domvisitor__ = "DOMVisitor";
static const char *__domdocument__ = "DOMDocument";
static const char *__domnode__ = "DOMMode";

// cookie
static const char *__cookie_manager__ = "CookieManager";
static const char *__delete_cookies_callback__ = "DeleteCookiesCallback";

// callback
static const char *__completion_callback__ = "CompletionCallback";

// 
static const char *__scheme_registrar__ = "SchemeRegistrar";


//
static const char *__frame__ = "Frame";
static const char *__browser__ = "Browser";
static const char *__settings__ = "Settings";
static const char *__main_args__ = "MainArgs";
static const char *__window_info__ = "WindowInfo";
static const char *__browser_settings__ = "BrowserSettings";
static const char *__request__ = "Request";
static const char *__string_visitor__ = "StringVisitor";
static const char *__process_message__ = "ProcessMessage";
static const char *__browser_host__ = "BrowserHost";
static const char *__point__ = "Point";
static const char *__mouse_event__ = "MouseEvent";
static const char *__key_event__ = "KeyEvent";
static const char *__request_context__ = "RequestContext";
static const char *__command_line__ = "CommandLine";

// todo
static const char *__v8accessor__ = "V8Accessor";
static const char *__v8_accesscontrol__ = "V8Accesscontrol";
static const char *__v8context__ = "V8Context";
static const char *__v8exception__ = "V8Exception";
static const char *__v8handler__ = "V8Handler";
static const char *__execute = "Execute";

static const char *__v8_propertyattribute__ = "V8Propertyattribute";
static const char *__v8stack_frame__ = "V8StackFrame";
static const char *__v8stack_trace__ = "V8StackTrace";
static const char *__v8value__ = "V8Value";

static const char *__v8interceptor__ = "V8Interceptor";



static const char *__task_runner__ = "TaskRunner";

static const char *__list_value__ = "ListValue";
static const char *__popup_features__ = "PopupFeatures";

static const char *__web_plugin_unstable_callback__ = "WebPluginUnstableCallback";
static const char *__web_plugin_info__ = "WebPluginInfo";
static const char *__register_cdm_callback__ = "RegisterCDMCallback";



// browser
static const char *__can_go_back = "CanGoBack";
static const char *__can_go_forward = "CanGoForward";
static const char *__get_focused_frame = "GetFocusedFrame";
static const char *__get_frame = "GetFrame";
static const char *__get_frame_byident = "GetFrameByident";
static const char *__get_frame_count = "GetFrameCount";
static const char *__get_frame_identifiers = "GetFrameIdentifiers";
static const char *__get_frame_names = "GetFrameNames";
static const char *__get_host = "GetHost";
static const char *__get_identifier = "GetIdentifier";
static const char *__get_main_frame = "GetMainFrame";
static const char *__go_back = "GoBack";
static const char *__go_forward = "GoForward";
static const char *__has_document = "HasDocument";
static const char *__is_loading = "IsLoading";
static const char *__is_popup = "IsPopup";
static const char *__is_same = "IsSame";
static const char *__reload = "Reload";
static const char *__reload_ignore_cache = "ReloadIgnoreCache";
static const char *__send_process_message = "SendProcessMessage";
static const char *__stop_load = "StopLoad";

static const char *__browser_process_handler__ = "BrowserProcessHandler";
static const char *__context_menu_handler__ = "ContextMenuHandler";
static const char *__dialog_handler__ = "DialogHandler";
static const char *__display_handler__ = "DisplayHandler";

static const char *__drag_handler__ = "DragHandler";
static const char *__focus_handler__ = "FocusHandler";
static const char *__geolocation_handler__ = "GeolocationHandler";
static const char *__jsdialog_handler__ = "JsDialogHandler";
static const char *__keyboard_handler__ = "KeyboardHandler";
static const char *__life_span_handler__ = "LifeSpanHandler";
static const char *__load_handler__ = "LoadHandler";
static const char *__print_handler__ = "PrintHandler";
static const char *__render_handler__ = "RenderHandler";
static const char *__render_process_handler__ = "RenderProcess_handler";
static const char *__request_context_handler__ = "RequestContextHandler";
static const char *__request_handler__ = "RequestHandler";
static const char *__resource_bundle_handler__ = "ResourceBundleHandler";
static const char *__resource_handler__ = "ResourceHandler";




static const char *__time__ = "Time";



static const char *__event_handle__ = "EventHandle";




// ptr
static const char *__int_ptr__ = "IntPtr";
static const char *__bool_ptr__ = "BoolPtr";
//static const char *__ptr_ptr__ = "PtrPtr";


















#endif