#include "../luacef.h"

//      _ _         _   
//  ___| |_|___ ___| |_ 
// |  _| | | -_|   |  _|
// |___|_|_|___|_|_|_|  
//=======================
/*
	<Client> {
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
			OnProcessMessageReceived(self, <Browser>, <int>, <ProcessMessage>);					
	}

	addon:
		<void> release();

	meta:
		__index;
		__newindex;
		__eq;
		__len;

*/

// implement client

typedef struct luacef_Client {

	cef_base_t base;

	struct _cef_context_menu_handler_t* (CEF_CALLBACK *get_context_menu_handler)(
		struct luacef_Client* self);

	struct _cef_dialog_handler_t* (CEF_CALLBACK *get_dialog_handler)(
		struct luacef_Client* self);

	struct _cef_display_handler_t* (CEF_CALLBACK *get_display_handler)(
		struct luacef_Client* self);

	struct _cef_download_handler_t* (CEF_CALLBACK *get_download_handler)(
		struct luacef_Client* self);

	struct _cef_drag_handler_t* (CEF_CALLBACK *get_drag_handler)(
		struct luacef_Client* self);

	struct _cef_find_handler_t* (CEF_CALLBACK *get_find_handler)(
		struct luacef_Client* self);

	struct _cef_focus_handler_t* (CEF_CALLBACK *get_focus_handler)(
		struct luacef_Client* self);

	struct _cef_geolocation_handler_t* (CEF_CALLBACK *get_geolocation_handler)(
		struct luacef_Client* self);

	struct _cef_jsdialog_handler_t* (CEF_CALLBACK *get_jsdialog_handler)(
		struct luacef_Client* self);

	struct _cef_keyboard_handler_t* (CEF_CALLBACK *get_keyboard_handler)(
		struct luacef_Client* self);

	struct _cef_life_span_handler_t* (CEF_CALLBACK *get_life_span_handler)(
		struct luacef_Client* self);

	struct _cef_load_handler_t* (CEF_CALLBACK *get_load_handler)(
		struct luacef_Client* self);

	struct _cef_render_handler_t* (CEF_CALLBACK *get_render_handler)(
		struct luacef_Client* self);

	struct _cef_request_handler_t* (CEF_CALLBACK *get_request_handler)(
		struct luacef_Client* self);

	int (CEF_CALLBACK *on_process_message_received)(struct luacef_Client* self,
		struct _cef_browser_t* browser, cef_process_id_t source_process,
		struct _cef_process_message_t* message);

	lua_State *L;
	int	ref;

} luacef_Client;

/*
	<ContextMenuHandler> Client:GetContextMenuHandler()
*/
struct _cef_context_menu_handler_t* CEF_CALLBACK luacef_Client_GetContextMenuHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetContextMenuHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DialogHandler> Client:GetDialogHandler()
*/
struct _cef_dialog_handler_t* CEF_CALLBACK luacef_Client_GetDialogHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetDialogHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DisplayHandler> Client:GetDisplayHandler()
*/
struct _cef_display_handler_t* CEF_CALLBACK luacef_Client_GetDisplayHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetDisplayHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DownloadHandler> Client:GetDownloadHandler()
*/
struct _cef_download_handler_t* CEF_CALLBACK luacef_Client_GetDownloadHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetDownloadHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<DragHandler> Client:GetDragHandler()
*/
struct _cef_drag_handler_t* CEF_CALLBACK luacef_Client_GetDragHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetDragHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<FindHandler> Client:GetFindHandler()
*/
struct _cef_find_handler_t* CEF_CALLBACK luacef_Client_GetFindHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetFindHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<FocusHandler> Client:GetFocusHandler()
*/
struct _cef_focus_handler_t* CEF_CALLBACK luacef_Client_GetFocusHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetFocusHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<GeolocationHandler> Client:GetGeolocationHandler()
*/
struct _cef_geolocation_handler_t* CEF_CALLBACK luacef_Client_GetGeolocationHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetGeolocationHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<JSDialogHandler> Client:GetJSDialogHandler()
*/
struct _cef_jsdialog_handler_t* CEF_CALLBACK luacef_Client_GetJSDialogHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetJSDialogHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<KeyboardHandler> Client:GetKeyboardHandler()
*/
struct _cef_keyboard_handler_t* CEF_CALLBACK luacef_Client_GetKeyboardHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetKeyboardHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<LifeSpanHandler> Client:GetLifeSpanHandler()
*/
struct _cef_life_span_handler_t* CEF_CALLBACK luacef_Client_GetLifeSpanHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetLifeSpanHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<LoadHandler> Client:GetLoadHandler()
*/
struct _cef_load_handler_t* CEF_CALLBACK luacef_Client_GetLoadHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetLoadHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<RenderHandler> Client:GetRenderHandler()
*/
struct _cef_render_handler_t* CEF_CALLBACK luacef_Client_GetRenderHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetRenderHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<RequestHandler> Client:GetRequestHandler()
*/
struct _cef_request_handler_t* CEF_CALLBACK luacef_Client_GetRequestHandler(
	struct luacef_Client* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetRequestHandler)) {

		luacef_pushuserdata(self->L, self, __client__);

		lua_pcall(self->L, 1, 1, 0); // call
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<int> Client:OnProcessMessageReceived(
		<Browser> browser,
		<int> process_id,
		<ProcessMessage> message
	)
*/
int CEF_CALLBACK luacef_Client_OnProcessMessageReceived(
	struct luacef_Client* self,
	struct _cef_browser_t* browser,
	cef_process_id_t source_process,
	struct _cef_process_message_t* message)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnProcessMessageReceived)) {

		luacef_pushuserdata(self->L, self, __client__);
		luacef_pushuserdata(self->L, browser, __browser__);
		lua_pushinteger(self->L, source_process);
		luacef_pushuserdata(self->L, message, __process_message__);

		lua_pcall(self->L, 4, 1, 0); // call
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

int luacef_Client_new(lua_State* L)
{
	size_t sz = sizeof(luacef_Client);
	luacef_Client *client = luacef_alloc(sz);
	client->base.size = sz;
	client->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		client->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __GetContextMenuHandler))
			client->get_context_menu_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetContextMenuHandler;

		if (lua_getfield(L, 1, __GetDialogHandler))
			client->get_dialog_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetDialogHandler;

		if (lua_getfield(L, 1, __GetDisplayHandler))
			client->get_display_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetDisplayHandler;

		if (lua_getfield(L, 1, __GetDownloadHandler))
			client->get_download_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetDownloadHandler;

		if (lua_getfield(L, 1, __GetDragHandler))
			client->get_drag_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetDragHandler;

		if (lua_getfield(L, 1, __GetFindHandler))
			client->get_find_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetFindHandler;

		if (lua_getfield(L, 1, __GetFocusHandler))
			client->get_focus_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetFocusHandler;

		if (lua_getfield(L, 1, __GetGeolocationHandler))
			client->get_geolocation_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetGeolocationHandler;

		if (lua_getfield(L, 1, __GetJSDialogHandler))
			client->get_jsdialog_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetJSDialogHandler;

		if (lua_getfield(L, 1, __GetKeyboardHandler))
			client->get_keyboard_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetKeyboardHandler;

		if (lua_getfield(L, 1, __GetLifeSpanHandler))
			client->get_life_span_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetLifeSpanHandler;

		if (lua_getfield(L, 1, __GetLoadHandler))
			client->get_load_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetLoadHandler;

		if (lua_getfield(L, 1, __GetRenderHandler))
			client->get_render_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetRenderHandler;

		if (lua_getfield(L, 1, __GetRequestHandler))
			client->get_request_handler = !lua_isfunction(L, -1) ? NULL : luacef_Client_GetRequestHandler;

		if (lua_getfield(L, 1, __OnProcessMessageReceived))
			client->on_process_message_received = !lua_isfunction(L, -1) ? NULL : luacef_Client_OnProcessMessageReceived;
	}
	else {
		lua_newtable(L);
		client->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, client, __client__);
	return 1;
}

static int luacef_Client_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_Client*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_Client_index(lua_State* L)
{
	luacef_Client *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_Client_release);

	else if (!strcmp(i, __GetContextMenuHandler))
		lua_getfield(L, -1, __GetContextMenuHandler);

	else if (!strcmp(i, __GetDialogHandler))
		lua_getfield(L, -1, __GetDialogHandler);

	else if (!strcmp(i, __GetDisplayHandler))
		lua_getfield(L, -1, __GetDisplayHandler);

	else if (!strcmp(i, __GetDownloadHandler))
		lua_getfield(L, -1, __GetDownloadHandler);

	else if (!strcmp(i, __GetDragHandler))
		lua_getfield(L, -1, __GetDragHandler);

	else if (!strcmp(i, __GetFindHandler))
		lua_getfield(L, -1, __GetFindHandler);

	else if (!strcmp(i, __GetFocusHandler))
		lua_getfield(L, -1, __GetFocusHandler);

	else if (!strcmp(i, __GetGeolocationHandler))
		lua_getfield(L, -1, __GetGeolocationHandler);

	else if (!strcmp(i, __GetJSDialogHandler))
		lua_getfield(L, -1, __GetJSDialogHandler);

	else if (!strcmp(i, __GetKeyboardHandler))
		lua_getfield(L, -1, __GetKeyboardHandler);

	else if (!strcmp(i, __GetLifeSpanHandler))
		lua_getfield(L, -1, __GetLifeSpanHandler);

	else if (!strcmp(i, __GetLoadHandler))
		lua_getfield(L, -1, __GetLoadHandler);

	else if (!strcmp(i, __GetRenderHandler))
		lua_getfield(L, -1, __GetRenderHandler);

	else if (!strcmp(i, __GetRequestHandler))
		lua_getfield(L, -1, __GetRequestHandler);

	else if (!strcmp(i, __OnProcessMessageReceived))
		lua_getfield(L, -1, __OnProcessMessageReceived);

	else return 0;

	return 1;
}

static int luacef_Client_newindex(lua_State* L)
{
	luacef_Client *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* i = lua_tostring(L, 2);
	
	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __GetContextMenuHandler)) {
		lua_setfield(L, -2, __GetContextMenuHandler);
		p->get_context_menu_handler = luacef_Client_GetContextMenuHandler;
	}

	else if (!strcmp(i, __GetDialogHandler)) {
		lua_setfield(L, -2, __GetDialogHandler);
		p->get_dialog_handler = luacef_Client_GetDialogHandler;
	}

	else if (!strcmp(i, __GetDisplayHandler)) {
		lua_setfield(L, -2, __GetDisplayHandler);
		p->get_display_handler = luacef_Client_GetDisplayHandler;
	}

	else if (!strcmp(i, __GetDownloadHandler)) {
		lua_setfield(L, -2, __GetDownloadHandler);
		p->get_download_handler = luacef_Client_GetDownloadHandler;
	}

	else if (!strcmp(i, __GetDragHandler)) {
		lua_setfield(L, -2, __GetDragHandler);
		p->get_drag_handler = luacef_Client_GetDragHandler;
	}

	else if (!strcmp(i, __GetFindHandler)) {
		lua_setfield(L, -2, __GetFindHandler);
		p->get_find_handler = luacef_Client_GetFindHandler;
	}

	else if (!strcmp(i, __GetFocusHandler)) {
		lua_setfield(L, -2, __GetFocusHandler);
		p->get_focus_handler = luacef_Client_GetFocusHandler;
	}

	else if (!strcmp(i, __GetGeolocationHandler)) {
		lua_setfield(L, -2, __GetGeolocationHandler);
		p->get_geolocation_handler = luacef_Client_GetGeolocationHandler;
	}

	else if (!strcmp(i, __GetJSDialogHandler)) {
		lua_setfield(L, -2, __GetJSDialogHandler);
		p->get_jsdialog_handler = luacef_Client_GetJSDialogHandler;
	}

	else if (!strcmp(i, __GetKeyboardHandler)) {
		lua_setfield(L, -2, __GetKeyboardHandler);
		p->get_keyboard_handler = luacef_Client_GetKeyboardHandler;
	}

	else if (!strcmp(i, __GetLifeSpanHandler)) {
		lua_setfield(L, -2, __GetLifeSpanHandler);
		p->get_life_span_handler = luacef_Client_GetLifeSpanHandler;
	}

	else if (!strcmp(i, __GetLoadHandler)) {
		lua_setfield(L, -2, __GetLoadHandler);
		p->get_load_handler = luacef_Client_GetLoadHandler;
	}

	else if (!strcmp(i, __GetRenderHandler)) {
		lua_setfield(L, -2, __GetRenderHandler);
		p->get_render_handler = luacef_Client_GetRenderHandler;
	}

	else if (!strcmp(i, __GetRequestHandler)) {
		lua_setfield(L, -2, __GetRequestHandler);
		p->get_request_handler = luacef_Client_GetRequestHandler;
	}

	else if (!strcmp(i, __OnProcessMessageReceived)) {
		lua_setfield(L, -2, __OnProcessMessageReceived);
		p->on_process_message_received = luacef_Client_OnProcessMessageReceived;
	}

	return 0;
}

static int luacef_Client_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(luacef_Client));
	return 1;
}

static const luaL_Reg luacef_Client_m[] = {
	{ "__index", luacef_Client_index },
	{ "__newindex", luacef_Client_newindex },
	{ "__len", luacef_len },
	{ "__eq", luacef_eq},
	{ NULL, NULL}
};

void luacef_Client_reg(lua_State* L)
{
	luaL_newmetatable(L, __client__);
	luaL_setfuncs(L, luacef_Client_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_Client_new);
	lua_setfield(L, -2, "newClient");
}