#include "../luacef.h"

//////////////////////////////////

// implement

typedef struct luacef_client {

	cef_base_t base;

	struct _cef_context_menu_handler_t* (CEF_CALLBACK *get_context_menu_handler)(
		struct luacef_client* self);

	struct _cef_dialog_handler_t* (CEF_CALLBACK *get_dialog_handler)(
		struct luacef_client* self);

	struct _cef_display_handler_t* (CEF_CALLBACK *get_display_handler)(
		struct luacef_client* self);

	struct _cef_download_handler_t* (CEF_CALLBACK *get_download_handler)(
		struct luacef_client* self);

	struct _cef_drag_handler_t* (CEF_CALLBACK *get_drag_handler)(
		struct luacef_client* self);

	struct _cef_find_handler_t* (CEF_CALLBACK *get_find_handler)(
		struct luacef_client* self);

	struct _cef_focus_handler_t* (CEF_CALLBACK *get_focus_handler)(
		struct luacef_client* self);

	struct _cef_geolocation_handler_t* (CEF_CALLBACK *get_geolocation_handler)(
		struct luacef_client* self);

	struct _cef_jsdialog_handler_t* (CEF_CALLBACK *get_jsdialog_handler)(
		struct luacef_client* self);

	struct _cef_keyboard_handler_t* (CEF_CALLBACK *get_keyboard_handler)(
		struct luacef_client* self);

	struct _cef_life_span_handler_t* (CEF_CALLBACK *get_life_span_handler)(
		struct luacef_client* self);

	struct _cef_load_handler_t* (CEF_CALLBACK *get_load_handler)(
		struct luacef_client* self);

	struct _cef_render_handler_t* (CEF_CALLBACK *get_render_handler)(
		struct luacef_client* self);

	struct _cef_request_handler_t* (CEF_CALLBACK *get_request_handler)(
		struct luacef_client* self);

	int (CEF_CALLBACK *on_process_message_received)(struct luacef_client* self,
		struct _cef_browser_t* browser, cef_process_id_t source_process,
		struct _cef_process_message_t* message);

	lua_State *L;
	void *self;
	int	ref; // add ref

} luacef_client;

/*
	client.ContextMenuHandler
*/
struct _cef_context_menu_handler_t* CEF_CALLBACK c_get_context_menu_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_context_menu_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.DialogHandler
*/
struct _cef_dialog_handler_t* CEF_CALLBACK c_get_dialog_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_dialog_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.DisplayHandler
*/
struct _cef_display_handler_t* CEF_CALLBACK c_get_display_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_display_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.DownloadHandler
*/
struct _cef_download_handler_t* CEF_CALLBACK c_get_download_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_download_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.DragHandler
*/
struct _cef_drag_handler_t* CEF_CALLBACK c_get_drag_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_drag_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
	client.FindHandler
*/
struct _cef_find_handler_t* CEF_CALLBACK c_get_find_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_find_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
	client.FocusHandler
*/
struct _cef_focus_handler_t* CEF_CALLBACK c_get_focus_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_focus_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
	client.GeolocationHandler
*/
struct _cef_geolocation_handler_t* CEF_CALLBACK c_get_geolocation_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_geolocation_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.JSDdialogHandler
*/
struct _cef_jsdialog_handler_t* CEF_CALLBACK c_get_jsdialog_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_jsdialog_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.KeyboardHandler
*/
struct _cef_keyboard_handler_t* CEF_CALLBACK c_get_keyboard_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_keyboard_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
	client.LifeSpanHandler
*/
struct _cef_life_span_handler_t* CEF_CALLBACK c_get_life_span_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, get_life_span_handler)) {
		return luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
client.LoadHandler
*/
struct _cef_load_handler_t* CEF_CALLBACK c_get_load_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_load_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.RenderHandler
*/
struct _cef_render_handler_t* CEF_CALLBACK c_get_render_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_render_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
client.RequestHandler
*/
struct _cef_request_handler_t* CEF_CALLBACK c_get_request_handler(
	struct luacef_client* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, get_request_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

// -- todo
int CEF_CALLBACK c_on_process_message_received(
	struct luacef_client* self,
	struct _cef_browser_t* browser,
	cef_process_id_t source_process,
	struct _cef_process_message_t* message)
{
	return 0;
}

/*
	newClient 
	{
		<ContextMenuHandler>	ContextMenuHandler;
		<DialogHandler>			DialogHandler;
		<DisplayHandler>		DisplayHandler;
		<DownloadHandler>		DownloadHandler;
		<DragHandler>			DragHandler;
		<FindHandler>			FindHandler;
		<FocusHandler>			FocusHandler;
		<GeolocationHandler>	GeolocationHandler;
		<JSDialogHandler>		JSDialogHandler;
		<KeyboardHandler>		KeyboardHandler;
		<LifeSpanHandler>		LifeSpanHandler;
		<LoadHandler>			LoadHandler;
		<RenderHandler			RenderHandler;
		<RequestHandler>		RequestHandler;

		<func>(<Browser>, <int>, <ProcessMessage>)			
								OnProcessMessageReceived;
	} -> <Client>
*/
int luacef_client_new(lua_State* L)
{
	size_t sz = sizeof(luacef_client);
	luacef_client *client = calloc(1, sz);
	client->base.size = sz;

	if (lua_istable(L, 1)) {
		client->L = L;
		lua_pushvalue(L, 1);
		client->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __life_span_handler__))
			client->get_life_span_handler = c_get_life_span_handler;

		if (lua_getfield(L, 1, get_context_menu_handler))
			client->get_context_menu_handler = c_get_context_menu_handler;

		if (lua_getfield(L, 1, get_display_handler))
			client->get_display_handler = c_get_display_handler;

		if (lua_getfield(L, 1, get_dialog_handler))
			client->get_dialog_handler = c_get_dialog_handler;

		if (lua_getfield(L, 1, get_download_handler))
			client->get_download_handler = c_get_download_handler;

		if (lua_getfield(L, 1, get_drag_handler))
			client->get_drag_handler = c_get_drag_handler;

		if (lua_getfield(L, 1, get_find_handler))
			client->get_find_handler = c_get_find_handler;

		if (lua_getfield(L, 1, get_focus_handler))
			client->get_focus_handler = c_get_focus_handler;

		if (lua_getfield(L, 1, get_geolocation_handler))
			client->get_geolocation_handler = c_get_geolocation_handler;

		if (lua_getfield(L, 1, get_jsdialog_handler))
			client->get_jsdialog_handler = c_get_jsdialog_handler;

		if (lua_getfield(L, 1, get_keyboard_handler))
			client->get_keyboard_handler = c_get_keyboard_handler;

		if (lua_getfield(L, 1, get_load_handler))
			client->get_load_handler = c_get_load_handler;

		if (lua_getfield(L, 1, get_render_handler))
			client->get_render_handler = c_get_render_handler;

		if (lua_getfield(L, 1, get_request_handler))
			client->get_request_handler = c_get_request_handler;

		if (lua_getfield(L, 1, on_process_message_received))
			client->on_process_message_received = c_on_process_message_received;
	}

	client->self = luacef_pushuserdata(L, client, __client__);
	return 1;
}

static int luacef_client_index(lua_State* L)
{
	luacef_client *c = luacef_touserdata(L, 1);
	if (!c) return 0;

	const char* id = lua_tostring(L, 2);

	if (!strcmp(id, __release__))
		lua_pushcfunction(L, luacef_release);

	else luacef_error_index(L, id);

	return 1;
}

static int luacef_client_newindex(lua_State* L)
{
	luacef_client *c = luacef_touserdata(L, 1);
	if (!c) return 0;

	const char* id = lua_tostring(L, 2);

	if (!strcmp(id, __release__))
		;//lua_pushcfunction(L, luacef_release);

	else luacef_error_index(L, id);

	return 0;
}

static const luaL_Reg luacef_client_m[] = {
	{ "__gc", luacef_release},
	{ "__index", luacef_client_index },
	{ "__newindex", luacef_client_newindex },
	{ NULL, NULL}
};

void luacef_client_reg(lua_State* L)
{
	luaL_newmetatable(L, __client__);
	luaL_setfuncs(L, luacef_client_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_client_new);
	lua_setfield(L, -2, "newClient");
}