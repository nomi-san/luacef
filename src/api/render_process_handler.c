#include "../luacef.h"

static const char	*_rph_on_render_thread_created = "OnRenderThreadCreated";
static const char	*_rph_on_web_kit_initialized = "OnWebKitInitialized";
static const char	*_rph_on_browser_created = "OnBrowserCreated";
static const char	*_rph_on_browser_destroyed = "OnBrowserDestroyed";
static const char	*_rph_get_load_handler = "LoadHandler";
static const char	*_rph_on_before_navigation = "OnBeforeNavigation";
static const char	*_rph_on_context_created = "OnContextCreated";
static const char	*_rph_on_context_released = "OnContextReleased";
static const char	*_rph_on_uncaught_exception = "OnUncaughtException";
static const char	*_rph_on_focused_node_changed = "OnFocusedNodeChanged";
static const char	*_rph_on_process_message_received = "OnProcessMessageReceived";

typedef struct luacef_render_process_handler {

	cef_base_t base;

	void (CEF_CALLBACK *on_render_thread_created)(
		struct luacef_render_process_handler*	self,
		struct _cef_list_value_t*				extra_info);

	void (CEF_CALLBACK *on_web_kit_initialized)(
		struct luacef_render_process_handler*	 self);

	void (CEF_CALLBACK *on_browser_created)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser);

	void (CEF_CALLBACK *on_browser_destroyed)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser);

	struct _cef_load_handler_t* (CEF_CALLBACK *get_load_handler)(
		struct luacef_render_process_handler*	self);

	int (CEF_CALLBACK *on_before_navigation)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_request_t*					request,
		cef_navigation_type_t					navigation_type,
		int										is_redirect);

	void (CEF_CALLBACK *on_context_created)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_v8context_t*				context);

	void (CEF_CALLBACK *on_context_released)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_v8context_t*				context);

	void (CEF_CALLBACK *on_uncaught_exception)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_v8context_t*				context,
		struct _cef_v8exception_t*				exception,
		struct _cef_v8stack_trace_t*			stackTrace);

	void (CEF_CALLBACK *on_focused_node_changed)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_domnode_t*					node);

	int (CEF_CALLBACK *on_process_message_received)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		cef_process_id_t						source_process,
		struct _cef_process_message_t*			message);

	lua_State* L;
	void* self;
	int ref;

} luacef_render_process_handler;

/*
	<void> RenderProcessHandler:OnRenderThreadCreated(
		<ListValue>	extra_info
	)
*/
void CEF_CALLBACK rph_on_render_thread_created(
	struct luacef_render_process_handler*	self,
	struct _cef_list_value_t*				extra_info)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_browser_created)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, extra_info, __CefListValue); // 2

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<void> RenderProcessHandler:OnWebKitInitialized()
*/
void CEF_CALLBACK rph_on_web_kit_initialized(
	struct luacef_render_process_handler*	 self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_browser_created)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		lua_pcall(self->L, 1, 0, -8);
	}
}

/*
	<void> RenderProcessHandler:OnBrowserCreated(
		<Browser> browser
	)
*/
void CEF_CALLBACK rph_on_browser_created(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_browser_created)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<void> RenderProcessHandler:OnBrowserDestoyed(
		<Browser> browser
	)
*/
void CEF_CALLBACK rph_on_browser_destroyed(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_browser_destroyed)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<LoadHandler> RenderProcessHandler.LoadHandler
*/
struct _cef_load_handler_t* CEF_CALLBACK rph_get_load_handler(
	struct luacef_render_process_handler*	self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_get_load_handler)) {
		return luacef_touserdata(self->L, -1);
	}
	return NULL;
}

/*
	<int> RenderProcessHandler:OnBeforeNavigation(
		<Browser>	browser,
		<Frame>		frame,
		<int>		navigation_type,
		<bool>		is_redirect
	)
*/
int CEF_CALLBACK rph_on_before_navigation(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_request_t*					request,
	cef_navigation_type_t					navigation_type,
	int										is_redirect)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_before_navigation)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, frame, __CefFrame);		// 3
		luacef_pushuserdata(self->L, request, __CefRequest);	// 4
		lua_pushinteger(self->L, navigation_type);			// 5
		lua_pushinteger(self->L, is_redirect);				// 6

		lua_pcall(self->L, 6, 0, -8);
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

/*
	<void> RenderProcessHandler:OnContextCreated(
		<Browser>	browser,
		<Frame>		frame,
		<V8Context>	context
	)
*/
void CEF_CALLBACK rph_on_context_created(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_v8context_t*				context)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_context_created)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);
		luacef_pushuserdata(self->L, frame, __CefFrame);
		luacef_pushuserdata(self->L, context, __v8context__);

		lua_pcall(self->L, 4, 0, -8);
	}
}

/*
	<void> RenderProcessHandler:OnContextReleased(
		<Browser>	browser,
		<Frame>		frame,
		<V8Context>	context
	)
*/
void CEF_CALLBACK rph_on_context_released(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_v8context_t*				context)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_context_released)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);
		luacef_pushuserdata(self->L, frame, __CefFrame);
		luacef_pushuserdata(self->L, context, __v8context__);

		lua_pcall(self->L, 4, 0, -8);
	}
}

/*
	<void> RenderProcessHandler:OnUncaughtException(
		<Browser>		browser,
		<Frame>			frame,
		<V8Context>		context,
		<V8Exception>	exception,
		<V8StackTrace>	stackTrace
	)
*/
void CEF_CALLBACK rph_on_uncaught_exception(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_v8context_t*				context,
	struct _cef_v8exception_t*				exception,
	struct _cef_v8stack_trace_t*			stackTrace)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_uncaught_exception)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);
		luacef_pushuserdata(self->L, frame, __CefFrame);
		luacef_pushuserdata(self->L, context, __v8context__);
		luacef_pushuserdata(self->L, exception, __v8exception__);
		luacef_pushuserdata(self->L, stackTrace, __v8stack_trace__);

		lua_pcall(self->L, 6, 0, -8);
	}
}

/*
	<void> RenderProcessHandler:OnFocusedNodeChanged(
		<Browser>	browser,
		<Frame>		frame,
		<DOMNode>	node
	)
*/
void CEF_CALLBACK rph_on_focused_node_changed(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_domnode_t*					node)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_focused_node_changed)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);
		luacef_pushuserdata(self->L, frame, __CefFrame);
		luacef_pushuserdata(self->L, node, __CefDOMMode);

		lua_pcall(self->L, 4, 0, -8);
	}
}

/*
	<int> RenderProcessHandler:OnProcessMessageReceived(
		<Browser>			browser,
		<int>				source_process_id,
		<ProcessMessage>	message
	)
*/
int CEF_CALLBACK rph_on_process_message_received(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	cef_process_id_t						source_process,
	struct _cef_process_message_t*			message)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, _rph_on_process_message_received)) {

		lua_pushlightuserdata(self->L, self->self); // self, first arg
		luaL_setmetatable(self->L, __CefRenderProcessHandler);

		luacef_pushuserdata(self->L, browser, __CefBrowser);
		lua_pushinteger(self->L, source_process);
		luacef_pushuserdata(self->L, message, __CefProcessMessage);

		lua_pcall(self->L, 4, 0, -8);
		return lua_tointeger(self->L, -1);
	}
	
	return 0;
}

static int luacef_RenderProcessHandler_new(lua_State* L) {
    size_t sz = sizeof(luacef_render_process_handler);
    luacef_render_process_handler* p = luacef_alloc(sz);
    p->base.size = sz;
    p->L = L;

    if (lua_istable(L, 1)) {
        lua_pushvalue(L, 1);
        p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

        if (lua_getfield(L, 1, _rph_on_render_thread_created))
            p->on_render_thread_created =
                !lua_isfunction(L, -1) ? NULL : rph_on_render_thread_created;

        if (lua_getfield(L, 1, _rph_on_web_kit_initialized))
            p->on_web_kit_initialized =
                !lua_isfunction(L, -1) ? NULL : rph_on_web_kit_initialized;

        if (lua_getfield(L, 1, _rph_on_browser_created))
            p->on_browser_created =
                !lua_isfunction(L, -1) ? NULL : rph_on_browser_created;

        if (lua_getfield(L, 1, _rph_on_browser_destroyed))
            p->on_browser_destroyed =
                !lua_isfunction(L, -1) ? NULL : rph_on_browser_destroyed;

        if (lua_getfield(L, 1, _rph_get_load_handler))
            p->get_load_handler =
                !lua_isfunction(L, -1) ? NULL : rph_get_load_handler;

        if (lua_getfield(L, 1, _rph_on_before_navigation))
            p->on_before_navigation =
                !lua_isfunction(L, -1) ? NULL : rph_on_before_navigation;

        if (lua_getfield(L, 1, _rph_on_context_created))
            p->on_context_created =
                !lua_isfunction(L, -1) ? NULL : rph_on_context_created;

        if (lua_getfield(L, 1, _rph_on_context_released))
            p->on_context_released =
                !lua_isfunction(L, -1) ? NULL : rph_on_context_released;

        if (lua_getfield(L, 1, _rph_on_uncaught_exception))
            p->on_uncaught_exception =
                !lua_isfunction(L, -1) ? NULL : rph_on_uncaught_exception;

        if (lua_getfield(L, 1, _rph_on_focused_node_changed))
            p->on_focused_node_changed =
                !lua_isfunction(L, -1) ? NULL : rph_on_focused_node_changed;

        if (lua_getfield(L, 1, _rph_on_process_message_received))
            p->on_process_message_received =
                !lua_isfunction(L, -1) ? NULL : rph_on_process_message_received;

    } else {
        lua_newtable(L);
        p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }

    luacef_pushuserdata(L, p, __CefRenderProcessHandler);
    return 1;
}

static int luacef_RenderProcessHandler_release(lua_State* L) {
    if (lua_isnoneornil(L, 1))
        return 0;
    void** ud = (void**)lua_touserdata(L, 1);
    if (ud && *ud) {
        luaL_unref(L, LUA_REGISTRYINDEX,
                   ((luacef_render_process_handler*)*ud)->ref);  //
        free(*ud);
        *ud = NULL;
    }
    return 0;
}

static int luacef_RenderProcessHandler_index(lua_State* L) {
    luacef_render_process_handler* p = luacef_touserdata(L, 1);
    if (!p)
        return 0;

    const char* i = lua_tostring(L, 2);

    lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

    if (!strcmp(i, __release__))
        lua_pushcfunction(L, luacef_RenderProcessHandler_release);

    else if (!strcmp(i, _rph_on_render_thread_created))
        lua_getfield(L, -1, _rph_on_render_thread_created);

    else if (!strcmp(i, _rph_on_web_kit_initialized))
        lua_getfield(L, -1, _rph_on_web_kit_initialized);

    else if (!strcmp(i, _rph_on_browser_created))
        lua_getfield(L, -1, _rph_on_browser_created);

    else if (!strcmp(i, _rph_on_browser_destroyed))
        lua_getfield(L, -1, _rph_on_browser_destroyed);

    else if (!strcmp(i, _rph_get_load_handler))
        lua_getfield(L, -1, _rph_get_load_handler);

    else if (!strcmp(i, _rph_on_before_navigation))
        lua_getfield(L, -1, _rph_on_before_navigation);

    else if (!strcmp(i, _rph_on_context_created))
        lua_getfield(L, -1, _rph_on_context_created);

    else if (!strcmp(i, _rph_on_context_released))
        lua_getfield(L, -1, _rph_on_context_released);

    else if (!strcmp(i, _rph_on_uncaught_exception))
        lua_getfield(L, -1, _rph_on_uncaught_exception);

    else if (!strcmp(i, _rph_on_focused_node_changed))
        lua_getfield(L, -1, _rph_on_focused_node_changed);

    else if (!strcmp(i, _rph_on_process_message_received))
        lua_getfield(L, -1, _rph_on_process_message_received);

    else
        return 0;

    return 1;
}

static int luacef_RenderProcessHandler_newindex(lua_State* L) {
    luacef_render_process_handler* p = luacef_touserdata(L, 1);
    if (!p)
        return 0;

    const char* i = lua_tostring(L, 2);

    lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
    lua_pushvalue(L, 3);

    if (!strcmp(i, _rph_on_render_thread_created)) {
        lua_setfield(L, -2, _rph_on_render_thread_created);
        p->on_render_thread_created =
            !lua_isfunction(L, 3) ? NULL : rph_on_render_thread_created;
    }

    else if (!strcmp(i, _rph_on_web_kit_initialized)) {
        lua_setfield(L, -2, _rph_on_web_kit_initialized);
        p->on_web_kit_initialized =
            !lua_isfunction(L, 3) ? NULL : rph_on_web_kit_initialized;
    }

    else if (!strcmp(i, _rph_on_browser_created)) {
        lua_setfield(L, -2, _rph_on_browser_created);
        p->on_browser_created =
            !lua_isfunction(L, 3) ? NULL : rph_on_browser_created;
    }

    else if (!strcmp(i, _rph_on_browser_destroyed)) {
        lua_setfield(L, -2, _rph_on_browser_destroyed);
        p->on_browser_destroyed =
            !lua_isfunction(L, 3) ? NULL : rph_on_browser_destroyed;
    }

    else if (!strcmp(i, _rph_get_load_handler)) {
        lua_setfield(L, -2, _rph_get_load_handler);
        p->get_load_handler =
            !lua_isfunction(L, 3) ? NULL : rph_get_load_handler;
    }

    else if (!strcmp(i, _rph_on_before_navigation)) {
        lua_setfield(L, -2, _rph_on_before_navigation);
        p->on_before_navigation =
            !lua_isfunction(L, 3) ? NULL : rph_on_before_navigation;
    }

    else if (!strcmp(i, _rph_on_context_created)) {
        lua_setfield(L, -2, _rph_on_context_created);
        p->on_context_created =
            !lua_isfunction(L, 3) ? NULL : rph_on_context_created;
    }

    else if (!strcmp(i, _rph_on_context_released)) {
        lua_setfield(L, -2, _rph_on_context_released);
        p->on_context_released =
            !lua_isfunction(L, 3) ? NULL : rph_on_context_released;
    }

    else if (!strcmp(i, _rph_on_uncaught_exception)) {
        lua_setfield(L, -2, _rph_on_uncaught_exception);
        p->on_uncaught_exception =
            !lua_isfunction(L, 3) ? NULL : rph_on_uncaught_exception;
    }

    else if (!strcmp(i, _rph_on_focused_node_changed)) {
        lua_setfield(L, -2, _rph_on_focused_node_changed);
        p->on_focused_node_changed =
            !lua_isfunction(L, 3) ? NULL : rph_on_focused_node_changed;
    }

    else if (!strcmp(i, _rph_on_process_message_received)) {
        lua_setfield(L, -2, _rph_on_process_message_received);
        p->on_process_message_received =
            !lua_isfunction(L, 3) ? NULL : rph_on_process_message_received;
    }

    return 0;
}

static const luaL_Reg luacef_RenderProcessHandler_m[] = {
    {"__index", luacef_RenderProcessHandler_index},
    {"__newindex", luacef_RenderProcessHandler_newindex},
    {NULL, NULL}};

// ===================================================

void luacef_RenderProcessHandler_reg(lua_State* L) {
    luaL_newmetatable(L, __CefRenderProcessHandler);
    luaL_setfuncs(L, luacef_RenderProcessHandler_m, 0);
    lua_pop(L, 1);

    lua_pushcfunction(L, luacef_RenderProcessHandler_new);
    lua_setfield(L, -2, "newRenderProcessHandler");
}
