#pragma once

#include "luacef.h"
#include "include/internal/cef_types_wrappers.h"

namespace LUACEF
{
	struct Settings : public CefSettings
	{
	public:
		static void __reg(State& L);
	private:
		static int __new(State& L);
		static int __index(State& L);
		static int __newindex(State& L);
		static int __gc(State& L);
	};
}