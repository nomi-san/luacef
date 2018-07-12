#include "../luacef.h"
#include "include/capi/cef_app_capi.h"

// App //======================================

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

/*
	<void> App:OnBeforeCommandLineProcessing(
		<str>			process_type,
		<CommandLine>	command_line
	)
*/
void CEF_CALLBACK a_on_before_command_line_processing(
	struct luacef_app*			self,
	const cef_string_t*			process_type,
	struct _cef_command_line_t* command_line)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_browser_process_handler)) {

		luacef_pushuserdata(self->L, self, __app__);

		luacef_pushstring(self->L, process_type); // 2
		luacef_pushuserdata(self->L, command_line, __command_line__); // 3

		lua_pcall(self->L, 3, 0, 8); // call, no return
	}
}

/*
	<void>	App:OnRegisterCustomSchemes(
		<SchemeRegistrar>	registrar
	)
*/
void CEF_CALLBACK a_on_register_custom_schemes(
	struct luacef_app* self,
	struct _cef_scheme_registrar_t* registrar)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_browser_process_handler)) {

		luacef_pushuserdata(self->L, self, __app__);

		luacef_pushstring(self->L, __scheme_registrar__); // 2

		lua_pcall(self->L, 2, 0, 8); // call, no return
	}
}

/*
	<ResourceBundleHandler> App:GetResourceBundleHandler()
*/
struct _cef_resource_bundle_handler_t*
	CEF_CALLBACK a_get_resource_bundle_handler(struct luacef_app* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_resource_bundle_handler)) {

		luacef_pushuserdata(self->L, self, __app__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<BrowserProcessHandler> App:GetBrowserProcessHandler()
*/
struct _cef_browser_process_handler_t*
	CEF_CALLBACK a_get_browser_process_handler(struct luacef_app* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_browser_process_handler)) {

		luacef_pushuserdata(self->L, self, __app__);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<RenderProcessHandler> App:GetRenderProcessHandler()
*/
struct _cef_render_process_handler_t*
	CEF_CALLBACK a_get_render_process_handler(struct luacef_app* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_render_process_handler)) {

		luacef_pushuserdata(self->L, self, __app__);

		lua_pcall(self->L, 1, 1, 8); // call
		
		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}
	
	return NULL;
}

/*
	<App> newApp
	{
		<ResourceBundleHandler>
			GetResourceBundleHandler(self);
		<BrowserProcessHandler>
			GetBrowserProcessHandler(self);
		<RenderProcessHandler>
			GetRenderProcessHandler(self);
		<void>
			OnBeforeCommandLineProcessing(self, <str>, <CommandLine>);
		<void>
			OnRegisterCustomSchemes(self, <SchemeRegistrar>);
	}
*/
static int luacef_app_new(lua_State* L)
{
	size_t sz = sizeof(luacef_app);
	luacef_app *app = luacef_alloc(sz);
	app->base.size = sz;
	app->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		app->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __on_before_command_line_processing))
			app->on_before_command_line_processing = a_on_before_command_line_processing;

		if (lua_getfield(L, 1, __on_register_custom_schemes))
			app->on_register_custom_schemes = a_on_register_custom_schemes;

		if (lua_getfield(L, 1, __get_resource_bundle_handler))
			app->get_resource_bundle_handler = a_get_resource_bundle_handler;

		if (lua_getfield(L, 1, __get_browser_process_handler))
			app->get_browser_process_handler = a_get_browser_process_handler;

		if (lua_getfield(L, 1, __get_render_process_handler))
			app->get_render_process_handler = a_get_render_process_handler;

	}
	else {
		lua_newtable(L);
		app->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, app, __app__);
	return 1;
}

static int luacef_app_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_app*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_app_index(lua_State* L)
{
	luacef_app *app = luacef_touserdata(L, 1);
	if (!app) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, app->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_app_release);

	else if (!strcmp(i, __on_before_command_line_processing))
		lua_getfield(L, -1, __on_before_command_line_processing);

	else if (!strcmp(i, __on_register_custom_schemes))
		lua_getfield(L, -1, __on_register_custom_schemes);

	else if (!strcmp(i, __get_resource_bundle_handler))
		lua_getfield(L, -1, __get_resource_bundle_handler);

	else if (!strcmp(i, __get_browser_process_handler))
		lua_getfield(L, -1, __get_browser_process_handler);

	else if (!strcmp(i, __get_render_process_handler))
		lua_getfield(L, -1, __get_render_process_handler);

	else return 0;

	return 1;
}

static int luacef_app_newindex(lua_State* L)
{
	luacef_app *app = luacef_touserdata(L, 1);
	if (!app) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, app->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __on_before_command_line_processing)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_before_command_line_processing);
		app->on_before_command_line_processing = a_on_before_command_line_processing;
	}

	else if (!strcmp(i, __on_register_custom_schemes)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_register_custom_schemes);
		app->on_register_custom_schemes = a_on_register_custom_schemes;
	}

	else if (!strcmp(i, __get_resource_bundle_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_resource_bundle_handler);
		app->get_resource_bundle_handler = a_get_resource_bundle_handler;
	}

	else if (!strcmp(i, __get_browser_process_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_browser_process_handler);
		app->get_browser_process_handler = a_get_browser_process_handler;
	}

	else if (!strcmp(i, __get_render_process_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_render_process_handler);
		app->get_render_process_handler = a_get_render_process_handler;
	}

	return 0;
} 

static const luaL_Reg luacef_app_m[] = {
	//{ "__gc", luacef_app_release },
	{ "__index", luacef_app_index },
	{ "__newindex", luacef_app_newindex },
	{ NULL, NULL}
};

// functions

/*
	<int> ExecuteProcess(
		<MainArgs>,
		<App>
	)
*/
static int luacef_execute_process(lua_State* L)
{
	cef_main_args_t *args = luacef_checkudata(L, 1, __main_args__);
	if (!args) return 0;

	cef_app_t *app = luacef_checkudata(L, 2, __app__);
	if (!app) return 0;

	int code = cef_execute_process(args, app, NULL);
	lua_pushinteger(L, code);

	return 1;
}

/*
	<int> Initialize(
		<MainArgs>,
		<Settings>,
		<App>
	)
*/
static int luacef_initialize(lua_State* L)
{
	cef_main_args_t *args = luacef_checkudata(L, 1, __main_args__);
	if (!args) return 0;

	cef_settings_t	*settings = luacef_checkudata(L, 2, __settings__);
	if (!settings) return 0;

	cef_app_t		*app = luacef_checkudata(L, 3, __app__);
	if (!app) return 0;

	int ret = cef_initialize(args, settings, app, NULL); // no sanbox

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<void> Shutdown()
*/
static int luacef_shutdown(lua_State* L)
{
	cef_shutdown();
	return 0;
}

/*
	<void> DoMessageLoopWork()
*/
static int luacef_do_message_loop_work(lua_State* L)
{
	cef_do_message_loop_work();
	return 0;
}

/*
	<void> RunMessageLoop()
*/
static int luacef_run_message_loop(lua_State* L)
{
	cef_run_message_loop();
	return 0;
}

/*
	<void> QuitMessageLoop()
*/
static int luacef_quit_message_loop(lua_State* L)
{
	cef_quit_message_loop();
	return 0;
}

/*
	<void> SetOSMmodalLoop(
		<int> osModalLoop
	)
*/
static int luacef_set_osmodal_loop(lua_State* L)
{
	int i = lua_tointeger(L, 1);
	cef_set_osmodal_loop(i);
	return 0;
}

/*
	<void> EnableHighDPISupport()
*/
static int luacef_enable_highdpi_support(lua_State* L)
{
	cef_enable_highdpi_support();
	return 0;
}

void luacef_app_reg(lua_State* L)
{
	luaL_newmetatable(L, __app__);
	luaL_setfuncs(L, luacef_app_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_app_new);
	lua_setfield(L, -2, "newApp");

	//

	lua_pushcfunction(L, luacef_shutdown);
	lua_setfield(L, -2, "Shutdown");

	lua_pushcfunction(L, luacef_run_message_loop);
	lua_setfield(L, -2, "RunMessageLoop");

	lua_pushcfunction(L, luacef_do_message_loop_work);
	lua_setfield(L, -2, "DoMessageLoopWork");

	lua_pushcfunction(L, luacef_quit_message_loop);
	lua_setfield(L, -2, "QuitMessageLoop");

	lua_pushcfunction(L, luacef_enable_highdpi_support);
	lua_setfield(L, -2, "EnableHighDPISupport");

	lua_pushcfunction(L, luacef_execute_process);
	lua_setfield(L, -2, "ExecuteProcess");

	lua_pushcfunction(L, luacef_initialize);
	lua_setfield(L, -2, "Initialize");

	lua_pushcfunction(L, luacef_set_osmodal_loop);
	lua_setfield(L, -2, "SetOSMmodalLoop");
}

