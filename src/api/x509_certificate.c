#include "../luacef.h"
#include "include/capi/cef_x509_certificate_capi.h"

// X509CertPrincipal
// ==================================================

#define SELF luacef_X509CertPrincipal

typedef cef_x509cert_principal_t SELF;

#define API(fn) \
	LCEF_API(X509CertPrincipal, fn)

#define API_N(fn) \
	LCEF_API_N(X509CertPrincipal, fn)

#define API_M(mname) \
	LCEF_M(X509CertPrincipal, mname)

// api =========================

API(GetDisplayName)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_userfree_t ret = p->get_display_name(p);

	luacef_pushstring_free(L, ret);
	return 1;
}

API(GetCommonName)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_userfree_t ret = p->get_common_name(p);

	luacef_pushstring_free(L, ret);
	return 1;
}


API(GetLocalityName)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_userfree_t ret = p->get_locality_name(p);

	luacef_pushstring_free(L, ret);
	return 1;
}

API(GetStateOrProvinceName)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_userfree_t ret = p->get_state_or_province_name(p);

	luacef_pushstring_free(L, ret);
	return 1;
}

API(GetCountryName)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_userfree_t ret = p->get_country_name(p);

	luacef_pushstring_free(L, ret);
	return 1;
}

API(GetStreetAddresses)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_list_t ret = cef_string_list_alloc();
	p->get_street_addresses(p, ret);

	luacef_pushudata(L, ret, __string_list__);
	return 1;
}

API(GetOrganizationNames)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_list_t ret = cef_string_list_alloc();
	p->get_organization_names(p, ret);

	luacef_pushudata(L, ret, __string_list__);
	return 1;
}

API(GetOrganizationUnitNames)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_list_t ret = cef_string_list_alloc();
	p->get_organization_unit_names(p, ret);

	luacef_pushudata(L, ret, __string_list__);
	return 1;
}

API(GetDomainComponents)
{
	SELF *p = luacef_toudata(L, 1);

	cef_string_list_t ret = cef_string_list_alloc();
	p->get_domain_components(p, ret);

	luacef_pushudata(L, ret, __string_list__);
	return 1;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

API_M(meta)
{
	{ "GetDisplayName",			API_N(GetDisplayName) },
	{ "GetCommonName",			API_N(GetCommonName) },
	{ "GetLocalityName",		API_N(GetLocalityName) },
	{ "GetStateOrProvinceName", API_N(GetStateOrProvinceName) },
	{ "GetCountryName",			API_N(GetCountryName) },
	{ "GetStreetAddresses",		API_N(GetStreetAddresses) },
	{ "GetOrganizationNames",	API_N(GetOrganizationNames) },
	{ "GetOrganizationUnitNames", API_N(GetOrganizationUnitNames) },
	{ "GetDomainComponents",	API_N(GetDomainComponents) },

	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },

	LUAREGEND
};

#undef SELF
#undef API
#undef API_N
#undef API_M

// X509Certificate
// ==================================================

#define SELF luacef_X509Certificate

typedef cef_x509certificate_t SELF;

#define API(fn) \
	LCEF_API(X509Certificate, fn)

#define API_N(fn) \
	LCEF_API_N(X509Certificate, fn)

#define API_M(mname) \
	LCEF_M(X509Certificate, mname)

// api =========================

API(GetSubject)
{
	SELF *p = luacef_toudata(L, 1);

	cef_x509cert_principal_t *ret = p->get_subject(p);
	
	luacef_pushudata(L, ret, __CefX509CertPrincipal);
	return 1;
}

API(GetIssuer)
{
	SELF *p = luacef_toudata(L, 1);

	cef_x509cert_principal_t *ret = p->get_issuer(p);

	luacef_pushudata(L, ret, __CefX509CertPrincipal);
	return 1;
}

API(GetSerialNumber)
{
	SELF *p = luacef_toudata(L, 1);

	cef_binary_value_t *ret = p->get_serial_number(p);

	luacef_pushudata(L, ret, __CefBinaryValue);
	return 1;
}

API(GetValidStart)
{
	SELF *p = luacef_toudata(L, 1);

	// todo
	//cef_binary_value_t *ret = p->get_valid_start(p);

	//luacef_pushudata(L, ret, __CefBinaryValue);
	return 1;
}

API(GetValidExpiry)
{
	SELF *p = luacef_toudata(L, 1);

	// todo
	//cef_binary_value_t *ret = p->get_valid_expiry(p);

	//luacef_pushudata(L, ret, __CefBinaryValue);
	return 1;
}

API(GetDerencoded)
{
	SELF *p = luacef_toudata(L, 1);

	cef_binary_value_t *ret = p->get_derencoded(p);

	luacef_pushudata(L, ret, __CefBinaryValue);
	return 1;
}

API(GetPemencoded)
{
	SELF *p = luacef_toudata(L, 1);

	cef_binary_value_t *ret = p->get_pemencoded(p);

	luacef_pushudata(L, ret, __CefBinaryValue);
	return 1;
}

API(GetIssuerChainSize)
{
	SELF *p = luacef_toudata(L, 1);

	size_t ret = p->get_issuer_chain_size(p);

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<void> X509Certificate:GetDerencodedIssuerChain(
		<IntPtr> chainCount,
		<PtrPtr> chain -- pointer to pointer of CefBinaryValue
	)
*/
API(GetDerencodedIssuerChain)
{
	SELF *p = luacef_toudata(L, 1);
	size_t *chainCount = luacef_toudata(L, 2);
	cef_binary_value_t** chain = luacef_toudata(L, 3);

	p->get_derencoded_issuer_chain(
		p,
		chainCount,
		chain
	);

	return 0;
}

/*
	<void> X509Certificate:GetPemencodedIssuerChain(
		<IntPtr> chainCount,
		<PtrPtr> chain -- pointer to pointer of CefBinaryValue
	)
*/
API(GetPemencodedIssuerChain)
{
	SELF *p = luacef_toudata(L, 1);
	size_t *chainCount = luacef_toudata(L, 2);
	cef_binary_value_t** chain = luacef_toudata(L, 3);

	p->get_pemencoded_issuer_chain(
		p,
		chainCount,
		chain
	);

	return 0;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

API_M(meta)
{
	{ "GetSubject", API_N(GetSubject) },
	{ "GetIssuer", API_N(GetIssuer) },
	{ "GetSerialNumber", API_N(GetSerialNumber) },
	{ "GetValidStart", API_N(GetValidStart) },
	{ "GetValidExpiry", API_N(GetValidExpiry) },
	{ "GetDerencoded", API_N(GetDerencoded) },
	{ "GetPemencoded", API_N(GetPemencoded) },
	{ "GetIssuerChainSize", API_N(GetIssuerChainSize) },
	{ "GetDerencodedIssuerChain", API_N(GetDerencodedIssuerChain) },
	{ "GetPemencodedIssuerChain", API_N(GetPemencodedIssuerChain) },

	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },

		LUAREGEND
};




void API_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, __CefX509CertPrincipal);
	luaL_setfuncs(L, LCEF_API_N(X509CertPrincipal, meta), 0);
	lua_setfield(L, -1, __index__);

	luaL_newmetatable(L, __CefX509Certificate);
	luaL_setfuncs(L, LCEF_API_N(X509Certificate, meta), 0);
	lua_setfield(L, -1, __index__);
}
