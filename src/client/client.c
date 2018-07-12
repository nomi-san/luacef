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
	int	ref;

} luacef_client;

/*
	<ContextMenuHandler> Client:GetContextMenuHandler()
*/
struct _cef_context_menu_handler_t* CEF_CALLBACK c_get_context_menu_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_context_menu_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DialogHandler> Client:GetDialogHandler()
*/
struct _cef_dialog_handler_t* CEF_CALLBACK c_get_dialog_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_dialog_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DisplayHandler> Client:GetDisplayHandler()
*/
struct _cef_display_handler_t* CEF_CALLBACK c_get_display_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_display_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DownloadHandler> Client:GetDownloadHandler()
*/
struct _cef_download_handler_t* CEF_CALLBACK c_get_download_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_download_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DragHandler> Client:GetDragHandler()
*/
struct _cef_drag_handler_t* CEF_CALLBACK c_get_drag_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_drag_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<FindHandler> Client:GetFindHandler()
*/
struct _cef_find_handler_t* CEF_CALLBACK c_get_find_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_find_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<FocusHandler> Client:GetFocusHandler()
*/
struct _cef_focus_handler_t* CEF_CALLBACK c_get_focus_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_focus_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<GeolocationHandler> Client:GetGeolocationHandler()
*/
struct _cef_geolocation_handler_t* CEF_CALLBACK c_get_geolocation_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_geolocation_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
client.JSDdialogHandler
*/
struct _cef_jsdialog_handler_t* CEF_CALLBACK c_get_jsdialog_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_jsdialog_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
client.KeyboardHandler
*/
struct _cef_keyboard_handler_t* CEF_CALLBACK c_get_keyboard_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_keyboard_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
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
	if (lua_getfield(self->L, -1, __get_life_span_handler)) {

		//lua_pushlightuserdata(self->L, self->self); // self
		//luaL_setmetatable(self->L, __client__);
		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

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
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_load_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
client.RenderHandler
*/
struct _cef_render_handler_t* CEF_CALLBACK c_get_render_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_render_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
client.RequestHandler
*/
struct _cef_request_handler_t* CEF_CALLBACK c_get_request_handler(
	struct luacef_client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_request_handler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
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
	<Client> newClient 
	{
		<ContextMenuHandler>
			GetContextMenuHandler(self);
		<DialogHandler>
			GetDialogHandler(self);
		<DisplayHandler>
			GetDisplayHandler(self);
		<DownloadHandler>
			GetDownloadHandler(self);
		<DragHandler>
			GetDragHandler(self);
		<FindHandler>
			GetFindHandler(self);
		<FocusHandler>
			GetFocusHandler(self);
		<GeolocationHandler>
			GetGeolocationHandler(self);
		<JSDialogHandler>
			GetJSDialogHandler(self);
		<KeyboardHandler>
			GetKeyboardHandler(self);
		<LifeSpanHandler>
			GetLifeSpanHandler(self);
		<LoadHandler>
			GetLoadHandler(self);
		<RenderHandler
			GetRenderHandler(self);
		<RequestHandler>
			GetRequestHandler(self);
		<int>
			OnProcessMessageReceived(<Browser>, <int>, <ProcessMessage>);					
	}
*/
int luacef_client_new(lua_State* L)
{
	size_t sz = sizeof(luacef_client);
	luacef_client *client = luacef_alloc(sz);
	client->base.size = sz;
	client->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		client->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __get_life_span_handler))
			client->get_life_span_handler = c_get_life_span_handler;

		if (lua_getfield(L, 1, __get_context_menu_handler))
			client->get_context_menu_handler = c_get_context_menu_handler;

		if (lua_getfield(L, 1, __get_display_handler))
			client->get_display_handler = c_get_display_handler;

		if (lua_getfield(L, 1, __get_dialog_handler))
			client->get_dialog_handler = c_get_dialog_handler;

		if (lua_getfield(L, 1, __get_download_handler))
			client->get_download_handler = c_get_download_handler;

		if (lua_getfield(L, 1, __get_drag_handler))
			client->get_drag_handler = c_get_drag_handler;

		if (lua_getfield(L, 1, __get_find_handler))
			client->get_find_handler = c_get_find_handler;

		if (lua_getfield(L, 1, __get_focus_handler))
			client->get_focus_handler = c_get_focus_handler;

		if (lua_getfield(L, 1, __get_geolocation_handler))
			client->get_geolocation_handler = c_get_geolocation_handler;

		if (lua_getfield(L, 1, __get_jsdialog_handler))
			client->get_jsdialog_handler = c_get_jsdialog_handler;

		if (lua_getfield(L, 1, __get_keyboard_handler))
			client->get_keyboard_handler = c_get_keyboard_handler;

		if (lua_getfield(L, 1, __get_load_handler))
			client->get_load_handler = c_get_load_handler;

		if (lua_getfield(L, 1, __get_render_handler))
			client->get_render_handler = c_get_render_handler;

		if (lua_getfield(L, 1, __get_request_handler))
			client->get_request_handler = c_get_request_handler;

		if (lua_getfield(L, 1, __on_process_message_received))
			client->on_process_message_received = c_on_process_message_received;
	}
	else {
		lua_newtable(L);
		client->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, client, __client__);
	return 1;
}

static int luacef_client_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_client*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_client_index(lua_State* L)
{
	luacef_client *c = luacef_touserdata(L, 1);
	if (!c) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, c->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_client_release);

	else if (!strcmp(i, __get_context_menu_handler))
		lua_getfield(L, -1, __get_context_menu_handler);

	else if (!strcmp(i, __get_dialog_handler))
		lua_getfield(L, -1, __get_dialog_handler);

	else if (!strcmp(i, __get_display_handler))
		lua_getfield(L, -1, __get_display_handler);

	else if (!strcmp(i, __get_download_handler))
		lua_getfield(L, -1, __get_download_handler);

	else if (!strcmp(i, __get_drag_handler))
		lua_getfield(L, -1, __get_drag_handler);

	else if (!strcmp(i, __get_find_handler))
		lua_getfield(L, -1, __get_find_handler);

	else if (!strcmp(i, __get_focus_handler))
		lua_getfield(L, -1, __get_focus_handler);

	else if (!strcmp(i, __get_geolocation_handler))
		lua_getfield(L, -1, __get_geolocation_handler);

	else if (!strcmp(i, __get_jsdialog_handler))
		lua_getfield(L, -1, __get_jsdialog_handler);

	else if (!strcmp(i, __get_keyboard_handler))
		lua_getfield(L, -1, __get_keyboard_handler);

	else if (!strcmp(i, __get_life_span_handler))
		lua_getfield(L, -1, __get_life_span_handler);

	else if (!strcmp(i, __get_load_handler))
		lua_getfield(L, -1, __get_load_handler);

	else if (!strcmp(i, __get_render_handler))
		lua_getfield(L, -1, __get_render_handler);

	else if (!strcmp(i, __get_request_handler))
		lua_getfield(L, -1, __get_request_handler);

	else if (!strcmp(i, __on_process_message_received))
		lua_getfield(L, -1, __on_process_message_received);

	else return 0;

	return 1;
}

static int luacef_client_newindex(lua_State* L)
{
	luacef_client *c = luacef_touserdata(L, 1);
	if (!c) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, c->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __get_context_menu_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_context_menu_handler);
		c->get_context_menu_handler = c_get_context_menu_handler;
	}

	else if (!strcmp(i, __get_dialog_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_dialog_handler);
		c->get_dialog_handler = c_get_dialog_handler;
	}

	else if (!strcmp(i, __get_display_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_display_handler);
		c->get_display_handler = c_get_display_handler;
	}

	else if (!strcmp(i, __get_download_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_download_handler);
		c->get_download_handler = c_get_download_handler;
	}

	else if (!strcmp(i, __get_drag_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_drag_handler);
		c->get_drag_handler = c_get_drag_handler;
	}

	else if (!strcmp(i, __get_find_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_find_handler);
		c->get_find_handler = c_get_find_handler;
	}

	else if (!strcmp(i, __get_focus_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_focus_handler);
		c->get_focus_handler = c_get_focus_handler;
	}

	else if (!strcmp(i, __get_geolocation_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_geolocation_handler);
		c->get_geolocation_handler = c_get_geolocation_handler;
	}

	else if (!strcmp(i, __get_jsdialog_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_jsdialog_handler);
		c->get_jsdialog_handler = c_get_jsdialog_handler;
	}

	else if (!strcmp(i, __get_keyboard_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_keyboard_handler);
		c->get_keyboard_handler = c_get_keyboard_handler;
	}

	else if (!strcmp(i, __get_life_span_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_life_span_handler);
		c->get_life_span_handler = c_get_life_span_handler;
	}

	else if (!strcmp(i, __get_load_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_load_handler);
		c->get_load_handler = c_get_load_handler;
	}

	else if (!strcmp(i, __get_render_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_render_handler);
		c->get_render_handler = c_get_render_handler;
	}

	else if (!strcmp(i, __get_request_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_request_handler);
		c->get_request_handler = c_get_request_handler;
	}

	else if (!strcmp(i, __on_process_message_received)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_process_message_received);
		c->on_process_message_received = c_on_process_message_received;
	}

	return 0;
}

static const luaL_Reg luacef_client_m[] = {
	//{ "__gc", luacef_client_release},
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