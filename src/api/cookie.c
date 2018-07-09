#include "../luacef.h"

struct _cef_cookie_visitor_t;
struct _cef_delete_cookies_callback_t;
struct _cef_set_cookie_callback_t;

typedef struct luacef_cookie_manager {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Set the schemes supported by this manager. The default schemes ("http",
	// "https", "ws" and "wss") will always be supported. If |callback| is non-
	// NULL it will be executed asnychronously on the IO thread after the change
	// has been applied. Must be called before any cookies are accessed.
	///
	void(CEF_CALLBACK* set_supported_schemes)(
		struct _cef_cookie_manager_t* self,
		cef_string_list_t schemes,
		struct _cef_completion_callback_t* callback);

	///
	// Visit all cookies on the IO thread. The returned cookies are ordered by
	// longest path, then by earliest creation date. Returns false (0) if cookies
	// cannot be accessed.
	///
	int(CEF_CALLBACK* visit_all_cookies)(struct _cef_cookie_manager_t* self,
		struct _cef_cookie_visitor_t* visitor);

	///
	// Visit a subset of cookies on the IO thread. The results are filtered by the
	// given url scheme, host, domain and path. If |includeHttpOnly| is true (1)
	// HTTP-only cookies will also be included in the results. The returned
	// cookies are ordered by longest path, then by earliest creation date.
	// Returns false (0) if cookies cannot be accessed.
	///
	int(CEF_CALLBACK* visit_url_cookies)(struct _cef_cookie_manager_t* self,
		const cef_string_t* url,
		int includeHttpOnly,
		struct _cef_cookie_visitor_t* visitor);

	///
	// Sets a cookie given a valid URL and explicit user-provided cookie
	// attributes. This function expects each attribute to be well-formed. It will
	// check for disallowed characters (e.g. the ';' character is disallowed
	// within the cookie value attribute) and fail without setting the cookie if
	// such characters are found. If |callback| is non-NULL it will be executed
	// asnychronously on the IO thread after the cookie has been set. Returns
	// false (0) if an invalid URL is specified or if cookies cannot be accessed.
	///
	int(CEF_CALLBACK* set_cookie)(struct _cef_cookie_manager_t* self,
		const cef_string_t* url,
		const struct _cef_cookie_t* cookie,
		struct _cef_set_cookie_callback_t* callback);

	///
	// Delete all cookies that match the specified parameters. If both |url| and
	// |cookie_name| values are specified all host and domain cookies matching
	// both will be deleted. If only |url| is specified all host cookies (but not
	// domain cookies) irrespective of path will be deleted. If |url| is NULL all
	// cookies for all hosts and domains will be deleted. If |callback| is non-
	// NULL it will be executed asnychronously on the IO thread after the cookies
	// have been deleted. Returns false (0) if a non-NULL invalid URL is specified
	// or if cookies cannot be accessed. Cookies can alternately be deleted using
	// the Visit*Cookies() functions.
	///
	int(CEF_CALLBACK* delete_cookies)(
		struct _cef_cookie_manager_t* self,
		const cef_string_t* url,
		const cef_string_t* cookie_name,
		struct _cef_delete_cookies_callback_t* callback);

	///
	// Sets the directory path that will be used for storing cookie data. If
	// |path| is NULL data will be stored in memory only. Otherwise, data will be
	// stored at the specified |path|. To persist session cookies (cookies without
	// an expiry date or validity interval) set |persist_session_cookies| to true
	// (1). Session cookies are generally intended to be transient and most Web
	// browsers do not persist them. If |callback| is non-NULL it will be executed
	// asnychronously on the IO thread after the manager's storage has been
	// initialized. Returns false (0) if cookies cannot be accessed.
	///
	int(CEF_CALLBACK* set_storage_path)(
		struct _cef_cookie_manager_t* self,
		const cef_string_t* path,
		int persist_session_cookies,
		struct _cef_completion_callback_t* callback);

	///
	// Flush the backing store (if any) to disk. If |callback| is non-NULL it will
	// be executed asnychronously on the IO thread after the flush is complete.
	// Returns false (0) if cookies cannot be accessed.
	///
	int(CEF_CALLBACK* flush_store)(struct _cef_cookie_manager_t* self,
		struct _cef_completion_callback_t* callback);
} luacef_cookie_manager;


/*
	<CookieManager> CookieManager.GetGlobal(
		<CompletionCallbak>	callback
	)
*/
static int luacef_cookie_manager_get_global_manager(lua_State *L)
{
	cef_completion_callback_t *p = luacef_checkudata(L, 1, __completion_callback__);

	cef_cookie_manager_t* p2 = cef_cookie_manager_get_global_manager(p);

	luacef_pushuserdata(L, p2, __cookie_manager__);
	return 1;
}

/*
	<CookieManager> CookieManager.CreateManager(
		<str>	path,
		<int>	persist_session_cookies,
		<CompletionCallback>	callback
	)
*/
static int luacef_cookie_manager_create_manager(lua_State *L)
{
	const char *cs = lua_tostring(L, 1);
	int i = lua_tointeger(L, 2);
	cef_completion_callback_t * p = luacef_checkudata(L, 3, __completion_callback__);


	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	cef_cookie_manager_t* p2 = cef_cookie_manager_create_manager(&s, i, p);

	luacef_pushuserdata(L, p2, __cookie_manager__);
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

typedef struct luacef_set_cookie_callback {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_complete)(struct luacef_set_cookie_callback_t* self,
		int success);

} luacef_set_cookie_callback;


// cef_delete_cookies_callback_t

typedef struct luacef_delete_cookies_callback {

	cef_base_ref_counted_t base;

	void(CEF_CALLBACK* on_complete)(
		struct luacef_delete_cookies_callback_t*	self,
		int											num_deleted);

} luacef_delete_cookies_callback;

void luacef_delete_cookies_callback_test()
{
	cef_delete_cookies_callback_t *p;
	p->base;
	p->on_complete;
}

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

}

static int luacef_delete_cookies_callback_index(lua_State *L)
{

}

static int luacef_delete_cookies_callback_newindex(lua_State *L)
{

	return 0;
}

static const luaL_Reg luacef_delete_cookies_callback_m[] = {
	{ "__gc", luacef_delete_cookies_callback_release },
	{ "__index", luacef_delete_cookies_callback_index },
	{ "__newindex", luacef_delete_cookies_callback_newindex },
	{ NULL, NULL}
};