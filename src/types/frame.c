#include "../luacef.h"

static int luacef_frame_new(lua_State* L)
{
	size_t sz = sizeof(cef_frame_t);
	cef_frame_t *f = calloc(1, sz);
	f->base.size = sz;

	/*
	f->copy;
	f->cut;
	f->del;
	f->execute_java_script;
	f->get_browser;
	f->get_identifier;
	f->get_name;
	f->get_parent;
	f->get_source;
	f->get_text;
	f->get_url;
	f->get_v8context;
	f->is_focused;
	f->is_main;
	f->is_valid;
	f->load_request;
	f->load_string;
	f->load_url;
	f->paste;
	f->redo;
	f->select_all;
	f->undo;
	f->view_source;
	f->visit_dom;
	*/

	luacef_pushuserdata(L, f, __frame__);
	return 1;
}

/*
	<void> Frame:Copy()
*/
static int luacef_frame_copy(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->copy(f);

	return 0;
}

/*
	<void> Frame:Cut()
*/
static int luacef_frame_cut(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->cut(f);

	return 0;
}

/*
	<void> Frame:Delete()
*/
static int luacef_frame_del(lua_State* L)
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
static int luacef_frame_execute_java_script(lua_State* L)
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
static int luacef_frame_get_browser(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_browser_t *b = f->get_browser(f);

	luacef_pushuserdata(L, b, __browser__);
	return 1;
}

/*
	<int> Frame:GetIdentifier()
*/
static int luacef_frame_get_identifier(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushinteger(L, f->get_identifier(f));
	return 1;
}

/*
	<str> Frame:GetName()
*/
static int luacef_frame_get_name(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_string_t *name = f->get_name(f);

	lua_pushwstring(L, name->str);
	return 1;
}

/*
	<Frame> Frame:GetParent()
*/
static int luacef_frame_get_parent(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_frame_t *fp = f->get_parent(f);

	luacef_pushuserdata(L, fp, __frame__);
	return 1;
}

/*
	<void> Frame:GetSource(
		<StringVisitor> visitor
	)
*/
static int luacef_frame_get_source(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_string_visitor_t *v = luacef_checkudata(L, 2, __string_visitor__);

	f->get_source(f, v);

	return 0;
}

/*
	<void> Frame:GetText(
		<StringVisitor> visitor
	)
*/
static int luacef_frame_get_text(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_string_visitor_t *v = luacef_checkudata(L, 2, __string_visitor__);

	f->get_text(f, v);

	return 0;
}

/*
	<str> Frame:GetURL()
*/
static int luacef_frame_get_url(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_string_utf16_t* url =  f->get_url(f);

	lua_pushwstring(L, url->str);
	return 1;
}

/*
	<V8Context> Frame:GetV8context()
*/
static int luacef_frame_get_v8context(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	cef_v8context_t *v8 = f->get_v8context(f);

	luacef_pushuserdata(L, v8, __v8context__);
	return 1;
}

/*
	<bool> Frame:IsFocused()
*/
static int luacef_frame_is_focused(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushboolean(L, f->is_focused(f));
	return 1;
}

/*
	<bool> Frame:IsMain()
*/
static int luacef_frame_is_main(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	lua_pushboolean(L, f->is_main(f));
	return 1;
}

/*
	<bool> Frame:IsValid()
*/
static int luacef_frame_is_valid(lua_State* L)
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
static int luacef_frame_load_request(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_request_t *r = luacef_checkudata(L, 2, __request__);

	f->load_request(f, r);
	return 0;
}

/*
	<void> Frame:LoadString(
		<str> string_val,
		<str> url
	)
*/
static int luacef_frame_load_string(lua_State* L)
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
	<void> Frame:LoadUrl(
		<str> url
	)
*/
static int luacef_frame_load_url(lua_State* L)
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
static int luacef_frame_paste(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->paste(f);
	return 0;
}

/*
	<void> Frame:Redo()
*/
static int luacef_frame_redo(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->redo(f);
	return 0;
}

/*
	<void> Frame:SelectAll()
*/
static int luacef_frame_select_all(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->select_all(f);
	return 0;
}

/*
	<void> Frame:Undo()
*/
static int luacef_frame_undo(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);

	f->undo(f);
	return 0;
}

/*
	<void> Frame:ViewSource()
*/
static int luacef_frame_view_source(lua_State* L)
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
static int luacef_frame_visit_dom(lua_State* L)
{
	cef_frame_t *f = luacef_touserdata(L, 1);
	cef_domvisitor_t *dv = luacef_checkudata(L, 2, __domvisitor__);

	f->visit_dom(f, dv);

	return 0;
}




//=====================

static const luaL_Reg luacef_frame_m[] = {
	{ "Copy", luacef_frame_copy },
	{ "Cut", luacef_frame_cut },
	{ "Delete", luacef_frame_del },
	{ "ExecuteJavaScript", luacef_frame_execute_java_script },
	{ "GetBrowser", luacef_frame_get_browser },
	{ "GetIdentifier", luacef_frame_get_identifier },
	{ "GetName", luacef_frame_get_name },
	{ "GetParent", luacef_frame_get_parent },
	{ "GetSource", luacef_frame_get_source },
	{ "GetText", luacef_frame_get_text },
	{ "GetURL", luacef_frame_get_url },
	{ "GetV8context", luacef_frame_get_v8context },
	{ "IsFocused", luacef_frame_is_focused },
	{ "IsMain", luacef_frame_is_main },
	{ "IsValid", luacef_frame_is_valid },
	{ "LoadRequest", luacef_frame_load_request },
	{ "LoadString", luacef_frame_load_string },
	{ "LoadUrl", luacef_frame_load_url },
	{ "Paste", luacef_frame_paste },
	{ "Redo", luacef_frame_redo },
	{ "SelectAll", luacef_frame_select_all },
	{ "Undo", luacef_frame_undo },
	{ "ViewSource", luacef_frame_view_source },
	{ "VisitDOM", luacef_frame_visit_dom },
	{ NULL, NULL }
};

void luacef_frame_reg(lua_State* L)
{
	luaL_newmetatable(L, __frame__);
	luaL_setfuncs(L, luacef_frame_m, 0);
	lua_setfield(L, -1, __index__);

	//
}