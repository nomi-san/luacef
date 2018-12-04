#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"

//    _       _ _     _            _             _ _         
//   |_|___ _| |_|___| |___ ___   | |_ ___ ___ _| | |___ ___ 
//   | |_ -| . | | .'| | . | . |  |   | .'|   | . | | -_|  _|
//  _| |___|___|_|__,|_|___|_  |  |_|_|__,|_|_|___|_|___|_|  
//=|___|===================|___|==============================


static const char *__OnJSDialog = "OnJSDialog";
static const char *__OnBeforeUnloadDialog = "OnBeforeUnloadDialog";
static const char *__OnResetDialogState = "OnResetDialogState";
static const char *__OnDialogClosed = "OnDialogClosed";

// jsdialog_callback ===============================================

static int luacef_JSDialogCallback_Continue(lua_State *L)
{
	cef_jsdialog_callback_t *p = luacef_touserdata(L, 1);
	int success = lua_tointeger(L, 2);
	const cef_string_t user_input = luacef_tostring(L, 3);

	p->cont(p, success, &user_input);

	return 0;
}

static int luacef_JSDialogCallback_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(cef_jsdialog_callback_t));
	return 1;
}

static const luaL_Reg luacef_JSDialogCallback_m[] = {
	{ "Continue", luacef_JSDialogCallback_Continue },
	{ "__len", luacef_JSDialogCallback_len },
	{ NULL, NULL }
};

// jsdialog_handler =====================================

// implement

typedef struct luacef_JSDialogHandler {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* on_jsdialog)(struct luacef_JSDialogHandler* self,
		struct _cef_browser_t* browser,
		const cef_string_t* origin_url,
		cef_jsdialog_type_t dialog_type,
		const cef_string_t* message_text,
		const cef_string_t* default_prompt_text,
		struct _cef_jsdialog_callback_t* callback,
		int* suppress_message);

	int(CEF_CALLBACK* on_before_unload_dialog)(
		struct luacef_JSDialogHandler* self,
		struct _cef_browser_t* browser,
		const cef_string_t* message_text,
		int is_reload,
		struct _cef_jsdialog_callback_t* callback);

	void(CEF_CALLBACK* on_reset_dialog_state)(
		struct luacef_JSDialogHandler* self,
		struct _cef_browser_t* browser);

	void(CEF_CALLBACK* on_dialog_closed)(struct luacef_JSDialogHandler* self,
		struct _cef_browser_t* browser);

	lua_State *L;
	int ref;

} luacef_JSDialogHandler;

/*
	<int> JSDialogHandler:OnJSDialog(
		<Browser> browser,
		<str> origin_url,
		<int> dialog_type,
		<str> message_text,
		<str> default_prompt_text,
		<JSDialogCallback> callback,
		<int*> suppress_message
	)
*/
int CEF_CALLBACK luacef_JSDialogHandler_OnJSDialog(
	struct luacef_JSDialogHandler* self,
	struct _cef_browser_t* browser,
	const cef_string_t* origin_url,
	cef_jsdialog_type_t dialog_type,
	const cef_string_t* message_text,
	const cef_string_t* default_prompt_text,
	struct _cef_jsdialog_callback_t* callback,
	int* suppress_message)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnJSDialog)) {

		luacef_pushuserdata(self->L, self, __jsdialog_handler__); // 1, self
		luacef_pushuserdata(self->L, browser, __browser__); // 2
		luacef_pushstring(self->L, origin_url); // 3
		lua_pushinteger(self->L, dialog_type); // 4
		luacef_pushstring(self->L, message_text); // 5
		luacef_pushstring(self->L, default_prompt_text); // 6
		luacef_pushuserdata(self->L, callback, __jsdialog_callback__); // 7
		luacef_pushuserdata(self->L, suppress_message, __int_ptr__); // 8

		lua_pcall(self->L, 8, 1, 0);
		lua_pop(self->L, 1);
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

/*
	<int> JSDialogHandler:OnBeforeUnloadDialog(
		<Browser> browser,
		<str> message_text,
		<int> is_reload,
		<JSDialogCallback> callback
	)
*/
int CEF_CALLBACK luacef_JSDialogHandler_OnBeforeUnloadDialog(
	struct luacef_JSDialogHandler* self,
	struct _cef_browser_t* browser,
	const cef_string_t* message_text,
	int is_reload,
	struct _cef_jsdialog_callback_t* callback)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeUnloadDialog)) {

		luacef_pushuserdata(self->L, self, __jsdialog_handler__); // 1, self
		luacef_pushuserdata(self->L, browser, __browser__); // 2
		luacef_pushstring(self->L, message_text); // 3
		lua_pushinteger(self->L, is_reload); // 4
		luacef_pushuserdata(self->L, callback, __jsdialog_callback__); // 5

		lua_pcall(self->L, 5, 1, 0);
		lua_pop(self->L, 1);
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

/*
	<void> JSDialogHandler:OnResetDialogState(
		<Browser> browser
	)
*/
void CEF_CALLBACK luacef_JSDialogHandler_OnResetDialogState(
	struct luacef_JSDialogHandler* self,
	struct _cef_browser_t* browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnResetDialogState)) {

		luacef_pushuserdata(self->L, self, __jsdialog_handler__); // 1, self
		luacef_pushuserdata(self->L, browser, __browser__); // 2

		lua_pcall(self->L, 2, 0, 0);
		lua_pop(self->L, 1);
	}
}

/*
	<void> JSDialogHandler:OnDialogClosed(
		<Browser> browser
	)
*/
void CEF_CALLBACK luacef_JSDialogHandler_OnDialogClosed(
	struct luacef_JSDialogHandler* self,
	struct _cef_browser_t* browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnDialogClosed)) {

		luacef_pushuserdata(self->L, self, __jsdialog_handler__); // 1, self
		luacef_pushuserdata(self->L, browser, __browser__); // 2

		lua_pcall(self->L, 2, 0, 0);
		lua_pop(self->L, 1);
	}
}

static int luacef_JSDialogHandler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_JSDialogHandler);
	luacef_JSDialogHandler *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnJSDialog))
			p->on_jsdialog = !lua_isfunction(L, -1) ? NULL : luacef_JSDialogHandler_OnJSDialog;

		if (lua_getfield(L, 1, __OnBeforeUnloadDialog))
			p->on_before_unload_dialog = !lua_isfunction(L, -1) ? NULL : luacef_JSDialogHandler_OnBeforeUnloadDialog;

		if (lua_getfield(L, 1, __OnDialogClosed))
			p->on_dialog_closed = !lua_isfunction(L, -1) ? NULL : luacef_JSDialogHandler_OnDialogClosed;

		if (lua_getfield(L, 1, __OnResetDialogState))
			p->on_reset_dialog_state = !lua_isfunction(L, -1) ? NULL : luacef_JSDialogHandler_OnResetDialogState;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __jsdialog_handler__);
	return 1;
}

static int luacef_JSDialogHandler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_JSDialogHandler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_JSDialogHandler_index(lua_State *L)
{
	luacef_JSDialogHandler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_JSDialogHandler_release);

	else if (!strcmp(i, __OnJSDialog))
		lua_getfield(L, -1, __OnJSDialog);

	else if (!strcmp(i, __OnBeforeUnloadDialog))
		lua_getfield(L, -1, __OnBeforeUnloadDialog);

	else if (!strcmp(i, __OnDialogClosed))
		lua_getfield(L, -1, __OnDialogClosed);

	else if (!strcmp(i, __OnResetDialogState))
		lua_getfield(L, -1, __OnResetDialogState);

	else return 0;

	return 1;
}

static int luacef_JSDialogHandler_newindex(lua_State *L)
{
	luacef_JSDialogHandler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnJSDialog)) {
		lua_setfield(L, -2, __OnJSDialog);
		p->on_jsdialog = luacef_JSDialogHandler_OnJSDialog;
	}

	else if (!strcmp(i, __OnBeforeUnloadDialog)) {
		lua_setfield(L, -2, __OnBeforeUnloadDialog);
		p->on_jsdialog = luacef_JSDialogHandler_OnBeforeUnloadDialog;
	}

	else if (!strcmp(i, __OnDialogClosed)) {
		lua_setfield(L, -2, __OnDialogClosed);
		p->on_jsdialog = luacef_JSDialogHandler_OnDialogClosed;
	}

	else if (!strcmp(i, __OnResetDialogState)) {
		lua_setfield(L, -2, __OnResetDialogState);
		p->on_jsdialog = luacef_JSDialogHandler_OnResetDialogState;
	}

	return 0;
}

static int luacef_JSDialogHandler_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(luacef_JSDialogHandler));
	return 1;
}

static const luaL_Reg luacef_JSDialogHandler_m[] = {
	{ "__index", luacef_JSDialogHandler_index },
	{ "__newindex", luacef_JSDialogHandler_newindex },
	{ "__len", luacef_JSDialogHandler_len },
	{ "__eq", luacef_eq},
	{ NULL, NULL }
};

// register ============================================

void luacef_JSDialogHandler_reg(lua_State *L)
{
	luaL_newmetatable(L, __jsdialog_callback__);
	luaL_setfuncs(L, luacef_JSDialogCallback_m, 0);
	lua_setfield(L, -1, __index__);
	
	luaL_newmetatable(L, __jsdialog_handler__);
	luaL_setfuncs(L, luacef_JSDialogHandler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_JSDialogHandler_new);
	lua_setfield(L, -2, "newJSDialogHandler");
}