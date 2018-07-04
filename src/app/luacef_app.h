#pragma once

#include "../luacef.h"
#include "include/capi/cef_app_capi.h"
#include "../handler/luacef_resource_bunble_handler.h"
#include "../handler/luacef_browser_process_handler.h"
#include "../handler/luacef_render_process_handler.h"

static const char *__app__ = "app";
void luacef_app_reg(lua_State* L);