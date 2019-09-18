#include "luacef.h"

using namespace luacef;

LUACEF_API int luaopen_luacef(lua_State *L)
{
	lState = L;

	return 0;
}