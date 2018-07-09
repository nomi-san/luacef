#pragma once

#define lua_towstring(L, n)	(comgen_towstr(L, n))
#define lua_pushwstring(L, s) (comgen_pushwstr(L, s))

static const wchar_t *comgen_towstr(lua_State *L, int stkidx);
static void comgen_pushwstr(lua_State *L, wchar_t *ts);
static void comgen_clearwstr(wchar_t *ws);
static cef_string_t luacef_string_from_cs(const char* cs);
static cef_string_t luacef_string_from_wcs(const wchar_t* wcs);
static cef_string_t luacef_to_cefstring_from_cs(lua_State* L, int i);
static cef_string_t luacef_to_cefstring_from_wcs(lua_State* L, int i);
static const char* luacef_string_to_cs(cef_string_t s);
static const wchar_t* luacef_string_to_wcs(cef_string_t s);
static void luacef_pushstring(lua_State* L, cef_string_t *s);

static const wchar_t *comgen_towstr(lua_State *L, int stkidx)
{
	if (lua_isnoneornil(L, stkidx)) return L"";
	const char *s = lua_tostring(L, stkidx);
	int size = MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	wchar_t *ws = (wchar_t *)CoTaskMemAlloc(size * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, s, -1, ws, size);
	return ws;
}

static void comgen_pushwstr(lua_State *L, wchar_t *ts) {
	int size = WideCharToMultiByte(CP_UTF8, 0, ts, -1, /* s */ 0, /* size */ 0, 0, 0);
	char *s = calloc(size, sizeof(char));
	WideCharToMultiByte(CP_UTF8, 0, ts, -1, s, size, 0, 0);
	lua_pushstring(L, s);
	free(s);
}

static void comgen_clearwstr(wchar_t *ws) {
	CoTaskMemFree(ws);
}

static cef_string_t luacef_string_from_cs(const char* cs)
{
	cef_string_t s = { 0 };
	cef_string_utf8_to_utf16(cs, strlen(cs), &s);
	return s;
}

static cef_string_t luacef_string_from_wcs(const wchar_t* wcs)
{
	cef_string_t s = { 0 };
	cef_string_wide_to_utf16(wcs, wcslen(wcs), &s);
	return s;
}

static cef_string_t luacef_to_cefstring_from_cs(lua_State* L, int i)
{
	cef_string_t s = { 0 };
	const char* cs = lua_tostring(L, i);
	cef_string_utf8_to_utf16(cs, strlen(cs), &s);

	return s;
}

static cef_string_t luacef_to_cefstring_from_wcs(lua_State* L, int i)
{
	cef_string_t s = { 0 };
	const wchar_t* wcs = comgen_towstr(L, i);
	cef_string_wide_to_utf16(wcs, wcslen(wcs), &s);
	return s;
}

static const char* luacef_string_to_cs(cef_string_t s)
{
	cef_string_utf8_t src = { 0 };
	cef_string_utf16_to_utf8(s.str, s.length, &src);
	return src.str;
}

static const wchar_t* luacef_string_to_wcs(cef_string_t s)
{	
	cef_string_wide_t src = { 0 };
	cef_string_utf16_to_wide(s.str, s.length, &src);
	return src.str;
}

static void luacef_pushstring(lua_State* L, cef_string_t *s)
{
	cef_string_utf8_t src = { 0 };
	cef_string_utf16_to_utf8(s->str, s->length, &src);
	lua_pushstring(L, src.str);
}

static cef_string_t luacef_tostring(lua_State *L, int i)
{
	const char *cs = lua_tostring(L, i);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);

	return s;
}

static const wchar_t *lua_towstring_(lua_State *L, int i)
{
	const char *cs = lua_tostring(L, i);
	cef_string_t s = { 0 };
	cef_string_utf8_to_utf16(cs, strlen(cs), &s);
	return s.str;
}

static void lua_pushwstring_(lua_State *L, const wchar_t *wcs)
{
	cef_string_utf8_t s = { 0 };
	cef_string_wide_to_utf8(wcs, wcslen(wcs), &s);

	lua_pushstring(L, s.str);
}