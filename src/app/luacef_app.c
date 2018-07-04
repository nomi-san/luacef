#include "luacef_app.h"

// App //======================================
static const char *_a_on_before_command_line_processing = "OnBeforeCommandLineProcessing";
static const char *_a_on_register_custom_schemes		= "OnRegisterCustomSchemes";
static const char *_a_get_resource_bundle_handler		= "ResourceBundleHandler";
static const char *_a_get_browser_process_handler		= "BrowserProcessHandler";
static const char *_a_get_render_process_handler		= "RenderProcessHandler";

typedef struct luacef_app {

	cef_base_t base;

	void (CEF_CALLBACK *on_before_command_line_processing)(
		struct luacef_app*			self,
		const cef_string_t*			process_type,
		struct _cef_command_line_t*	command_line);

	void (CEF_CALLBACK *on_register_custom_schemes)(
		struct luacef_app*				self,
		struct _cef_scheme_registrar_t* registrar);

	struct _cef_resource_bundle_handler_t* (
		CEF_CALLBACK *get_resource_bundle_handler)(struct luacef_app* self);

	struct _cef_browser_process_handler_t* (
		CEF_CALLBACK *get_browser_process_handler)(struct luacef_app* self);

	struct _cef_render_process_handler_t* (
		CEF_CALLBACK *get_render_process_handler)(struct luacef_app* self);

	lua_State *L;
	int ref;

} luacef_app;


// todo
void CEF_CALLBACK a_on_before_command_line_processing(
	struct luacef_app*			self,
	const cef_string_t*			process_type,
	struct _cef_command_line_t* command_line)
{

}

// todo
void CEF_CALLBACK a_on_register_custom_schemes(
	struct luacef_app* self,
	struct _cef_scheme_registrar_t* registrar)
{

}

struct _cef_resource_bundle_handler_t*
	CEF_CALLBACK a_get_resource_bundle_handler(struct luacef_app* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, _a_get_resource_bundle_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

struct _cef_browser_process_handler_t*
	CEF_CALLBACK a_get_browser_process_handler(struct luacef_app* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, _a_get_browser_process_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

struct _cef_render_process_handler_t*
	CEF_CALLBACK a_get_render_process_handler(struct luacef_app* self)
{
	if (self->L) {
		lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
		if (lua_getfield(self->L, -1, _a_get_render_process_handler)) {
			return (void*)lua_tointeger(self->L, -1);
		}
	}

	return NULL;
}

/*
	newApp
	{
		<ResourceBundleHandler>		ResourceBundleHandler;
		<BrowserProcessHandler>		BrowserProcessHandler;
		<RenderProcessHandler>		RenderProcessHandler;

		<func>(<str>, <CommandLine>)
									OnBeforeCommandLineProcessing;
		<func>(<SchemeRegistrar>)	
									OnRegisterCustomSchemes;

	} -> <App>

	// function; self = app
*/
static int luacef_app_new(lua_State* L)
{
	size_t sz = sizeof(luacef_app);
	luacef_app *app = luacef_newuserdata(L, sz);
	app->base.size = sz;

	if (lua_istable(L, 1)) {
		app->L = L;
		lua_pushvalue(L, 1);
		app->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, _a_on_before_command_line_processing))
			app->on_before_command_line_processing = a_on_before_command_line_processing;

		if (lua_getfield(L, 1, _a_on_register_custom_schemes))
			app->on_register_custom_schemes = a_on_register_custom_schemes;

		if (lua_getfield(L, 1, _a_get_resource_bundle_handler))
			app->get_resource_bundle_handler = a_get_resource_bundle_handler;

		if (lua_getfield(L, 1, _a_get_browser_process_handler))
			app->get_browser_process_handler = a_get_browser_process_handler;

		if (lua_getfield(L, 1, _a_get_render_process_handler))
			app->get_render_process_handler = a_get_render_process_handler;

		lua_pushvalue(L, -6); // userdata
	}

	luaL_setmetatable(L, __app__);
	return 1;
}

static int luacef_app_index(lua_State* L)
{
	cef_app_t *app = luacef_touserdata(L, 1);
	if (!app) return 0;

	const char* id = lua_tostring(L, 2);

	if (!strcmp(id, __release__))
		lua_pushcfunction(L, luacef_release);

	else luacef_error_index(L, id);

	return 1;
}

static int luacef_app_newindex(lua_State* L)
{
	cef_app_t *app = luacef_touserdata(L, 1);
	if (!app) return 0;

	const char* id = lua_tostring(L, 2);

	if (!strcmp(id, __release__))
		;
	else luacef_error_index(L, id);

	return 0;
}

static const luaL_Reg luacef_app_m[] = {
	{ "__gc", luacef_release },
	{ "__index", luacef_app_index },
	{ "__newindex", luacef_app_newindex },
	{ NULL, NULL}
};

void luacef_app_reg(lua_State* L)
{
	luaL_newmetatable(L, __app__);
	luaL_setfuncs(L, luacef_app_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_app_new);
	lua_setfield(L, -2, "newApp");
}