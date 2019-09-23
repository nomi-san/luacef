#pragma once

#include "luacef.h"
#include "include/internal/cef_string.h"

namespace LUACEF
{
	class String : public CefString
	{
	public:



		uint32_t hash();

	};
}