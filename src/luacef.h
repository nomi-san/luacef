#pragma once

#ifdef BUILD_AS_DLL
#define LUACEF_API __declspec(dllexport)
#else
#define LUACEF_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lapi.h"
#include "lauxlib.h"

/////////////////////////
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_client_capi.h"

#include "app/luacef_app.h"
#include "base/luacef_base.h"
#include "client/luacef_client.h"

#include "string/luacef_string.h"
#include "types/luacef_types.h"
#include "handler/luacef_handler.h"

#ifdef __cplusplus
}
#endif

#define PLS lua_State*
static lua_State* __mainState = NULL;
static int __interpreter = 0;

static const char* __release__ = "release";
static const char* __index__ = "__index";

void* luacef_checkudata(lua_State* L, int i, const char* s);
void* luacef_touserdata(lua_State* L, int i);
void* luacef_newuserdata(lua_State* L, size_t sz);
void* luacef_pushuserdata(lua_State* L, void* udata, const char* meta);

int luacef_release(lua_State* L);
int luacef_index(lua_State* L);
int luacef_newindex(lua_State* L);
void luacef_error_index(lua_State* L, const char* index);

static const luaL_Reg luacef_rl_gc[] = {
	//{ "__index",	luacef_index },
	//{ "__newindex", luacef_newindex },
	{ "__gc", luacef_release },
	{ "release", luacef_release }, // hand release
	{NULL, NULL}
};

