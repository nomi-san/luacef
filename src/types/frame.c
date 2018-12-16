#include "../luacef.h"
#include "include/capi/cef_frame_capi.h"

#define SELF luacef_Frame

typedef cef_frame_t SELF;

#define API(fn) \
	LCEF_API(Frame, fn)

#define API_N(fn) \
	LCEF_API_N(Frame, fn)

#define API_M(mname) \
	LCEF_M(Frame, mname)

/*
	<void> Frame:Copy()
*/
API(Copy)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->copy(f);

	return 0;
}

/*
	<void> Frame:Cut()
*/
API(Cut)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->cut(f);

	return 0;
}

/*
	<void> Frame:Delete()
*/
API(Delete)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->del(f);

	return 0;
}

/*
	<void> Frame:ExecuteJavaScript(
		<str>	code,
		<str>	url,
		<int>	start_line
	)
*/
API(ExecuteJavaScript)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	const cef_string_t code = luacef_tostring(L, 2);
	const cef_string_t url = luacef_tostring(L, 3);
	int start_line = lua_tointeger(L, 4);

	f->execute_java_script(f, &code, &url, start_line);

	return 0;
}

/*
	<Browser> Frame:GetBrowser()
*/
API(GetBrowser)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_browser_t *b = f->get_browser(f);

	luacef_pushuserdata(L, b, __CefBrowser);
	return 1;
}

/*
	<int> Frame:GetIdentifier()
*/
API(GetIdentifier)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushinteger(L, f->get_identifier(f));
	return 1;
}

/*
	<str> Frame:GetName()
*/
API(GetName)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_string_t *name = f->get_name(f);

	lua_pushwstring(L, name->str);
	return 1;
}

/*
	<Frame> Frame:GetParent()
*/
API(GetParent)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_frame_t *fp = f->get_parent(f);

	luacef_pushuserdata(L, fp, __CefFrame);
	return 1;
}

/*
	<void> Frame:GetSource(
		<StringVisitor> visitor
	)
*/
API(GetSource)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_string_visitor_t *v = luacef_checkudata(L, 2, __CefStringVisitor);

	f->get_source(f, v);

	return 0;
}

/*
	<void> Frame:GetText(
		<StringVisitor> visitor
	)
*/
API(GetText)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_string_visitor_t *v = luacef_checkudata(L, 2, __CefStringVisitor);

	f->get_text(f, v);

	return 0;
}

/*
	<str> Frame:GetURL()
*/
API(GetURL)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_string_utf16_t* url =  f->get_url(f);

	lua_pushwstring(L, url->str);
	return 1;
}

/*
	<V8Context> Frame:GetV8Context()
*/
API(GetV8Context)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_v8context_t *v8 = f->get_v8context(f);

	luacef_pushuserdata(L, v8, __v8context__);
	return 1;
}

/*
	<bool> Frame:IsFocused()
*/
API(IsFocused)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushboolean(L, f->is_focused(f));
	return 1;
}

/*
	<bool> Frame:IsMain()
*/
API(IsMain)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushboolean(L, f->is_main(f));
	return 1;
}

/*
	<bool> Frame:IsValid()
*/
API(IsValid)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushboolean(L, f->is_valid(f));
	return 1;
}

/*
	<void> Frame:LoadRequest(
		<Request> request
	)
*/
API(LoadRequest)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_request_t *r = luacef_checkudata(L, 2, __CefRequest);

	f->load_request(f, r);
	return 0;
}

/*
	<void> Frame:LoadString(
		<str> string_val,
		<str> url
	)
*/
API(LoadString)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	const char* cs_val = lua_tostring(L, 2);
	const char* cs_url = lua_tostring(L, 3);

	cef_string_t val = { 0 }, url = { 0 };
	cef_string_from_utf8(cs_val, strlen(cs_val), &val);
	cef_string_from_utf8(cs_url, strlen(cs_url), &url);
	f->load_string(f, &val, &url);

	return 0;
}

/*
	<void> Frame:LoadURL(
		<str> url
	)
*/
API(LoadURL)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	const char* cs = lua_tostring(L, 2);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	f->load_url(f, &s);

	return 0;
}

/*
	<void> Frame:Paste()
*/
API(Paste)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->paste(f);
	return 0;
}

/*
	<void> Frame:Redo()
*/
API(Redo)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->redo(f);
	return 0;
}

/*
	<void> Frame:SelectAll()
*/
API(SelectAll)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->select_all(f);
	return 0;
}

/*
	<void> Frame:Undo()
*/
API(Undo)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->undo(f);
	return 0;
}

/*
	<void> Frame:ViewSource()
*/
API(ViewSource)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->view_source(f);

	return 0;
}

/*
	<void> Frame:VisitDOM(
		<DOMVisitor> visitor
	)
*/
API(VisitDOM)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_domvisitor_t *dv = luacef_checkudata(L, 2, __CefDOMVisitor);

	f->visit_dom(f, dv);

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

// meta =========================

API_M(meta)
{
	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },

	{ "Copy",				API_N(Copy) },
	{ "Cut",				API_N(Cut) },
	{ "Delete",				API_N(Delete) },
	{ "ExecuteJavaScript",	API_N(ExecuteJavaScript) },
	{ "GetBrowser",			API_N(GetBrowser) },
	{ "GetIdentifier",		API_N(GetIdentifier) },
	{ "GetName",			API_N(GetName) },
	{ "GetParent",			API_N(GetParent) },
	{ "GetSource",			API_N(GetSource) },
	{ "GetText",			API_N(GetText) },
	{ "GetURL",				API_N(GetURL) },
	{ "GetV8Context",		API_N(GetV8Context) },
	{ "IsFocused",			API_N(IsFocused) },
	{ "IsMain",				API_N(IsMain) },
	{ "IsValid",			API_N(IsValid) },
	{ "LoadRequest",		API_N(LoadRequest) },
	{ "LoadString",			API_N(LoadString) },
	{ "LoadURL",			API_N(LoadURL) },
	{ "Paste",				API_N(Paste) },
	{ "Redo",				API_N(Redo) },
	{ "SelectAll",			API_N(SelectAll) },
	{ "Undo",				API_N(Undo) },
	{ "ViewSource",			API_N(ViewSource) },
	{ "VisitDOM",			API_N(VisitDOM) },
	{ NULL, NULL }
};

void API_N(reg)(lua_State* L)
{
	luaL_newmetatable(L, __CefFrame);
	luaL_setfuncs(L, API_N(meta), 0);
	lua_setfield(L, -1, __index__);
}