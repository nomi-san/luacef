#pragma once
#include "../luacef.h"

void luacef_client_reg(lua_State* L);

static const char
	*__client__ = "Client",
	*_c_get_context_menu_handler	= "ContextMenuHandler",
	*_c_get_dialog_handler			= "DialogHandler",
	*_c_get_display_handler			= "DisplayHandler",
	*_c_get_download_handler		= "DownloadHandler",
	*_c_get_drag_handler			= "DragHandler",
	*_c_get_find_handler			= "FindHandler",
	*_c_get_focus_handler			= "FocusHandler",
	*_c_get_geolocation_handler		= "GeolocationHandler",
	*_c_get_jsdialog_handler		= "JSDialogHandler",
	*_c_get_keyboard_handler		= "KeyboardHandler",
	*_c_get_life_span_handler		= "LifeSpanHandler",
	*_c_get_load_handler			= "LoadHandler",
	*_c_get_render_handler			= "RenderHandler",
	*_c_get_request_handler			= "RequestHandler",
	*_c_on_process_message_received = "OnProcessMessageReceived";