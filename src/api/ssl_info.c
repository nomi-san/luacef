#include "../luacef.h"
#include "include/capi/cef_ssl_info_capi.h"

#define API(fn) \
	LCEF_API(SSLInfo, fn)

#define API_N(fn) \
	LCEF_API_N(SSLInfo, fn)

#define API_M(mname) \
	LCEF_M(SSLInfo, mname)

#define SELF luacef_SSLInfo

typedef cef_sslinfo_t  SELF;


API(GetCertStatus)
{
	SELF *p = luacef_toudata(L, 1);

	cef_cert_status_t ret = p->get_cert_status(p);

	lua_pushinteger(L, ret);
	return 1;
}

API(GetX509Certificate)
{
	SELF *p = luacef_toudata(L, 1);

	cef_x509certificate_t *ret = p->get_x509certificate(p);

	luacef_pushudata(L, ret, __CefX509Certificate);
	return 1;
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

API_M(meta)
{
	{ "GetCertStatus", API_N(GetCertStatus) },
	{ "GetX509Certificate", API_N(GetX509Certificate) },

	{ "__len", API_N(len) },
	{ "__unm", API_N(unm) },

	{ NULL, NULL }
};

// static functions ==========================================

/*
	<int> IsCertStatusError(
		<int> status
	)
*/
static int luacef_IsCertStatusError(lua_State* L)
{
	cef_cert_status_t stt = lua_tointeger(L, 1);

	int ret = cef_is_cert_status_error(stt);

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<int> IsCertStatusMinorError(
		<int> status
	)
*/
static int luacef_IsCertStatusMinorError(lua_State* L)
{
	cef_cert_status_t stt = lua_tointeger(L, 1);

	int ret = cef_is_cert_status_minor_error(stt);

	lua_pushinteger(L, ret);
	return 1;
}

// ==================================================

void API_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, "CefSSLInfo");
	luaL_setfuncs(L, API_N(meta), 0);
	lua_setfield(L, -1, __index__);

	lua_pushcfunction(L, luacef_IsCertStatusError);
	lua_setfield(L, -2, "IsCertStatusError");

	lua_pushcfunction(L, luacef_IsCertStatusMinorError);
	lua_setfield(L, -2, "IsCertStatusMinorError");
}