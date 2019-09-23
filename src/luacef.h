#pragma once

#ifdef _MSC_VER
#pragma warning(disable: 4307)
#pragma warning(disable: 4996)
#endif

#include "ilua.h"
using namespace ILua;

#define LUACEF          luacef
#define LUACEF_API      extern "C" __declspec(dllexport)

#define LUACEF_CAST_PTR(dest, src) \
	dest = reinterpret_cast<decltype(dest)>(static_cast<void*>(src))

namespace LUACEF
{
	template <typename T>
	void pushUPtr(State& L, T uptr) {
		lua_State *state; T *p_uptr;
		if (uptr) {
			state = reinterpret_cast<lua_State*>(&L);
			p_uptr = reinterpret_cast<T*>(lua_newuserdata(state, sizeof(void*)));
			(*p_uptr) = uptr;
			luaL_setmetatable(state, uptr->__name);
		}
	}

	template <typename T>
	void pushUPtr(State& L, T uptr, const char *tname) {
		lua_State *state; T *p_uptr;
		if (uptr) {
			state = reinterpret_cast<lua_State*>(&L);
			p_uptr = reinterpret_cast<T*>(lua_newuserdata(state, sizeof(void*)));
			(*p_uptr) = uptr;
			luaL_setmetatable(state, tname);
		}
	}

	template <typename T>
	bool toUPtr(State& L, T& ref, int idx = 1) {
		lua_State *state; T *p_uptr;
		state = reinterpret_cast<lua_State*>(&L);
		if (!lua_isnoneornil(state, idx)) {
			p_uptr = reinterpret_cast<T*>(lua_touserdata(state, idx));
			if (p_uptr) {
				ref = *p_uptr;
				return true;
			}
		}
		return false;
	}

	template <typename T>
	void checkUPtr(State& L, T& ref, int idx) {
		lua_State *state; T *p_uptr;
		state = reinterpret_cast<lua_State*>(&L);
		p_uptr = reinterpret_cast<T*>(luaL_checkudata(state, idx, ref->__name));
		if (p_uptr) {
			ref = *p_uptr;
		}
	}




	static State *g_state;
}