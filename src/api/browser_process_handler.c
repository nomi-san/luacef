#include "../luacef.h"
#include "include/capi/cef_browser_process_handler_capi.h"

typedef struct luacef_BrowserProcessHandler {

	cef_browser_process_handler_t self;

	lua_State *L;
	int ref;

} luacef_BrowserProcessHandler;

#define BPH(fn) \
	LCEF_API(BrowserProcessHandler, fn)

#define BPH_N(fn) \
	LCEF_API_N(BrowserProcessHandler, fn)

#define BPH_M(mname) \
	LCEF_M(BrowserProcessHandler, mname)

#define SELF luacef_BrowserProcessHandler

/*
	<void> BrowserProcessHandler:OnContextInitialized()
*/
void CEF_CALLBACK BPH_N(OnContextInitialized)(SELF *self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnContextInitialized)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // 1

		lua_pcall(self->L, 1, 0, 8);
	}
}

/*
	<void> BrowserProcessHandler:OnBeforeChildProcessLaunch(
		<CefCommandLine>	command_line
	)
*/
void CEF_CALLBACK BPH_N(OnBeforeChildProcessLaunch)(SELF *self,
	struct _cef_command_line_t*	command_line)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeChildProcessLaunch)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // 1
		luacef_pushuserdata(self->L, command_line, __CefCommandLine); // 2
		
		lua_pcall(self->L, 2, 0, 8);
	}
}

/*
	<void> BrowserProcessHandler:OnRenderProcessThreadCreated(
		<CefListValue> extra_info
	)
*/
void CEF_CALLBACK BPH_N(OnRenderProcessThreadCreated)(
	SELF *self,
	struct _cef_list_value_t*				extra_info)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnRenderProcessThreadCreated)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // 1
		luacef_pushuserdata(self->L, self, __CefListValue); // 2

		lua_pcall(self->L, 2, 0, 8);
	}
}

/*
	<void> BrowserProcessHandler:OnScheduleMessagePumpWork(
		<int> delay_ms
	)
*/
void CEF_CALLBACK BPH_N(OnScheduleMessagePumpWork)(SELF *self, int64 delay_ms)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnScheduleMessagePumpWork)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // 1
		lua_pushinteger(self->L, delay_ms); // 2

		lua_pcall(self->L, 2, 0, 8);
	}
}

/*
	<CefPrintHandler> BrowserProcessHandler:GetPrintHandler()
*/
struct _cef_print_handler_t* CEF_CALLBACK BPH_N(GetPrintHandler)(SELF *self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetPrintHandler)) {

		luacef_pushuserdata(self->L, self, __browser_process_handler__); // 1

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

BPH(new)
{
	size_t sz = sizeof(SELF);
	SELF *p = calloc(1, sz);
	p->self.base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __OnContextInitialized))
			p->self.on_context_initialized = (void*)BPH_N(OnContextInitialized);

		if (lua_getfield(L, 1, __OnBeforeChildProcessLaunch))
			p->self.on_before_child_process_launch = (void*)BPH_N(OnBeforeChildProcessLaunch);

		if (lua_getfield(L, 1, __OnRenderProcessThreadCreated))
			p->self.on_render_process_thread_created = (void*)BPH_N(OnRenderProcessThreadCreated);

		if (lua_getfield(L, 1, __OnScheduleMessagePumpWork))
			p->self.on_schedule_message_pump_work = (void*)BPH_N(OnScheduleMessagePumpWork);

		if (lua_getfield(L, 1, __GetPrintHandler))
			p->self.get_print_handler = (void*)BPH_N(GetPrintHandler);
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __browser_process_handler__);
	return 1;
}

BPH(index)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(p->L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		; //

	else if (!strcmp(i, __OnContextInitialized))
		lua_getfield(L, -1, __OnContextInitialized);

	else if (!strcmp(i, __OnBeforeChildProcessLaunch))
		lua_getfield(L, -1, __OnBeforeChildProcessLaunch);

	else if (!strcmp(i, __OnRenderProcessThreadCreated))
			lua_getfield(L, -1, __OnRenderProcessThreadCreated);

	else if (!strcmp(i, __OnScheduleMessagePumpWork))
			lua_getfield(L, -1, __OnScheduleMessagePumpWork);

	else if (!strcmp(i, __GetPrintHandler))
			lua_getfield(L, -1, __GetPrintHandler);

	else return 0;

	return 1;
}

BPH(newindex)
{
	SELF* p = luacef_touserdata(L, 1);
	if (!p || !p->L) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnContextInitialized)) {
		lua_setfield(L, -2, __OnContextInitialized);
		p->self.on_context_initialized = (void*)BPH_N(OnContextInitialized);
	}

	else if (!strcmp(i, __OnBeforeChildProcessLaunch)) {
		lua_setfield(L, -2, __OnBeforeChildProcessLaunch);
		p->self.on_before_child_process_launch = (void*)BPH_N(OnBeforeChildProcessLaunch);
	}

	else if (!strcmp(i, __OnRenderProcessThreadCreated)) {
		lua_setfield(L, -2, __OnRenderProcessThreadCreated);
		p->self.on_render_process_thread_created = (void*)BPH_N(OnRenderProcessThreadCreated);
	}

	else if (!strcmp(i, __OnScheduleMessagePumpWork)) {
		lua_setfield(L, -2, __OnScheduleMessagePumpWork);
		p->self.on_schedule_message_pump_work = (void*)BPH_N(OnScheduleMessagePumpWork);
	}

	else if (!strcmp(i, __GetPrintHandler)) {
		lua_setfield(L, -2, __GetPrintHandler);
		p->self.get_print_handler = (void*)BPH_N(GetPrintHandler);
	}
		
	return 0;
}

BPH(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

BPH(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

BPH_M(meta)
{
	{ "__unm", BPH_N(unm) },
	{ "__len", BPH_N(len) },
	{ "__index", BPH_N(index) },
	{ "__newindex", BPH_N(newindex) },

	LUAREGEND
};

void BPH_N(reg)(lua_State* L)
{
	luaL_newmetatable(L, __browser_process_handler__);
	luaL_setfuncs(L, BPH_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, BPH_N(new));
	lua_setfield(L, -2, "newBrowserProcessHandler");
}