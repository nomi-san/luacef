#include "luacef_handler.h"

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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, extra_info, __list_value__); // 2

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
		luaL_setmetatable(self->L, __render_process_handler__);

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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__); // 2

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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__); // 2

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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__); // 2
		luacef_pushuserdata(self->L, frame, __frame__);		// 3
		luacef_pushuserdata(self->L, request, __request__);	// 4
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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);
		luacef_pushuserdata(self->L, frame, __frame__);
		luacef_pushuserdata(self->L, node, __domnode__);

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
		luaL_setmetatable(self->L, __render_process_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);
		lua_pushinteger(self->L, source_process);
		luacef_pushuserdata(self->L, message, __process_message__);

		lua_pcall(self->L, 4, 0, -8);
		return lua_tointeger(self->L, -1);
	}
	
	return 0;
}