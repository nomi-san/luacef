#include "../luacef.h"

#if defined(WIN32) || (_WIN32)

#define CP_UTF8 65001

// to wchar_t*
const wchar_t *lua_towstring(lua_State *L, int stkidx)
{
	if (lua_isnoneornil(L, stkidx)) return L"";
	const char *s = lua_tostring(L, stkidx);
	int size = MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	wchar_t *ws = (wchar_t *)CoTaskMemAlloc(size * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, s, -1, ws, size);
	return ws;
}

// push wchar_t*
void lua_pushwstring(lua_State *L, wchar_t *ts) {
	int size = WideCharToMultiByte(CP_UTF8, 0, ts, -1, /* s */ 0, /* size */ 0, 0, 0);
	char *s = (char*)calloc(size, sizeof(char));
	WideCharToMultiByte(CP_UTF8, 0, ts, -1, s, size, 0, 0);
	lua_pushstring(L, s);
	free(s);
}

// clear wchar_t*
void lua_clearwstring(wchar_t *ws) {
	CoTaskMemFree(ws);
}

#else

// to wchar_t* via cefstring
const wchar_t *lua_towstring(lua_State *L, int i)
{
	const char *cs = lua_tostring(L, i);
	cef_string_t s = { 0 };
	cef_string_utf8_to_utf16(cs, strlen(cs), &s);
	return s.str;
}

// push wchar_t* via cefstring
void lua_pushwstring(lua_State *L, const wchar_t *wcs)
{
	cef_string_utf8_t s = { 0 };
	cef_string_wide_to_utf8(wcs, wcslen(wcs), &s);

	lua_pushstring(L, s.str);
}

#endif

// to cefstring
cef_string_t luacef_tostring(lua_State *L, int i)
{
	const char *cs = lua_tostring(L, i);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);

	return s;
}

// push cefstring*
void luacef_pushstring(lua_State* L, cef_string_t *s)
{
	cef_string_utf8_t src = { 0 };
	cef_string_utf16_to_utf8(s->str, s->length, &src);
	lua_pushstring(L, src.str);
}

// push cef_string_free
void luacef_pushstring_free(lua_State* L, cef_string_userfree_t s)
{
	cef_string_utf8_t src = { 0 };
	cef_string_utf16_to_utf8(s->str, s->length, &src);
	lua_pushstring(L, src.str);
	cef_string_userfree_free(s);
}