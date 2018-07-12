#include "../luacef.h"

// MainArgs //================================================
static const char *_ma__instance = "instance";

/*
	cef.newMainArgs {
		<udata>	instance;

	} --> <MainArgs>
*/
static int luacef_main_args_new(lua_State* L)
{
	size_t sz = sizeof(cef_main_args_t);
	cef_main_args_t *args = luacef_newuserdata(L, sz);
	args->instance = GetModuleHandleA(NULL);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, _ma__instance))
			args->instance = lua_touserdata(L, -1);

		lua_pushvalue(L, -2);
	}

	luaL_setmetatable(L, __main_args__);
	return 1;
}

static int luacef_main_args_index(lua_State* L)
{
	cef_main_args_t* args = luacef_checkudata(L, 1, __main_args__);
	if (!args) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _ma__instance))
		lua_pushlightuserdata(L, args->instance);

	else
		luacef_error_index(L, index);

	return 1;
}

static int luacef_main_args_newindex(lua_State* L)
{
	cef_main_args_t* args = luacef_checkudata(L, 1, __main_args__);
	if (!args) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _ma__instance))
		args->instance = lua_touserdata(L, 3);

	else
		luacef_error_index(L, index);

	return 0;
}

static const luaL_Reg luacef_main_args_m[] = {
	{ "__gc" , luacef_release },
	{ "__index" , luacef_main_args_index },
	{ "__newindex" , luacef_main_args_newindex },
	{ NULL, NULL }
};


// WindowInfo //=====================================
static const char *_wi_style			= "style";
static const char *_wi_parent_window	= "parent_window";
static const char *_wi_x				= "x";
static const char *_wi_y				= "y";
static const char *_wi_width			= "width";
static const char *_wi_height			= "height";
static const char *_wi_ex_style			= "ex_style";
static const char *_wi_menu				= "menu";
static const char *_wi_window			= "window";
static const char *_wi_window_name		= "window_name";
static const char *_wi_transparent_painting_enabled = "transparent_painting_enabled";
static const char *_wi_windowless_rendering_enabled = "windowless_rendering_enabled";

/*
	cef.newWindowInfo 
	{
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

	} -> <WindowInfo>
*/
static int luacef_window_info_new(lua_State* L)
{
	size_t sz = sizeof(cef_window_info_t);
	cef_window_info_t *wi = luacef_newuserdata(L, sz);

	// default value
	wi->style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | /*(__interpreter ?*/ WS_VISIBLE /* : 0)*/;
	wi->parent_window = NULL;
	wi->x = CW_USEDEFAULT;
	wi->y = CW_USEDEFAULT;
	wi->width = CW_USEDEFAULT;
	wi->height = CW_USEDEFAULT;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, _wi_window_name))
			wi->window_name = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _wi_style))
			wi->style = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_parent_window))
			wi->parent_window = lua_touserdata(L, -1);

		if (lua_getfield(L, 1, _wi_x))
			wi->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_y))
			wi->y = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_width))
			wi->width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_height))
			wi->height = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_ex_style))
			wi->ex_style = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_menu))
			wi->menu = lua_touserdata(L, -1);

		if (lua_getfield(L, 1, _wi_transparent_painting_enabled))
			;//wi->transparent_painting_enabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _wi_window))
			wi->window = lua_touserdata(L, -1);

		if (lua_getfield(L, 1, _wi_windowless_rendering_enabled))
			wi->windowless_rendering_enabled = lua_tointeger(L, -1);

		lua_pushvalue(L, -13);
	}

	luaL_setmetatable(L, __window_info__);
	return 1;
}

static luacef_window_info_index(lua_State* L)
{
	cef_window_info_t* wi = luacef_touserdata(L, 1);
	if (!wi) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _wi_style))
		lua_pushinteger(L, wi->style);

	else if (!strcmp(index, _wi_parent_window))
		lua_pushlightuserdata(L, wi->parent_window);

	else if (!strcmp(index, _wi_x))
		lua_pushinteger(L, wi->x);

	else if (!strcmp(index, _wi_y))
		lua_pushinteger(L, wi->x);

	else if (!strcmp(index, _wi_width))
		lua_pushinteger(L, wi->width);

	else if (!strcmp(index, _wi_height))
		lua_pushinteger(L, wi->height);

	else if (!strcmp(index, _wi_ex_style))
		lua_pushinteger(L, wi->ex_style);

	else if (!strcmp(index, _wi_menu))
		lua_pushlightuserdata(L, wi->menu);

	else if (!strcmp(index, _wi_transparent_painting_enabled))
		;//lua_pushinteger(L, wi->transparent_painting_enabled);

	else if (!strcmp(index, _wi_window))
		lua_pushlightuserdata(L, wi->window);

	else if (!strcmp(index, _wi_windowless_rendering_enabled))
		lua_pushinteger(L, wi->windowless_rendering_enabled);

	else if (!strcmp(index, _wi_window_name))
		luacef_pushstring(L, &wi->window_name);

	else
		luacef_error_index(L, index);

	return 1;
}

static luacef_window_info_newindex(lua_State* L)
{
	cef_window_info_t* wi = luacef_checkudata(L, 1, __window_info__);
	if (!wi) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _wi_style))
		wi->style = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_parent_window))
		wi->parent_window = lua_touserdata(L, 3);

	else if (!strcmp(index, _wi_x))
		wi->x = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_y))
		wi->x = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_width))
		wi->width = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_height))
		wi->height = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_ex_style))
		wi->ex_style = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_menu))
		wi->menu = lua_touserdata(L, 3);

	else if (!strcmp(index, _wi_transparent_painting_enabled))
		;//wi->transparent_painting_enabled = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_window))
		wi->window = lua_touserdata(L, 3);

	else if (!strcmp(index, _wi_windowless_rendering_enabled))
		wi->windowless_rendering_enabled = lua_tointeger(L, 3);

	else if (!strcmp(index, _wi_window_name))
		wi->window_name = luacef_tostring(L, 3);
		
	else
		luacef_error_index(L, index);

	return 0;
}

static const luaL_Reg luacef_window_info_m[] = {
	{ "__gc" , luacef_release },
	{ "__index" , luacef_window_info_index },
	{ "__newindex" , luacef_window_info_newindex },
	{ NULL, NULL }
};

// Settings //=============================================================
static const char *_s_multi_threaded_message_loop	= "multi_threaded_message_loop";
static const char *_s_single_process				= "single_process";
static const char *_s_log_severity					= "log_severity";
static const char *_s_user_agent					= "user_agent";
static const char *_s_accept_language_list			= "accept_language_list";
static const char *_s_background_color				= "background_color";
static const char *_s_browser_subprocess_path		= "browser_subprocess_path";
static const char *_s_cache_path					= "cache_path";
static const char *_s_command_line_args_disabled	= "command_line_args_disabled";
static const char *_s_context_safety_implementation	= "context_safety_implementation";
static const char *_s_external_message_pump			= "external_message_pump";
static const char *_s_ignore_certificate_errors		= "ignore_certificate_errors";
static const char *_s_javascript_flags				= "javascript_flags";
static const char *_s_locales_dir_path				= "locales_dir_path";
static const char *_s_locale							= "locale";
static const char *_s_log_file						= "log_file";
static const char *_s_pack_loading_disabled			= "pack_loading_disabled";
static const char *_s_persist_session_cookies		= "persist_session_cookies";
static const char *_s_persist_user_preferences		= "persist_user_preferences";
static const char *_s_product_version				= "product_version";
static const char *_s_remote_debugging_port			= "remote_debugging_port";
static const char *_s_resources_dir_path			= "resources_dir_path";
static const char *_s_uncaught_exception_stack_size	= "uncaught_exception_stack_size";
static const char *_s_user_data_path				= "user_data_path";
static const char *_s_windowless_rendering_enabled	= "windowless_rendering_enabled";

/*
	cef.newSettings	{
		<int>	multi_threaded_message_loop;
		<int>	single_process;
		<int>	log_severity;
		<str>	user_agent;
		<str>	accept_language_list;
		<int>	background_color;
		<str>	browser_subprocess_path;
		<str>	cache_path;
		<int>	command_line_args_disabled;
		<int>	context_safety_implementation;
		<int>	external_message_pump;
		<int>	ignore_certificate_errors;
		<str>	javascript_flags;
		<str>	locales_dir_path;
		<str>	locale;
		<str>	log_file;
		<int>	pack_loading_disabled;
		<int>	persist_session_cookies;
		<int>	persist_user_preferences;
		<str>	product_version;
		<int>	remote_debugging_port;
		<str>	resources_dir_path;
		<int>	uncaught_exception_stack_size;
		<str>	user_data_path;
		<int>	windowless_rendering_enabled;

	} --> <Settings>
*/
static int luacef_settings_new(lua_State* L)
{
	size_t sz = sizeof(cef_settings_t);
	cef_settings_t* s = luacef_newuserdata(L, sz);
	s->size = sz;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, _s_multi_threaded_message_loop))
			s->multi_threaded_message_loop = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_single_process))
			s->single_process = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_log_severity))
			s->log_severity = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_user_agent))
			s->user_agent = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_accept_language_list))
			s->accept_language_list = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_background_color))
			s->background_color = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_browser_subprocess_path))
			s->browser_subprocess_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_cache_path)) 
			s->cache_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_command_line_args_disabled))
			s->command_line_args_disabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_context_safety_implementation))
			;//s->context_safety_implementation = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_external_message_pump))
			s->external_message_pump = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_ignore_certificate_errors))
			s->ignore_certificate_errors = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_javascript_flags))
			s->javascript_flags = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_locales_dir_path))
			s->locales_dir_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_locale))
			s->locale = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_log_file))
			s->log_file = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_pack_loading_disabled))
			s->pack_loading_disabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_persist_session_cookies))
			s->persist_session_cookies = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_persist_user_preferences))
			s->persist_user_preferences = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_product_version))
			s->product_version = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_remote_debugging_port))
			s->remote_debugging_port = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_resources_dir_path))
			s->resources_dir_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_uncaught_exception_stack_size))
			s->uncaught_exception_stack_size = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, _s_user_data_path))
			s->user_data_path = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, _s_windowless_rendering_enabled))
			s->windowless_rendering_enabled = lua_tointeger(L, -1);

		lua_pushvalue(L, -26); // userdata
	}

	luaL_setmetatable(L, __settings__);

	return 1;
}

static int luacef_settings_index(lua_State* L)
{
	cef_settings_t* s = luacef_checkudata(L, 1, __settings__);
	if (!s) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _s_single_process))
		lua_pushinteger(L, s->single_process);

	else if (!strcmp(index, _s_multi_threaded_message_loop))
		lua_pushinteger(L, s->multi_threaded_message_loop);

	else if (!strcmp(index, _s_log_severity))
		lua_pushinteger(L, s->log_severity);
	
	else if (!strcmp(index, _s_user_agent))
		luacef_pushstring(L, &s->user_agent);

	else 
		luaL_error(L, "cannot get member '%s'", index);

	return 1;
}

static int luacef_settings_newindex(lua_State* L)
{
	cef_settings_t* s = luacef_checkudata(L, 1, __settings__);
	if (!s) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _s_single_process))
		s->single_process = lua_tointeger(L, 3);

	else if (!strcmp(index, _s_multi_threaded_message_loop))
		s->multi_threaded_message_loop = lua_tointeger(L, 3);

	else if (!strcmp(index, _s_log_severity))
		s->log_severity = lua_tointeger(L, 3);

	else if (!strcmp(index, _s_user_agent))
		s->user_agent = luacef_tostring(L, 3);

	else 
		luaL_error(L, "cannot get member '%s'", index);

	return 0;
}

static const luaL_Reg luacef_settings_m[] = {
	{ "__gc" , luacef_release },
	{ "__index" , luacef_settings_index },
	{ "__newindex" , luacef_settings_newindex },
	{ NULL, NULL}
};

// BrowserSettings //===========================================
static const char *_bs_plugins		= "plugins";
static const char *_bs_databases	= "databases";
static const char *_bs_webgl		= "webgl";
static const char *_bs_web_security = "web_security";
static const char *_bs_javascript	= "javascript";
static const char *_bs_remote_fonts = "remote_fonts";
static const char *_bs_image_loading	= "image_loading";
static const char *_bs_caret_browsing	= "caret_browsing";
static const char *_bs_background_color = "background_color";
static const char *_bs_tab_to_links		= "tab_to_links";
static const char *_bs_text_area_resize = "text_area_resize";
static const char *_bs_local_storage	= "local_storage";
static const char *_bs_minimum_font_size	= "minimum_font_size";
static const char *_bs_fixed_font_family	= "fixed_font_family";
static const char *_bs_application_cache	= "application_cache";
static const char *_bs_accept_language_list	= "accept_language_list";
static const char *_bs_cursive_font_family	= "cursive_font_family";
static const char *_bs_default_encoding		= "default_encoding";
static const char *_bs_default_font_size	= "default_font_size";
static const char *_bs_fantasy_font_family	= "fantasy_font_family";
static const char *_bs_javascript_dom_paste = "javascript_dom_paste";
static const char *_bs_serif_font_family	= "serif_font_family";
static const char *_bs_standard_font_family = "standard_font_family";
static const char *_bs_javascript_close_windows = "javascript_close_windows";
static const char *_bs_javascript_open_windows	= "javascript_open_windows";
static const char *_bs_default_fixed_font_size	= "default_fixed_font_size";
static const char *_bs_sans_serif_font_family	= "sans_serif_font_family";
static const char *_bs_windowless_frame_rate	= "windowless_frame_rate";
static const char *_bs_minimum_logical_font_size = "minimum_logical_font_size";
static const char *_bs_file_access_from_file_urls	= "file_access_from_file_urls";
static const char *_bs_javascript_access_clipboard	= "javascript_access_clipboard";
static const char *_bs_image_shrink_standalone_to_fit	= "image_shrink_standalone_to_fit";
static const char *_bs_universal_access_from_file_urls	= "universal_access_from_file_urls";

/*
	cef.newBrowserSettings 
	{
		<str>	accept_language_list;
		<State>	application_cache;
		<int>	background_color;
		<State>	caret_browsing;
		<str>	cursive_font_family;
		<State>	databases;
		<str>	default_encoding;
		<int>	default_fixed_font_size;
		<int>	default_font_size;
		<str>	fantasy_font_family;
		<State>	file_access_from_file_urls;
		<str>	fixed_font_family;
		<State>	image_loading;
		<State>	image_shrink_standalone_to_fit;
		<State>	javascript;
		<State>	javascript_access_clipboard;
		<State>	javascript_close_windows;
		<State>	javascript_dom_paste;
		<State>	javascript_open_windows;
		<State>	local_storage;
		<int>	minimum_font_size;
		<int>	minimum_logical_font_size;
		<State>	plugins;
		<State>	remote_fonts;
		<str>	sans_serif_font_family;
		<str>	serif_font_family;
		<str>	standard_font_family;
		<State>	tab_to_links;
		<State>	text_area_resize;
		<State>	universal_access_from_file_urls;
		<State>	webgl;
		<State>	web_security;
		<int>	windowless_frame_rate;

	} -> browsersettings
*/
int luacef_browser_settings_new(lua_State* L)
{
	size_t sz = sizeof(cef_browser_settings_t);
	cef_browser_settings_t *bs = calloc(1, sz);
	bs->size = sz;
	
	/*
	bs->accept_language_list; //str
	bs->application_cache; //state
	bs->background_color; //int
	bs->caret_browsing; //state
	bs->cursive_font_family; //str
	bs->databases; //state
	bs->default_encoding; //str
	bs->default_fixed_font_size; //int
	bs->default_font_size; //int
	bs->fantasy_font_family; //str
	bs->file_access_from_file_urls; //state
	bs->fixed_font_family; //str
	bs->image_loading; //state
	bs->image_shrink_standalone_to_fit; //state
	bs->javascript; //state
	bs->javascript_access_clipboard; //state
	bs->javascript_close_windows; //state
	bs->javascript_dom_paste; //state
	bs->javascript_open_windows; //state
	bs->local_storage; //state
	bs->minimum_font_size; //int
	bs->minimum_logical_font_size; //int
	bs->plugins; //state
	bs->remote_fonts; //state
	bs->sans_serif_font_family; //str
	bs->serif_font_family; //str
	bs->standard_font_family; //str
	bs->tab_to_links; //state
	bs->text_area_resize; //state
	bs->universal_access_from_file_urls; //state
	bs->webgl; //state
	bs->web_security; //state
	bs->windowless_frame_rate; //int
	*/

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, _bs_accept_language_list))
			bs->accept_language_list = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_application_cache))
			bs->application_cache = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_background_color))
			bs->background_color = lua_tointeger(L, -1); //int

		if (lua_getfield(L, 1, _bs_caret_browsing))
			;// bs->caret_browsing = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_cursive_font_family))
			bs->cursive_font_family = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_databases))
			bs->databases = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_default_encoding))
			bs->default_encoding = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_default_fixed_font_size))
			bs->default_fixed_font_size = lua_tointeger(L, -1); //int

		if (lua_getfield(L, 1, _bs_default_font_size))
			bs->default_font_size = lua_tointeger(L, -1); //int

		if (lua_getfield(L, 1, _bs_fantasy_font_family))
			bs->fantasy_font_family = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_file_access_from_file_urls))
			bs->file_access_from_file_urls = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_fixed_font_family))
			bs->fixed_font_family = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_image_loading))
			bs->image_loading = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_image_shrink_standalone_to_fit))
			bs->image_shrink_standalone_to_fit = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_javascript))
			bs->javascript = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_javascript_access_clipboard))
			bs->javascript_access_clipboard = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_javascript_close_windows))
			bs->javascript_close_windows = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_javascript_dom_paste))
			bs->javascript_dom_paste = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_javascript_open_windows))
			;// bs->javascript_open_windows = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_local_storage))
			bs->local_storage = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_minimum_font_size))
			bs->minimum_font_size = lua_tointeger(L, -1); //int

		if (lua_getfield(L, 1, _bs_minimum_logical_font_size))
			bs->minimum_logical_font_size = lua_tointeger(L, -1); //int

		if (lua_getfield(L, 1, _bs_plugins))
			bs->plugins = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_remote_fonts))
			bs->remote_fonts = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_sans_serif_font_family))
			bs->sans_serif_font_family = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_serif_font_family))
			bs->serif_font_family = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_standard_font_family))
			bs->standard_font_family = luacef_tostring(L, -1); //str

		if (lua_getfield(L, 1, _bs_tab_to_links))
			bs->tab_to_links = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_text_area_resize))
			bs->text_area_resize = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_universal_access_from_file_urls))
			bs->universal_access_from_file_urls = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_webgl))
			bs->webgl = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_web_security))
			bs->web_security = lua_tointeger(L, -1); //state

		if (lua_getfield(L, 1, _bs_windowless_frame_rate))
			bs->windowless_frame_rate = lua_tointeger(L, -1); //int
	}
	
	luacef_pushuserdata(L, bs, __browser_settings__);
	return 1;
}

int luacef_browser_settings_index(lua_State* L)
{
	cef_browser_settings_t* bs = luacef_checkudata(L, 1, __browser_settings__);
	if (!bs) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _bs_accept_language_list))
		luacef_pushstring(L, &bs->accept_language_list); //str

	else if (!strcmp(index, _bs_application_cache))
		lua_pushinteger(L, bs->application_cache); //state

	else if (!strcmp(index, _bs_background_color))
		lua_pushinteger(L, bs->background_color); //int

	else if (!strcmp(index, _bs_caret_browsing))
		;// lua_pushinteger(L, bs->caret_browsing); //state

	else if (!strcmp(index, _bs_cursive_font_family))
		luacef_pushstring(L, &bs->cursive_font_family); //str

	else if (!strcmp(index, _bs_databases))
		lua_pushinteger(L, bs->databases); //state

	else if (!strcmp(index, _bs_default_encoding))
		luacef_pushstring(L, &bs->default_encoding); //str

	else if (!strcmp(index, _bs_default_fixed_font_size))
		lua_pushinteger(L, bs->default_fixed_font_size); //int

	else if (!strcmp(index, _bs_default_font_size))
		lua_pushinteger(L, bs->default_font_size); //int

	else if (!strcmp(index, _bs_fantasy_font_family))
		luacef_pushstring(L, &bs->fantasy_font_family); //str

	else if (!strcmp(index, _bs_file_access_from_file_urls))
		lua_pushinteger(L, bs->file_access_from_file_urls); //state

	else if (!strcmp(index, _bs_fixed_font_family))
		luacef_pushstring(L, &bs->fixed_font_family); //str

	else if (!strcmp(index, _bs_image_loading))
		lua_pushinteger(L, bs->image_loading); //state

	else if (!strcmp(index, _bs_image_shrink_standalone_to_fit))
		lua_pushinteger(L, bs->image_shrink_standalone_to_fit); //state

	else if (!strcmp(index, _bs_javascript))
		lua_pushinteger(L, bs->javascript); //state

	else if (!strcmp(index, _bs_javascript_access_clipboard))
		lua_pushinteger(L, bs->javascript_access_clipboard); //state

	else if (!strcmp(index, _bs_javascript_close_windows))
		lua_pushinteger(L, bs->javascript_close_windows); //state

	else if (!strcmp(index, _bs_javascript_dom_paste))
		lua_pushinteger(L, bs->javascript_dom_paste); //state

	else if (!strcmp(index, _bs_javascript_open_windows))
		;// lua_pushinteger(L, bs->javascript_open_windows); //state

	else if (!strcmp(index, _bs_local_storage))
		lua_pushinteger(L, bs->local_storage); //state

	else if (!strcmp(index, _bs_minimum_font_size))
		lua_pushinteger(L, bs->minimum_font_size); //int

	else if (!strcmp(index, _bs_minimum_logical_font_size))
		lua_pushinteger(L, bs->minimum_logical_font_size); //int

	else if (!strcmp(index, _bs_plugins))
		lua_pushinteger(L, bs->plugins); //state

	else if (!strcmp(index, _bs_remote_fonts))
		lua_pushinteger(L, bs->remote_fonts); //state

	else if (!strcmp(index, _bs_sans_serif_font_family))
		luacef_pushstring(L, &bs->sans_serif_font_family); //str

	else if (!strcmp(index, _bs_serif_font_family))
		luacef_pushstring(L, &bs->serif_font_family); //str

	else if (!strcmp(index, _bs_standard_font_family))
		luacef_pushstring(L, &bs->standard_font_family); //str

	else if (!strcmp(index, _bs_tab_to_links))
		lua_pushinteger(L, bs->tab_to_links); //state

	else if (!strcmp(index, _bs_text_area_resize))
		lua_pushinteger(L, bs->text_area_resize); //state

	else if (!strcmp(index, _bs_universal_access_from_file_urls))
		lua_pushinteger(L, bs->universal_access_from_file_urls); //state

	else if (!strcmp(index, _bs_webgl))
		lua_pushinteger(L, bs->webgl); //state

	else if (!strcmp(index, _bs_web_security))
		lua_pushinteger(L, bs->web_security); //state

	else if (!strcmp(index, _bs_windowless_frame_rate))
		lua_pushinteger(L, bs->windowless_frame_rate); //int

	else
		luaL_error(L, "cannot get member '%s'", index);

	return 1;
}

int luacef_browser_settings_newindex(lua_State* L)
{
	cef_browser_settings_t* bs = luacef_checkudata(L, 1, __browser_settings__);
	if (!bs) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, _bs_accept_language_list))
		bs->accept_language_list = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_application_cache))
		bs->application_cache = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_background_color))
		bs->background_color = lua_tointeger(L, 3); //int

	else if (!strcmp(index, _bs_caret_browsing))
		;// bs->caret_browsing = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_cursive_font_family))
		bs->cursive_font_family = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_databases))
		bs->databases = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_default_encoding))
		bs->default_encoding = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_default_fixed_font_size))
		bs->default_fixed_font_size = lua_tointeger(L, 3); //int

	else if (!strcmp(index, _bs_default_font_size))
		bs->default_font_size = lua_tointeger(L, 3); //int

	else if (!strcmp(index, _bs_fantasy_font_family))
		bs->fantasy_font_family = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_file_access_from_file_urls))
		bs->file_access_from_file_urls = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_fixed_font_family))
		bs->fixed_font_family = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_image_loading))
		bs->image_loading = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_image_shrink_standalone_to_fit))
		bs->image_shrink_standalone_to_fit = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_javascript))
		bs->javascript = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_javascript_access_clipboard))
		bs->javascript_access_clipboard = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_javascript_close_windows))
		bs->javascript_close_windows = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_javascript_dom_paste))
		bs->javascript_dom_paste = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_javascript_open_windows))
		;// bs->javascript_open_windows = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_local_storage))
		bs->local_storage = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_minimum_font_size))
		bs->minimum_font_size = lua_tointeger(L, 3); //int

	else if (!strcmp(index, _bs_minimum_logical_font_size))
		bs->minimum_logical_font_size = lua_tointeger(L, 3); //int

	else if (!strcmp(index, _bs_plugins))
		bs->plugins = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_remote_fonts))
		bs->remote_fonts = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_sans_serif_font_family))
		bs->sans_serif_font_family = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_serif_font_family))
		bs->serif_font_family = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_standard_font_family))
		bs->standard_font_family = luacef_tostring(L, 3); //str

	else if (!strcmp(index, _bs_tab_to_links))
		bs->tab_to_links = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_text_area_resize))
		bs->text_area_resize = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_universal_access_from_file_urls))
		bs->universal_access_from_file_urls = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_webgl))
		bs->webgl = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_web_security))
		bs->web_security = lua_tointeger(L, 3); //state

	else if (!strcmp(index, _bs_windowless_frame_rate))
		bs->windowless_frame_rate = lua_tointeger(L, 3); //int

	else
		luaL_error(L, "cannot get member '%s'", index);

	return 0;
}

static const luaL_Reg luacef_browser_settings_m[] = {
	{ "__gc" , luacef_release },
	{ "__index" , luacef_browser_settings_index },
	{ "__newindex" , luacef_browser_settings_newindex },
	{ NULL, NULL}
};









//=========================================

void luacef_types_reg(lua_State* L)
{
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

	// Settings
	luaL_newmetatable(L, __settings__);
	luaL_setfuncs(L, luacef_settings_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_settings_new);
	lua_setfield(L, -2, "newSettings");

	// BrowserSettings
	luaL_newmetatable(L, __browser_settings__);
	luaL_setfuncs(L, luacef_browser_settings_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_browser_settings_new);
	lua_setfield(L, -2, "newBrowserSettings");

}
