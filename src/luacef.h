#pragma once

/*
     _         
    | |_ _ ___
    | | | | _ |/
    |_|___|_|_|/              _
         ___| |_ __ ___ _____|_|_ _ _____
        |  _|   | _| _ |     | | | |     ||
        |___|_|_|_||___|_|_|_|_|___|_|_|_||     _
                ___ _____| |_ ___ _| |_| |___ _| ||
               | -_|     | _ | -_| _ | _ | -_| _ ||
               |___|_|_|_|___|___|___|___|___|___||    _ 
                      | _|_ ___ _____ ___ _ _ _ ___ __| |__
                      | | _| _ |     | -_| | | | _ | _| _//
                      |_|_||_|_|_|_|_|___|_____|___|_||_|\/

		-- Chromium Embedded Framework for Lua --
*/

#ifdef BUILD_AS_DLL
#define LUACEF_API __declspec(dllexport)
#else
#define LUACEF_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "lua.h"
#include "lapi.h"
#include "lauxlib.h"

//////////////////////////////////////
#include "include/cef_version.h"
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_client_capi.h"
#include "include/internal/cef_types.h""

#include "luacef_string.h"
#include "luacef_api.h"

#include "types/luacef_types.h"
#include "handler/luacef_handler.h"

#ifdef __cplusplus
}
#endif

// from chromium 52 :))
typedef cef_base_ref_counted_t cef_base_t;

static lua_State* __mainState = NULL;
static int __interpreter = 0; // for fix visible window on windows

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

#define luacef_alloc(sz) (calloc(1, sz))
#define luacef_free(p) (free(*(void**)p)