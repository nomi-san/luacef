#include "../luacef.h"
#include "include/capi/cef_display_handler_capi.h"

#define SELF luacef_DisplayHandler

typedef struct SELF {

	cef_display_handler_t self;

	lua_State *L; // state
	int ref; // table ref

} SELF;

#define API(fn) \
	LCEF_API(DisplayHandler, fn)

#define API_N(fn) \
	LCEF_API_N(DisplayHandler, fn)

#define API_M(mname) \
	LCEF_M(DisplayHandler, mname)

// callback =========================

void CEF_CALLBACK API_N(OnAddressChange)(SELF* self,
	struct _cef_browser_t* browser,
	struct _cef_frame_t* frame,
	const cef_string_t* url)
{

}

void CEF_CALLBACK API_N(OnTitleChange)(SELF* self,
	struct _cef_browser_t* browser,
	const cef_string_t* title)
{

}

void CEF_CALLBACK API_N(OnFaviconURLChange)(SELF* self,
	struct _cef_browser_t* browser,
	cef_string_list_t icon_urls)
{

}

void CEF_CALLBACK API_N(OnFullscreenModeChange)(
	SELF* self,
	struct _cef_browser_t* browser,
	int fullscreen)
{

}

int CEF_CALLBACK API_N(OnTooltip)(SELF* self,
	struct _cef_browser_t* browser,
	cef_string_t* text)
{

}

void CEF_CALLBACK API_N(OnStatusMessage)(SELF* self,
	struct _cef_browser_t* browser,
	const cef_string_t* value)
{

}

int CEF_CALLBACK API_N(OnConsoleMessage)(SELF* self,
	struct _cef_browser_t* browser,
	const cef_string_t* message,
	const cef_string_t* source,
	int line)
{

}

// api =========================

API(new)
{

}

API(index)
{

}

API(newindex)
{

}

API(len)
{

}

API(unm)
{

}

API_M(meta)
{

	{ NULL, NULL }
};

void API_N(reg)()
{

}