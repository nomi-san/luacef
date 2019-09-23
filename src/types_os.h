#pragma once

#include "luacef.h"
#include "include/internal/cef_win.h"

namespace LUACEF
{
	class MainArgs : public CefMainArgs
	{
	public:
		MainArgs() {}
		virtual ~MainArgs() {}

		static int __new(State& L);
		static int __index(State& L);
		static int __newindex(State& L);
		static int __gc(State& L);
		static void __reg(State& L);
	};

	class WindowInfo : public CefWindowInfo
	{
	public:
		WindowInfo() : CefWindowInfo() {}

		static int __new(State& L);
		static int __index(State& L);
		static int __newindex(State& L);
		static int __gc(State& L);
		static void __reg(State& L);

		static int __SetAsChild(State& L);
		static int __SetAsPopup(State& L);
		static int __SetAsWindowless(State& L);
	};
}