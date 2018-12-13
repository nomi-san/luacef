#include "../luacef.h"
#include "include/capi/cef_dialog_handler_capi.h"

#define SELF luacef_DialogHandler

typedef struct SELF {

	cef_dialog_handler_t self;

	lua_State *L; // state
	int ref; // table ref

} SELF;

#define API(fn) \
	LCEF_API(DialogHandler, fn)

#define API_N(fn) \
	LCEF_API_N(DialogHandler, fn)

#define API_M(mname) \
	LCEF_M(DialogHandler, mname)

// callback =========================

int CEF_CALLBACK API_N(OnFileDialog)(
	SELF* self,
	struct _cef_browser_t* browser,
	cef_file_dialog_mode_t mode,
	const cef_string_t* title,
	const cef_string_t* default_file_path,
	cef_string_list_t accept_filters,
	int selected_accept_filter,
	struct _cef_file_dialog_callback_t* callback)
{

	return 0;
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

	LUAREGEND
};

void API_N(reg)()
{

}