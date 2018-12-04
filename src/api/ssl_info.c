#include "../luacef.h"

#include "include/capi/cef_values_capi.h"
#include "include/capi/cef_x509_certificate_capi.h"

typedef struct luacef_sslinfo {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Returns a bitmask containing any and all problems verifying the server
	// certificate.
	///
	cef_cert_status_t(CEF_CALLBACK* get_cert_status)(struct _cef_sslinfo_t* self);

	///
	// Returns the X.509 certificate.
	///
	struct _cef_x509certificate_t*(CEF_CALLBACK* get_x509certificate)(
		struct _cef_sslinfo_t* self);
} luacef_sslinfo;

//#include "include/cef_ssl_info.h"





// static function ==========================================

/*
	<bool> IsCertStatusError(
		<int> status
	)
*/
static int luacef_IsCertStatusError(lua_State* L)
{
	cef_cert_status_t stt = luaL_checkinteger(L, 1);

	lua_pushboolean(L, cef_is_cert_status_error(stt));
	return 1;
}

/*
	<bool> IsCertStatusMinorError(
		<int> status
	)
*/
static int luacef_IsCertStatusMinorError(lua_State* L)
{
	cef_cert_status_t stt = luaL_checkinteger(L, 1);

	lua_pushboolean(L, cef_is_cert_status_minor_error(stt));
	return 1;
}

// ==================================================

// ==================================================

void luacef_SSLInfo(lua_State *L)
{

	lua_pushcfunction(L, luacef_IsCertStatusError);
	lua_setfield(L, -2, "IsCertStatusError");

	lua_pushcfunction(L, luacef_IsCertStatusMinorError);
	lua_setfield(L, -2, "IsCertStatusMinorError");
}