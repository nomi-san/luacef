#ifndef LUACEF_INCLUDE_H_
#define LUACEF_INCLUDE_H_
#pragma once

#ifdef _MSC_VER
#pragma warning(disable: 4273)
#pragma warning(disable: 4090)
#pragma warning(disable: 6011)
#pragma warning(disable: 6001)
#pragma warning(disable: 26451)
#pragma warning(disable: 28251)
#endif

#ifndef DLL_PUBLIC
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#else
#define DLL_PUBLIC
#endif
#endif
#endif

/*
	 __            _____ _____ _____ 
	|  |   _ _ ___|   __|   __|   __|
	|  |__| | | .'|  |__|   __|   __|
	|_____|___|__,|_____|_____|__|  
	<Lua bindings to Chromium Embedded Framework>

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "lua.h"
#include "lapi.h"
#include "lauxlib.h"

//////////////////////////////////////
#define	CEF_STRING_TYPE_UTF16 1 // cannot use utf8

#include "include/cef_version.h"
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_client_capi.h"
#include "include/internal/cef_types.h"

#include "luacef_api.h"

// string.c
const wchar_t *lua_towlstring(lua_State *L, int idx, int *len);
void lua_pushwstring(lua_State *L, wchar_t *ts);
void lua_clearwstring(wchar_t *ws);
void luacef_pushstring(lua_State* L, cef_string_t *s);
void luacef_pushstring_free(lua_State* L, cef_string_userfree_t s);
cef_string_t luacef_tostring(lua_State *L, int i);

#define lua_towstring(L, i) lua_towlstring(L, i, NULL)

// from chromium <= 52
typedef cef_base_ref_counted_t cef_base_t;

static lua_State* __mainState = NULL;

static const char __release__[] = "release";
static const char __index__[]	= "__index";
static const char __new__[]		= "new";

void* luacef_checkudata(lua_State* L, int i, const char* s);
void* luacef_touserdata(lua_State* L, int i);
void* luacef_newuserdata(lua_State* L, size_t sz);
void luacef_pushuserdata(lua_State* L, void* udata, const char* meta);

#define luacef_pushudata luacef_pushuserdata
#define luacef_toudata luacef_touserdata
#define luacef_newudata luacef_newuserdata

int luacef_release(lua_State* L);
int luacef_index(lua_State* L);
int luacef_newindex(lua_State* L);
int luacef_eq(lua_State* L);
int luacef_len(lua_State* L);
void luacef_error_index(lua_State* L, const char* index);

#define luacef_alloc(sz) (calloc(1, sz))
#define luacef_alloct(t) (calloc(1, sizeof(t)))
#define luacef_int long long
#define luacef_double double

#define LCEF_API(type, fn) \
	static int luacef_##type##_##fn(lua_State *L)

#define LCEF_API_N(type, fn) \
	luacef_##type##_##fn

#define LCEF_M(type, mname) \
	static const luaL_Reg luacef_##type##_##mname[] =

#define LUAREGEND \
	{ NULL, NULL }


#if LUA_VERSION_NUM == 501
int _lua_getfield(lua_State *L, int i, const char *k);
#define lua_getfield _lua_getfield

#define lua_rawlen(L, i) lua_objlen(L, i)
#define lua_getuservalue lua_getfenv
lua_isinteger(lua_State *L, int i);
void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup);
void luaL_setmetatable(lua_State *L, const char *tname);
#endif

#ifdef __cplusplus
}
#endif
#endif

/*/
/*      __         __  __     ______        ______     ______     ______
/*  __ /\ \ _____ /\ \/\ \ _ /\  __ \ ____ /\  ___\ _ /\  ___\ _ /\  ___\_
/*   __\ \ \___  _\ \ \_\ \ _\ \ \_\ \ ____\ \ \__/___\ \  __\ __\ \  __\__
/*    __\ \_____\ _\ \_____\ _\ \_\ \_\ ____\ \_____\ _\ \_____\ _\ \_\ ____
/*     __\/_____/___\/_____/___\/_/\/_/______\/_____/___\/_____/___\/_/______
/*
/*/