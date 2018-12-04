#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
      
//  _           _   
// | |_ ___ ___| |_ 
// |  _| .'|_ -| '_|
// |_| |__,|___|_,_|                
//==================

// task =======================================

/*
	<void> Task:Execute()
*/
static int luacef_Task_Execute(lua_State *L)
{
	cef_task_t *p = luacef_touserdata(L, 1);

	p->execute(p);

	return 0;
}

// task_runner ============================================

/*
	<bool> TaskRunner:IsSame(
		<TaskRunner> that
	)
*/
static int luacef_TaskRunner_IsSame(lua_State *L)
{
	cef_task_runner_t *p = luacef_touserdata(L, 1);
	cef_task_runner_t *that = luacef_checkudata(L, 2, __task_runner__);

	int r = p->is_same(
		p,
		that
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> TaskRunner:BelongsToCurrentThread()
*/
static int luacef_TaskRunner_BelongsToCurrentThread(lua_State *L)
{
	cef_task_runner_t *p = luacef_touserdata(L, 1);

	int r = p->belongs_to_current_thread(p);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> TaskRunner:BelongsToThread(
		<int> threadId
	)
*/
static int luacef_TaskRunner_BelongsToThread(lua_State *L)
{
	cef_task_runner_t *p = luacef_touserdata(L, 1);
	cef_thread_id_t id = lua_tointeger(L, 2);

	int r = p->belongs_to_thread(
		p, 
		id
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> TaskRunner:PostTask(
		<Task> task
	)
*/
static int luacef_TaskRunner_PostTask(lua_State *L)
{
	cef_task_runner_t *p = luacef_touserdata(L, 1);
	cef_task_t *task = luacef_checkudata(L, 2, __task__);

	int r = p->post_task(
		p,
		task
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> TaskRunner:PostDelayedTask(
		<Task> task,
		<int> delay_ms
	)
*/
static int luacef_TaskRunner_PostDelayedTask(lua_State *L)
{
	cef_task_runner_t *p = luacef_touserdata(L, 1);
	cef_task_t *task = luacef_checkudata(L, 2, __task__);
	int delay_ms = lua_tointeger(L, 3);

	int r = p->post_delayed_task(
		p,
		task,
		delay_ms
	);

	lua_pushboolean(L, r);
	return 1;
}

// static members ===================================================

/*
	<TaskRunner> TaskRunner.GetForCurrentThread()
*/
static int luacef_TaskRunner_GetForCurrentThread(lua_State *L)
{
	cef_task_runner_t *r = cef_task_runner_get_for_current_thread();

	luacef_pushuserdata(L, r, __task_runner__);
	return 1;
}

/*
	<TaskRunner> TaskRunner.GetForThread(
		<int> thread_id
	)
*/
static int luacef_TaskRunner_GetForThread(lua_State *L)
{
	cef_thread_id_t id = lua_tointeger(L, 1);

	cef_task_runner_t *r = cef_task_runner_get_for_thread(
		id
	);

	luacef_pushuserdata(L, r, __task_runner__);
	return 1;
}

// static functions ============================

/*
	<bool> CurrentlyOn(
		<int> threadId
	)
*/
static int luacef_CurrentlyOn(lua_State *L)
{
	cef_thread_id_t id = lua_tointeger(L, 1);

	int r = cef_currently_on(id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> PostTask(
		<int> threadId,
		<Task> task
	)
*/
static int luacef_PostTask(lua_State *L)
{
	cef_thread_id_t id = lua_tointeger(L, 1);
	cef_task_t *task = luacef_checkudata(L, 2, __task__);

	int r = cef_post_task(id, task);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> PostDelayedTask(
		<Task> task,
		<int> delay_ms
	)
*/
static int luacef_PostDelayedTask(lua_State *L)
{
	cef_thread_id_t id = lua_tointeger(L, 1);
	cef_task_t *task = luacef_checkudata(L, 2, __task__);
	int delay_ms = lua_tointeger(L, 3);
	
	int r = cef_post_delayed_task(id, task, delay_ms);

	lua_pushboolean(L, r);
	return 1;
}

// ==================================================

static const luaL_Reg luacef_Task_m[] = {
	{ "Execute", luacef_Task_Execute },
	{ NULL, NULL}
};

static const luaL_Reg luacef_TaskRunner_m[] = {
	{ "IsSame", luacef_TaskRunner_IsSame },
	{ "BelongsToCurrentThread", luacef_TaskRunner_BelongsToCurrentThread },
	{ "BelongsToThread", luacef_TaskRunner_BelongsToThread },
	{ "PostTask", luacef_TaskRunner_PostTask },
	{ "PostDelayedTask", luacef_TaskRunner_PostDelayedTask },
	{ "GetForCurrentThread", luacef_TaskRunner_GetForCurrentThread },
	{ "GetForThread", luacef_TaskRunner_GetForThread },
	{ NULL, NULL}
};

// ==================================================

void luacef_Task_reg(lua_State *L)
{
	luaL_newmetatable(L, __task__);
	luaL_setfuncs(L, luacef_Task_m, 0);
	lua_setfield(L, -1, __index__);

	luaL_newmetatable(L, __task_runner__);
	luaL_setfuncs(L, luacef_TaskRunner_m, 0);
	lua_setfield(L, -1, __index__);

	lua_pushcfunction(L, luacef_CurrentlyOn);
	lua_setfield(L, -2, "CurrentlyOn");

	lua_pushcfunction(L, luacef_PostTask);
	lua_setfield(L, -2, "PostTask");

	lua_pushcfunction(L, luacef_PostDelayedTask);
	lua_setfield(L, -2, "PostDelayedTask");
}