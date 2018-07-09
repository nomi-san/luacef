#include "luacef_types.h"

/*
	<bool> IsCertStatusError(
		<int>	status
	)
*/
static int luacef_is_cert_status_error(lua_State* L)
{
	int stt = luaL_checkinteger(L, 1);

	lua_pushboolean(L, cef_is_cert_status_error(stt));
	return 1;
}

/*
	<bool> IsCertStatusMinorError(
		<int>	status
	)
*/
static int luacef_is_cert_status_minor_error(lua_State* L)
{
	int stt = luaL_checkinteger(L, 1);

	lua_pushboolean(L, cef_is_cert_status_minor_error(stt));
	return 1;
}

/*
	<void> IsWebPluginUnstable(
		<str>						path,
		<WebPluginUnstableCallback>	status
	)
*/
static int luacef_is_web_plugin_unstable(lua_State* L)
{
	const char *cs = lua_tostring(L, 1);
	cef_web_plugin_unstable_callback_t *cb = luacef_checkudata(L, 2, __web_plugin_unstable_callback__);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);

	cef_is_web_plugin_unstable(&s, cb);
	return 0;
}
;

/*
	<int> VersionInfo(
		<int>	entry
	)
	Entry list:
	0 - CEF_VERSION_MAJOR
	1 - CEF_COMMIT_NUMBER
	2 - CHROME_VERSION_MAJOR
	3 - CHROME_VERSION_MINOR
	4 - CHROME_VERSION_BUILD
	5 - CHROME_VERSION_PATCH
*/
static int luacef_version_info(lua_State* L)
{
	int entry = luaL_checkinteger(L, 1);
	
	lua_pushinteger(L, cef_version_info(entry));
	return 1;
}

/*
	<void> ShowBrowser(
		<Browser>	browser
		[, <int>	show_flag]
	)
*/
static int luacef_show_browser(lua_State* L)
{
	cef_browser_t *b = luacef_touserdata(L, 1);
	cef_browser_host_t *bh = b->get_host(b);
	ShowWindow(bh->get_window_handle(bh), lua_isnone(L, 2) ? 5 : lua_tointeger(L, 2));
	return 0;
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
	<void> RunMessageLoop()
*/
static int luacef_run_message_loop(lua_State* L)
{
	cef_run_message_loop();
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
	cef.QuitMessageLoop() -> <nil>
*/
static int luacef_quit_message_loop(lua_State* L)
{
	cef_quit_message_loop();
	return 0;
}

/*
cef.EnableHighDPISupport() -> <nil>
*/
static int luacef_enable_highdpi_support(lua_State* L)
{
	cef_enable_highdpi_support();
	return 0;
}

/*
	cef.ExecuteProcess(
		<MainArgs>,
		<App>
	) -> <int>
*/
static int luacef_execute_process(lua_State* L)
{
	cef_main_args_t *args = luacef_checkudata(L, 1, __main_args__);
	if (!args) return 0;

	cef_app_t *app = luacef_checkudata(L, 2, __app__);
	if (!app) return 0;

	else {
		int code = cef_execute_process(args, app, NULL);
		lua_pushinteger(L, code);
	}

	return 1;
}

/*
	cef.Initialize(
		<MainArgs>,
		<Settings>,
		<App>
	) -> <int>
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
	cef.CreateBrowser(
		<WindowInfo>,
		<Client>,
		<str>,
		<Settings>
	) -> <int>
*/
static int luacef_create_browser(lua_State* L)
{
	cef_window_info_t *winfo = luacef_checkudata(L, 1, __window_info__);
	if (!winfo) return 0;

	cef_client_t *client = luacef_checkudata(L, 2, __client__);
	if (!client) return 0;

	const char *cs_url = lua_tostring(L, 3);

	cef_string_t url = { 0 };
	cef_string_from_utf8(cs_url, strlen(cs_url), &url);

	cef_browser_settings_t *bs = luacef_checkudata(L, 4, __browser_settings__);
	if (!bs) return 0;

	int ret = cef_browser_host_create_browser(
		winfo,
		client,
		&url,
		bs,
		NULL
	);

	lua_pushinteger(L, ret);
	return 1;
}

/*
	cef.CreateBrowserSync(
		<WindowInfo>,
		<Client>,
		<str>,
		<BrowserSettings>
	) -> <Browser>
*/
static int luacef_create_browser_sync(lua_State* L)
{
	cef_window_info_t *winfo = luacef_checkudata(L, 1, __window_info__);
	if (!winfo) return 0;

	cef_client_t *client = luacef_checkudata(L, 2, __client__);
	if (!client) return 0;

	cef_string_t url = luacef_tostring(L, 3);

	cef_browser_settings_t *bs = luacef_checkudata(L, 4, __browser_settings__);
	if (!bs) return 0;

	cef_browser_t *browser = cef_browser_host_create_browser_sync(
		winfo,
		client,
		&url,
		bs,
		NULL
	);
	
	lua_pushinteger(L, (int)browser);
	return 1;
}

/*
	cef.ClearSchemeHandlerFactories() -> <int>
*/
static int luacef_clear_scheme_handler_factories(lua_State* L)
{
	int ret = cef_clear_scheme_handler_factories();

	lua_pushinteger(L, ret);
	return 1;
}

/*
	cef.CommandLineCreate() -> <CommandLine>
*/
static int luacef_command_line_create(lua_State* L)
{
	//cef_command_line_create();

	// todo

	return 1;
}

/*
	cef.CommandLineGetGlobal() -> <CommandLine>
*/
static int luacef_command_line_get_global(lua_State* L)
{
	//cef_command_line_get_global();

	// todo

	return 1;
}

/*
	cef.DictionaryValueCreate() -> <DictionaryValue>
*/
static luacef_dictionary_value_create(lua_State* L)
{
	//cef_dictionary_value_create;

	// todo

	return 1;
}

/*
	cef.CurrentlyOn(
		<ThreadId>
	) -> <int>
*/
static int luacef_currently_on(lua_State* L)
{
	//cef_currently_on;

	// todo

	return 1;
}

/*
	cef.ImageCreate() -> <Image>
*/
static int luacef_image_create(lua_State* L)
{
	//cef_image_create

	// todo

	return 1;
}

void luacef_funcs_reg(lua_State* L)
{

	lua_pushcfunction(L, luacef_show_browser);
	lua_setfield(L, -2, "ShowBrowser");
	
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

	lua_pushcfunction(L, luacef_create_browser);
	lua_setfield(L, -2, "CreateBrowser");

	lua_pushcfunction(L, luacef_create_browser_sync);
	lua_setfield(L, -2, "CreateBrowserSync");

	lua_pushcfunction(L, luacef_clear_scheme_handler_factories);
	lua_setfield(L, -2, "ClearSchemeHandlerFactories");
}