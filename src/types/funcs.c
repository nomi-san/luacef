#include "../luacef.h"

// app =======================


// ssl_info =============================

// ==============================

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

// ===============

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
	//ShowWindow(bh->get_window_handle(bh), lua_isnone(L, 2) ? 5 : lua_tointeger(L, 2));
	return 0;
}



// browser ===============================================

// ============================================

/*
	<int> ClearSchemeHandlerFactories()
*/
static int luacef_clear_scheme_handler_factories(lua_State* L)
{
	int ret = cef_clear_scheme_handler_factories();

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<CommandLine> CommandLineCreate()
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

	lua_pushcfunction(L, luacef_clear_scheme_handler_factories);
	lua_setfield(L, -2, "ClearSchemeHandlerFactories");
}