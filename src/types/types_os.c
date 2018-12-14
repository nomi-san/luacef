#include "../luacef.h"

// MainArgs
// ==================================================
/*
	<CewfMainArgs> cef.newMainArgs(<table> main_args)

	-- Windows:

		<CefMainArgs> {
			<udata> instance
		}

	-- Linux:

		<CefMainArgs> {
			<int> argc,
			<table> argv
		}
*/

#define SELF luacef_MainArgs

typedef cef_main_args_t SELF;

#define API(fn) \
	LCEF_API(MainArgs, fn)

#define API_N(fn) \
	LCEF_API_N(MainArgs, fn)

#define API_M(mname) \
	LCEF_M(MainArgs, mname)

// api =========================

API(new)
{
	size_t sz = sizeof(SELF);
	SELF *p = calloc(1, sz);
#if defined(OS_WIN)
	p->instance = GetModuleHandleW(NULL);
#endif

	if (lua_istable(L, 1)) {
#if defined(OS_WIN)
		if (lua_getfield(L, 1, "instance"))
			p->instance = lua_touserdata(L, -1);

#elif defined(OS_LINUX)
		if (lua_getfield(L, 1, "argc")) {
			p->argc = lua_tointeger(L, -1);

			if (lua_getfield(L, 1, "argv"))
				if (p->argv) free(p->argv);
				p->argv = malloc(sizeof(char*) * p->argc);

				if (lua_istable(L, -1)) {

					for (int i = 1, i < p->argc, ; i++) {
						lua_rawgeti(L, -1, i);
						p->argv[i-1] = lua_tostring(L, 1);
						lua_pop(L, 1);
					}
				}
		}
#endif
	}

	luacef_pushuserdata(L, p, __main_args__);
	return 1;
}

API(index)
{
	cef_main_args_t* args = luacef_touserdata(L, 1);
	if (!args) return 0;

	const char* i = lua_tostring(L, 2);

	if (!strcmp(i, "instance"))
		lua_pushlightuserdata(L, args->instance);

	else return 0;

	return 1;
}

API(newindex)
{
	cef_main_args_t* args = luacef_touserdata(L, 1);
	if (!args) return 0;

	const char* i = lua_tostring(L, 2);
	lua_pushvalue(L, 3);

	if (!strcmp(i, "instance"))
		args->instance = lua_touserdata(L, -1);

	return 0;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

// meta =========================

API_M(meta)
{
	{ "__len", API_N(len) },
	{ "__unm", API_N(unm) },
	{ "__index" , API_N(index) },
	{ "__newindex" , API_N(newindex) },

	LUAREGEND
};

#undef SELF
#undef API
#undef API_N
#undef API_M

// WindowInfo
// ==================================================
/*
	<CefWindowInfo> cef.newWindowInfo(<table> window_info)

	-- Windows:

		<CefWindowInfo> {
			<int> x,
			<int> y,
			<int> width,
			<int> height,
			<udata> window,
			<udata> parent_window,
			<int> windowless_rendering_enabled,
			<str> window_name,
			<udata> menu,
			<int> style,
			<int> ex_style
		}

	-- Linux:

		<CefWindowInfo> {
			<int> x,
			<int> y,
			<int> width,
			<int> height,
			<int> window,
			<int> parent_window,
			<int> windowless_rendering_enabled,
		}
*/

#define SELF luacef_WindowInfo

typedef cef_window_info_t SELF;

#define API(fn) \
	LCEF_API(WindowInfo, fn)

#define API_N(fn) \
	LCEF_API_N(WindowInfo, fn)

#define API_M(mname) \
	LCEF_M(WindowInfo, mname)

// api =========================

API(new)
{
	size_t sz = sizeof(SELF);
	SELF *wi = calloc(1, sz);

	// default value
	wi->style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | /*(__interpreter ?*/ WS_VISIBLE /* : 0)*/;
	wi->parent_window = NULL;
	wi->x = CW_USEDEFAULT;
	wi->y = CW_USEDEFAULT;
	wi->width = CW_USEDEFAULT;
	wi->height = CW_USEDEFAULT;

	if (lua_istable(L, 1)) {

#if defined(OS_WIN)
		if (lua_getfield(L, 1, "window_name"))
			wi->window_name = luacef_tostring(L, -1);

		if (lua_getfield(L, 1, "style"))
			wi->style = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "ex_style"))
			wi->ex_style = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "menu"))
			wi->menu = luacef_tohandle(L, -1);
#endif

		if (lua_getfield(L, 1, "x"))
			wi->x = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "y"))
			wi->y = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "width"))
			wi->width = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "height"))
			wi->height = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "parent_window"))
			wi->parent_window = luacef_tohandle(L, -1);

		if (lua_getfield(L, 1, "windowless_rendering_enabled"))
			wi->windowless_rendering_enabled = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, "window"))
			wi->window = luacef_tohandle(L, -1);

		//if (lua_getfield(L, 1, __transparent_painting_enabled))
			//p->transparent_painting_enabled = lua_tointeger(L, -1);
	}

	luacef_pushuserdata(L, wi, __window_info__);
	return 1;
}

API(index)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, "parent_window"))
		luacef_pushhandle(L, p->parent_window);

#if defined(OS_WIN)
	else if (!strcmp(index, "window_name"))
		luacef_pushstring(L, &p->window_name);

	else if (!strcmp(index, "style"))
		lua_pushinteger(L, p->style);

	else if (!strcmp(index, "ex_style"))
		lua_pushinteger(L, p->ex_style);

	else if (!strcmp(index, "menu"))
		luacef_pushhandle(L, p->menu);
#endif

	else if (!strcmp(index, "x"))
		lua_pushinteger(L, p->x);

	else if (!strcmp(index, "y"))
		lua_pushinteger(L, p->x);

	else if (!strcmp(index, "width"))
		lua_pushinteger(L, p->width);

	else if (!strcmp(index, "height"))
		lua_pushinteger(L, p->height);

	else if (!strcmp(index, "window"))
		luacef_pushhandle(L, p->window);

	else if (!strcmp(index, "windowless_rendering_enabled"))
		lua_pushinteger(L, p->windowless_rendering_enabled);

	//else if (!strcmp(index, __transparent_painting_enabled))
	//	lua_pushinteger(L, p->transparent_painting_enabled);

	else return 0;

	return 1;
}

API(newindex)
{
	SELF* p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* index = lua_tostring(L, 2);

	if (!strcmp(index, "parent_window"))
		p->parent_window = luacef_tohandle(L, 3);

#if defined(OS_WIN)
	else if (!strcmp(index, "window_name"))
		p->window_name = luacef_tostring(L, 3);

	else if (!strcmp(index, "style"))
		p->style = lua_tointeger(L, 3);

	else if (!strcmp(index, "ex_style"))
		p->ex_style = lua_tointeger(L, 3);

	else if (!strcmp(index, "menu"))
		p->menu = luacef_tohandle(L, 3);
#endif

	else if (!strcmp(index, "x"))
		p->x = lua_tointeger(L, 3);

	else if (!strcmp(index, "y"))
		p->x = lua_tointeger(L, 3);

	else if (!strcmp(index, "width"))
		p->width = lua_tointeger(L, 3);

	else if (!strcmp(index, "height"))
		p->height = lua_tointeger(L, 3);

	else if (!strcmp(index, "window"))
		p->window = luacef_tohandle(L, 3);

	else if (!strcmp(index, "windowless_rendering_enabled"))
		p->windowless_rendering_enabled = lua_tointeger(L, 3);

	//else if (!strcmp(index, "transparent_painting_enabled"))
		//p->transparent_painting_enabled = lua_tointeger(L, 3);

	return 0;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

// meta =========================

API_M(meta)
{
	{ "__len", API_N(len) },
	{ "__unm", API_N(unm) },
	{ "__index" , API_N(index) },
	{ "__newindex" , API_N(newindex) },

	LUAREGEND
};




// register =========================

void luacef_types_os_reg(lua_State *L)
{
	luaL_newmetatable(L, __main_args__);
	luaL_setfuncs(L, LCEF_API_N(MainArgs, meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, LCEF_API_N(MainArgs, new));
	lua_setfield(L, -2, "newMainArgs");

	luaL_newmetatable(L, __window_info__);
	luaL_setfuncs(L, LCEF_API_N(WindowInfo, meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, LCEF_API_N(WindowInfo, new));
	lua_setfield(L, -2, "newWindowInfo");
}