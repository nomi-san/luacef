#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"

static const char *__on_pre_key_event = "OnPreKeyEvent";
static const char *__on_key_event = "OnKeyEvent";

typedef struct luacef_keyboard_handler {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* on_pre_key_event)(struct luacef_keyboard_handler* self,
		struct _cef_browser_t* browser,
		const struct _cef_key_event_t* event,
		cef_event_handle_t os_event,
		int* is_keyboard_shortcut);

	int(CEF_CALLBACK* on_key_event)(struct luacef_keyboard_handler* self,
		struct _cef_browser_t* browser,
		const struct _cef_key_event_t* event,
		cef_event_handle_t os_event);

	lua_State *L;
	int ref;

} luacef_keyboard_handler;

/*
	<bool> KeyboardHandler:OnPreKeyEvent(
		<Browser>	browser,
		<KeyEvent>	event,
		<EventHandle>	os_event,
		<BoolPtr>	is_keyboard_shortcut
	)
*/
int CEF_CALLBACK kh_on_pre_key_event(struct luacef_keyboard_handler* self,
	struct _cef_browser_t* browser,
	const struct _cef_key_event_t* event,
	cef_event_handle_t os_event,
	int* is_keyboard_shortcut)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_pre_key_event)) {

		luacef_pushuserdata(self->L, self, __keyboard_handler__); // self, 1

		luacef_pushuserdata(self->L, browser, __browser__); // 2

		luacef_pushuserdata(self->L, event, __key_event__); // 3

		luacef_pushuserdata(self->L, os_event, __event_handle__); // 4

		luacef_pushuserdata(self->L, is_keyboard_shortcut, __bool_ptr__); // 5
		
		lua_pcall(self->L, 5, 1, 8);
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

/*
	<bool> KeyboardHandler:OnKeyEvent(
		<Browser>	browser,
		<KeyEvent>	event,
		<EventHandle>	os_event,
	)
*/
int CEF_CALLBACK kh_on_key_event(struct luacef_keyboard_handler* self,
	struct _cef_browser_t* browser,
	const struct _cef_key_event_t* event,
	cef_event_handle_t os_event)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_pre_key_event)) {

		luacef_pushuserdata(self->L, self, __keyboard_handler__); // self, 1

		luacef_pushuserdata(self->L, browser, __browser__); // 2

		luacef_pushuserdata(self->L, event, __key_event__); // 3

		luacef_pushuserdata(self->L, os_event, __event_handle__); // 4

		lua_pcall(self->L, 4, 1, 8);
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

/*
	<KeyboardHandler> newKeyboardHandler {
		<bool>
			OnPreKeyEvent(<Browser>, <KeyEvent>, <EventHandle>, <BoolPtr>);
		<bool>
			OnKeyEvent(<Browser>, <KeyEvent>, <EventHandle>);
	}
*/
static int luacef_keyboard_handler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_keyboard_handler);
	luacef_keyboard_handler *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __on_pre_key_event))
			p->on_pre_key_event = kh_on_pre_key_event;

		if (lua_getfield(L, 1, __on_key_event))
			p->on_key_event = kh_on_key_event;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __keyboard_handler__);
	return 1;
}

static int luacef_keyboard_handler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_keyboard_handler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_keyboard_handler_index(lua_State *L)
{
	luacef_keyboard_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_keyboard_handler_release);

	else if (!strcmp(i, __on_pre_key_event))
		lua_getfield(L, -1, __on_pre_key_event);

	else if (!strcmp(i, __on_key_event))
		lua_getfield(L, -1, __on_key_event);

	else return 0;

	return 1;
}

static int luacef_keyboard_handler_newindex(lua_State *L)
{
	luacef_keyboard_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __on_pre_key_event)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_pre_key_event);
		p->on_pre_key_event = kh_on_pre_key_event;
	}

	else if (!strcmp(i, __on_key_event)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_pre_key_event);
		p->on_key_event = kh_on_key_event;
	}

	return 0;
}

static const luaL_Reg luacef_keyboard_handler_m[] = {
	{ "__index", luacef_keyboard_handler_index },
	{ "__newindex", luacef_keyboard_handler_newindex },
	{ NULL, NULL }
};

// ===========================================

static int luacef_key_event_index(lua_State *L)
{
	cef_key_event_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, "type"))
		lua_pushinteger(L, p->type);

	else if (!strcmp(i, "modifiers"))
		lua_pushinteger(L, p->modifiers);

	else if (!strcmp(i, "windows_key_code"))
		lua_pushinteger(L, p->windows_key_code);

	else if (!strcmp(i, "native_key_code"))
		lua_pushinteger(L, p->native_key_code);

	else if (!strcmp(i, "is_system_key"))
		lua_pushboolean(L, p->type);

	else if (!strcmp(i, "character"))
		lua_pushwstring(L, &p->character);

	else if (!strcmp(i, "unmodified_character"))
		lua_pushwstring(L, &p->unmodified_character);

	else if (!strcmp(i, "focus_on_editable_field"))
		lua_pushboolean(L, p->focus_on_editable_field);

	else return 0;

	return 1;
}

static int luacef_key_event_newindex(lua_State *L)
{
	cef_key_event_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, "type"))
		p->type = lua_tointeger(L, 3);

	else if (!strcmp(i, "modifiers"))
		p->modifiers = lua_tointeger(L, 3);

	else if (!strcmp(i, "windows_key_code"))
		p->windows_key_code = lua_tointeger(L, 3);

	else if (!strcmp(i, "native_key_code"))
		p->native_key_code = lua_tointeger(L, 3);

	else if (!strcmp(i, "is_system_key"))
		p->type = lua_tointeger(L, 3);

	else if (!strcmp(i, "character"))
		p->character = lua_towstring(L, 3);

	else if (!strcmp(i, "unmodified_character"))
		p->unmodified_character = lua_towstring(L, 3);

	else if (!strcmp(i, "focus_on_editable_field"))
		p->focus_on_editable_field = lua_tointeger(L, 3);

	return 0;
}

static const luaL_Reg luacef_key_event_m[] = {
	{ "__index", luacef_key_event_index },
	{ "__newindex", luacef_key_event_newindex },
	{ NULL, NULL }
};

void luacef_keyboard_handler_reg(lua_State *L)
{
	luaL_newmetatable(L, __keyboard_handler__);
	luaL_setfuncs(L, luacef_keyboard_handler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_keyboard_handler_new);
	lua_setfield(L, -2, "newKeyboardHandler");

	luaL_newmetatable(L, __key_event__);
	luaL_setfuncs(L, luacef_key_event_m, 0);
	lua_pop(L, 1);

}