#include "client.h"

LUACEF_USING;

Client::Client()
{
	this->L = lState;
}

Client::Client(lua_State *L)
{
	this->L = L;
}

Client::~Client()
{

}