#include "../luacef.h"

typedef struct luacef_browser_process_handler {

	cef_base_t base;

	void (CEF_CALLBACK *on_context_initialized)(
		struct luacef_browser_process_handler*	self);

	void (CEF_CALLBACK *on_before_child_process_launch)(
		struct luacef_browser_process_handler*	self,
		struct _cef_command_line_t*				command_line);

	void (CEF_CALLBACK *on_render_process_thread_created)(
		struct luacef_browser_process_handler*	self,
		struct _cef_list_value_t*				extra_info);

	struct _cef_print_handler_t* (CEF_CALLBACK *get_print_handler)(
		struct luacef_browser_process_handler*	self);

	void (CEF_CALLBACK *on_schedule_message_pump_work)(
		struct luacef_browser_process_handler*	self,
		int64									delay_ms);

	lua_State *L;
	int ref;

} luacef_browser_process_handler;

/*
	<void> BrowserProcessHandler:OnContextInitialized()
*/
void CEF_CALLBACK bph_on_context_initialized(
	struct luacef_browser_process_handler*	self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_context_initialized)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // self, first arg

		lua_pcall(self->L, 1, 0, -8);
	}
}

/*
	<void> BrowserProcessHandler:OnBeforeChildProcessLaunch(
		<CommandLine>	command_line
	)
*/
void CEF_CALLBACK bph_on_before_child_process_launch(
	struct luacef_browser_process_handler*	self,
	struct _cef_command_line_t*				command_line)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_context_initialized)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // self, first arg

		luacef_pushuserdata(self->L, command_line, __command_line__);
		
		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<void> BrowserProcessHandler:OnRenderProcessThreadCreated(
		<ListValue> extra_info
	)
*/
void CEF_CALLBACK bph_on_render_process_thread_created(
	struct luacef_browser_process_handler*	self,
	struct _cef_list_value_t*				extra_info)
{
	// todo
}

/*
	<void> BrowserProcessHandler:OnScheduleMessagePumpWork(
		<int> delay_ms
	)
*/
void CEF_CALLBACK bph_on_schedule_message_pump_work(
	struct luacef_browser_process_handler*	self,
	int64									delay_ms)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_schedule_message_pump_work)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // self, first arg

		lua_pushinteger(self->L, delay_ms);

		lua_pcall(self->L, 2, 0, -8);
	}
}

/*
	<PrintHandler> BrowserProcessHandler.PrintHandler
*/
struct _cef_print_handler_t* CEF_CALLBACK bph_get_print_handler(
	struct luacef_browser_process_handler*	self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __get_print_handler)) {
		return luacef_touserdata(self->L, -1);
	}
	return NULL;
}

static int luacef_browser_process_handler_new(lua_State* L)
{
	size_t sz = sizeof(luacef_browser_process_handler);
	luacef_browser_process_handler *p = calloc(1, sz);
	p->base.size = sz;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __on_context_initialized))
			p->on_context_initialized = bph_on_context_initialized;

		if (lua_getfield(L, 1, __on_before_child_process_launch))
			p->on_before_child_process_launch = bph_on_before_child_process_launch;

		if (lua_getfield(L, 1, __on_render_process_thread_created))
			p->on_render_process_thread_created = bph_on_render_process_thread_created;

		if (lua_getfield(L, 1, __on_schedule_message_pump_work))
			p->on_schedule_message_pump_work = bph_on_schedule_message_pump_work;

		if (lua_getfield(L, 1, __get_print_handler))
			p->get_print_handler = bph_get_print_handler;
	}

	luacef_pushuserdata(L, p, __browser_process_handler__);
	return 1;
}

static int luacef_browser_process_handler_release(lua_State* L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_browser_process_handler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_browser_process_handler_index(lua_State* L)
{
	luacef_browser_process_handler* p = luacef_touserdata(L, 1);
	if (!p || !p->L) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(p->L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_browser_process_handler_release);

	else if (!strcmp(i, __on_context_initialized))
		lua_getfield(L, -1, __on_context_initialized);

	else if (!strcmp(i, __on_before_child_process_launch))
		lua_getfield(L, -1, __on_before_child_process_launch);

	else if (!strcmp(i, __on_render_process_thread_created))
			lua_getfield(L, -1, __on_render_process_thread_created);

	else if (!strcmp(i, __on_schedule_message_pump_work))
			lua_getfield(L, -1, __on_schedule_message_pump_work);

	else if (!strcmp(i, __get_print_handler))
			lua_getfield(L, -1, __get_print_handler);

	else return 0;

	return 1;
}

static int luacef_browser_process_handler_newindex(lua_State* L)
{
	luacef_browser_process_handler* p = luacef_touserdata(L, 1);
	if (!p || !p->L) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(p->L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __on_context_initialized)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_context_initialized);
		p->on_context_initialized = bph_on_context_initialized;
	}

	else if (!strcmp(i, __on_before_child_process_launch)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_before_child_process_launch);
		p->on_before_child_process_launch = bph_on_before_child_process_launch;
	}

	else if (!strcmp(i, __on_render_process_thread_created)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_render_process_thread_created);
		p->on_render_process_thread_created = bph_on_render_process_thread_created;
	}

	else if (!strcmp(i, __on_schedule_message_pump_work)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_schedule_message_pump_work);
		p->on_schedule_message_pump_work = bph_on_schedule_message_pump_work;
	}

	else if (!strcmp(i, __get_print_handler)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __get_print_handler);
		p->get_print_handler = bph_get_print_handler;
	}
		
	return 0;
}

static const luaL_Reg luacef_browser_process_handler_m[] = {
	{ "__index", luacef_browser_process_handler_index },
	{ "__newindex", luacef_browser_process_handler_newindex },
	{ NULL, NULL }
};

void luacef_browser_process_handler_reg(lua_State* L)
{
	luaL_newmetatable(L, __browser_process_handler__);
	luaL_setfuncs(L, luacef_browser_process_handler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_browser_process_handler_new);
	lua_setfield(L, -2, "newBrowserProcessHandler");
}