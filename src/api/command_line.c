#include "../luacef.h"

#include "include/capi/cef_command_line_capi.h"

typedef cef_command_line_t luacef_CommandLine;

/*
	<int> CommandLine:IsValid()
*/
static int luacef_CommandLine_IsValid(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	int i = p->is_valid(p);

	lua_pushinteger(L, i);
	return 1;
}

/*
	<int> CommandLine:IsReadOnly()
*/
static int luacef_CommandLine_IsReadOnly(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	int i = p->is_read_only(p);

	lua_pushinteger(L, i);
	return 1;
}

/*
	<CefCommandLine> CommandLine:Copy()
*/
static int luacef_CommandLine_Copy(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	luacef_CommandLine *cpy = p->copy(p);

	luacef_pushudata(L, cpy, __CefCommandLine);
	return 1;
}

/*
	<nil> CommandLine:InitFromArgv(<int> argc, <table> argv)
*/
static int luacef_CommandLine_InitFromArgv(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	int argc = lua_tointeger(L, 2);
	char **argv = malloc(argc * sizeof(char*));

	for (int i = 0; i < argc; i++) {
		lua_rawgeti(L, 3, i + 1);
		argv[i] = lua_tostring(L, -1);
	}

	p->init_from_argv(p, argc, argv);

	free(argv);

	return 0;
}

/*
	<nil> CommandLine:InitFromString(<str> command_line)
*/
static int luacef_CommandLine_InitFromString(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 1);
	p->init_from_string(p, &s);

	return 0;
}

/*
	<nil> CommandLine:Reset()
*/
static int luacef_CommandLine_Reset(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	p->reset(p);

	return 0;
}

/*
	<CefStringList> CommandLine:GetArgv()
*/
static int luacef_CommandLine_GetArgv(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);
	cef_string_list_t l = cef_string_list_alloc();

	p->get_argv(p, l);

	luacef_pushudata(L, l, __string_list__);
	return 1;
}

/*
	<str> CommandLine:GetCommandLineString()
*/
static int luacef_CommandLine_GetCommandLineString(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_userfree_t s = p->get_command_line_string(p);

	luacef_pushstring_free(L, s);
	return 1;
}

/*
	<str> CommandLine:GetProgram()
*/
static int luacef_CommandLine_GetProgram(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_userfree_t s = p->get_program(p);

	luacef_pushstring_free(L, s);
	return 1;
}

/*
	<nil> CommandLine:SetProgram(<str> program)
*/
static int luacef_CommandLine_SetProgram(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	p->set_program(p, &s);

	return 0;
}

/*
	<int> CommandLine:HasSwitches()
*/
static int luacef_CommandLine_HasSwitches(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);
	
	int i = p->has_switches(p);

	lua_pushinteger(L, i);
	return 1;
}

/*
	<int> CommandLine:HasSwitch(<str> switch)
*/
static int luacef_CommandLine_HasSwitch(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	int i = p->has_switch(p, &s);

	lua_pushinteger(L, i);
	return 1;
}

/*
	<str> CommandLine:GetSwitchValue(<str> switch)
*/
static int luacef_CommandLine_GetSwitchValue(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	cef_string_userfree_t r = p->get_switch_value(p, &s);

	luacef_pushstring_free(L, r);
	return 1;
}

/*
	<table> CommandLine:GetSwitches()
		-> { ["--switch"] = "1", ... }
*/
static int luacef_CommandLine_GetSwitches(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_map_t map = cef_string_map_alloc();
	p->get_switches(p, map);
	//cef_string_map_key;

	//
	// todo;
	//

	lua_newtable(L);

	return 1;
}

/*
	<nil> CommandLine:AppendSwitch(<str> name)
*/
static int luacef_CommandLine_AppendSwitch(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	p->append_switch(p, &s);

	return 0;
}

/*
	<nil> CommandLine:AppendSwitchWithValue(<str> name, <str> value)
*/
static int luacef_CommandLine_AppendSwitchWithValue(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	cef_string_t s2 = luacef_tostring(L, 3);
	p->append_switch_with_value(p, &s, &s2);

	return 0;
}

/*
	<int> CommandLine:HasArguments()
*/
static int luacef_CommandLine_HasArguments(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	int i = p->has_arguments(p);

	lua_pushinteger(L, 1);
	return 0;
}

/*
	<table> CommandLine:GetArguments()
		-> { "--s1", "--s2", ... }
*/
static int luacef_CommandLine_GetArguments(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_list_t l = cef_string_list_alloc;
	p->get_arguments(p, l);

	lua_newtable(L);

	int sz = cef_string_list_size(l);

	cef_string_t s = { 0 };
	cef_string_utf8_t s2 = { 0 };

	for (int i = 0; i < sz; i++) {
		cef_string_list_value(l, i, &s);
		cef_string_to_utf8(s.str, s.length, &s2);
		lua_pushstring(L, s2.str);
		lua_rawseti(L, -2, i+1);
	}

	cef_string_list_free(l);

	lua_pushvalue(L, -1);
	return 0;
}

/*
	<nil> CommandLine:AppendArgument(<str> argument)
*/
static int luacef_CommandLine_AppendArgument(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	p->append_argument(p, &s);

	return 0;
}

/*
	<nil> CommandLine:PrependWrapper(<str> wrapper)
*/
static int luacef_CommandLine_PrependWrapper(lua_State *L)
{
	luacef_CommandLine *p = luacef_toudata(L, 1);

	cef_string_t s = luacef_tostring(L, 2);
	p->prepend_wrapper(p, &s);

	return 0;
}

// static functions =========================

/*
	<CefCommandLine> cef.CommandLine.Create()
	<CefCommandLine> CommandLine.Create()
*/
static int luacef_CommandLine_Create(lua_State *L)
{
	cef_command_line_t *p = cef_command_line_create();

	luacef_pushudata(L, p, __CefCommandLine);
	return 1;
}

/*
	<CefCommandLine> cef.CommandLine.GetGlobal()
	<CefCommandLine> CommandLine.GetGlobal()
*/
static int luacef_CommandLine_GetGlobal(lua_State *L)
{
	cef_command_line_t *p = cef_command_line_get_global();

	luacef_pushudata(L, p, __CefCommandLine);
	return 1;
}

// ==================================================

static const luaL_Reg luacef_CommandLine_meta[] = {
	{ "IsValid", luacef_CommandLine_IsValid },
	{ "IsReadOnly", luacef_CommandLine_IsReadOnly },
	{ "Copy", luacef_CommandLine_Copy },
	{ "InitFromArgv", luacef_CommandLine_InitFromArgv },
	{ "InitFromString", luacef_CommandLine_InitFromString },
	{ "Reset", luacef_CommandLine_Reset },
	{ "GetArgv", luacef_CommandLine_GetArgv },
	{ "GetCommandLineString", luacef_CommandLine_GetCommandLineString },
	{ "GetProgram", luacef_CommandLine_GetProgram },
	{ "SetProgram", luacef_CommandLine_SetProgram },
	{ "HasSwitches", luacef_CommandLine_HasSwitches },
	{ "HasSwitch", luacef_CommandLine_HasSwitch },
	{ "GetSwitchValue", luacef_CommandLine_GetSwitchValue },
	{ "GetSwitches", luacef_CommandLine_GetSwitches },
	{ "AppendSwitch", luacef_CommandLine_AppendSwitch },
	{ "AppendSwitchWithValue", luacef_CommandLine_AppendSwitchWithValue },
	{ "HasArguments", luacef_CommandLine_HasArguments },
	{ "GetArguments", luacef_CommandLine_GetArguments },
	{ "AppendArgument", luacef_CommandLine_AppendArgument },
	{ "PrependWrapper", luacef_CommandLine_PrependWrapper },
	//
	{ "Create", luacef_CommandLine_Create },
	{ "GetGlobal", luacef_CommandLine_GetGlobal },
	{ NULL, NULL }
};

static const luaL_Reg luacef_CommandLine_meta_static[] = {
	{ "Create", luacef_CommandLine_Create },
	{ "GetGlobal", luacef_CommandLine_GetGlobal },
	{ NULL, NULL }
};

void luacef_CommandLine_reg(lua_State *L)
{
	luaL_newmetatable(L, __CefCommandLine);
	luaL_setfuncs(L, luacef_CommandLine_meta, 0);
	lua_setfield(L, -1, __index__);

	lua_newtable(L);
	luaL_setfuncs(L, luacef_CommandLine_meta_static, 0);
	lua_setfield(L, -2, "CommandLine");
}