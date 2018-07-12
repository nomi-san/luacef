#include "../luacef_api.h"

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