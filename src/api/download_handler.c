#include "../luacef.h"
#include "include/capi/cef_download_handler_capi.h"

// BeforeDownloadCallback
// =========================

#define SELF luacef_BeforeDownloadCallback

typedef cef_before_download_callback_t SELF;

#define API(fn) \
	LCEF_API(BeforeDownloadCallback, fn)

#define API_N(fn) \
	LCEF_API_N(BeforeDownloadCallback, fn)

#define API_M(mname) \
	LCEF_M(BeforeDownloadCallback, mname)

/*
	<void>	BeforeDownloadCallback:Continue(
		<str>	download_path,
		<int>	show_dialog
	)
*/
API(Continue)
{
	cef_before_download_callback_t *p = luacef_touserdata(L, 1);
	cef_string_t s = luacef_tostring(L, 2);
	int i = lua_tointeger(L, 3);

	p->cont(p, &s, i);

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

API_M(meta)
{
	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },
	{ "Continue", API_N(Continue) },
	{ NULL, NULL }
};

#undef SELF
#undef API
#undef API_N
#undef API_M

// DownloadItemCallback
// =========================

#define SELF luacef_DownloadItemCallback

typedef cef_download_item_callback_t SELF;

#define API(fn) \
	LCEF_API(DownloadItemCallback, fn)

#define API_N(fn) \
	LCEF_API_N(DownloadItemCallback, fn)

#define API_M(mname) \
	LCEF_M(DownloadItemCallback, mname)

/*
	<void>	DownloadItemCallback:Cancel()
*/
API(Cancel)
{
	cef_download_item_callback_t *p = luacef_touserdata(L, 1);

	p->cancel(p);

	return 0;
}

/*
	<void>	DownloadItemCallback:Pause()
*/
API(Pause)
{
	cef_download_item_callback_t *p = luacef_touserdata(L, 1);

	p->pause(p);

	return 0;
}

/*
	<void>	DownloadItemCallback:Resume()
*/
API(Resume)
{
	cef_download_item_callback_t *p = luacef_touserdata(L, 1);

	p->resume(p);

	return 0;
}

API_M(meta)
{
	{ "Cancel", API_N(Cancel) },
	{ "Pause", API_N(Pause) },
	{ "Resume", API_N(Resume) },
	{ NULL, NULL }
};

#undef SELF
#undef API
#undef API_N
#undef API_M

// DownloadHandler
// =================================

#define SELF luacef_DownloadHandler

typedef struct SELF {

	cef_download_handler_t self;

	lua_State *L; // state
	int ref; // table ref

} SELF;

#define API(fn) \
	LCEF_API(DownloadHandler, fn)

#define API_N(fn) \
	LCEF_API_N(DownloadHandler, fn)

#define API_M(mname) \
	LCEF_M(DownloadHandler, mname)

/*
	<void>	DownloadHandler:OnBeforeDownload(
		<Browser>		browser,
		<DownloadItem>	download_item,
		<str>			suggested_name,
		<BeforeDownloadCallback>	callback
	)
*/
void CEF_CALLBACK API_N(OnBeforeDownload)(
	SELF* self,
	struct _cef_browser_t* browser,
	struct _cef_download_item_t* download_item,
	const cef_string_t* suggested_name,
	struct _cef_before_download_callback_t* callback)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeDownload)) {
		
		luacef_pushuserdata(self->L, self, __DownloadHandler__);

		luacef_pushuserdata(self->L, browser, __CefBrowser);

		luacef_pushuserdata(self->L, download_item, __CefDownloadItem);

		luacef_pushstring(self->L, suggested_name);

		luacef_pushuserdata(self->L, callback, __BeforeDownloadCallback);
		
		lua_pcall(self->L, 5, 0, 8);
	}
}

/*
	<void>	DownloadHandler:OnDownloadUpdated(
		<Browser>		browser,
		<DownloadItem>	download_item,
		<DownloadItemCallback>	callback
	)
*/
void CEF_CALLBACK API_N(OnDownloadUpdated)(
	SELF* self,
	struct _cef_browser_t* browser,
	struct _cef_download_item_t* download_item,
	struct _cef_download_item_callback_t* callback)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnBeforeDownload)) {

		luacef_pushuserdata(self->L, self, __DownloadHandler__);

		luacef_pushuserdata(self->L, browser, __CefBrowser);

		luacef_pushuserdata(self->L, download_item, __CefDownloadItem);

		luacef_pushuserdata(self->L, callback, __DownloadItemCallback);

		lua_pcall(self->L, 4, 0, 8);
	}
}

/*
	<DownloadHandler> newDownloadHandler
	{
		<void>
			DownloadHandler:OnDownloadUpdated(self, <Browser>, <DownloadItem>, <DownloadItemCallback>);
		<void>
			DownloadHandler:OnBeforeDownload(self, <Browser>, <DownloadItem>, <str>, <BeforeDownloadCallback>);
	}
*/
API(new)
{
	size_t sz = sizeof(SELF);
	SELF *p = luacef_alloc(sz);
	p->self.base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __OnBeforeDownload))
			p->self.on_before_download = (void*)API_N(OnBeforeDownload);

		if (lua_getfield(L, 1, __OnDownloadUpdated))
			p->self.on_download_updated = (void*)API_N(OnDownloadUpdated);

	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __DownloadHandler__);
	return 1;
}

API(index)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __OnBeforeDownload))
		lua_getfield(L, -1, __OnBeforeDownload);

	else if (!strcmp(i, __OnDownloadUpdated))
		lua_getfield(L, -1, __OnDownloadUpdated);

	else return 0;

	return 1;
}

API(newindex)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnBeforeDownload)) {
		lua_setfield(L, -2, __OnBeforeDownload);
		p->self.on_before_download = (void*)API_N(OnBeforeDownload);
	}

	else if (!strcmp(i, __OnDownloadUpdated)) {
		lua_setfield(L, -2, __OnDownloadUpdated);
		p->self.on_download_updated = (void*)API_N(OnDownloadUpdated);
	}

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

API_M(meta)
{
	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },
	{ "__index", API_N(index) },
	{ "__newindex", API_N(newindex) },
	
	LUAREGEND
};

// =================================================

void API_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, __DownloadHandler__);
	luaL_setfuncs(L, API_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, API_N(new));
	lua_setfield(L, -2, "newDownloadHandler");

	luaL_newmetatable(L, __BeforeDownloadCallback);
	luaL_setfuncs(L, LCEF_API_N(BeforeDownloadCallback, meta), 0);
	lua_setfield(L, -1, __index__);

	luaL_newmetatable(L, __DownloadItemCallback);
	luaL_setfuncs(L, LCEF_API_N(DownloadItemCallback, meta), 0);
	lua_setfield(L, -1, __index__);
}