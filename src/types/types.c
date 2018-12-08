#include "../luacef.h"
                               
//          _   _   _             
//  ___ ___| |_| |_|_|___ ___ ___ 
// |_ -| -_|  _|  _| |   | . |_ -|
// |___|___|_| |_| |_|_|_|_  |___|
//=======================|___|=====
/*
	<Settings> {
		<uint> size;
		<bool> single_process;
		<str> browser_subprocess_path;
		<str> framework_dir_path;
		<bool> multi_threaded_message_loop;
		<bool> external_message_pump;
		<bool> windowless_rendering_enabled;
		<bool> command_line_args_disabled;
		<str> cache_path;
		<str> user_data_path;
		<bool> persist_session_cookies;
		<bool> persist_user_preferences;
		<str> user_agent;
		<str> product_version;
		<str> locale;
		<str> log_file;
		<int> log_severity;
		<str> javascript_flags;
		<str> resources_dir_path;
		<str> locales_dir_path;
		<bool> pack_loading_disabled;
		<int> remote_debugging_port;
		<int> uncaught_exception_stack_size;
		<bool> ignore_certificate_errors;
		<bool> enable_net_security_expiration;
		<uint> background_color;
		<str> accept_language_list;
	}
*/
#pragma region settings
static const char *__size							= "size";
static const char *__single_process					= "single_process";
static const char *__multi_threaded_message_loop	= "multi_threaded_message_loop";
static const char *__log_severity					= "log_severity";
static const char *__user_agent						= "user_agent";
static const char *__accept_language_list			= "accept_language_list";
static const char *__background_color				= "background_color";
static const char *__browser_subprocess_path		= "browser_subprocess_path";
static const char *__cache_path						= "cache_path";
static const char *__command_line_args_disabled		= "command_line_args_disabled";
static const char *__external_message_pump			= "external_message_pump";
static const char *__ignore_certificate_errors		= "ignore_certificate_errors";
static const char *__javascript_flags				= "javascript_flags";
static const char *__locales_dir_path				= "locales_dir_path";
static const char *__locale							= "locale";
static const char *__log_file						= "log_file";
static const char *__pack_loading_disabled			= "pack_loading_disabled";
static const char *__persist_session_cookies		= "persist_session_cookies";
static const char *__persist_user_preferences		= "persist_user_preferences";
static const char *__product_version				= "product_version";
static const char *__remote_debugging_port			= "remote_debugging_port";
static const char *__resources_dir_path				= "resources_dir_path";
static const char *__uncaught_exception_stack_size	= "uncaught_exception_stack_size";
static const char *__user_data_path					= "user_data_path";
static const char *__windowless_rendering_enabled	= "windowless_rendering_enabled";
static const char *__framework_dir_path				= "framework_dir_path";
static const char *__enable_net_security_expiration = "enable_net_security_expiration";
//static const char *__context_safety_implementation	= "context_safety_implementation";

static int luacef_settings_new(lua_State* L)
{
	size_t sz = sizeof(cef_settings_t);
	cef_settings_t* s = luacef_alloc(sz);
	s->size = sz;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __size))
			s->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __single_process))
			s->single_process = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __browser_subprocess_path))
			s->browser_subprocess_path = luacef_tostring(L, -1);
		
		if (lua_getfield(L, 1, __framework_dir_path))
			s->framework_dir_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __multi_threaded_message_loop))
			s->multi_threaded_message_loop = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __external_message_pump))
			s->external_message_pump = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __windowless_rendering_enabled))
			s->windowless_rendering_enabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __command_line_args_disabled))
			s->command_line_args_disabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __cache_path))
			s->cache_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __user_data_path))
			s->user_data_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __persist_session_cookies))
			s->persist_session_cookies = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __persist_user_preferences))
			s->persist_user_preferences = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __user_agent))
			s->user_agent = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __product_version))
			s->product_version = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __locale))
			s->locale = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __log_file))
			s->log_file = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __log_severity))
			s->log_severity = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __javascript_flags))
			s->javascript_flags = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __resources_dir_path))
			s->resources_dir_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __locales_dir_path))
			s->locales_dir_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __pack_loading_disabled))
			s->pack_loading_disabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __remote_debugging_port))
			s->remote_debugging_port = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __uncaught_exception_stack_size))
			s->uncaught_exception_stack_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __ignore_certificate_errors))
			s->ignore_certificate_errors = lua_tointeger(L, -1);
		
		if (lua_getfield(L, 1, __enable_net_security_expiration))
			s->enable_net_security_expiration = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __background_color))
			s->background_color = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __accept_language_list))
			s->accept_language_list = luacef_tostring(L, -1);

		//if (lua_getfield(L, 1, __context_safety_implementation))
			//s->context_safety_implementation = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, s, __settings__);
	return 1;
}

static int luacef_settings_index(lua_State* L)
{
	cef_settings_t* s = luacef_touserdata(L, 1);
	if (!s) return 0;

	const char* i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);
	
	else if (!strcmp(i, __size))
		lua_pushinteger(L, s->size);

	else if (!strcmp(i, __single_process))
		lua_pushboolean(L, s->single_process);

	else if (!strcmp(i, __browser_subprocess_path))
		s->browser_subprocess_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __framework_dir_path))
		s->framework_dir_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __multi_threaded_message_loop))
		lua_pushboolean(L, s->multi_threaded_message_loop);

	else if (!strcmp(i, __external_message_pump))
		lua_pushboolean(L, s->external_message_pump);

	else if (!strcmp(i, __windowless_rendering_enabled))
		lua_pushboolean(L, s->windowless_rendering_enabled);

	else if (!strcmp(i, __command_line_args_disabled))
		lua_pushboolean(L, s->command_line_args_disabled);

	else if (!strcmp(i, __cache_path))
		luacef_pushstring(L, &s->cache_path);

	else if (!strcmp(i, __user_data_path))
		luacef_pushstring(L, &s->user_data_path);

	else if (!strcmp(i, __persist_session_cookies))
		lua_pushboolean(L, s->persist_session_cookies);

	else if (!strcmp(i, __persist_user_preferences))
		lua_pushboolean(L, s->persist_user_preferences);

	else if (!strcmp(i, __user_agent))
		luacef_pushstring(L, &s->user_agent);

	else if (!strcmp(i, __product_version))
		luacef_pushstring(L, &s->product_version);

	else if (!strcmp(i, __locale))
		luacef_pushstring(L, &s->locale);

	else if (!strcmp(i, __log_file))
		luacef_pushstring(L, &s->log_file);

	else if (!strcmp(i, __log_severity))
		lua_pushinteger(L, s->log_severity);

	else if (!strcmp(i, __javascript_flags))
		luacef_pushstring(L, &s->javascript_flags);

	else if (!strcmp(i, __resources_dir_path))
		luacef_pushstring(L, &s->resources_dir_path);

	else if (!strcmp(i, __locales_dir_path))
		luacef_pushstring(L, &s->locales_dir_path);

	else if (!strcmp(i, __pack_loading_disabled))
		lua_pushboolean(L, s->pack_loading_disabled);

	else if (!strcmp(i, __remote_debugging_port))
		lua_pushinteger(L, s->remote_debugging_port);

	else if (!strcmp(i, __uncaught_exception_stack_size))
		lua_pushinteger(L, s->uncaught_exception_stack_size);

	else if (!strcmp(i, __ignore_certificate_errors))
		lua_pushboolean(L, s->ignore_certificate_errors);

	else if (!strcmp(i, __enable_net_security_expiration))
		lua_pushboolean(L, s->enable_net_security_expiration);

	else if (!strcmp(i, __background_color))
		lua_pushinteger(L, s->background_color);

	else if (!strcmp(i, __accept_language_list))
		luacef_pushstring(L, &s->accept_language_list);

	else return 0;

	return 1;
}

static int luacef_settings_newindex(lua_State* L)
{
	cef_settings_t* s = luacef_touserdata(L, 1);
	if (!s) return 0;

	const char* i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __size))
		s->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __single_process))
		s->single_process = lua_tointeger(L, -1);

	else if (!strcmp(i, __browser_subprocess_path))
		s->browser_subprocess_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __framework_dir_path))
		s->framework_dir_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __multi_threaded_message_loop))
		s->multi_threaded_message_loop = lua_tointeger(L, -1);

	else if (!strcmp(i, __external_message_pump))
		s->external_message_pump = lua_tointeger(L, -1);

	else if (!strcmp(i, __windowless_rendering_enabled))
		s->windowless_rendering_enabled = lua_tointeger(L, -1);

	else if (!strcmp(i, __command_line_args_disabled))
		s->command_line_args_disabled = lua_tointeger(L, -1);

	else if (!strcmp(i, __cache_path))
		s->cache_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __user_data_path))
		s->user_data_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __persist_session_cookies))
		s->persist_session_cookies = lua_tointeger(L, -1);

	else if (!strcmp(i, __persist_user_preferences))
		s->persist_user_preferences = lua_tointeger(L, -1);

	else if (!strcmp(i, __user_agent))
		s->user_agent = luacef_tostring(L, -1);

	else if (!strcmp(i, __product_version))
		s->product_version = luacef_tostring(L, -1);

	else if (!strcmp(i, __locale))
		s->locale = luacef_tostring(L, -1);

	else if (!strcmp(i, __log_file))
		s->log_file = luacef_tostring(L, -1);

	else if (!strcmp(i, __log_severity))
		s->log_severity = lua_tointeger(L, -1);

	else if (!strcmp(i, __javascript_flags))
		s->javascript_flags = luacef_tostring(L, -1);

	else if (!strcmp(i, __resources_dir_path))
		s->resources_dir_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __locales_dir_path))
		s->locales_dir_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __pack_loading_disabled))
		s->pack_loading_disabled = lua_tointeger(L, -1);

	else if (!strcmp(i, __remote_debugging_port))
		s->remote_debugging_port = lua_tointeger(L, -1);

	else if (!strcmp(i, __uncaught_exception_stack_size))
		s->uncaught_exception_stack_size = lua_tointeger(L, -1);

	else if (!strcmp(i, __ignore_certificate_errors))
		s->ignore_certificate_errors = lua_tointeger(L, -1);

	else if (!strcmp(i, __enable_net_security_expiration))
		s->enable_net_security_expiration = lua_tointeger(L, -1);

	else if (!strcmp(i, __background_color))
		s->background_color = lua_tointeger(L, -1);

	else if (!strcmp(i, __accept_language_list))
		s->accept_language_list = luacef_tostring(L, -1);

	return 0;
}

static const luaL_Reg luacef_settings_m[] = {
	//{ "__gc" , luacef_release },
	{ "__index" , luacef_settings_index },
	{ "__newindex" , luacef_settings_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                          _                  _           _              _   _   _             
//  ___ ___ ___ _ _ ___ ___| |_    ___ ___ ___| |_ ___ _ _| |_    ___ ___| |_| |_|_|___ ___ ___ 
// |  _| -_| . | | | -_|_ -|  _|  |  _| . |   |  _| -_|_'_|  _|  |_ -| -_|  _|  _| |   | . |_ -|
// |_| |___|_  |___|___|___|_|    |___|___|_|_|_| |___|_,_|_|    |___|___|_| |_| |_|_|_|_  |___|
//===========|_|=======================================================================|___|=====
/*
	<RequestContextSettings> {
		<str>	cache_path;
		<bool>	persist_session_cookies;
		<bool>	persist_user_preferences;
		<bool>	ignore_certificate_errors;
		<bool>	enable_net_security_expiration;
		<str>	accept_language_list;
	}
*/
#pragma region request_context_settings
//static const char *__size = "size";
//static const char *__cache_path = "cache_path";
//static const char *__persist_session_cookies = "persist_session_cookies";
//static const char *__persist_user_preferences = "persist_user_preferences";
//static const char *__ignore_certificate_errors = "ignore_certificate_errors";
//static const char *__enable_net_security_expiration = "enable_net_security_expiration";
//static const char *__accept_language_list = "accept_language_list";

static int luacef_request_context_settings_new(lua_State *L)
{
	size_t sz = sizeof(cef_request_context_settings_t);
	cef_request_context_settings_t *p = luacef_alloc(sz);
	p->size = sz;

	if (lua_istable(L, 1)) {
		
		if (lua_getfield(L, 1, __size))
			p->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __cache_path))
			p->cache_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __persist_session_cookies))
			p->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __persist_user_preferences))
			p->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __ignore_certificate_errors))
			p->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __enable_net_security_expiration))
			p->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __accept_language_list))
			p->accept_language_list = luacef_tostring(L, -1);

	}

	luacef_pushuserdata(L, p, __request_context_settings__);
	return 1;
}

static int luacef_request_context_settings_index(lua_State *L)
{
	cef_request_context_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __size))
		lua_pushinteger(L, p->size);

	else if (!strcmp(i, __cache_path))
		luacef_pushstring(L, &p->cache_path);

	else if (!strcmp(i, __persist_session_cookies))
		lua_pushboolean(L, p->persist_session_cookies);

	else if (!strcmp(i, __persist_user_preferences))
		lua_pushboolean(L, p->persist_user_preferences);

	else if (!strcmp(i, __ignore_certificate_errors))
		lua_pushboolean(L, p->ignore_certificate_errors);

	else if (!strcmp(i, __enable_net_security_expiration))
		lua_pushboolean(L, p->enable_net_security_expiration);

	else if (!strcmp(i, __accept_language_list))
		luacef_pushstring(L, &p->accept_language_list);

	else return 0;

	return 1;
}

static int luacef_request_context_settings_newindex(lua_State *L)
{
	cef_request_context_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __size))
		p->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __cache_path))
		p->cache_path = luacef_tostring(L, -1);

	else if (!strcmp(i, __persist_session_cookies))
		p->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __persist_user_preferences))
		p->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __ignore_certificate_errors))
		p->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __enable_net_security_expiration))
		p->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __accept_language_list))
		p->accept_language_list = luacef_tostring(L, -1);

	return 0;
}

static const luaL_Reg luacef_request_context_settings_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_request_context_settings_index },
	{ "__newindex", luacef_request_context_settings_newindex },
	{ NULL, NULL }
};
#pragma endregion

//  _                                        _   _   _             
// | |_ ___ ___ _ _ _ ___ ___ ___    ___ ___| |_| |_|_|___ ___ ___ 
// | . |  _| . | | | |_ -| -_|  _|  |_ -| -_|  _|  _| |   | . |_ -|
// |___|_| |___|_____|___|___|_|    |___|___|_| |_| |_|_|_|_  |___|
//========================================================|___|=====
/*
	<BrowserSettings> newBrowserSettings {
		<uint> size;
		<int> windowless_frame_rate;
		<str> standard_font_family;
		<str> fixed_font_family;
		<str> serif_font_family;
		<str> sans_serif_font_family;
		<str> cursive_font_family;
		<str> fantasy_font_family;
		<int> default_font_size;
		<int> default_fixed_font_size;
		<int> minimum_font_size;
		<int> minimum_logical_font_size;
		<str> default_encoding;
		<int> remote_fonts;
		<int> javascript;
		<int> javascript_close_windows;
		<int> javascript_access_clipboard;
		<int> javascript_dom_paste;
		<int> plugins;
		<int> universal_access_from_file_urls;
		<int> file_access_from_file_urls;
		<int> web_security;
		<int> image_loading;
		<int> image_shrink_standalone_to_fit;
		<int> text_area_resize;
		<int> tab_to_links;
		<int> local_storage;
		<int> databases;
		<int> application_cache;
		<int> webgl;
		<uint> background_color;
		<str> accept_language_list;
	}
*/
#pragma region browser_settings
//static const char *__size = "size";
static const char *__windowless_frame_rate = "windowless_frame_rate";
static const char *__standard_font_family = "standard_font_family";
static const char *__fixed_font_family = "fixed_font_family";
static const char *__serif_font_family = "serif_font_family";
static const char *__sans_serif_font_family = "sans_serif_font_family";
static const char *__cursive_font_family = "cursive_font_family";
static const char *__fantasy_font_family = "fantasy_font_family";
static const char *__default_font_size = "default_font_size";
static const char *__default_fixed_font_size = "default_fixed_font_size";
static const char *__minimum_font_size = "minimum_font_size";
static const char *__minimum_logical_font_size = "minimum_logical_font_size";
static const char *__default_encoding = "default_encoding";
static const char *__remote_fonts = "remote_fonts";
static const char *__javascript = "javascript";
static const char *__javascript_close_windows = "javascript_close_windows";
static const char *__javascript_access_clipboard = "javascript_access_clipboard";
static const char *__javascript_dom_paste = "javascript_dom_paste";
static const char *__plugins = "plugins";
static const char *__universal_access_from_file_urls = "universal_access_from_file_urls";
static const char *__file_access_from_file_urls = "file_access_from_file_urls";
static const char *__web_security = "web_security";
static const char *__image_loading = "image_loading";
static const char *__image_shrink_standalone_to_fit = "image_shrink_standalone_to_fit";
static const char *__text_area_resize = "text_area_resize";
static const char *__tab_to_links = "tab_to_links";
static const char *__local_storage = "local_storage";
static const char *__databases = "databases";
static const char *__application_cache = "application_cache";
static const char *__webgl = "webgl";
//static const char *__background_color = "background_color";
//static const char *__accept_language_list = "accept_language_list";

static int luacef_browser_settings_new(lua_State *L)
{
	size_t sz = sizeof(cef_browser_settings_t);
	cef_browser_settings_t *p = luacef_alloc(sz);
	p->size = sz;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __size))
			p->size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __windowless_frame_rate))
			p->windowless_frame_rate = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __standard_font_family))
			p->standard_font_family = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __fixed_font_family))
			p->fixed_font_family = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __serif_font_family))
			p->serif_font_family = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __sans_serif_font_family))
			p->sans_serif_font_family = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __cursive_font_family))
			p->cursive_font_family = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __fantasy_font_family))
			p->fantasy_font_family = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __default_font_size))
			p->default_font_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __default_fixed_font_size))
			p->default_fixed_font_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __minimum_font_size))
			p->minimum_font_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __minimum_logical_font_size))
			p->minimum_logical_font_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __default_encoding))
			p->default_encoding = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __remote_fonts))
			p->remote_fonts = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __javascript))
			p->javascript = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __javascript_close_windows))
			p->javascript_close_windows = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __javascript_access_clipboard))
			p->javascript_access_clipboard = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __javascript_dom_paste))
			p->javascript_dom_paste = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __plugins))
			p->plugins = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __universal_access_from_file_urls))
			p->universal_access_from_file_urls = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __file_access_from_file_urls))
			p->file_access_from_file_urls = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __web_security))
			p->web_security = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __image_loading))
			p->image_loading = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __image_shrink_standalone_to_fit))
			p->image_shrink_standalone_to_fit = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __text_area_resize))
			p->text_area_resize = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __tab_to_links))
			p->tab_to_links = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __local_storage))
			p->local_storage = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __databases))
			p->databases = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __application_cache))
			p->application_cache = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __webgl))
			p->webgl = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __background_color))
			p->background_color = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __accept_language_list))
			p->accept_language_list = luacef_tostring(L, -1);
	}

	luacef_pushuserdata(L, p, __browser_settings__);
	return 1;
}

static int luacef_browser_settings_index(lua_State *L)
{
	cef_browser_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __size))
		lua_pushinteger(L, p->size);

	else if (!strcmp(i, __windowless_frame_rate))
		lua_pushinteger(L, p->windowless_frame_rate);

	else if (!strcmp(i, __standard_font_family))
		luacef_pushstring(L, &p->standard_font_family);

	else if (!strcmp(i, __fixed_font_family))
		luacef_pushstring(L, &p->fixed_font_family);

	else if (!strcmp(i, __serif_font_family))
		luacef_pushstring(L, &p->serif_font_family);

	else if (!strcmp(i, __sans_serif_font_family))
		luacef_pushstring(L, &p->sans_serif_font_family);

	else if (!strcmp(i, __cursive_font_family))
		luacef_pushstring(L, &p->cursive_font_family);

	else if (!strcmp(i, __fantasy_font_family))
		luacef_pushstring(L, &p->fantasy_font_family);

	else if (!strcmp(i, __default_font_size))
		lua_pushinteger(L, p->default_font_size);

	else if (!strcmp(i, __default_fixed_font_size))
		lua_pushinteger(L, p->default_fixed_font_size);

	else if (!strcmp(i, __minimum_font_size))
		lua_pushinteger(L, p->minimum_font_size);

	else if (!strcmp(i, __minimum_logical_font_size))
		lua_pushinteger(L, p->minimum_logical_font_size);

	else if (!strcmp(i, __default_encoding))
		luacef_pushstring(L, &p->default_encoding);

	else if (!strcmp(i, __remote_fonts))
		lua_pushinteger(L, p->remote_fonts);

	else if (!strcmp(i, __javascript))
		lua_pushinteger(L, p->javascript);

	else if (!strcmp(i, __javascript_close_windows))
		lua_pushinteger(L, p->javascript_close_windows);

	else if (!strcmp(i, __javascript_access_clipboard))
		lua_pushinteger(L, p->javascript_access_clipboard);

	else if (!strcmp(i, __javascript_dom_paste))
		lua_pushinteger(L, p->javascript_dom_paste);

	else if (!strcmp(i, __plugins))
		lua_pushinteger(L, p->plugins);

	else if (!strcmp(i, __universal_access_from_file_urls))
		lua_pushinteger(L, p->universal_access_from_file_urls);

	else if (!strcmp(i, __file_access_from_file_urls))
		lua_pushinteger(L, p->file_access_from_file_urls);

	else if (!strcmp(i, __web_security))
		lua_pushinteger(L, p->web_security);

	else if (!strcmp(i, __image_loading))
		lua_pushinteger(L, p->image_loading);

	else if (!strcmp(i, __image_shrink_standalone_to_fit))
		lua_pushinteger(L, p->image_shrink_standalone_to_fit);

	else if (!strcmp(i, __text_area_resize))
		lua_pushinteger(L, p->text_area_resize);

	else if (!strcmp(i, __tab_to_links))
		lua_pushinteger(L, p->tab_to_links);

	else if (!strcmp(i, __local_storage))
		lua_pushinteger(L, p->local_storage);

	else if (!strcmp(i, __databases))
		lua_pushinteger(L, p->databases);

	else if (!strcmp(i, __application_cache))
		lua_pushinteger(L, p->application_cache);

	else if (!strcmp(i, __webgl))
		lua_pushinteger(L, p->webgl);

	else if (!strcmp(i, __background_color))
		lua_pushinteger(L, p->background_color);

	else if (!strcmp(i, __accept_language_list))
		luacef_pushstring(L, &p->accept_language_list);

	else return 0;

	return 1;
}

static int luacef_browser_settings_newindex(lua_State *L)
{
	cef_browser_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __size))
		p->size = lua_tointeger(L, -1);

	else if (!strcmp(i, __windowless_frame_rate))
		p->windowless_frame_rate = lua_tointeger(L, -1);

	else if (!strcmp(i, __standard_font_family))
		p->standard_font_family = luacef_tostring(L, -1);

	else if (!strcmp(i, __fixed_font_family))
		p->fixed_font_family = luacef_tostring(L, -1);

	else if (!strcmp(i, __serif_font_family))
		p->serif_font_family = luacef_tostring(L, -1);

	else if (!strcmp(i, __sans_serif_font_family))
		p->sans_serif_font_family = luacef_tostring(L, -1);

	else if (!strcmp(i, __cursive_font_family))
		p->cursive_font_family = luacef_tostring(L, -1);

	else if (!strcmp(i, __fantasy_font_family))
		p->fantasy_font_family = luacef_tostring(L, -1);

	else if (!strcmp(i, __default_font_size))
		p->default_font_size = lua_tointeger(L, -1);

	else if (!strcmp(i, __default_fixed_font_size))
		p->default_fixed_font_size = lua_tointeger(L, -1);

	else if (!strcmp(i, __minimum_font_size))
		p->minimum_font_size = lua_tointeger(L, -1);

	else if (!strcmp(i, __minimum_logical_font_size))
		p->minimum_logical_font_size = lua_tointeger(L, -1);

	else if (!strcmp(i, __default_encoding))
		p->default_encoding = luacef_tostring(L, -1);

	else if (!strcmp(i, __remote_fonts))
		p->remote_fonts = lua_tointeger(L, -1);

	else if (!strcmp(i, __javascript))
		p->javascript = lua_tointeger(L, -1);

	else if (!strcmp(i, __javascript_close_windows))
		p->javascript_close_windows = lua_tointeger(L, -1);

	else if (!strcmp(i, __javascript_access_clipboard))
		p->javascript_access_clipboard = lua_tointeger(L, -1);

	else if (!strcmp(i, __javascript_dom_paste))
		p->javascript_dom_paste = lua_tointeger(L, -1);

	else if (!strcmp(i, __plugins))
		p->plugins = lua_tointeger(L, -1);

	else if (!strcmp(i, __universal_access_from_file_urls))
		p->universal_access_from_file_urls = lua_tointeger(L, -1);

	else if (!strcmp(i, __file_access_from_file_urls))
		p->file_access_from_file_urls = lua_tointeger(L, -1);

	else if (!strcmp(i, __web_security))
		p->web_security = lua_tointeger(L, -1);

	else if (!strcmp(i, __image_loading))
		p->image_loading = lua_tointeger(L, -1);

	else if (!strcmp(i, __image_shrink_standalone_to_fit))
		p->image_shrink_standalone_to_fit = lua_tointeger(L, -1);

	else if (!strcmp(i, __text_area_resize))
		p->text_area_resize = lua_tointeger(L, -1);

	else if (!strcmp(i, __tab_to_links))
		p->tab_to_links = lua_tointeger(L, -1);

	else if (!strcmp(i, __local_storage))
		p->local_storage = lua_tointeger(L, -1);

	else if (!strcmp(i, __databases))
		p->databases = lua_tointeger(L, -1);

	else if (!strcmp(i, __application_cache))
		p->application_cache = lua_tointeger(L, -1);

	else if (!strcmp(i, __webgl))
		p->webgl = lua_tointeger(L, -1);

	else if (!strcmp(i, __background_color))
		p->background_color = lua_tointeger(L, -1);

	else if (!strcmp(i, __accept_language_list))
		p->accept_language_list = luacef_tostring(L, -1);

	return 0;
}

static const luaL_Reg luacef_browser_settings_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_browser_settings_index },
	{ "__newindex", luacef_browser_settings_newindex },
	{ NULL, NULL}
};
#pragma endregion 

//          _             _       
//  _ _ ___| |___ ___ ___| |_ ___ 
// | | |  _| | . | .'|  _|  _|_ -|
// |___|_| |_|  _|__,|_| |_| |___|
//===========|_|===================
/*
	<URLParts> newURLParts {
		<str>	spec;
		<str>	scheme;
		<str>	username;
		<str>	password;
		<str>	host;
		<str>	port;
		<str>	origin;
		<str>	path;
		<str>	query;
	}
*/
#pragma region urlparts
static const char *__spec = "spec";
static const char *__scheme = "scheme";
static const char *__username = "username";
static const char *__password = "password";
static const char *__host = "host";
static const char *__port = "port";
static const char *__origin = "origin";
static const char *__path = "path";
static const char *__query = "query";

static int luacef_urlparts_new(lua_State *L)
{
	size_t sz = sizeof(cef_urlparts_t);
	cef_urlparts_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __spec))
			p->spec = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __scheme))
			p->scheme = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __username))
			p->username = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __password))
			p->password = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __host))
			p->host = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __port))
			p->port = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __origin))
			p->origin = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __path))
			p->path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __query))
			p->query = luacef_tostring(L, -1);
	}

	luacef_pushuserdata(L, p, __urlparts__);
	return 1;
}

static int luacef_urlparts_index(lua_State *L)
{
	cef_urlparts_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __spec))
		luacef_pushstring(L, &p->spec);

	else if (!strcmp(i, __scheme))
		luacef_pushstring(L, &p->scheme);

	else if (!strcmp(i, __username))
		luacef_pushstring(L, &p->username);

	else if (!strcmp(i, __password))
		luacef_pushstring(L, &p->password);

	else if (!strcmp(i, __host))
		luacef_pushstring(L, &p->host);

	else if (!strcmp(i, __port))
		luacef_pushstring(L, &p->port );

	else if (!strcmp(i, __origin))
		luacef_pushstring(L, &p->origin);

	else if (!strcmp(i, __path))
		luacef_pushstring(L, &p->path);

	else if (!strcmp(i, __query))
		luacef_pushstring(L, &p->query);

	else return 0;

	return 1;
}

static int luacef_urlparts_newindex(lua_State *L)
{
	cef_urlparts_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __spec))
		p->spec = luacef_tostring(L, -1);

	else if (!strcmp(i, __scheme))
		p->scheme = luacef_tostring(L, -1);

	else if (!strcmp(i, __username))
		p->username = luacef_tostring(L, -1);

	else if (!strcmp(i, __password))
		p->password = luacef_tostring(L, -1);

	else if (!strcmp(i, __host))
		p->host = luacef_tostring(L, -1);

	else if (!strcmp(i, __port))
		p->port = luacef_tostring(L, -1);

	else if (!strcmp(i, __origin))
		p->origin = luacef_tostring(L, -1);

	else if (!strcmp(i, __path))
		p->path = luacef_tostring(L, -1);

	else if (!strcmp(i, __query))
		p->query = luacef_tostring(L, -1);

	return 0;
}

static const luaL_Reg luacef_urlparts_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_urlparts_index },
	{ "__newindex", luacef_urlparts_newindex },
	{ NULL, NULL}
};
#pragma endregion

//              _   _     
//  ___ ___ ___| |_|_|___ 
// |  _| . | . | '_| | -_|
// |___|___|___|_,_|_|___|
//=========================
/*
	<Cookie> newCookie {
		<str>	name;
		<str>	value;
		<str>	domain;
		<str>	path;
		<bool>	secure;
		<bool>	httponly;
		<Time>	creation;
		<Time>	last_access;
		<bool>	has_expires;
		<Time>	expires;
	}
*/
#pragma region cookie
static const char *__name = "name";
static const char *__value = "value";
static const char *__domain = "domain";
//static const char *__path = "path";
static const char *__secure = "secure";
static const char *__httponly = "httponly";
static const char *__creation = "creation";
static const char *__last_access = "last_access";
static const char *__has_expires = "has_expires";
static const char *__expires = "expires";

static int luacef_cookie_new(lua_State *L)
{
	size_t sz = sizeof(cef_cookie_t);
	cef_cookie_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __name))
			p->name = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __value))
			p-> value = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __domain))
			p->domain = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __path))
			p->path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __secure))
			p->secure = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __httponly))
			p->httponly = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __creation))
			p->creation = *(cef_time_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __last_access))
			p->last_access = *(cef_time_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __has_expires))
			p->has_expires = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __expires))
			p->expires = *(cef_time_t*)luacef_touserdata(L, -1);
	}

	luacef_pushuserdata(L, p, __cookie__);
	return 1;
}

static int luacef_cookie_index(lua_State *L)
{
	cef_cookie_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __name))
		luacef_pushstring(L, &p->name);

	else if (!strcmp(i, __value))
		luacef_pushstring(L, &p->value);

	else if (!strcmp(i, __domain))
		luacef_pushstring(L, &p->domain);

	else if (!strcmp(i, __path))
		luacef_pushstring(L, &p->path);

	else if (!strcmp(i, __secure))
		lua_pushboolean(L, p->secure);

	else if (!strcmp(i, __httponly))
		lua_pushboolean(L, p->httponly);

	else if (!strcmp(i, __creation))
		luacef_pushuserdata(L, &p->creation, __time__);

	else if (!strcmp(i, __last_access))
		luacef_pushuserdata(L, &p->last_access , __time__);

	else if (!strcmp(i, __has_expires))
		lua_pushboolean(L, p->has_expires);

	else if (!strcmp(i, __expires))
		luacef_pushuserdata(L, &p->expires, __time__);

	else return 0;

	return 1;
}

static int luacef_cookie_newindex(lua_State *L)
{
	cef_cookie_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __name))
		p->name = luacef_tostring(L, -1);

	else if (!strcmp(i, __value))
		p->value = luacef_tostring(L, -1);

	else if (!strcmp(i, __domain))
		p->domain = luacef_tostring(L, -1);

	else if (!strcmp(i, __path))
		p->path = luacef_tostring(L, -1);

	else if (!strcmp(i, __secure))
		p->secure = lua_tointeger(L, -1);

	else if (!strcmp(i, __httponly))
		p->httponly = lua_tointeger(L, -1);

	else if (!strcmp(i, __creation))
		p->creation = *(cef_time_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __last_access))
		p->last_access = *(cef_time_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __has_expires))
		p->has_expires = lua_tointeger(L, -1);

	else if (!strcmp(i, __expires))
		p->expires = *(cef_time_t*)luacef_touserdata(L, -1);

	return 0;
}

static const luaL_Reg luacef_cookie_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_cookie_index },
	{ "__newindex", luacef_cookie_newindex },
	{ NULL, NULL}
};
#pragma endregion

//          _     _   
//  ___ ___|_|___| |_ 
// | . | . | |   |  _|
// |  _|___|_|_|_|_|  
//=|_|=================
/*
	<Point> newPoint {
		<int>	x;
		<int>	y;
	}
*/
#pragma region point
static const char *__x = "x";
static const char *__y = "y";

static int luacef_point_new(lua_State *L)
{
	size_t sz = sizeof(cef_point_t);
	cef_point_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __x))
			p->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __y))
			p->y = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __point__);
	return 1;
}

static int luacef_point_index(lua_State *L)
{
	cef_point_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __x))
		lua_pushinteger(L, p->x);

	else if (!strcmp(i, __y))
		lua_pushinteger(L, p->y);

	else return 0;

	return 1;
}

static int luacef_point_newindex(lua_State *L)
{
	cef_point_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __x))
		p->x = lua_tointeger(L, -1);

	else if (!strcmp(i, __y))
		p->y = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_point_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_point_index },
	{ "__newindex", luacef_point_newindex },
	{ NULL, NULL}
};
#pragma endregion

//              _   
//  ___ ___ ___| |_ 
// |  _| -_|  _|  _|
// |_| |___|___|_|  
//===================
/*
	<Rect> {
		<int> x;
		<int> y;
		<int> width;
		<int> height;
	}
*/
#pragma region rect
//static const char *__x = "x";
//static const char *__y = "y";
static const char *__width = "width";
static const char *__height = "height";

static int luacef_rect_new(lua_State *L)
{
	size_t sz = sizeof(cef_rect_t);
	cef_rect_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __x))
			p->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __y))
			p->y = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __width))
			p->width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __height))
			p->height = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __rect__);
	return 1;
}

static int luacef_rect_index(lua_State *L)
{
	cef_rect_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __x))
		lua_pushinteger(L, p->x);

	else if (!strcmp(i, __y))
		lua_pushinteger(L, p->y);

	else if (!strcmp(i, __width))
		lua_pushinteger(L, p->width);

	else if (!strcmp(i, __height))
		lua_pushinteger(L, p->height);

	else return 0;

	return 1;
}

static int luacef_rect_newindex(lua_State *L)
{
	cef_rect_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __x))
		p->x = lua_tointeger(L, -1);

	else if (!strcmp(i, __y))
		p->y = lua_tointeger(L, -1);

	else if (!strcmp(i, __width))
		p->width = lua_tointeger(L, -1);

	else if (!strcmp(i, __height))
		p->height = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_rect_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_rect_index },
	{ "__newindex", luacef_rect_newindex },
	{ NULL, NULL}
};
#pragma endregion       

//      _         
//  ___|_|___ ___ 
// |_ -| |- _| -_|
// |___|_|___|___|
//=================
/*
	<Size> {
		<int>	width;
		<int>	height
	}
*/
#pragma region size
//static const char *__width = "width";
//static const char *__height = "height";

static int luacef_size_new(lua_State *L)
{
	size_t sz = sizeof(cef_size_t);
	cef_size_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __width))
			p->width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __height))
			p->height = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __size__);
	return 1;
}

static int luacef_size_index(lua_State *L)
{
	cef_size_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __width))
		lua_pushinteger(L, p->width);

	else if (!strcmp(i, __height))
		lua_pushinteger(L, p->height);

	else return 0;

	return 1;
}

static int luacef_size_newindex(lua_State *L)
{
	cef_size_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __width))
		p->width = lua_tointeger(L, -1);

	else if (!strcmp(i, __height))
		p->height = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_size_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_size_index },
	{ "__newindex", luacef_size_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                      
//  ___ ___ ___ ___ ___ 
// |  _| .'|   | . | -_|
// |_| |__,|_|_|_  |___|
//=============|___|=====
/*
	<Range> {
		<int>	from;
		<int>	to
	}
*/
#pragma region range
static const char *__from = "from";
static const char *__to = "to";

static int luacef_range_new(lua_State *L)
{
	size_t sz = sizeof(cef_range_t);
	cef_range_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __from))
			p->from = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __to))
			p->to = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __range__);
	return 1;
}

static int luacef_range_index(lua_State *L)
{
	cef_range_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __from))
		lua_pushinteger(L, p->from);

	else if (!strcmp(i, __to))
		lua_pushinteger(L, p->to);

	else return 0;

	return 1;
}

static int luacef_range_newindex(lua_State *L)
{
	cef_range_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __from))
		p->from = lua_tointeger(L, -1);

	else if (!strcmp(i, __to))
		p->to = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_range_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_range_index },
	{ "__newindex", luacef_range_newindex },
	{ NULL, NULL}
};
#pragma endregion

//  _             _       
// |_|___ ___ ___| |_ ___ 
// | |   |_ -| -_|  _|_ -|
// |_|_|_|___|___|_| |___|
//=========================
/*
	<Insets> {
		<int>	top;
		<int>	left;
		<int>	bottom;
		<int>	right;
	}
*/
#pragma region insets
static const char *__top = "top";
static const char *__left = "left";
static const char *__bottom = "bottom";
static const char *__right = "right";

static int luacef_insets_new(lua_State *L)
{
	size_t sz = sizeof(cef_insets_t);
	cef_insets_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __top))
			p->top = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __left))
			p->left = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __bottom))
			p->bottom = lua_tointeger(L, -1);
		
		if (lua_getfield(L, 1, __right))
			p->right = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __insets__);
	return 1;
}

static int luacef_insets_index(lua_State *L)
{
	cef_insets_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __top))
		lua_pushinteger(L, p->top);

	else if (!strcmp(i, __left))
		lua_pushinteger(L, p->left);

	else if (!strcmp(i, __bottom))
		lua_pushinteger(L, p->bottom);

	else if (!strcmp(i, __right))
		lua_pushinteger(L, p->right);

	else return 0;

	return 1;
}

static int luacef_insets_newindex(lua_State *L)
{
	cef_insets_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __top))
		p->top = lua_tointeger(L, -1);

	else if (!strcmp(i, __left))
		p->left = lua_tointeger(L, -1);

	else if (!strcmp(i, __bottom))
		p->bottom = lua_tointeger(L, -1);

	else if (!strcmp(i, __right))
		p->right = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_insets_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_insets_index },
	{ "__newindex", luacef_insets_newindex },
	{ NULL, NULL}
};
#pragma endregion

//    _                     _   _                    _         
//  _| |___ ___ ___ ___ ___| |_| |___    ___ ___ ___|_|___ ___ 
// | . |  _| .'| . | . | .'| . | | -_|  |  _| -_| . | | . |   |
// |___|_| |__,|_  |_  |__,|___|_|___|  |_| |___|_  |_|___|_|_|
//=============|___|___|========================|___|===========
/*
	<DraggableRegion> {
		<Rect>	bounds;
		<bool>	draggable;
	}
*/
#pragma region draggable_region
static const char *__bounds = "bounds";
static const char *__draggable = "draggable";

static int luacef_draggable_region_new(lua_State *L)
{
	size_t sz = sizeof(cef_draggable_region_t);
	cef_draggable_region_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __bounds))
			p->bounds = *(cef_rect_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __draggable))
			p->draggable = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __draggable_region__);
	return 1;
}

static int luacef_draggable_region_index(lua_State *L)
{
	cef_draggable_region_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __bounds))
		luacef_pushuserdata(L, &p->bounds, __range__);

	else if (!strcmp(i, __draggable))
		lua_pushboolean(L, p->draggable);

	else return 0;

	return 1;
}

static int luacef_draggable_region_newindex(lua_State *L)
{
	cef_draggable_region_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __bounds))
		p->bounds = *(cef_rect_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __draggable))
		p->draggable = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_draggable_region_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_draggable_region_index },
	{ "__newindex", luacef_draggable_region_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                             _     ___     
//  ___ ___ ___ ___ ___ ___   |_|___|  _|___ 
// |_ -|  _|  _| -_| -_|   |  | |   |  _| . |
// |___|___|_| |___|___|_|_|  |_|_|_|_| |___|
//============================================
/*
	<ScreenInfo> newScreenInfo {
		<float> device_scale_factor;
		<int> depth;
		<int> depth_per_component;
		<bool> is_monochrome;
		<Rect> rect;
		<Rect> available_rect;
	}
*/
#pragma region screen_info
static const char *__device_scale_factor = "device_scale_factor";
static const char *__depth = "depth";
static const char *__depth_per_component = "depth_per_component";
static const char *__is_monochrome = "is_monochrome";
static const char *__rect = "rect";
static const char *__available_rect = "available_rect";

static int luacef_screen_info_new(lua_State *L)
{
	size_t sz = sizeof(cef_screen_info_t);
	cef_screen_info_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __device_scale_factor))
			p->device_scale_factor = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __depth))
			p->depth = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __depth_per_component))
			p->depth_per_component = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __is_monochrome))
			p->is_monochrome = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __rect))
			p->rect = *(cef_rect_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __available_rect))
			p->available_rect = *(cef_rect_t*)luacef_touserdata(L, -1);
	}

	luacef_pushuserdata(L, p, __screen_info__);
	return 1;
}

static int luacef_screen_info_index(lua_State *L)
{
	cef_screen_info_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __device_scale_factor))
		lua_pushnumber(L, p->device_scale_factor);

	else if (!strcmp(i, __depth))
		lua_pushinteger(L, p->depth);

	else if (!strcmp(i, __depth_per_component))
		lua_pushinteger(L, p->depth_per_component);

	else if (!strcmp(i, __is_monochrome))
		lua_pushinteger(L, p->is_monochrome);

	else if (!strcmp(i, __rect))
		luacef_pushuserdata(L, &p->rect, __rect__);

	else if (!strcmp(i, __available_rect))
		luacef_pushuserdata(L, &p->available_rect, __rect__);

	else return 0;

	return 1;
}

static int luacef_screen_info_newindex(lua_State *L)
{
	cef_screen_info_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __device_scale_factor))
		p->device_scale_factor = lua_tonumber(L, -1);

	else if (!strcmp(i, __depth))
		p->depth = lua_tointeger(L, -1);

	else if (!strcmp(i, __depth_per_component))
		p->depth_per_component = lua_tointeger(L, -1);

	else if (!strcmp(i, __is_monochrome))
		p->is_monochrome = lua_tointeger(L, -1);

	else if (!strcmp(i, __rect))
		p->rect = *(cef_rect_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __available_rect))
		p->available_rect = *(cef_rect_t*)luacef_touserdata(L, -1);

	return 0;
}

static const luaL_Reg luacef_screen_info_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_screen_info_index },
	{ "__newindex", luacef_screen_info_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                                           _   
//  _____ ___ _ _ ___ ___    ___ _ _ ___ ___| |_ 
// |     | . | | |_ -| -_|  | -_| | | -_|   |  _|
// |_|_|_|___|___|___|___|  |___|\_/|___|_|_|_|  
//================================================
/*
	<MouseEvent> {
		<int> x;
		<int> y;
		<int> modifiers;
	}
*/
#pragma region mouse_event
static const char *__modifiers = "modifiers";

static int luacef_mouse_event_new(lua_State *L)
{
	size_t sz = sizeof(cef_mouse_event_t);
	cef_mouse_event_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {
		
		if (lua_getfield(L, 1, __x))
			p->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __y))
			p->y = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __modifiers))
			p->modifiers = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __mouse_event__);
	return 1;
}

static int luacef_mouse_event_index(lua_State *L)
{
	cef_mouse_event_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __x))
		lua_pushinteger(L, p->x);

	else if (!strcmp(i, __y))
		lua_pushinteger(L, p->y);

	else if (!strcmp(i, __modifiers))
		lua_pushinteger(L, p->modifiers);

	else return 0;

	return 1;
}

static int luacef_mouse_event_newindex(lua_State *L)
{
	cef_mouse_event_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __x))
		p->x = lua_tointeger(L, -1);

	else if (!strcmp(i, __y))
		p->y = lua_tointeger(L, -1);

	else if (!strcmp(i, __modifiers))
		p->modifiers = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_mouse_event_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_mouse_event_index },
	{ "__newindex", luacef_mouse_event_newindex },
	{ NULL, NULL}
};
#pragma endregion

//  _                              _   
// | |_ ___ _ _    ___ _ _ ___ ___| |_ 
// | '_| -_| | |  | -_| | | -_|   |  _|
// |_,_|___|_  |  |___|\_/|___|_|_|_|  
//=========|___|========================
/*
	<KeyEvent> newKeyEvent {
		<int>	type;
		<int>	modifires;
		<int>	windows_key_code;
		<int>	native_key_code;
		<bool>	is_system_key;
		<str>	character;
		<str>	unmodified_character;
		<bool>	focus_on_editable_field;
	}
*/
#pragma region key_event
static const char *__type = "type";
//static const char *__modifiers = "modifiers";
static const char *__windows_key_code = "windows_key_code";
static const char *__native_key_code = "native_key_code";
static const char *__is_system_key = "is_system_key";
static const char *__character = "character";
static const char *__unmodified_character = "unmodified_character";
static const char *__focus_on_editable_field = "focus_on_editable_field";

static int luacef_key_event_new(lua_State *L)
{
	size_t sz = sizeof(cef_key_event_t);
	cef_key_event_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __type))
			p->type = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __modifiers))
			p->modifiers = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __windows_key_code))
			p->windows_key_code = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __native_key_code))
			p->native_key_code = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __is_system_key))
			p->type = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __character)) {
			wchar_t buf[1];
			mbstowcs(buf, lua_tostring(L, -1), 1);
			p->character = buf[0];
		}

		if (lua_getfield(L, 1, __unmodified_character)) {
			wchar_t buf[1];
			mbstowcs(buf, lua_tostring(L, -1), 1);
			p->unmodified_character = buf[0];
		}

		if (lua_getfield(L, 1, __focus_on_editable_field))
			p->focus_on_editable_field = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __key_event__);
	return 1;
}

static int luacef_key_event_index(lua_State *L)
{
	cef_key_event_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);
	
	else if (!strcmp(i, __type))
		lua_pushinteger(L, p->type);

	else if (!strcmp(i, __modifiers))
		lua_pushinteger(L, p->modifiers);

	else if (!strcmp(i, __windows_key_code))
		lua_pushinteger(L, p->windows_key_code);

	else if (!strcmp(i, __native_key_code))
		lua_pushinteger(L, p->native_key_code);

	else if (!strcmp(i, __is_system_key))
		lua_pushboolean(L, p->type);

	else if (!strcmp(i, __character)) {
		cef_string_utf8_t s = { 0 };
		cef_string_to_utf8(&p->character, 1, &s);
		char buf[2] = { s.str[0], '\0' };
		lua_pushstring(L, buf);
	}

	else if (!strcmp(i, __unmodified_character)) {
		cef_string_utf8_t s = { 0 };
		cef_string_to_utf8(&p->unmodified_character, 1, &s);
		char buf[2] = { s.str[0], '\0' };
		lua_pushstring(L, buf);
	}

	else if (!strcmp(i, __focus_on_editable_field))
		lua_pushboolean(L, p->focus_on_editable_field);

	else return 0;

	return 1;
}

static int luacef_key_event_newindex(lua_State *L)
{
	cef_key_event_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __type))
		p->type = lua_tointeger(L, -1);

	else if (!strcmp(i, __modifiers))
		p->modifiers = lua_tointeger(L, -1);

	else if (!strcmp(i, __windows_key_code))
		p->windows_key_code = lua_tointeger(L, -1);

	else if (!strcmp(i, __native_key_code))
		p->native_key_code = lua_tointeger(L, -1);

	else if (!strcmp(i, __is_system_key))
		p->type = lua_tointeger(L, -1);

	else if (!strcmp(i, __character)) {
		wchar_t buf[1];
		mbstowcs(buf, lua_tostring(L, -1), 1);
		p->character = buf[0];
	}

	else if (!strcmp(i, __unmodified_character)) {
		wchar_t buf[1];
		mbstowcs(buf, lua_tostring(L, -1), 1);
		p->unmodified_character = buf[0];
	}

	else if (!strcmp(i, __focus_on_editable_field))
		p->focus_on_editable_field = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_key_event_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_key_event_index },
	{ "__newindex", luacef_key_event_newindex },
	{ NULL, NULL }
};
#pragma endregion

//                         ___         _                   
//  ___ ___ ___ _ _ ___   |  _|___ ___| |_ _ _ ___ ___ ___ 
// | . | . | . | | | . |  |  _| -_| .'|  _| | |  _| -_|_ -|
// |  _|___|  _|___|  _|  |_| |___|__,|_| |___|_| |___|___|
//=|_|=====|_|=====|_|======================================
/*
	<PopupFeatures> {
		<int> x;
		<int> xSet;
		<int> y;
		<int> ySet;
		<int> width;
		<int> widthSet;
		<int> height;
		<int> heightSet;
		<int> menuBarVisible;
		<int> statusBarVisible;
		<int> toolBarVisible;
		<int> locationBarVisible;
		<int> scrollbarsVisible;
		<int> resizable;
		<int> fullscreen;
		<int> dialog;
	}
*/
#pragma region popup_features
//static const char *__x = "x";
static const char *__xSet = "xSet";
//static const char *__y = "y";
static const char *__ySet = "ySet";
//static const char *__width = "width";
static const char *__widthSet = "widthSet";
//static const char *__height = "height";
static const char *__heightSet = "heightSet";
static const char *__menuBarVisible = "menuBarVisible";
static const char *__statusBarVisible = "statusBarVisible";
static const char *__toolBarVisible = "toolBarVisible";
static const char *__locationBarVisible = "locationBarVisible";
static const char *__scrollbarsVisible = "scrollbarsVisible";
static const char *__resizable = "resizable";
static const char *__fullscreen = "fullscreen";
static const char *__dialog = "dialog";

static int luacef_popup_features_new(lua_State *L)
{
	size_t sz = sizeof(cef_popup_features_t);
	cef_popup_features_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __x))
			p->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __xSet))
			p->xSet = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __y))
			p->y = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __ySet))
			p->ySet = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __width))
			p->width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __widthSet))
			p->widthSet = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __height))
			p->height = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __heightSet))
			p->heightSet = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __menuBarVisible))
			p->menuBarVisible = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __statusBarVisible))
			p->statusBarVisible = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __toolBarVisible))
			p->toolBarVisible = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __locationBarVisible))
			p->locationBarVisible = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __scrollbarsVisible))
			p->scrollbarsVisible = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __resizable))
			p->resizable = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __fullscreen))
			p->fullscreen = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __dialog))
			p->dialog = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __popup_features__);
	return 1;
}

static int luacef_popup_features_index(lua_State *L)
{
	cef_popup_features_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __x))
		lua_pushinteger(L, p->x);

	else if (!strcmp(i, __xSet))
		lua_pushinteger(L, p->xSet);

	else if (!strcmp(i, __y))
		lua_pushinteger(L, p->y);

	else if (!strcmp(i, __ySet))
		lua_pushinteger(L, p->ySet);

	else if (!strcmp(i, __width))
		lua_pushinteger(L, p->width);

	else if (!strcmp(i, __widthSet))
		lua_pushinteger(L, p->widthSet);

	else if (!strcmp(i, __height))
		lua_pushinteger(L, p->height);

	else if (!strcmp(i, __heightSet))
		lua_pushinteger(L, p->heightSet);

	else if (!strcmp(i, __menuBarVisible))
		lua_pushinteger(L, p->menuBarVisible);

	else if (!strcmp(i, __statusBarVisible))
		lua_pushinteger(L, p->statusBarVisible);

	else if (!strcmp(i, __toolBarVisible))
		lua_pushinteger(L, p->toolBarVisible);

	else if (!strcmp(i, __locationBarVisible))
		lua_pushinteger(L, p->locationBarVisible);

	else if (!strcmp(i, __scrollbarsVisible))
		lua_pushinteger(L, p->scrollbarsVisible);

	else if (!strcmp(i, __resizable))
		lua_pushinteger(L, p->resizable);

	else if (!strcmp(i, __fullscreen))
		lua_pushinteger(L, p->fullscreen);

	else if (!strcmp(i, __dialog))
		lua_pushinteger(L, p->dialog);
	
	else return 0;

	return 1;
}

static int luacef_popup_features_newindex(lua_State *L)
{
	cef_popup_features_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __x))
		p->x = lua_tointeger(L, -1);

	else if (!strcmp(i, __xSet))
		p->xSet = lua_tointeger(L, -1);

	else if (!strcmp(i, __y))
		p->y = lua_tointeger(L, -1);

	else if (!strcmp(i, __ySet))
		p->ySet = lua_tointeger(L, -1);

	else if (!strcmp(i, __width))
		p->width = lua_tointeger(L, -1);

	else if (!strcmp(i, __widthSet))
		p->widthSet = lua_tointeger(L, -1);

	else if (!strcmp(i, __height))
		p->height = lua_tointeger(L, -1);

	else if (!strcmp(i, __heightSet))
		p->heightSet = lua_tointeger(L, -1);

	else if (!strcmp(i, __menuBarVisible))
		p->menuBarVisible = lua_tointeger(L, -1);

	else if (!strcmp(i, __statusBarVisible))
		p->statusBarVisible = lua_tointeger(L, -1);

	else if (!strcmp(i, __toolBarVisible))
		p->toolBarVisible = lua_tointeger(L, -1);

	else if (!strcmp(i, __locationBarVisible))
		p->locationBarVisible = lua_tointeger(L, -1);

	else if (!strcmp(i, __scrollbarsVisible))
		p->scrollbarsVisible = lua_tointeger(L, -1);

	else if (!strcmp(i, __resizable))
		p->resizable = lua_tointeger(L, -1);

	else if (!strcmp(i, __fullscreen))
		p->fullscreen = lua_tointeger(L, -1);

	else if (!strcmp(i, __dialog))
		p->dialog = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_popup_features_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_popup_features_index },
	{ "__newindex", luacef_popup_features_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                          _ _   _         
//  ___ ___ ___ ___ ___ ___|_| |_|_|___ ___ 
// | . | -_| . | . | . |_ -| |  _| | . |   |
// |_  |___|___|  _|___|___|_|_| |_|___|_|_|
//=|___|=======|_|===========================
/*
	<Geoposition> {
		<double> latitude;
		<double> longitude;
		<double> altitude;
		<double> accuracy;
		<double> altitude_accuracy;
		<double> heading;
		<double> speed;
		<Time> timestamp;
		<int> error_code;
		<str> error_message;
	}
*/
#pragma region geoposition
static const char *__latitude = "latitude";
static const char *__longitude = "longitude";
static const char *__altitude = "altitude";
static const char *__accuracy = "accuracy";
static const char *__altitude_accuracy = "altitude_accuracy";
static const char *__heading = "heading";
static const char *__speed = "speed";
static const char *__timestamp = "timestamp";
static const char *__error_code = "error_code";
static const char *__error_message = "error_message";

static int luacef_geoposition_new(lua_State *L)
{
	size_t sz = sizeof(cef_geoposition_t);
	cef_geoposition_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __latitude))
			p->latitude = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __longitude))
			p->longitude = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __altitude))
			p->altitude = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __accuracy))
			p->accuracy = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __altitude_accuracy))
			p->altitude_accuracy = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __heading))
			p->heading = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __speed))
			p->speed = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __timestamp))
			p->timestamp = *(cef_time_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __error_code))
			p->error_code = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __error_message))
			p->error_message = luacef_tostring(L, -1);
	}

	luacef_pushuserdata(L, p, __geoposition__);
	return 1;
}

static int luacef_geoposition_index(lua_State *L)
{
	cef_geoposition_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __latitude))
		lua_pushnumber(L, p->latitude);

	else if (!strcmp(i, __longitude))
		lua_pushnumber(L, p->longitude);

	else if (!strcmp(i, __altitude))
		lua_pushnumber(L, p->altitude);

	else if (!strcmp(i, __accuracy))
		lua_pushnumber(L, p->accuracy);

	else if (!strcmp(i, __altitude_accuracy))
		lua_pushnumber(L, p->altitude_accuracy);

	else if (!strcmp(i, __heading))
		lua_pushnumber(L, p->heading);

	else if (!strcmp(i, __speed))
		lua_pushnumber(L, p->speed);

	else if (!strcmp(i, __timestamp))
		luacef_pushuserdata(L, &p->timestamp, __time__);

	else if (!strcmp(i, __error_code))
		lua_pushinteger(L, p->error_code);

	else if (!strcmp(i, __error_message))
		luacef_pushstring(L, &p->error_message);

	return 1;
}

static int luacef_geoposition_newindex(lua_State *L)
{
	cef_geoposition_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __latitude))
		p->latitude = lua_tonumber(L, -1);

	else if (!strcmp(i, __longitude))
		p->longitude = lua_tonumber(L, -1);

	else if (!strcmp(i, __altitude))
		p->altitude = lua_tonumber(L, -1);

	else if (!strcmp(i, __accuracy))
		p->accuracy = lua_tonumber(L, -1);

	else if (!strcmp(i, __altitude_accuracy))
		p->altitude_accuracy = lua_tonumber(L, -1);

	else if (!strcmp(i, __heading))
		p->heading = lua_tonumber(L, -1);

	else if (!strcmp(i, __speed))
		p->speed = lua_tonumber(L, -1);

	else if (!strcmp(i, __timestamp))
		p->timestamp = *(cef_time_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __error_code))
		p->error_code = lua_tointeger(L, -1);

	else if (!strcmp(i, __error_message))
		p->error_message = luacef_tostring(L, -1);

	return 0;
}

static const luaL_Reg luacef_geoposition_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_geoposition_index },
	{ "__newindex", luacef_geoposition_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                             _     ___     
//  ___ _ _ ___ ___ ___ ___   |_|___|  _|___ 
// |  _| | |  _|_ -| . |  _|  | |   |  _| . |
// |___|___|_| |___|___|_|    |_|_|_|_| |___|
//============================================
/*
	<Cursorinfo> {
		<Point> hotspot;
		<float> image_scale_factor;
		<udata> buffer;
		<Size> size;
	}
*/
#pragma region cursor_info
static const char *__hotspot = "hotspot";
static const char *__image_scale_factor = "image_scale_factor";
static const char *__buffer = "buffer";
//static const char *__size;

static int luacef_cursor_info_new(lua_State *L)
{
	size_t sz = sizeof(cef_cursor_info_t);
	cef_cursor_info_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __hotspot))
			p->hotspot = *(cef_point_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __image_scale_factor))
			p->image_scale_factor = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __buffer))
			p->buffer = lua_touserdata(L, -1);

		if (lua_getfield(L, 1, __size))
			p->size = *(cef_size_t*)luacef_touserdata(L, -1);
	}

	luacef_pushuserdata(L, p, __cursor_info__);
	return 1;
}

static int luacef_cursor_info_index(lua_State *L)
{
	cef_cursor_info_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __hotspot))
		luacef_pushuserdata(L, &p->hotspot, __point__);

	else if (!strcmp(i, __image_scale_factor))
		lua_pushnumber(L, p->image_scale_factor);

	else if (!strcmp(i, __buffer))
		lua_pushlightuserdata(L, p->buffer);

	else if (!strcmp(i, __size))
		luacef_pushuserdata(L, &p->size, __size__);

	return 1;
}

static int luacef_cursor_info_newindex(lua_State *L)
{
	cef_cursor_info_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __hotspot))
		p->hotspot = *(cef_point_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __image_scale_factor))
		p->image_scale_factor = lua_tonumber(L, -1);

	else if (!strcmp(i, __buffer))
		p->buffer = lua_touserdata(L, -1);

	else if (!strcmp(i, __size))
		p->size = *(cef_size_t*)luacef_touserdata(L, -1);

	return 0;
}

static const luaL_Reg luacef_cursor_info_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_cursor_info_index },
	{ "__newindex", luacef_cursor_info_newindex },
	{ NULL, NULL}
};
#pragma endregion

//        _ ___            _     _              _   _   _             
//  ___ _| |  _|   ___ ___|_|___| |_    ___ ___| |_| |_|_|___ ___ ___ 
// | . | . |  _|  | . |  _| |   |  _|  |_ -| -_|  _|  _| |   | . |_ -|
// |  _|___|_|    |  _|_| |_|_|_|_|    |___|___|_| |_| |_|_|_|_  |___|
//=|_|============|_|========================================|___|=====
/*
	<PDFPrintSettings> {
		<str> header_footer_title;
		<str> header_footer_url;
		<int> page_width;
		<int> page_height;
		<int> scale_factor;
		<double> margin_top;
		<double> margin_right;
		<double> margin_bottom;
		<double> margin_left;
		<int> margin_type;
		<bool> header_footer_enabled;
		<bool> selection_only;
		<bool> landscape;
		<bool> backgrounds_enabled;
	}
*/
#pragma region pdf_print_settings
static const char *__header_footer_title = "header_footer_title";
static const char *__header_footer_url = "header_footer_url";
static const char *__page_width = "page_width";
static const char *__page_height = "page_height";
static const char *__scale_factor = "scale_factor";
static const char *__margin_top = "margin_top";
static const char *__margin_right = "margin_right";
static const char *__margin_bottom = "margin_bottom";
static const char *__margin_left = "margin_left";
static const char *__margin_type = "margin_type";
static const char *__header_footer_enabled = "header_footer_enabled";
static const char *__selection_only = "selection_only";
static const char *__landscape = "landscape";
static const char *__backgrounds_enabled = "backgrounds_enabled";

static int luacef_pdf_print_settings_new(lua_State *L)
{
	size_t sz = sizeof(cef_pdf_print_settings_t);
	cef_pdf_print_settings_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __header_footer_url))
			p->header_footer_url = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __page_width))
			p->page_width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __page_height))
			p->page_height = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __scale_factor))
			p->scale_factor = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __margin_top))
			p->margin_top = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __margin_right))
			p->margin_right = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __margin_bottom))
			p->margin_bottom = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __margin_left))
			p->margin_left = lua_tonumber(L, -1);

		if (lua_getfield(L, 1, __margin_type))
			p->margin_type = lua_tointeger(L, -1);;

		if (lua_getfield(L, 1, __header_footer_enabled))
			p->header_footer_enabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __selection_only))
			p->selection_only = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __landscape))
			p->landscape = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __backgrounds_enabled))
			p->backgrounds_enabled = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __pdf_print_settings__);
	return 1;
}

static int luacef_pdf_print_settings_index(lua_State *L)
{
	cef_pdf_print_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __header_footer_title))
		luacef_pushstring(L, &p->header_footer_title);

	else if (!strcmp(i, __header_footer_url))
		luacef_pushstring(L, &p->header_footer_url);

	else if (!strcmp(i, __page_width))
		lua_pushinteger(L, p->page_width);

	else if (!strcmp(i, __page_height))
		lua_pushinteger(L, p->page_height);

	else if (!strcmp(i, __scale_factor))
		lua_pushinteger(L, p->scale_factor);

	else if (!strcmp(i, __margin_top))
		lua_pushnumber(L, p->margin_top);

	else if (!strcmp(i, __margin_right))
		lua_pushnumber(L, p->margin_right);

	else if (!strcmp(i, __margin_bottom))
		lua_pushnumber(L, p->margin_bottom);

	else if (!strcmp(i, __margin_left))
		lua_pushnumber(L, p->margin_left);

	else if (!strcmp(i, __margin_type))
		lua_pushinteger(L, p->margin_type);

	else if (!strcmp(i, __header_footer_enabled))
		lua_pushboolean(L, p->header_footer_enabled);

	else if (!strcmp(i, __selection_only))
		lua_pushboolean(L, p->selection_only);

	else if (!strcmp(i, __landscape))
		lua_pushboolean(L, p->landscape);

	else if (!strcmp(i, __backgrounds_enabled))
		lua_pushboolean(L, p->backgrounds_enabled);

	return 1;
}

static int luacef_pdf_print_settings_newindex(lua_State *L)
{
	cef_pdf_print_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __header_footer_title))
		p->header_footer_title = luacef_tostring(L, -1);

	else if (!strcmp(i, __header_footer_url))
		p->header_footer_url = luacef_tostring(L, -1);

	else if (!strcmp(i, __page_width))
		p->page_width = lua_tointeger(L, -1);

	else if (!strcmp(i, __page_height))
		p->page_height = lua_tointeger(L, -1);

	else if (!strcmp(i, __scale_factor))
		p->scale_factor = lua_tointeger(L, -1);

	else if (!strcmp(i, __margin_top))
		p->margin_top = lua_tonumber(L, -1);

	else if (!strcmp(i, __margin_right))
		p->margin_right = lua_tonumber(L, -1);

	else if (!strcmp(i, __margin_bottom))
		p->margin_bottom = lua_tonumber(L, -1);

	else if (!strcmp(i, __margin_left))
		p->margin_left = lua_tonumber(L, -1);

	else if (!strcmp(i, __margin_type))
		p->margin_type = lua_tointeger(L, -1);

	else if (!strcmp(i, __header_footer_enabled))
		p->header_footer_enabled = lua_tointeger(L, -1);

	else if (!strcmp(i, __selection_only))
		p->selection_only = lua_tointeger(L, -1);

	else if (!strcmp(i, __landscape))
		p->landscape = lua_tointeger(L, -1);

	else if (!strcmp(i, __backgrounds_enabled))
		p->backgrounds_enabled = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_pdf_print_settings_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_pdf_print_settings_index },
	{ "__newindex", luacef_pdf_print_settings_newindex },
	{ NULL, NULL}
};
#pragma endregion

//  _              _                 _              _   _   _             
// | |_ ___ _ _   | |___ _ _ ___ _ _| |_    ___ ___| |_| |_|_|___ ___ ___ 
// | . | . |_'_|  | | .'| | | . | | |  _|  |_ -| -_|  _|  _| |   | . |_ -|
// |___|___|_,_|  |_|__,|_  |___|___|_|    |___|___|_| |_| |_|_|_|_  |___|
//======================|___|====================================|___|=====
/*
	<BoxLayoutSettings> {
		<bool>	horizontal;
		<int>	inside_border_horizontal_spacing;
		<int>	inside_border_vertical_spacing;
		<Insets>	inside_border_insets;
		<int>	between_child_spacing;
		<int>	main_axis_alignment;
		<int>	cross_axis_alignment;
		<int>	minimum_cross_axis_size;
		<int>	default_flex;
	}
*/
#pragma region box_layout_settings
static const char *__horizontal = "horizontal";
static const char *__inside_border_horizontal_spacing = "inside_border_horizontal_spacing";
static const char *__inside_border_vertical_spacing = "inside_border_vertical_spacing";
static const char *__inside_border_insets = "inside_border_insets";
static const char *__between_child_spacing = "between_child_spacing";
static const char *__main_axis_alignment = "main_axis_alignment";
static const char *__cross_axis_alignment = "cross_axis_alignment";
static const char *__minimum_cross_axis_size = "minimum_cross_axis_size";
static const char *__default_flex = "default_flex";

static int luacef_box_layout_settings_new(lua_State *L)
{
	size_t sz = sizeof(cef_box_layout_settings_t);
	cef_box_layout_settings_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __horizontal))
			p->horizontal = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __inside_border_horizontal_spacing))
			p->inside_border_horizontal_spacing = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __inside_border_vertical_spacing))
			p->inside_border_vertical_spacing = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __inside_border_insets))
			p->inside_border_insets = *(cef_insets_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __between_child_spacing))
			p->between_child_spacing = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __main_axis_alignment))
			p->main_axis_alignment = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __cross_axis_alignment))
			p->cross_axis_alignment = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __minimum_cross_axis_size))
			p->minimum_cross_axis_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __default_flex))
			p->default_flex = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __box_layout_settings__);
	return 1;
}

static int luacef_box_layout_settings_index(lua_State *L)
{
	cef_box_layout_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __horizontal))
		lua_pushboolean(L, p->horizontal);

	else if (!strcmp(i, __inside_border_horizontal_spacing))
		lua_pushinteger(L, p->inside_border_horizontal_spacing);

	else if (!strcmp(i, __inside_border_vertical_spacing))
		lua_pushinteger(L, p->inside_border_vertical_spacing);

	else if (!strcmp(i, __inside_border_insets))
		luacef_pushuserdata(L, &p->inside_border_insets, __insets__);

	else if (!strcmp(i, __between_child_spacing))
		lua_pushinteger(L, p->between_child_spacing);

	else if (!strcmp(i, __main_axis_alignment))
		lua_pushinteger(L, p->main_axis_alignment);

	else if (!strcmp(i, __cross_axis_alignment))
		lua_pushinteger(L, p->cross_axis_alignment);

	else if (!strcmp(i, __minimum_cross_axis_size))
		lua_pushinteger(L, p->minimum_cross_axis_size);

	else if (!strcmp(i, __default_flex))
		lua_pushinteger(L, p->default_flex);

	else return 0;

	return 1;
}

static int luacef_box_layout_settings_newindex(lua_State *L)
{
	cef_box_layout_settings_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __horizontal))
		p->horizontal = lua_tointeger(L, -1);

	else if (!strcmp(i, __inside_border_horizontal_spacing))
		p->inside_border_horizontal_spacing = lua_tointeger(L, -1);

	else if (!strcmp(i, __inside_border_vertical_spacing))
		p->inside_border_vertical_spacing = lua_tointeger(L, -1);

	else if (!strcmp(i, __inside_border_insets))
		p->inside_border_insets = *(cef_insets_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __between_child_spacing))
		p->between_child_spacing = lua_tointeger(L, -1);

	else if (!strcmp(i, __main_axis_alignment))
		p->main_axis_alignment = lua_tointeger(L, -1);

	else if (!strcmp(i, __cross_axis_alignment))
		p->cross_axis_alignment = lua_tointeger(L, -1);

	else if (!strcmp(i, __minimum_cross_axis_size))
		p->minimum_cross_axis_size = lua_tointeger(L, -1);

	else if (!strcmp(i, __default_flex))
		p->default_flex = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_box_layout_settings_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_box_layout_settings_index },
	{ "__newindex", luacef_box_layout_settings_newindex },
	{ NULL, NULL}
};
#pragma endregion

//                            _ _   _                      _         _ _         
//  ___ ___ _____ ___ ___ ___|_| |_|_|___ ___    _ _ ___ _| |___ ___| |_|___ ___ 
// |  _| . |     | . | . |_ -| |  _| | . |   |  | | |   | . | -_|  _| | |   | -_|
// |___|___|_|_|_|  _|___|___|_|_| |_|___|_|_|  |___|_|_|___|___|_| |_|_|_|_|___|
//===============|_|==============================================================
/*
	<CompositionUnderline> {
		<Range>	range;
		<uint>	color;
		<uint>	background_color;
		<bool>	thick;
	}
*/
#pragma region composition_underline
static const char *__range = "range";
static const char *__color = "color";
//static const char *__background_color = "background_color";
static const char *__thick = "thick";

static int luacef_composition_underline_new(lua_State *L)
{
	size_t sz = sizeof(cef_composition_underline_t);
	cef_composition_underline_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __range))
			p->range = *(cef_range_t*)luacef_touserdata(L, -1);

		if (lua_getfield(L, 1, __color))
			p->color = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __background_color))
			p->background_color = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __thick))
			p->thick = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, p, __composition_underline__);
	return 1;
}

static int luacef_composition_underline_index(lua_State *L)
{
	cef_composition_underline_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __range))
		luacef_pushuserdata(L, &p->range, __range__);

	else if (!strcmp(i, __color))
		lua_pushinteger(L, p->color);

	else if (!strcmp(i, __background_color))
		lua_pushinteger(L, p->background_color);

	else if (!strcmp(i, __thick))
		lua_pushboolean(L, p->thick);

	else return 0;

	return 1;
}

static int luacef_composition_underline_newindex(lua_State *L)
{
	cef_composition_underline_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __range))
		p->range = *(cef_range_t*)luacef_touserdata(L, -1);

	else if (!strcmp(i, __color))
		p->color = lua_tointeger(L, -1);

	else if (!strcmp(i, __background_color))
		p->background_color = lua_tointeger(L, -1);

	else if (!strcmp(i, __thick))
		p->thick = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_composition_underline_m[] = {
	//{ "__gc", luacef_release },
	{ "__index", luacef_composition_underline_index },
	{ "__newindex", luacef_composition_underline_newindex },
	{ NULL, NULL}
};
#pragma endregion

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//            _                        
//  _____ ___|_|___    ___ ___ ___ ___ 
// |     | .'| |   |  | .'|  _| . |_ -|
// |_|_|_|__,|_|_|_|  |__,|_| |_  |___|
//============================|___|=====
/*
	<MainArgs> {
		<udata>	instance;
	}
*/

static const char *__instance = "instance";

static int luacef_main_args_new(lua_State* L)
{
	size_t sz = sizeof(cef_main_args_t);
	cef_main_args_t *args = luacef_alloc(sz);
	args->instance = GetModuleHandleW(NULL);
	
	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __instance))
			args->instance = lua_touserdata(L, -1);
	}

	luacef_pushuserdata(L, args, __main_args__);
	return 1;
}

static int luacef_main_args_index(lua_State* L)
{
	cef_main_args_t* args = luacef_touserdata(L, 1);
	if (!args) return 0;

	const char* i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __instance))
		lua_pushlightuserdata(L, args->instance);

	else return 0;

	return 1;
}

static int luacef_main_args_newindex(lua_State* L)
{
	cef_main_args_t* args = luacef_touserdata(L, 1);
	if (!args) return 0;

	const char* i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, __instance))
		args->instance = lua_touserdata(L, -1);

	return 0;
}

static const luaL_Reg luacef_main_args_m[] = {
	//{ "__gc" , luacef_release },
	{ "__index" , luacef_main_args_index },
	{ "__newindex" , luacef_main_args_newindex },
	{ NULL, NULL }
};

//        _       _              _     ___     
//  _ _ _|_|___ _| |___ _ _ _   |_|___|  _|___ 
// | | | | |   | . | . | | | |  | |   |  _| . |
// |_____|_|_|_|___|___|_____|  |_|_|_|_| |___|
//==============================================
/*
	<WindowInfo> {
		<int>	style
		<udata>	parent_window
		<int>	x
		<int>	y
		<int>	width
		<int>	height
		<int>	ex_style
		<udata>	menu
		<int>	transparent_painting_enabled
		<udata>	window
		<int>	windowless_rendering_enabled
		<str>	window_name
	}
*/

static const char *__style			= "style";
static const char *__parent_window	= "parent_window";
//static const char *__x				= "x";
//static const char *__y				= "y";
//static const char *__width			= "width";
//static const char *__height			= "height";
static const char *__ex_style			= "ex_style";
static const char *__menu				= "menu";
static const char *__window			= "window";
static const char *__window_name		= "window_name";
static const char *__transparent_painting_enabled = "transparent_painting_enabled";
//static const char *__windowless_rendering_enabled = "windowless_rendering_enabled";

static int luacef_window_info_new(lua_State* L)
{
	size_t sz = sizeof(cef_window_info_t);
	cef_window_info_t *wi = luacef_alloc(sz);

	// default value
	wi->style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | /*(__interpreter ?*/ WS_VISIBLE /* : 0)*/;
	wi->parent_window = NULL;
	wi->x = CW_USEDEFAULT;
	wi->y = CW_USEDEFAULT;
	wi->width = CW_USEDEFAULT;
	wi->height = CW_USEDEFAULT;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __window_name))
			wi->window_name = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, __style))
			wi->style = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __parent_window))
			wi->parent_window = lua_touserdata(L, -1);

		if (lua_getfield(L, 1, __x))
			wi->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __y))
			wi->y = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __width))
			wi->width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __height))
			wi->height = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __ex_style))
			wi->ex_style = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __menu))
			wi->menu = lua_touserdata(L, -1);

		//if (lua_getfield(L, 1, __transparent_painting_enabled))
			//wi->transparent_painting_enabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __window))
			wi->window = lua_touserdata(L, -1);

		if (lua_getfield(L, 1, __windowless_rendering_enabled))
			wi->windowless_rendering_enabled = lua_tointeger(L, -1);
	}
	
	luacef_pushuserdata(L, wi, __window_info__);
	return 1;
}

static luacef_window_info_index(lua_State* L)
{
	cef_window_info_t* wi = luacef_touserdata(L, 1);
	if (!wi) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(index, __style))
		lua_pushinteger(L, wi->style);

	else if (!strcmp(index, __parent_window))
		lua_pushlightuserdata(L, wi->parent_window);

	else if (!strcmp(index, __x))
		lua_pushinteger(L, wi->x);

	else if (!strcmp(index, __y))
		lua_pushinteger(L, wi->x);

	else if (!strcmp(index, __width))
		lua_pushinteger(L, wi->width);

	else if (!strcmp(index, __height))
		lua_pushinteger(L, wi->height);

	else if (!strcmp(index, __ex_style))
		lua_pushinteger(L, wi->ex_style);

	else if (!strcmp(index, __menu))
		lua_pushlightuserdata(L, wi->menu);

	//else if (!strcmp(index, __transparent_painting_enabled))
		//lua_pushinteger(L, wi->transparent_painting_enabled);

	else if (!strcmp(index, __window))
		lua_pushlightuserdata(L, wi->window);

	else if (!strcmp(index, __windowless_rendering_enabled))
		lua_pushinteger(L, wi->windowless_rendering_enabled);

	else if (!strcmp(index, __window_name))
		luacef_pushstring(L, &wi->window_name);

	else return 0;

	return 1;
}

static luacef_window_info_newindex(lua_State* L)
{
	cef_window_info_t* wi = luacef_touserdata(L, 1);
	if (!wi) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, __style))
		wi->style = lua_tointeger(L, 3);

	else if (!strcmp(index, __parent_window))
		wi->parent_window = lua_touserdata(L, 3);

	else if (!strcmp(index, __x))
		wi->x = lua_tointeger(L, 3);

	else if (!strcmp(index, __y))
		wi->x = lua_tointeger(L, 3);

	else if (!strcmp(index, __width))
		wi->width = lua_tointeger(L, 3);

	else if (!strcmp(index, __height))
		wi->height = lua_tointeger(L, 3);

	else if (!strcmp(index, __ex_style))
		wi->ex_style = lua_tointeger(L, 3);

	else if (!strcmp(index, __menu))
		wi->menu = lua_touserdata(L, 3);

	//else if (!strcmp(index, __transparent_painting_enabled))
		//wi->transparent_painting_enabled = lua_tointeger(L, 3);

	else if (!strcmp(index, __window))
		wi->window = lua_touserdata(L, 3);

	else if (!strcmp(index, __windowless_rendering_enabled))
		wi->windowless_rendering_enabled = lua_tointeger(L, 3);

	else if (!strcmp(index, __window_name))
		wi->window_name = luacef_tostring(L, 3);

	return 0;
}

static const luaL_Reg luacef_window_info_m[] = {
	//{ "__gc" , luacef_release },
	{ "__index" , luacef_window_info_index },
	{ "__newindex" , luacef_window_info_newindex },
	{ NULL, NULL }
};



//=========================================

void luacef_types_reg(lua_State* L)
{
	// settings
	luaL_newmetatable(L, __settings__);
	luaL_setfuncs(L, luacef_settings_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_settings_new);
	lua_setfield(L, -2, "newSettings");

	// request_context_settings
	luaL_newmetatable(L, __request_context_settings__);
	luaL_setfuncs(L, luacef_request_context_settings_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_request_context_settings_new);
	lua_setfield(L, -2, "newRequestContextSettings");

	// browser_settings
	luaL_newmetatable(L, __browser_settings__);
	luaL_setfuncs(L, luacef_browser_settings_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_browser_settings_new);
	lua_setfield(L, -2, "newBrowserSettings");

	// urlparts
	luaL_newmetatable(L, __urlparts__);
	luaL_setfuncs(L, luacef_urlparts_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_urlparts_new);
	lua_setfield(L, -2, "newURLParts");

	// cookie
	luaL_newmetatable(L, __cookie__);
	luaL_setfuncs(L, luacef_cookie_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_cookie_new);
	lua_setfield(L, -2, "newCookie");

	// point
	luaL_newmetatable(L, __point__);
	luaL_setfuncs(L, luacef_point_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_point_new);
	lua_setfield(L, -2, "newPoint");

	// rect
	luaL_newmetatable(L, __rect__);
	luaL_setfuncs(L, luacef_rect_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_rect_new);
	lua_setfield(L, -2, "newRect");
		
	// size
	luaL_newmetatable(L, __size__);
	luaL_setfuncs(L, luacef_size_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_size_new);
	lua_setfield(L, -2, "newSize");

	// range
	luaL_newmetatable(L, __range__);
	luaL_setfuncs(L, luacef_range_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_range_new);
	lua_setfield(L, -2, "newRange");
		
	// insets
	luaL_newmetatable(L, __insets__);
	luaL_setfuncs(L, luacef_insets_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_insets_new);
	lua_setfield(L, -2, "newInsets");

	// draggable_region
	luaL_newmetatable(L, __draggable_region__);
	luaL_setfuncs(L, luacef_draggable_region_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_draggable_region_new);
	lua_setfield(L, -2, "newDraggableRegion");
		
	// screen_info
	luaL_newmetatable(L, __screen_info__);
	luaL_setfuncs(L, luacef_screen_info_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_screen_info_new);
	lua_setfield(L, -2, "newScreenInfo");

	// mouse_event
	luaL_newmetatable(L, __mouse_event__);
	luaL_setfuncs(L, luacef_mouse_event_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_mouse_event_new);
	lua_setfield(L, -2, "newMouseEvent");
		
	// key_event
	luaL_newmetatable(L, __key_event__);
	luaL_setfuncs(L, luacef_key_event_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_key_event_new);
	lua_setfield(L, -2, "newKeyEvent");

	// popup_features
	luaL_newmetatable(L, __popup_features__);
	luaL_setfuncs(L, luacef_popup_features_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_popup_features_new);
	lua_setfield(L, -2, "newPopupFeatures");

	// geoposition
	luaL_newmetatable(L, __geoposition__);
	luaL_setfuncs(L, luacef_geoposition_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_geoposition_new);
	lua_setfield(L, -2, "newGeoposition");

	// cursor_info
	luaL_newmetatable(L, __cursor_info__);
	luaL_setfuncs(L, luacef_cursor_info_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_cursor_info_new);
	lua_setfield(L, -2, "newCursorInfo");

	// pdf_print_settings
	luaL_newmetatable(L, __pdf_print_settings__);
	luaL_setfuncs(L, luacef_pdf_print_settings_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_pdf_print_settings_new);
	lua_setfield(L, -2, "newPDFPrintSettings");

	// box_layout_settings
	luaL_newmetatable(L, __box_layout_settings__);
	luaL_setfuncs(L, luacef_box_layout_settings_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_box_layout_settings_new);
	lua_setfield(L, -2, "newBoxLayoutSettings");

	// composition_underline
	luaL_newmetatable(L, __composition_underline__);
	luaL_setfuncs(L, luacef_composition_underline_m, 0);
	lua_pop(L, 1);
	lua_pushcfunction(L, luacef_composition_underline_new);
	lua_setfield(L, -2, "newCompositionUnderline");

	// win type

	// MainArgs
	luaL_newmetatable(L, __main_args__);
	luaL_setfuncs(L, luacef_main_args_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_main_args_new);
	lua_setfield(L, -2, "newMainArgs");

	// WindowInfo
	luaL_newmetatable(L, __window_info__);
	luaL_setfuncs(L, luacef_window_info_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_window_info_new);
	lua_setfield(L, -2, "newWindowInfo");

}
