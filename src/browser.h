#pragma once

#include "luacef.h"
#include "include/cef_browser.h"

namespace LUACEF
{
	class BrowserHost;

	class Browser : public CefBrowser
	{
	public:
		static void __reg(lua_State *L);

	private:
		static int __index(lua_State *L);
		IMPLEMENT_REFCOUNTING(Browser);
	};

	class BrowserHost : public CefBrowserHost
	{
	public:
		static void __reg(lua_State *L);

	private:
		static int __index(lua_State *L);
		IMPLEMENT_REFCOUNTING(BrowserHost);
	};
}