#ifndef LUACEF_INCLUDE_H_
#define LUACEF_INCLUDE_H_
#pragma once

#ifdef _MSC_VER
#pragma warning( disable : 4273)
#pragma warning( disable : 4090)
#pragma warning( disable : 6011)
#pragma warning( disable : 6001)
#pragma warning( disable : 26451)
#pragma warning( disable : 28251)
#endif

/*
	 __            _____ _____ _____ 
	|  |   _ _ ___|   __|   __|   __|
	|  |__| | | .'|  |__|   __|   __|
	|_____|___|__,|_____|_____|__|  
	< Chromium Embedded Framework for Lua >

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
#define	CEF_STRING_TYPE_UTF16 1

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

static const char *__release__ = "release";
static const char *__index__ = "__index";
static const char *__new__ = "new";

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

#ifndef EXPORT
#if defined(_MSC_VER)
#define EXPORT(t) __declspec(dllexport) t
#define IMPORT(t) __declspec(dllimport) t
#elif defined(__GNUC__)
#define EXPORT(t) __attribute__((visibility("default"))) t
#define IMPORT(t) t
#else
#define EXPORT(t) t
#define IMPORT(t) t
#pragma warning Unknown dynamic link import/export semantics.
#endif
#endif


#define LCEF_API(type, fn) \
	static int luacef_##type##_##fn(lua_State *L)

#define LCEF_API_N(type, fn) \
	luacef_##type##_##fn

#define LCEF_M(type, mname) \
	static const luaL_Reg luacef_##type##_##mname[] =

#define LUAREGEND \
	{ NULL, NULL }

#ifdef __cplusplus
}
#endif
#endif
