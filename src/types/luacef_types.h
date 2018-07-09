#pragma once

#include "../luacef.h"

void luacef_types_reg(lua_State* L);
void luacef_funcs_reg(lua_State* L);

void luacef_frame_reg(lua_State* L);
void luacef_browser_reg(lua_State* L);

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
static const char *__v8accessor__				= "V8Accessor";
static const char *__v8_accesscontrol__			= "V8Accesscontrol";
static const char *__v8context__				= "V8Context";
static const char *__v8exception__				= "V8Exception";
static const char *__v8handler__				= "V8Handler";
static const char *__v8_propertyattribute__		= "V8Propertyattribute";
static const char *__v8stack_frame__			= "V8StackFrame";
static const char *__v8stack_trace__			= "V8StackTrace";
static const char *__v8value__					= "V8Value";

static const char *__list_value__ = "ListValue";
static const char *__popup_features__ = "PopupFeatures";

static const char *__web_plugin_unstable_callback__ = "WebPluginUnstableCallback";
static const char *__web_plugin_info__ = "WebPluginInfo";
static const char *__register_cdm_callback__ = "RegisterCDMCallback";

cef_cookie_t;
cef_cookie_visitor_t;
cef_cookie_manager_t;