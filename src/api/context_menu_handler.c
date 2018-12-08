#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_frame_capi.h"
#include "include/capi/cef_menu_model_capi.h"

//              _           _                           _             _ _         
//  ___ ___ ___| |_ ___ _ _| |_    _____ ___ ___ _ _   | |_ ___ ___ _| | |___ ___ 
// |  _| . |   |  _| -_|_'_|  _|  |     | -_|   | | |  |   | .'|   | . | | -_|  _|
// |___|___|_|_|_| |___|_,_|_|    |_|_|_|___|_|_|___|  |_|_|__,|_|_|___|_|___|_|  
//=================================================================================
/*
	<RunContextMenuCallback>
	<ContextMenuHandler>
	<ContextMenuParams>
	<ContextMenuHandler> newContextMenuHandler()
*/

// run_context_menu_callback ===============================

static luacef_RunContextMenuCallback_Continue(lua_State *L)
{
	cef_run_context_menu_callback_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	cef_event_flags_t event_flags = lua_tointeger(L, 3);

	p->cont(p, command_id, event_flags);

	return 0;
}

static luacef_RunContextMenuCallback_Cancel(lua_State *L)
{
	cef_run_context_menu_callback_t *p = luacef_touserdata(L, 1);

	p->cancel(p);

	return 0;
}

static const luaL_Reg luacef_RunContextMenuCallback_m[] = {
	{ "Continue", luacef_RunContextMenuCallback_Continue },
	{ "Cancel", luacef_RunContextMenuCallback_Cancel},
	{ NULL, NULL}
};

// context_menu_handler =================================================
// implement

typedef struct luacef_ContextMenuHandler {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_before_context_menu)(
		struct luacef_ContextMenuHandler* self,
		struct _cef_browser_t* browser,
		struct _cef_frame_t* frame,
		struct _cef_context_menu_params_t* params,
		struct _cef_menu_model_t* model);

	int(CEF_CALLBACK* run_context_menu)(
		struct luacef_ContextMenuHandler* self,
		struct _cef_browser_t* browser,
		struct _cef_frame_t* frame,
		struct _cef_context_menu_params_t* params,
		struct _cef_menu_model_t* model,
		struct _cef_run_context_menu_callback_t* callback);

	int(CEF_CALLBACK* on_context_menu_command)(
		struct luacef_ContextMenuHandler* self,
		struct _cef_browser_t* browser,
		struct _cef_frame_t* frame,
		struct _cef_context_menu_params_t* params,
		int command_id,
		cef_event_flags_t event_flags);

	void(CEF_CALLBACK* on_context_menu_dismissed)(
		struct luacef_ContextMenuHandler* self,
		struct _cef_browser_t* browser,
		struct _cef_frame_t* frame);

	lua_State *L;
	int ref;

} luacef_ContextMenuHandler;

void CEF_CALLBACK luacef_ContextMenuHandler_OnBeforeContextMenu(
	struct luacef_ContextMenuHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_frame_t* frame,
	struct _cef_context_menu_params_t* params,
	struct _cef_menu_model_t* model)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeContextMenu)) {

		luacef_pushuserdata(self->L, self, __context_menu_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		luacef_pushuserdata(self->L, params, __context_menu_params__);
		luacef_pushuserdata(self->L, model, __menu_model__);

		lua_pcall(self->L, 5, 0, 8);
	}
}

int CEF_CALLBACK luacef_ContextMenuHandler_RunContextMenu(
	struct luacef_ContextMenuHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_frame_t* frame,
	struct _cef_context_menu_params_t* params,
	struct _cef_menu_model_t* model,
	struct _cef_run_context_menu_callback_t* callback)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __RunContextMenu)) {

		luacef_pushuserdata(self->L, self, __context_menu_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		luacef_pushuserdata(self->L, params, __context_menu_params__);
		luacef_pushuserdata(self->L, model, __menu_model__);
		luacef_pushuserdata(self->L, callback, __run_context_menu_callback__);

		lua_pcall(self->L, 6, 1, 8);
		return lua_toboolean(self->L, -1);
	}

	return 0;
}

int CEF_CALLBACK luacef_ContextMenuHandler_OnContextMenuCommand(
	struct luacef_ContextMenuHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_frame_t* frame,
	struct _cef_context_menu_params_t* params,
	int command_id,
	cef_event_flags_t event_flags)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnContextMenuCommand)) {

		luacef_pushuserdata(self->L, self, __context_menu_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		luacef_pushuserdata(self->L, params, __context_menu_params__);
		lua_pushinteger(self->L, command_id);
		lua_pushinteger(self->L, event_flags);

		lua_pcall(self->L, 6, 1, 8);
		return lua_toboolean(self->L, -1);
	}

	return 0;
}

void CEF_CALLBACK luacef_ContextMenuHandler_OnContextMenuDismissed(
	struct luacef_ContextMenuHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_frame_t* frame)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnContextMenuDismissed)) {

		luacef_pushuserdata(self->L, self, __context_menu_handler__);
		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);

		lua_pcall(self->L, 3, 0, 8);
	}
}

static int luacef_ContextMenuHandler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_ContextMenuHandler);
	luacef_ContextMenuHandler *p = NULL;
	p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnBeforeContextMenu))
			p->on_before_context_menu = !lua_isfunction(L, -1) ? NULL : luacef_ContextMenuHandler_OnBeforeContextMenu;

		if (lua_getfield(L, 1, __RunContextMenu))
			p->run_context_menu = !lua_isfunction(L, -1) ? NULL : luacef_ContextMenuHandler_RunContextMenu;

		if (lua_getfield(L, 1, __OnContextMenuCommand))
			p->on_context_menu_command = !lua_isfunction(L, -1) ? NULL : luacef_ContextMenuHandler_OnContextMenuCommand;

		if (lua_getfield(L, 1, __OnContextMenuDismissed))
			p->on_context_menu_dismissed = !lua_isfunction(L, -1) ? NULL : luacef_ContextMenuHandler_OnContextMenuDismissed;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	
	luacef_pushuserdata(L, p, __context_menu_handler__);
	return 1;
}

static int luacef_ContextMenuHandler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_ContextMenuHandler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_ContextMenuHandler_index(lua_State *L)
{
	luacef_ContextMenuHandler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_ContextMenuHandler_release);

	if (!strcmp(i, __OnBeforeContextMenu))
		lua_getfield(L, -1, __OnBeforeContextMenu);

	else if (!strcmp(i, __RunContextMenu))
		lua_getfield(L, -1, __RunContextMenu);

	else if (!strcmp(i, __OnContextMenuCommand))
		lua_getfield(L, -1, __OnContextMenuCommand);

	else if (!strcmp(i, __OnContextMenuDismissed))
		lua_getfield(L, -1, __OnContextMenuDismissed);

	else return 0;

	return 1;
}

static int luacef_ContextMenuHandler_newindex(lua_State *L)
{
	luacef_ContextMenuHandler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnBeforeContextMenu)) {
		lua_setfield(L, -2, __OnBeforeContextMenu);
		p->on_before_context_menu = !lua_isfunction(L, 3) ? NULL : luacef_ContextMenuHandler_OnBeforeContextMenu;
	}

	else if (!strcmp(i, __RunContextMenu)) {
		p->on_before_context_menu = !lua_isfunction(L, 3) ? NULL : luacef_ContextMenuHandler_RunContextMenu;
	}

	else if (!strcmp(i, __OnContextMenuCommand)){
		p->on_context_menu_command = !lua_isfunction(L, 3) ? NULL : luacef_ContextMenuHandler_OnContextMenuCommand;
	}

	else if (!strcmp(i, __OnContextMenuDismissed)) {
		p->on_context_menu_dismissed = !lua_isfunction(L, 3) ? NULL : luacef_ContextMenuHandler_OnContextMenuDismissed;
	}

	return 0;
}

static const luaL_Reg luacef_ContextMenuHandler_m[] = {
	{ "__index", luacef_ContextMenuHandler_index },
	{ "__newindex", luacef_ContextMenuHandler_newindex },
	{ NULL, NULL }
};

// context_menu_params ======================================

static int luacef_ContextMenuParams_GetXCoord(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	int r = p->get_xcoord(p);

	lua_pushinteger(L, r);
	return 1;
}

static int luacef_ContextMenuParams_GetYCoord(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	int r = p->get_ycoord(p);

	lua_pushinteger(L, r);
	return 1;
}

static int luacef_ContextMenuParams_GetTypeFlags(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_context_menu_type_flags_t r = p->get_type_flags(p);

	lua_pushinteger(L, r);
	return 1;
}

static int luacef_ContextMenuParams_GetLinkUrl(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_link_url(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetUnfilteredLinkUrl(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_unfiltered_link_url(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetSourceUrl(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_source_url(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_HasImageContents(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	int r = p->has_image_contents(p);

	lua_pushboolean(L, r);
	return 1;
}

static int luacef_ContextMenuParams_GetTitleText(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_title_text(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetPageUrl(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_page_url(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetFrameUrl(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_frame_url(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetFrameCharset(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_frame_charset(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetMediaType(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	int r = p->get_media_type(p);

	lua_pushinteger(L, r);
	return 1;
}

static int luacef_ContextMenuParams_GetMediaStateFlags(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	int r = p->get_media_state_flags(p);

	lua_pushinteger(L, r);
	return 1;
}

static int luacef_ContextMenuParams_GetSelectionText(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_selection_text(p);

	luacef_pushstring_free(L, s);
	return 1;
}

static int luacef_ContextMenuParams_GetMisspelledWord(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	cef_string_userfree_t s = p->get_misspelled_word(p);

	luacef_pushstring_free(L, s);
	return 1;
}

///
// Returns true (1) if suggestions exist, false (0) otherwise. Fills in
// |suggestions| from the spell check service for the misspelled word if there
// is one.
///
int(CEF_CALLBACK* get_dictionary_suggestions)(
	struct _cef_context_menu_params_t* self,
	cef_string_list_t suggestions);
static int luacef_ContextMenuParams_GetDictionarySuggestions(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);
	
	
	// todo

	return 1;
}

static int luacef_ContextMenuParams_IsEditable(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_editable(p));
	return 1;
}

static int luacef_ContextMenuParams_IsSpellCheckEnabled(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_spell_check_enabled(p));
	return 1;
}

static int luacef_ContextMenuParams_GetEditStateFlags(lua_State *L)
{

	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_edit_state_flags(p));
	return 1;
}

static int luacef_ContextMenuParams_IsCustomMenu(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_custom_menu(p));
	return 1;
}

static int luacef_ContextMenuParams_IsPepperMenu(lua_State *L)
{
	cef_context_menu_params_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_custom_menu(p));
	return 1;
}

static const luaL_Reg luacef_ContextMenuParams_m[] = {
	{ "GetXCoord", luacef_ContextMenuParams_GetXCoord },
	{ "GetYCoord", luacef_ContextMenuParams_GetYCoord },
	{ "GetTypeFlags", luacef_ContextMenuParams_GetTypeFlags },
	{ "GetLinkUrl", luacef_ContextMenuParams_GetLinkUrl },
	{ "GetUnfilteredLinkUrl", luacef_ContextMenuParams_GetUnfilteredLinkUrl },
	{ "GetSourceUrl", luacef_ContextMenuParams_GetSourceUrl },
	{ "HasImageContents", luacef_ContextMenuParams_HasImageContents },
	{ "GetTitleText", luacef_ContextMenuParams_GetTitleText },
	{ "GetPageUrl", luacef_ContextMenuParams_GetPageUrl },
	{ "GetFrameUrl", luacef_ContextMenuParams_GetFrameUrl },
	{ "GetFrameCharset", luacef_ContextMenuParams_GetFrameCharset },
	{ "GetMediaType", luacef_ContextMenuParams_GetMediaType },
	{ "GetMediaStateFlags", luacef_ContextMenuParams_GetMediaStateFlags },
	{ "GetSelectionText", luacef_ContextMenuParams_GetSelectionText },
	{ "GetMisspelledWord", luacef_ContextMenuParams_GetMisspelledWord },
	{ "GetDictionarySuggestions", luacef_ContextMenuParams_GetDictionarySuggestions },
	{ "IsEditable", luacef_ContextMenuParams_IsEditable },
	{ "IsSpellCheckEnabled", luacef_ContextMenuParams_IsSpellCheckEnabled },
	{ "GetEditStateFlags", luacef_ContextMenuParams_GetEditStateFlags },
	{ "IsCustomMenu", luacef_ContextMenuParams_IsCustomMenu },
	{ "IsPepperMenu", luacef_ContextMenuParams_IsPepperMenu },
	{ NULL, NULL}
};

// register ====================================

void luacef_ContextMenuHandler_reg(lua_State *L)
{
	luaL_newmetatable(L, __run_context_menu_callback__);
	luaL_setfuncs(L, luacef_RunContextMenuCallback_m, 0);
	lua_setfield(L, -1, __index__);

	luaL_newmetatable(L, __context_menu_handler__);
	luaL_setfuncs(L, luacef_ContextMenuHandler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_ContextMenuHandler_new);
	lua_setfield(L, -2, "newContextMenuHandler");

	luaL_newmetatable(L, __context_menu_params__);
	luaL_setfuncs(L, luacef_ContextMenuParams_m, 0);
	lua_setfield(L, -1, __index__);
}