#pragma once

#include "luacef.h"
#include "include/internal/cef_win.h"

LUACEF_SCOPE
{
	struct MainArgs : public CefMainArgs
	{
	public:
		MainArgs();
		MainArgs(HINSTANCE instance);
		~MainArgs();

	private:
		static int __index(lua_State *L);
		static int __newindex(lua_State *L);
		static int __gc(lua_State *L);
	};
}