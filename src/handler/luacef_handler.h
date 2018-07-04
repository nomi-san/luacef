#pragma once
#include "../luacef.h"

static const char *__browser_process_handler__	= "BrowserProcessHandler";
static const char *__context_menu_handler__		= "ContextMenuHandler";
static const char *__dialog_handler__			= "DialogHandler";
static const char *__display_handler__			= "DisplayHandler";
static const char *__download_handler__			= "DownloadHandler";
static const char *__drag_handler__				= "DragHandler";
static const char *__find_handler__				= "FindHandler";
static const char *__focus_handler__			= "FocusHandler";
static const char *__geolocation_handler__		= "GeolocationHandler";
static const char *__jsdialog_handler__			= "JsDialogHandler";
static const char *__keyboard_handler__			= "KeyboardHandler";
static const char *__life_span_handler__		= "LifeSpanHandler";
static const char *__load_handler__				= "LoadHandler";
static const char *__print_handler__			= "PrintHandler";
static const char *__render_handler__			= "RenderHandler";
static const char *__render_process_handler__	= "RenderProcess_handler";
static const char *__request_context_handler__	= "RequestContextHandler";
static const char *__request_handler__			= "RequestHandler";
static const char *__resource_bundle_handler__	= "ResourceBundleHandler";
static const char *__resource_handler__			= "ResourceHandler";

void luacef_life_span_handler_reg(lua_State* L);

static void luacef_handler_reg(lua_State* L)
{
	luacef_life_span_handler_reg(L);
}