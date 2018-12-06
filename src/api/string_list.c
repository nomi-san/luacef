#include "../luacef.h"
#include "include/internal/cef_string_list.h"

/*
	<CefStringList> CefStringList;

	- create new string list:
		cef.newStringList{<str>, <str>, ...}
		cef.newStringList(<str>)
			-> <CefStringList>

	- read string from index (from zero):
		CefStringList[0] -> <str> -- index 0
		CefStringList[1] -> <str> -- index 1
		...
		CefStringList[n] -> <str> -- index n

		-- or //
		CefStringList:value (<int>)

	- append string to end of list:
		CefStringList:append(<str>) -- a string
		CefStringList:append{<str>, <str> ...} -- multiple strings

	- clear list:
		CefStringList:clear()

	- get size of list:
		CefStringList:size()
		#CefStringList 
			-> <int>

	- get poinnter:
		(-CefStringList) -> <udata>

	- print list to console:
		CefStringList:print()
			>> CefStringList: 0x00abcdef { ... }
*/

static const char __string_list__[] = "CefStringList";

int luacef_StringList_append(lua_State *L)
{
	cef_string_list_t sl = luacef_toudata(L, 1);

	int len;
	const char *str = lua_tolstring(L, 2, &len);

	cef_string_t s = { 0 };
	cef_string_from_utf8(str, len, &s);
	cef_string_list_append(sl, &s);

	return 0;
}

int luacef_StringList_clear(lua_State *L)
{
	cef_string_list_t sl = luacef_toudata(L, 1);
	
	cef_string_list_clear(sl);

	return 0;
}

int luacef_StringList_free(lua_State *L)
{
	cef_string_list_t sl = luacef_toudata(L, 1);

	cef_string_list_free(sl);

	return 0;
}

int luacef_StringList_len(lua_State *L);

int luacef_StringList_new(lua_State *L)
{
	cef_string_list_t sl = cef_string_list_alloc();

	int len = 0;
	const char *str = NULL;
	cef_string_t s = { 0 };

	if (lua_isstring(L, 1)) {

		str = lua_tolstring(L, 1, &len);
		
		cef_string_from_utf8(str, len, &s);
		cef_string_list_append(sl, &s);
	}
	else if (lua_istable(L, 1)) {
		int sz = lua_rawlen(L, 1);

		for (int i = 0; i < sz; i++) {
			lua_rawgeti(L, 1, i + 1);
			
			str = lua_tolstring(L, -1, &len);
			cef_string_from_utf8(str, len, &s);
			cef_string_list_append(sl, &s);
		}
	}

	luacef_pushudata(L, sl, __string_list__);
	return 1;
}

int luacef_StringList_print(lua_State *L);

int luacef_StringList_index(lua_State *L)
{
	cef_string_list_t sl = luacef_toudata(L, 1);

	if (lua_isinteger(L, 2)) {
		int idx = lua_tointeger(L, 2);

		if (idx >= cef_string_list_size(sl))
			return 0;

		cef_string_t s = { 0 };
		cef_string_utf8_t s2 = { 0 };
		
		cef_string_list_value(sl, idx, &s);
		cef_string_to_utf8(s.str, s.length, &s2);

		lua_pushstring(L, s2.str);
	}
	else if (lua_isstring(L, 2)) {
		const char *idx = lua_tostring(L, 2);
		if (!strcmp(idx, "append"))
			lua_pushcfunction(L, luacef_StringList_append);
		else if (!strcmp(idx, "clear"))
			lua_pushcfunction(L, luacef_StringList_clear);
		else if (!strcmp(idx, "free"))
			lua_pushcfunction(L, luacef_StringList_free);
		else if (!strcmp(idx, "size"))
			lua_pushcfunction(L, luacef_StringList_len);
		else if (!strcmp(idx, "print"))
			lua_pushcfunction(L, luacef_StringList_print);

		else return 0;
	}

	return 1;
}

int luacef_StringList_len(lua_State *L)
{
	cef_string_list_t sl = luacef_toudata(L, 1);
	int sz = cef_string_list_size(sl);

	lua_pushinteger(L, sz);
	return 1;
}

int luacef_StringList_unm(lua_State *L)
{
	cef_string_list_t sl = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, sl);
	return 1;
}

int luacef_StringList_print(lua_State *L)
{
	void **p = lua_touserdata(L, 1);
	cef_string_list_t sl = *p;
	int sz = cef_string_list_size(sl);

	cef_string_t s = { 0 };
	cef_string_utf8_t s2 = { 0 };
	
	printf("%s: %08x {", __string_list__, p);
	for (size_t i = 0; i < sz; i++) {
		cef_string_list_value(sl, i, &s);
		cef_string_to_utf8(s.str, s.length, &s2);
		if (i != sz - 1)
			printf(" %s,", s2.str);
		else
			printf(" %s ", s2.str);
	}
			
	printf("}\n");

	fflush(stdout);
	return 0;
}

// ==================================================

static const luaL_Reg luacef_StringList_meta[] = {
	{ "__index", luacef_StringList_index },
	{ "__call", luacef_StringList_append },
	{ "__len", luacef_StringList_len },
	{ "__unm", luacef_StringList_unm },
	{ NULL, NULL }
};

void luacef_StringList_reg(lua_State *L)
{
	luaL_newmetatable(L, __string_list__);
	luaL_setfuncs(L, luacef_StringList_meta, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_StringList_new);
	lua_setfield(L, -2, "newStringList");
}