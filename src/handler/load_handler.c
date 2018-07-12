#include "../luacef.h"

typedef struct luacef_load_handler {

	cef_base_t base;

	void (CEF_CALLBACK *on_loading_state_change)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		int							isLoading,
		int							canGoBack,
		int							canGoForward);

	void (CEF_CALLBACK *on_load_start)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		struct _cef_frame_t*		frame,
		cef_transition_type_t		transition_type);

	void (CEF_CALLBACK *on_load_end)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		struct _cef_frame_t*		frame,
		int							httpStatusCode);

	void (CEF_CALLBACK *on_load_error)(
		struct luacef_load_handler* self,
		struct _cef_browser_t*		browser,
		struct _cef_frame_t*		frame,
		cef_errorcode_t				errorCode,
		const cef_string_t*			errorText,
		const cef_string_t*			failedUrl);

	lua_State* L;
	int ref;

} luacef_load_handler;

const char  
	*_lh_on_loading_state_change	= "OnLoadingStateChange",
	*_lh_on_load_start				= "OnLoadStart",
	*_lh_on_load_end				= "OnLoadEnd",
	*_lh_on_load_error				= "OnLoadError";

void CEF_CALLBACK lh_on_loading_state_change(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	int							isLoading,
	int							canGoBack,
	int							canGoForward)
{

}

void CEF_CALLBACK lh_on_load_start(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	struct _cef_frame_t*		frame,
	cef_transition_type_t		transition_type)
{

}

void CEF_CALLBACK lh_on_load_end(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	struct _cef_frame_t*		frame,
	int							httpStatusCode)
{

}

void CEF_CALLBACK lh_on_load_error(
	struct luacef_load_handler* self,
	struct _cef_browser_t*		browser,
	struct _cef_frame_t*		frame,
	cef_errorcode_t				errorCode,
	const cef_string_t*			errorText,
	const cef_string_t*			failedUrl)
{

}