#include "../luacef.h"

struct _cef_cookie_visitor_t;
struct _cef_delete_cookies_callback_t;
struct _cef_set_cookie_callback_t;

void(CEF_CALLBACK* set_supported_schemes)(
	struct _cef_cookie_manager_t* self,
	cef_string_list_t schemes,
	struct _cef_completion_callback_t* callback);
/*
	<void> CookieManager:SetSupportedSchemes(
		<>
	)
*/
static int luacef_CookieManager_SetSupportedSchemes(lua_State *L)
{
	// todo
	return 0;
}

/*
	<bool> CookieManager:VisitAllCookies(
		<CookieVisitor> visitor
	)
*/
static int luacef_CookieManager_VisitAllCookies(lua_State *L)
{
	cef_cookie_manager_t *p = luacef_touserdata(L, 1);
	cef_cookie_visitor_t *visitor = luacef_checkudata(L, 2, __cookie_visitor__);

	int r = p->visit_all_cookies(
		p,
		visitor
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> CookieManager:VisitUrlCookies(
		<str> url,
		<bool> includeHttpOnly,
		<CookieVisitor> isitor
	)
*/
static int luacef_CookieManager_VisitUrlCookies(lua_State *L)
{
	cef_cookie_manager_t *p = luacef_touserdata(L, 1);
	cef_string_t url = luacef_tostring(L, 2);
	int includeHttpOnly = lua_tointeger(L, 3);
	cef_cookie_visitor_t *visitor = luacef_checkudata(L, 4, __cookie_visitor__);

	int r = p->visit_url_cookies(
		p,
		&url,
		includeHttpOnly,
		visitor
	);

	lua_pushboolean(L, r);
	return 1;
}

static int luacef_CookieManager_SetCookie(lua_State *L)
{
	cef_cookie_manager_t *p = luacef_touserdata(L, 1);
	cef_string_t url = luacef_tostring(L, 2);
	cef_cookie_t *cookie = luacef_checkudata(L, 3, __cookie__);
	cef_delete_cookies_callback_t *cb = luacef_checkudata(L, 4, __set_cookies_callback__);

	int r = p->set_cookie(
		p,
		&url,
		cookie,
		cb
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> CookieManager:DeleteCookies(
		<str> url,
		<str> cookie_name,
		<DeleteCookiesCallback> callback
	)
*/
static int luac_CookieManager_DeleteCookies(lua_State *L)
{
	cef_cookie_manager_t *p = luacef_touserdata(L, 1);
	cef_string_t url = luacef_tostring(L, 2);
	cef_string_t cookie_name = luacef_tostring(L, 3);
	cef_delete_cookies_callback_t *cb = luacef_checkudata(L, 4, __delete_cookies_callback__);

	int r = p->delete_cookies(
		p,
		&url,
		&cookie_name,
		cb
	);
	
	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> CookieManager:SetStoragePath(
		<str> path,
		<bool> persist_session_cookies,
		<CompletionCallback> callback
	)
*/
static int luacef_CookieManager_SetStoragePath(lua_State *L)
{
	cef_cookie_manager_t *p = luacef_touserdata(L, 1);
	cef_string_t s = luacef_tostring(L, 2);
	int b = lua_tointeger(L, 3);
	cef_completion_callback_t *cb = luacef_checkudata(L, 4, __completion_callback__);

	int r = p->set_storage_path(
		p,
		&s,
		b,
		cb
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> CookieManager:FlushStore(
		<CompletionCallback> callback
	)
*/
static int luacef_CookieManager_FlushStore(lua_State *L)
{
	cef_cookie_manager_t *p = luacef_touserdata(L, 1);
	cef_completion_callback_t *cb = luacef_checkudata(L, 2, __completion_callback__);

	int r = p->flush_store(p, cb);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<CookieManager> CookieManager.GetGlobalManager(
		<CompletionCallbak>	callback
	)
*/
static int luacef_CookieManager_GetGlobalManager(lua_State *L)
{
	cef_completion_callback_t *p = luacef_checkudata(L, 1, __completion_callback__);

	cef_cookie_manager_t* p2 = cef_cookie_manager_get_global_manager(p);

	luacef_pushuserdata(L, p2, __cookie_manager__);
	return 1;
}

/*
	<CookieManager> CookieManager.CreateManager(
		<str>	path,
		<bool>	persist_session_cookies,
		<CompletionCallback>	callback
	)
*/
static int luacef_CookieManager_CreateManager(lua_State *L)
{
	cef_string_t path = luacef_tostring(L, 1);
	int persist_session_cookies = lua_tointeger(L, 2);
	cef_completion_callback_t * callback = luacef_checkudata(L, 3, __completion_callback__);

	cef_cookie_manager_t* r = cef_cookie_manager_create_manager(
		&path,
		persist_session_cookies,
		callback
	);

	luacef_pushuserdata(L, r, __cookie_manager__);
	return 1;
}

typedef struct luacef_cookie_visitor {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* visit)(struct luacef_cookie_visitor* self,
		const struct _cef_cookie_t* cookie,
		int count,
		int total,
		int* deleteCookie);

} luacef_cookie_visitor;

//static luacef_
//#include "include/cef_cookie.h"

// callback =====================================

typedef struct luacef_set_cookie_callback {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_complete)(struct luacef_set_cookie_callback_t* self,
		int success);

	lua_State *L;
	int ref;

} luacef_set_cookie_callback;


// cef_delete_cookies_callback_t

typedef struct luacef_delete_cookies_callback {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_complete)(
		struct luacef_delete_cookies_callback_t*	self,
		int											num_deleted);

} luacef_delete_cookies_callback;

static int luacef_delete_cookies_callback_new(lua_State* L)
{
	size_t sz = sizeof(luacef_delete_cookies_callback);
	luacef_delete_cookies_callback *p = luacef_alloc(sz);
	p->base.size = sz;

	if (lua_istable(L, 1)) {

	}
	else {
		lua_newtable(L);
	}

	luacef_pushuserdata(L, p, __delete_cookies_callback__);
	return 1;
}

static int luacef_delete_cookies_callback_release(lua_State *L)
{

	return 0;
}

static int luacef_delete_cookies_callback_index(lua_State *L)
{

	return 0;
}

static int luacef_delete_cookies_callback_newindex(lua_State *L)
{

	return 0;
}

static const luaL_Reg luacef_delete_cookies_callback_m[] = {
	//{ "__gc", luacef_delete_cookies_callback_release },
	{ "__index", luacef_delete_cookies_callback_index },
	{ "__newindex", luacef_delete_cookies_callback_newindex },
	{ NULL, NULL}
};