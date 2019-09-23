#include "luacef.h"
#include "app.h"
#include "client.h"
#include "life_span_hadler.h"
#include "types_os.h"

using namespace LUACEF;

LUACEF_API int luaopen_luacef(State& L)
{
	g_state = &L;

	L.newTable();

	App::__reg(L);
	//Client::__reg(L);
	//LifeSpanHandler::__reg(L);
	//MainArgs::__reg(L);

	

	return 1;
}