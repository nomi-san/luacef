#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"

// implement

typedef struct lua_geolocation_callback {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* cont)(struct _cef_geolocation_callback_t* self, int allow);

} lua_geolocation_callback;

typedef struct luacef_geolocation_handler {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* on_request_geolocation_permission)(
		struct _cef_geolocation_handler_t* self,
		struct _cef_browser_t* browser,
		const cef_string_t* requesting_url,
		int request_id,
		struct _cef_geolocation_callback_t* callback);

	void(CEF_CALLBACK* on_cancel_geolocation_permission)(
		struct _cef_geolocation_handler_t* self,
		struct _cef_browser_t* browser,
		int request_id);

} luacef_geolocation_handler;
