#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_download_item_capi.h"

// before_download_callback ===================================

/*
	<void>	BeforeDownloadCallback:Cont(
		<str>	download_path,
		<int>	show_dialog
	)
*/
static int luacef_before_download_callback_cont(lua_State *L)
{
	cef_before_download_callback_t *p = luacef_touserdata(L, 1);
	cef_string_t s = luacef_tostring(L, 2);
	int i = lua_tointeger(L, 3);

	p->cont(p, &s, i);

	return 0;
}

static const luaL_Reg luacef_before_download_callback_m[] = {
	{ "Cont", luacef_before_download_callback_cont },
	{ NULL, NULL }
};

// download_item_callback ===========================================

/*
	<void>	DownloadItemCallback:Cancel()
*/
static int luacef_download_item_callback_cancel(lua_State *L)
{
	cef_download_item_callback_t *p = luacef_touserdata(L, 1);

	p->cancel(p);

	return 0;
}

/*
	<void>	DownloadItemCallback:Pause()
*/
static int luacef_download_item_callback_pause(lua_State *L)
{
	cef_download_item_callback_t *p = luacef_touserdata(L, 1);

	p->pause(p);

	return 0;
}

/*
	<void>	DownloadItemCallback:Resume()
*/
static int luacef_download_item_callback_resume(lua_State *L)
{
	cef_download_item_callback_t *p = luacef_touserdata(L, 1);

	p->resume(p);

	return 0;
}

static const luaL_Reg luacef_download_item_callback_m[] = {
	{ "Cancel", luacef_download_item_callback_cancel },
	{ "Pause", luacef_download_item_callback_pause },
	{ "Resume", luacef_download_item_callback_resume },
	{ NULL, NULL }
};

// download_handler =================================

typedef struct luacef_download_handler {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_before_download)(
		struct luacef_download_handler* self,
		struct _cef_browser_t* browser,
		struct _cef_download_item_t* download_item,
		const cef_string_t* suggested_name,
		struct _cef_before_download_callback_t* callback);

	void(CEF_CALLBACK* on_download_updated)(
		struct luacef_download_handler* self,
		struct _cef_browser_t* browser,
		struct _cef_download_item_t* download_item,
		struct _cef_download_item_callback_t* callback);

	lua_State *L;
	int ref;

} luacef_download_handler;

/*
	<void>	DownloadHandler:OnBeforeDownload(
		<Browser>		browser,
		<DownloadItem>	download_item,
		<str>			suggested_name,
		<BeforeDownloadCallback>	callback
	)
*/
void CEF_CALLBACK dh_on_before_download(
	struct luacef_download_handler* self,
	struct _cef_browser_t* browser,
	struct _cef_download_item_t* download_item,
	const cef_string_t* suggested_name,
	struct _cef_before_download_callback_t* callback)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_before_download)) {
		
		luacef_pushuserdata(self->L, self, __download_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);

		luacef_pushuserdata(self->L, download_item, __download_item__);

		luacef_pushstring(self->L, suggested_name);

		luacef_pushuserdata(self->L, callback, __before_download_callback__);
		
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
void CEF_CALLBACK dh_on_download_updated(
	struct luacef_download_handler* self,
	struct _cef_browser_t* browser,
	struct _cef_download_item_t* download_item,
	struct _cef_download_item_callback_t* callback)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __on_before_download)) {

		luacef_pushuserdata(self->L, self, __download_handler__);

		luacef_pushuserdata(self->L, browser, __browser__);

		luacef_pushuserdata(self->L, download_item, __download_item__);

		luacef_pushuserdata(self->L, callback, __download_item_callback__);

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
static luacef_download_handler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_download_handler);
	luacef_download_handler *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __on_before_download))
			p->on_before_download = dh_on_before_download;

		if (lua_getfield(L, 1, __on_download_updated))
			p->on_download_updated = dh_on_download_updated;

	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __download_handler__);
	return 1;
}

static int luacef_download_handler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_download_handler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_download_handler_index(lua_State* L)
{
	luacef_download_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_download_handler_release);

	else if (!strcmp(i, __on_before_download))
		lua_getfield(L, -1, __on_before_download);

	else if (!strcmp(i, __on_download_updated))
		lua_getfield(L, -1, __on_download_updated);

	else return 0;

	return 1;
}

static int luacef_download_handler_newindex(lua_State* L)
{
	luacef_download_handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __on_before_download)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_before_download);
		p->on_before_download = dh_on_before_download;
	}

	else if (!strcmp(i, __on_download_updated)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __on_download_updated);
		p->on_download_updated = dh_on_download_updated;
	}

	return 0;
}

static const luaL_Reg luacef_download_handler_m[] = {
	{ "__index", luacef_download_handler_index },
	{ "__newindex", luacef_download_handler_newindex },
	{ NULL, NULL }
};

// =================================================

void luacef_download_handler_reg(lua_State *L)
{
	luaL_newmetatable(L, __download_handler__);
	luaL_setfuncs(L, luacef_download_handler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_download_handler_new);
	lua_setfield(L, -2, "newDownloadHandler");

	luaL_newmetatable(L, __before_download_callback__);
	luaL_setfuncs(L, luacef_before_download_callback_m, 0);
	lua_setfield(L, -1, __index__);

	luaL_newmetatable(L, __download_item_callback__);
	luaL_setfuncs(L, luacef_download_item_callback_m, 0);
	lua_setfield(L, -1, __index__);

}