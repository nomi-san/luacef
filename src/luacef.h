#pragma once

#include "compat-5.3.h"
#include "include/cef_base.h"

#define LUACEF          luacef
#define LUACEF_API      extern "C" __declspec(dllexport)
#define LUACEF_SCOPE    namespace LUACEF
#define LUACEF_USING    using namespace LUACEF

LUACEF_SCOPE
{
	static lua_State *lState;

	static void* newUPtr(lua_State* L, size_t sz)
	{
		void **ud = (void**)lua_newuserdata(L, sizeof(void*));
		*ud = calloc(1, sz);
		return *ud;
	}

	static void* checkUPtr(lua_State* L, int i, const char* s)
	{
		if (lua_isnoneornil(L, i)) return NULL;
		void **ud = (void**)luaL_checkudata(L, i, s);
		if (!ud || !*ud) return NULL;
		return *ud;
	}

	static void* toUPtr(lua_State* L, int i)
	{
		if (lua_isnoneornil(L, i)) return NULL;
		void **ud = (void**)lua_touserdata(L, i);
		if (!ud || !*ud) return NULL;
		return *ud;
	}

	static void pushUPtr(lua_State* L, void* udata, const char* meta)
	{
		if (!udata) return;
		void** ud = (void**)lua_newuserdata(L, 4u);
		*ud = udata;
		luaL_setmetatable(L, meta);
	}

	template <typename T>
	void pushUPtr_(lua_State* L, T* uptr, const char* meta)
	{
		if (!uptr) return;
		T** puptr = reinterpret_cast<T**>(lua_newuserdata(L, sizeof(void*)));
		(*puptr) = uptr;
		luaL_setmetatable(L, meta);
	}

	template <typename T>
	void pushUPtr_(lua_State* L, CefRefPtr<T*> uptr, const char* meta)
	{
		if (!uptr) return;
		CefRefPtr<T*> *puptr = reinterpret_cast<CefRefPtr<T*>*>(lua_newuserdata(L, sizeof(void*)));
		(*puptr) = uptr;
		luaL_setmetatable(L, meta);
	}
}