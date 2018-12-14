#ifndef LUACEF_INCLUDE_API_H_
#define LUACEF_INCLUDE_API_H_
#pragma once

#if defined(OS_WIN)
#define luacef_pushhandle(L, handle) lua_pushlightuserdata(L, handle)
#define luacef_tohandle(L, idx) lua_touserdata(L, idx)
#elif defined(OS_LINUX)
#define luacef_pushhandle(L, handle) lua_pushinteger(L, handle)
#define luacef_tohandle(L, idx) lua_tointegerx(L,(idx),NULL)
#endif

typedef int *IntPtr;
typedef double *NumPtr;
typedef void** PtrPtr;

/*
	----- C ----------------
	lua:newuserdata  <- alloc
	~~~~~~~~~~~~~~~
		   |
		   v
		 heap[1] -> [0] := cef_type <- alloc
		   |                   |---> :: free
		   v                   |---> :: set/get
		 self //  <------------|        ~~~~~~~
		~~~~~~~~               v          ^^^
		   |           <type properties>    \
		   v                   v         ~~~~~~~~~
	[method, property] <- <metatable> -> reference
		   |
		   v
	----- LUA --------------
*/

// ptr

static const char __IntPtr__[] = "IntPtr";
static const char __NumPtr__[] = "NumPtr";
static const char __PtrPtr__[] = "PtrPtr";

// binary value
static const char __binary_value__[] = "CefBinaryValue";

// image
static const char __image__[] = "CefImage";

// app
static const char __app__[] = "CefApp";
static const char *__OnBeforeCommandLineProcessing = "OnBeforeCommandLineProcessing";
static const char *__OnRegisterCustomSchemes = "OnRegisterCustomSchemes";
static const char *__GetResourceBundleHandler = "GetResourceBundleHandler";
static const char *__GetBrowserProcessHandler = "GetBrowserProcessHandler";
static const char *__GetRenderProcessHandler = "GetRenderProcessHandler";

// base
static const char __base__[] = "CefBase";

// client
static const char __client__[] = "CefClient";
static const char *__GetContextMenuHandler = "GetContextMenuHandler";
static const char *__GetDialogHandler = "GetDialogHandler";
static const char *__GetDisplayHandler = "GetDisplayHandler";
static const char *__GetDownloadHandler = "GetDownloadHandler";
static const char *__GetDragHandler = "GetDragHandler";
static const char *__GetFindHandler = "GetFindHandler";
static const char *__GetFocusHandler = "GetFocusHandler";
static const char *__GetGeolocationHandler = "GetGeolocationHandler";
static const char *__GetJSDialogHandler = "GetJSDialogHandler";
static const char *__GetKeyboardHandler = "GetKeyboardHandler";
static const char *__GetLifeSpanHandler = "GetLifeSpanHandler";
static const char *__GetLoadHandler = "GetLoadHandler";
static const char *__GetRenderHandler = "GetRenderHandler";
static const char *__GetRequestHandler = "GetRequestHandler";
static const char *__OnProcessMessageReceived = "OnProcessMessageReceived";

// find_handler
static const char __find_handler__[]	= "CefFindHandler";
static const char __OnFindResult[]		= "OnFindResult";

// request
static const char *__post_data__ = "CefPostData";
static const char *__post_data_element__ = "PostData";

// life_span_handler
static const char __DoClose[]			= "DoClose";
static const char __OnBeforePopup[]		= "OnBeforePopup";
static const char __OnAfterCreated[]	= "OnAfterCreated";
static const char __OnBeforeClose[]		= "OnBeforeClose";

// rect


// download_handler
static const char *__download_handler__ = "DownloadHandler";
static const char *__before_download_callback__ = "BeforeDownloadCallback";
static const char *__download_item_callback__ = "DownloadItemCallback";

static const char *__cont = "Cont";
//static const char *__pause = "Pause";
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
static const char *__cookie_visitor__ = "CookieVisitor";
static const char *__delete_cookies_callback__ = "DeleteCookiesCallback";
static const char *__set_cookies_callback__ = "SerCookieCallback";

// callback
static const char *__completion_callback__ = "CompletionCallback";
static const char *__OnComplete = "OnComplete";
static const char *__callback__ = "Callback";

// 
static const char *__scheme_registrar__ = "SchemeRegistrar";

static const char __string_list__[] = "CefStringList";

//
static const char __frame__[] = "CefFrame";
static const char __browser__[] = "CefBrowser";
static const char __main_args__[] = "CefMainArgs";
static const char __window_info__[] = "CefWindowInfo";
static const char __request__[] = "CefRequest";
static const char *__string_visitor__ = "StringVisitor";
static const char *__process_message__ = "ProcessMessage";
static const char *__browser_host__ = "BrowserHost";

static const char *__request_context__ = "RequestContext";
static const char *__command_line__ = "CommandLine";

// todo
static const char *__v8accessor__ = "V8Accessor";
static const char *__v8_accesscontrol__ = "V8Accesscontrol";
static const char *__v8context__ = "CefV8Context";
static const char *__v8exception__ = "V8Exception";
static const char __v8handler__[] = "CefV8Handler";
static const char *__execute = "Execute";

static const char *__v8_propertyattribute__ = "V8Propertyattribute";
static const char *__v8stack_frame__ = "V8StackFrame";
static const char *__v8stack_trace__ = "V8StackTrace";
static const char *__v8value__ = "CefV8Value";

static const char *__v8interceptor__ = "V8Interceptor";


static const char *__task__ = "Task";
static const char *__task_runner__ = "TaskRunner";



static const char *__web_plugin_unstable_callback__ = "WebPluginUnstableCallback";
static const char *__web_plugin_info__ = "WebPluginInfo";
static const char *__register_cdm_callback__ = "RegisterCDMCallback";
static const char *__web_plugin_info_visitor__ = "WebPluginInfoVisitor";



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

// browser_process_handler
static const char __browser_process_handler__[]		= "CefBrowserProcessHandler";
static const char __OnContextInitialized[]			= "OnContextInitialized";
static const char __OnBeforeChildProcessLaunch[]	= "OnBeforeChildProcessLaunch";
static const char __OnRenderProcessThreadCreated[]	= "OnRenderProcessThreadCreated";
static const char __OnScheduleMessagePumpWork[]		= "OnScheduleMessagePumpWork";
static const char __GetPrintHandler[]				= "GetPrintHandler";

// context_menu_handler
static const char *__context_menu_handler__ = "ContextMenuHandler";
static const char *__context_menu_params__ = "ContextMenuParams";
static const char *__run_context_menu_callback__ = "RunContextMenuCallback";
static const char *__OnBeforeContextMenu = "OnBeforeContextMenu";
static const char *__RunContextMenu = "RunContextMenu";
static const char *__OnContextMenuCommand = "OnContextMenuCommand";
static const char *__OnContextMenuDismissed = "OnContextMenuDismissed";

// menu_model
static const char __menu_model__[] = "CefMenuModel";

// menu_model_delegate
static const char *__menu_model_delegate__ = "MenuModelDelegate";


static const char *__dialog_handler__ = "DialogHandler";
static const char *__display_handler__ = "DisplayHandler";

// drag_handler
static const char *__drag_handler__ = "DragHandler";
static const char *__OnDragEnter = "OnDragEnter";
static const char *__OnDraggableRegionsChanged = "OnDraggableRegionsChanged";

// drag_data
static const char __drag_data__[] = "CefDragData";

static const char __focus_handler__[] = "CefFocusHandler";
static const char __geolocation_handler__[] = "CefGeolocationHandler";

// jsdialog_handler
static const char __jsdialog_handler__[]		= "CefJSDialogHandler";
static const char __jsdialog_callback__[]		= "CefJSDialogCallback";


static const char __keyboard_handler__[]		= "CefKeyboardHandler";
static const char __life_span_handler__[]		= "CefLifeSpanHandler";
static const char __load_handler__[]			= "CefLoadHandler";
static const char __print_handler__[]			= "CefPrintHandler";
static const char __render_handler__[]			= "CefRenderHandler";
static const char __render_process_handler__[]	= "CefRenderProcess_handler";
static const char __request_context_handler__[] = "CefRequestContextHandler";
static const char __request_handler__[]			= "CefRequestHandler";
static const char __resource_bundle_handler__[] = "CefResourceBundleHandler";
static const char __resource_handler__[]		= "CefResourceHandler";


static const char __time__[] = "CefTime";

static const char __event_handle__[] = "CefEventHandle";

// types
static const char __settings__[]					= "CefSettings";
static const char __request_context_settings__[]	= "CefRequestContextSettings";
static const char __browser_settings__[]			= "CefBrowserSettings";
static const char __urlparts__[]					= "CefURLParts";
static const char __cookie__[]						= "CefCookie";
static const char __point__[]						= "CefPoint";
static const char __rect__[]						= "CefRect";
static const char __size__[]						= "CefSize";
static const char __range__[]						= "CefRange";
static const char __insets__[]						= "CefInsets";
static const char __draggable_region__[]			= "CefDraggableRegion";
static const char __screen_info__[]					= "CefScreenInfo";
static const char __mouse_event__[]					= "CefMouseEvent";
static const char __key_event__[]					= "CefKeyEvent";
static const char __popup_features__[]				= "CefPopupFeatures";
static const char __geoposition__[]					= "CefGeoposition";
static const char __cursor_info__[]					= "CefCursorInfo";
static const char __pdf_print_settings__[]			= "CefPDFPrintSettings";
static const char __box_layout_settings__[]			= "CefBoxLayoutSettings";
static const char __composition_underline__[]		= "CefCompositionUnderline";


// value
static const char __value__[] = "CefValue";
static const char __list_value__[] = "CefListValue";
static const char __dictionary_value__[] = "CefDictionaryValue";


#endif
