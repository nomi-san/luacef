#include "../luacef.h"
#include "include/capi/cef_app_capi.h"

typedef struct luacef_App {

	cef_base_t base;

	void (CEF_CALLBACK *on_before_command_line_processing)(
		struct luacef_App*			self,
		const cef_string_t*			process_type,
		struct _cef_command_line_t*	command_line);

	void (CEF_CALLBACK *on_register_custom_schemes)(
		struct luacef_App*				self,
		struct _cef_scheme_registrar_t* registrar);

	struct _cef_resource_bundle_handler_t* (
		CEF_CALLBACK *get_resource_bundle_handler)(struct luacef_App* self);

	struct _cef_browser_process_handler_t* (
		CEF_CALLBACK *get_browser_process_handler)(struct luacef_App* self);

	struct _cef_render_process_handler_t* (
		CEF_CALLBACK *get_render_process_handler)(struct luacef_App* self);

	lua_State *L;
	int ref;

    IMPL_REFCOUNT_MEMBER();

} luacef_App;

IMPL_REFCOUNT_METHODS(luacef_App);

/*
	<void> App:OnBeforeCommandLineProcessing(
		<str>			process_type,
		<CommandLine>	command_line
	)
*/
void CEF_CALLBACK luacef_App_OnBeforeCommandLineProcessing(
	struct luacef_App*			self,
	const cef_string_t*			process_type,
	struct _cef_command_line_t* command_line)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeCommandLineProcessing)) {

		luacef_pushuserdata(self->L, self, __CefApp);

		luacef_pushstring(self->L, process_type); // 2
		luacef_pushuserdata(self->L, command_line, __CefCommandLine); // 3

		lua_pcall(self->L, 3, 0, 8); // call, no return
	}
}

/*
	<void>	App:OnRegisterCustomSchemes(
		<SchemeRegistrar>	registrar
	)
*/
void CEF_CALLBACK luacef_App_OnRegisterCustomSchemes(
	struct luacef_App* self,
	struct _cef_scheme_registrar_t* registrar)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnRegisterCustomSchemes)) {

		luacef_pushuserdata(self->L, self, __CefApp);

		luacef_pushstring(self->L, __CefSchemeRegistrar); // 2

		lua_pcall(self->L, 2, 0, 8); // call, no return
	}
}

/*
	<ResourceBundleHandler> App:GetResourceBundleHandler()
*/
struct _cef_resource_bundle_handler_t*
	CEF_CALLBACK luacef_App_GetResourceBundleHandler(struct luacef_App* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetResourceBundleHandler)) {

		luacef_pushuserdata(self->L, self, __CefApp);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<BrowserProcessHandler> App:GetBrowserProcessHandler()
*/
struct _cef_browser_process_handler_t*
	CEF_CALLBACK luacef_App_GetBrowserProcessHandler(struct luacef_App* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetBrowserProcessHandler)) {

		luacef_pushuserdata(self->L, self, __CefApp);

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

/*
	<RenderProcessHandler> App:GetRenderProcessHandler()
*/
struct _cef_render_process_handler_t*
	CEF_CALLBACK luacef_App_GetRenderProcessHandler(struct luacef_App* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetRenderProcessHandler)) {

		luacef_pushuserdata(self->L, self, __CefApp);

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
static int luacef_App_new(lua_State* L)
{
	size_t sz = sizeof(luacef_App);
	luacef_App *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

    IMPL_REFCOUNT_INIT(luacef_App, p);

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnBeforeCommandLineProcessing))
			p->on_before_command_line_processing = luacef_App_OnBeforeCommandLineProcessing;

		if (lua_getfield(L, 1, __OnRegisterCustomSchemes))
			p->on_register_custom_schemes = luacef_App_OnRegisterCustomSchemes;

		if (lua_getfield(L, 1, __GetResourceBundleHandler))
			p->get_resource_bundle_handler = luacef_App_GetResourceBundleHandler;

		if (lua_getfield(L, 1, __GetBrowserProcessHandler))
			p->get_browser_process_handler = luacef_App_GetBrowserProcessHandler;

		if (lua_getfield(L, 1, __GetRenderProcessHandler))
			p->get_render_process_handler = luacef_App_GetRenderProcessHandler;

	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __CefApp);
	return 1;
}

static int App__gc(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
        luacef_App *p = *ud;
        p->base.release((void*)p);
	}

	return 0;
}

static int App__index(lua_State* L)
{
	luacef_App *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __OnBeforeCommandLineProcessing))
		lua_getfield(L, -1, __OnBeforeCommandLineProcessing);

	else if (!strcmp(i, __OnRegisterCustomSchemes))
		lua_getfield(L, -1, __OnRegisterCustomSchemes);

	else if (!strcmp(i, __GetResourceBundleHandler))
		lua_getfield(L, -1, __GetResourceBundleHandler);

	else if (!strcmp(i, __GetBrowserProcessHandler))
		lua_getfield(L, -1, __GetBrowserProcessHandler);

	else if (!strcmp(i, __GetRenderProcessHandler))
		lua_getfield(L, -1, __GetRenderProcessHandler);

	else return 0;

	return 1;
}

static int App__newindex(lua_State* L)
{
	luacef_App *app = luacef_touserdata(L, 1);
	if (!app) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, app->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnBeforeCommandLineProcessing)) {
		lua_setfield(L, -2, __OnBeforeCommandLineProcessing);
		app->on_before_command_line_processing = luacef_App_OnBeforeCommandLineProcessing;
	}

	else if (!strcmp(i, __OnRegisterCustomSchemes)) {
		lua_setfield(L, -2, __OnRegisterCustomSchemes);
		app->on_register_custom_schemes = luacef_App_OnRegisterCustomSchemes;
	}

	else if (!strcmp(i, __GetResourceBundleHandler)) {
		lua_setfield(L, -2, __GetResourceBundleHandler);
		app->get_resource_bundle_handler = luacef_App_GetResourceBundleHandler;
	}

	else if (!strcmp(i, __GetBrowserProcessHandler)) {
		lua_setfield(L, -2, __GetBrowserProcessHandler);
		app->get_browser_process_handler = luacef_App_GetBrowserProcessHandler;
	}

	else if (!strcmp(i, __GetRenderProcessHandler)) {
		
		lua_setfield(L, -2, __GetRenderProcessHandler);
		app->get_render_process_handler = luacef_App_GetRenderProcessHandler;
	}

	return 0;
} 

static int luacef_App_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(luacef_App));
	return 1;
}

static const luaL_Reg luacef_App_m[] = {
	{ "__index",    App__index },
	{ "__newindex", App__newindex },
	{ "__gc",       App__gc },
	{ "__len", luacef_App_len },
	{ "__eq", luacef_eq },
	{ NULL, NULL}
};

// functions

/*
	<int> ExecuteProcess(
		<MainArgs>,
		<App>
	)
*/
static int luacef_ExecuteProcess(lua_State* L)
{
	cef_main_args_t *args = luacef_checkudata(L, 1, __CefMainArgs);
	if (!args) return 0;

	cef_app_t *app = luacef_checkudata(L, 2, __CefApp);
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
static int luacef_Initialize(lua_State* L)
{
	cef_main_args_t *args = luacef_checkudata(L, 1, __CefMainArgs);
	if (!args) return 0;

	cef_settings_t	*settings = luacef_checkudata(L, 2, __CefSettings);
	if (!settings) return 0;

	cef_app_t		*app = luacef_checkudata(L, 3, __CefApp);
	if (!app) return 0;

	int ret = cef_initialize(args, settings, app, NULL); // no sanbox

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<void> Shutdown()
*/
static int luacef_Shutdown(lua_State* L)
{
	cef_shutdown();
	return 0;
}

/*
	<void> DoMessageLoopWork()
*/
static int luacef_DoMessageLoopWork(lua_State* L)
{
	cef_do_message_loop_work();
	return 0;
}

/*
	<void> RunMessageLoop()
*/
static int luacef_RunMessageLoop(lua_State* L)
{
	cef_run_message_loop();
	return 0;
}

/*
	<void> QuitMessageLoop()
*/
static int luacef_QuitMessageLoop(lua_State* L)
{
	cef_quit_message_loop();
	return 0;
}

/*
	<void> SetOSModalLoop(
		<bool> osModalLoop
	)
*/
static int luacef_SetOSModalLoop(lua_State* L)
{
	int i = lua_tointeger(L, 1);
	cef_set_osmodal_loop(i);
	return 0;
}

/*
	<void> EnableHighDPISupport()
*/
static int luacef_EnableHighDPISupport(lua_State* L)
{
	cef_enable_highdpi_support();
	return 0;
}

// =================================

void luacef_app_reg(lua_State* L)
{
	luaL_newmetatable(L, __CefApp);
	luaL_setfuncs(L, luacef_App_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_App_new);
	lua_setfield(L, -2, "newApp");

	//

	lua_pushcfunction(L, luacef_Shutdown);
	lua_setfield(L, -2, "Shutdown");

	lua_pushcfunction(L, luacef_RunMessageLoop);
	lua_setfield(L, -2, "RunMessageLoop");

	lua_pushcfunction(L, luacef_DoMessageLoopWork);
	lua_setfield(L, -2, "DoMessageLoopWork");

	lua_pushcfunction(L, luacef_QuitMessageLoop);
	lua_setfield(L, -2, "QuitMessageLoop");

	lua_pushcfunction(L, luacef_EnableHighDPISupport);
	lua_setfield(L, -2, "EnableHighDPISupport");

	lua_pushcfunction(L, luacef_ExecuteProcess);
	lua_setfield(L, -2, "ExecuteProcess");

	lua_pushcfunction(L, luacef_Initialize);
	lua_setfield(L, -2, "Initialize");

	lua_pushcfunction(L, luacef_SetOSModalLoop);
	lua_setfield(L, -2, "SetOSModalLoop");
}

