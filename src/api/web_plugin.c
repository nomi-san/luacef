#include "../luacef.h"
#include "include/capi/cef_base_capi.h"

/*
	<str> WebPluginInfo:GetName()
*/
static int luacef_web_plugin_info_get_name(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_t *s = p->get_name(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<str> WebPluginInfo:GetPath()
*/
static int luacef_web_plugin_info_get_path(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_t *s = p->get_path(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<str> WebPluginInfo:GetVersion()
*/
static int luacef_web_plugin_info_get_version(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_t *s = p->get_version(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<str> WebPluginInfo:GetDescription()
*/
static int luacef_web_plugin_info_get_description(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_t *s = p->get_description(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

cef_string_userfree_t(CEF_CALLBACK* get_name)(
	struct _cef_web_plugin_info_t* self);
cef_string_userfree_t(CEF_CALLBACK* get_path)(
	struct _cef_web_plugin_info_t* self);
cef_string_userfree_t(CEF_CALLBACK* get_version)(
	struct _cef_web_plugin_info_t* self);
cef_string_userfree_t(CEF_CALLBACK* get_description)(
	struct _cef_web_plugin_info_t* self);

/////////////////////////////////////////////////////////

/*
	<int> WebPluginInfoVisitor:Visit(
		<WebPluginInfo>	info,
		<int>			count,
		<int>			total
	)
*/
static int luacef_web_plugin_info_visitor_visit(lua_State* L)
{
	cef_web_plugin_info_visitor_t *p = lua_touserdata(L, 1);
	cef_web_plugin_info_t *p2 = luacef_checkudata(L, 2, __web_plugin_info__);
	int c = lua_tointeger(L, 3);
	int t = lua_tointeger(L, 4);

	int r = p->visit(p, p2, c, t);

	lua_pushinteger(L, r);
	return 1;
}

int (CEF_CALLBACK* visit)(struct _cef_web_plugin_info_visitor_t* self,
	struct _cef_web_plugin_info_t* info,
	int count,
	int total);

/////////////////////////////////////////////////////////////////

void(CEF_CALLBACK* is_unstable)(
	struct _cef_web_plugin_unstable_callback_t* self,
	const cef_string_t* path,
	int unstable);

static int luacef_web_plugin_unstable_callback_is_unstable(lua_State* L)
{
	cef_web_plugin_info_visitor_t *p = lua_touserdata(L, 1);

	// todo
	
	return 1;
}

//////////////////////////////////////////////////////////////////
// CDM
void(CEF_CALLBACK* on_cdm_registration_complete)(
	struct _cef_register_cdm_callback_t* self,
	cef_cdm_registration_error_t result,
	const cef_string_t* error_message);

static luacef_register_cdm_callback_new(lua_State* L)
{
	size_t sz = sizeof(cef_register_cdm_callback_t);
	cef_register_cdm_callback_t *p = luacef_alloc(sz);



	luacef_pushuserdata(L, p, __register_cdm_callback__);
	return 1;
}
