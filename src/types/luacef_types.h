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
static const char *__state__ = "State";
static const char *__request__ = "Request";
static const char *__domvisitor__ = "DOMVisitor";
static const char *__string_visitor__ = "StringVisitor";
static const char *__v8context__ = "V8Context";
static const char *__process_message__ = "ProcessMessage";
static const char *__browser_host__ = "BrowserHost";