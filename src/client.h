#pragma once

#include "luacef.h"
#include "include/cef_client.h"

LUACEF_SCOPE
{
	class Client : public CefClient
	{
	public:
		Client();
		Client(lua_State *L);
		virtual ~Client();

	private:
		lua_State *L;
		IMPLEMENT_REFCOUNTING(Client);
	};
}