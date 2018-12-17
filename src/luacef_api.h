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
static const char __CefBinaryValue[] = "CefBinaryValue";

// image
static const char __CefImage[] = "CefImage";

//
static const char __CefX509Certificate[] = "CefX509Certificate";
static const char __CefX509CertPrincipal[] = "CefX509CertPrincipal";

// app
static const char __CefApp[] = "CefApp";
static const char __OnBeforeCommandLineProcessing[] = "OnBeforeCommandLineProcessing";
static const char __OnRegisterCustomSchemes[] = "OnRegisterCustomSchemes";
static const char __GetResourceBundleHandler[] = "GetResourceBundleHandler";
static const char __GetBrowserProcessHandler[] = "GetBrowserProcessHandler";
static const char __GetRenderProcessHandler[] = "GetRenderProcessHandler";

// base
static const char __CefBase[] = "CefBase";

// client
static const char __CefClient[] = "CefClient";
static const char __GetContextMenuHandler[] = "GetContextMenuHandler";
static const char __GetDialogHandler[]		= "GetDialogHandler";
static const char __GetDisplayHandler[]		= "GetDisplayHandler";
static const char __GetDownloadHandler[]	= "GetDownloadHandler";
static const char __GetDragHandler[]		= "GetDragHandler";
static const char __GetFindHandler[]		= "GetFindHandler";
static const char __GetFocusHandler[]		= "GetFocusHandler";
static const char __GetGeolocationHandler[] = "GetGeolocationHandler";
static const char __GetJSDialogHandler[]	= "GetJSDialogHandler";
static const char __GetKeyboardHandler[]	= "GetKeyboardHandler";
static const char __GetLifeSpanHandler[]	= "GetLifeSpanHandler";
static const char __GetLoadHandler[]		= "GetLoadHandler";
static const char __GetRenderHandler[]		= "GetRenderHandler";
static const char __GetRequestHandler[]		= "GetRequestHandler";
static const char __OnProcessMessageReceived[] = "OnProcessMessageReceived";

// FindHandler
static const char __CefFindHandler[]	= "CefFindHandler";
static const char __OnFindResult[]		= "OnFindResult";

// request
static const char __CefPostData[] = "CefPostData";
static const char __CefPostDataElement[] = "CefPostDataElement";

// LifeSpanHandler
static const char __DoClose[]			= "DoClose";
static const char __OnBeforePopup[]		= "OnBeforePopup";
static const char __OnAfterCreated[]	= "OnAfterCreated";
static const char __OnBeforeClose[]		= "OnBeforeClose";


// DownloadHandler
static const char __DownloadHandler__[]			= "CefDownloadHandler";
static const char __BeforeDownloadCallback[]	= "BeforeDownloadCallback";
static const char __DownloadItemCallback[]		= "DownloadItemCallback";

static const char __Continue[] = "Continue";
static const char __Pause[] = "Pause";
static const char __Resume[] = "Resume";
static const char __OnBeforeDownload[] = "OnBeforeDownload";
static const char __OnDownloadUpdated[] = "OnDownloadUpdated";

// download_item
static const char *__CefDownloadItem = "CefDownloadItem";

static const char *__GetResourceHandler = "GetResourceHandler";
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
static const char __CefDOMVisitor[] = "CefDOMVisitor";
static const char __CefDOMDocument[] = "CefDOMDocument";
static const char __CefDOMMode[] = "CefDOMMode";

// cookie
static const char __CefCookieManager[] = "CefCookieManager";
static const char __CefCookieVisitor[] = "CefCookieVisitor";
static const char __CefDeleteCookiesCallback[] = "CefDeleteCookiesCallback";
static const char __CefSerCookieCallback[] = "CefSerCookieCallback";

// callback
static const char *__CefCompletionCallback = "CefCompletionCallback";
static const char *__OnComplete = "OnComplete";
static const char *__CefCallback = "CefCallback";

// 
static const char *__CefSchemeRegistrar = "SchemeRegistrar";

static const char __string_list__[] = "CefStringList";

//
static const char __CefFrame[]			= "CefFrame";
static const char __CefBrowser[]		= "CefBrowser";
static const char __CefMainArgs[]		= "CefMainArgs";
static const char __CefWindowInfo[]		= "CefWindowInfo";
static const char __CefRequest[]		= "CefRequest";
static const char __CefStringVisitor[]	= "CefStringVisitor";
static const char __CefProcessMessage[] = "CefProcessMessage";
static const char __CefBrowserHost[]	= "CefBrowserHost";
static const char __CefRequestContext[]	= "CefRequestContext";
static const char __CefCommandLine[]	= "CefCommandLine";

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

// Task
static const char __CefTask[]		= "Task";
static const char __CefTaskRunner[] = "TaskRunner";



static const char *__web_plugin_unstable_callback__ = "WebPluginUnstableCallback";
static const char *__web_plugin_info__ = "WebPluginInfo";
static const char *__register_cdm_callback__ = "RegisterCDMCallback";
static const char *__web_plugin_info_visitor__ = "WebPluginInfoVisitor";

// browser_process_handler
static const char __browser_process_handler__[]		= "CefBrowserProcessHandler";
static const char __OnContextInitialized[]			= "OnContextInitialized";
static const char __OnBeforeChildProcessLaunch[]	= "OnBeforeChildProcessLaunch";
static const char __OnRenderProcessThreadCreated[]	= "OnRenderProcessThreadCreated";
static const char __OnScheduleMessagePumpWork[]		= "OnScheduleMessagePumpWork";
static const char __GetPrintHandler[]				= "GetPrintHandler";

// context_menu_handler
static const char *__Continueext_menu_handler__ = "ContextMenuHandler";
static const char *__Continueext_menu_params__ = "ContextMenuParams";
static const char *__run_context_menu_callback__ = "RunContextMenuCallback";
static const char *__OnBeforeContextMenu = "OnBeforeContextMenu";
static const char *__RunContextMenu = "RunContextMenu";
static const char *__OnContextMenuCommand = "OnContextMenuCommand";
static const char *__OnContextMenuDismissed = "OnContextMenuDismissed";

// menu_model
static const char __CefMenuModel[] = "CefMenuModel";

// menu_model_delegate
static const char __CefMenuModelDelegate[] = "CefMenuModelDelegate";

static const char __CefDialogHandler[] = "CefDialogHandler";
static const char __CefDisplayHandler[] = "CefDisplayHandler";

// drag_handler
static const char __CefDragHandler[] = "CefDragHandler";
static const char __OnDragEnter[] = "OnDragEnter";
static const char __OnDraggableRegionsChanged[] = "OnDraggableRegionsChanged";

// drag_data
static const char __CefDragData[] = "CefDragData";

static const char __CefFocusHandler[] = "CefFocusHandler";
static const char __CefGeolocationHandler[] = "CefGeolocationHandler";

// jsdialog_handler
static const char __CefJSDialogHandler[]		= "CefJSDialogHandler";
static const char __CefJSDialogCallback[]		= "CefJSDialogCallback";

static const char __CefKeyboardHandler[]		= "CefKeyboardHandler";
static const char __CefLifeSpanHandler[]		= "CefLifeSpanHandler";
static const char __CefLoadHandler[]			= "CefLoadHandler";
static const char __CefPrintHandler[]			= "CefPrintHandler";

static const char __CefRenderProcessHandler[]	= "CefRenderProcessHandler";
static const char __CefRequestContextHandler[] = "CefRequestContextHandler";
static const char __CefRequestHandler[]			= "c";
static const char __CefResourceBundleHandler[] = "CefResourceBundleHandler";
static const char __CefResourceHandler[]		= "CefResourceHandler";

// RenderHandler
static const char __CefRenderHandler[]				= "CefRenderHandler";
static const char __GetAccessibilityHandler[]		= "GetAccessibilityHandler";
static const char __GetRootScreenRect[]				= "GetRootScreenRect";
static const char __GetViewRect[]					= "GetViewRect";
static const char __GetScreenPoint[]				= "GetScreenPoint";
static const char __GetScreenInfo[]					= "GetScreenInfo";
static const char __OnPopupShow[]					= "OnPopupShow";
static const char __OnPopupSize[]					= "OnPopupSize";
static const char __OnPaint[]						= "OnPaint";
static const char __OnCursorChange[]				= "OnCursorChange";
static const char __StartDragging[]					= "StartDragging";
static const char __UpdateDragCursor[]				= "UpdateDragCursor";
static const char __OnScrollOffsetChanged[]			= "OnScrollOffsetChanged";
static const char __OnIMECompositionRangeChanged[]	= "OnIMECompositionRangeChanged";


static const char __CefTime[] = "CefTime";

static const char __CefEventHandle[] = "CefEventHandle";

// types
static const char __CefSettings[]					= "CefSettings";
static const char __CefRequestContextSettings[]	= "CefRequestContextSettings";
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


// Value
static const char __CefValue[] = "CefValue";
static const char __CefListValue[] = "CefListValue";
static const char __CefDictionaryValue[] = "CefDictionaryValue";


#endif
