#include "../luacef.h"

// Request // =====================================

/*
	<bool> Request:IsReadOnly()
*/
static int luacef_request_is_read_only(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_read_only(p));
	return 1;
}

/*
	<str> Request:GetURL()
*/
static int luacef_request_get_url(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_url(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);
	
	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<void> Request:SetURL(
		<str> url
	)
*/
static int luacef_request_set_url(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);
	const char *cs = lua_tostring(L, 2);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	p->set_url(p, &s);
	
	return 0;
}

/*
	<str> Request:GetMethod()
*/
static int luacef_request_get_method(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_method(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<void> Request:SetMethod(
		<str> method
	)
*/
static int luacef_request_set_method(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);
	const char *cs = lua_tostring(L, 2);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	p->set_method(p, &s);
	
	return 0;
}

/*
	<void> Request:SetReferrer(
		<str> referrer_url,
		<int> referrer_policy
	)
*/
static int luacef_request_set_referrer(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);
	const char* cs = lua_tostring(L, 2);
	int po = lua_tointeger(L, 3);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	p->set_referrer(p, &s, po);

	return 0;
}

/*
	<str> Request:GetReferrerURL()
*/
static int luacef_request_get_referrer_url(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_referrer_url(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<int> Request:GetReferrerPolicy()
*/
static int luacef_request_get_referrer_policy(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_referrer_policy(p));
	return 1;
}

/*
	<PostData> Request:GetPostData()
*/
static int luacef_request_get_post_data(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	cef_post_data_t *p2 = p->get_post_data(p);

	luacef_pushuserdata(L, p2, __post_data__);
	return 1;
}

/*
	<void> Request:SetPostData(
		<PostData> postData
	}
*/
static int luacef_request_set_post_data(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);
	cef_post_data_t *p2 = luacef_checkudata(L, 2, __post_data__);

	p->set_post_data(p, p2);

	return 0;
}

//void (CEF_CALLBACK *get_header_map)(struct _cef_request_t* self,
//	cef_string_multimap_t headerMap);
/*
	todo
*/
static int luacef_request_get_header_map(lua_State* L)
{
	return 0;
}

//void (CEF_CALLBACK *set_header_map)(struct _cef_request_t* self,
//	cef_string_multimap_t headerMap);
/*
	todo
*/
static int luacef_request_set_header_map(lua_State* L)
{
	return 0;
}

//void (CEF_CALLBACK *set)(struct _cef_request_t* self, const cef_string_t* url,
//	const cef_string_t* method, struct _cef_post_data_t* postData,
//	cef_string_multimap_t headerMap);
/*
	todo
*/
static int luacef_request_set(lua_State* L)
{

	return 0;
}

/*
	<int> Request:GetFlags()
*/
static int luacef_request_get_flags(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_flags(p));
	return 1;
}

/*
	<void> Request:SetFlags(
		<int>	set_flags
	)
*/
static int luacef_request_set_flags(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);
	int flag = lua_tointeger(L, 2);

	p->set_flags(p, flag);

	return 0;
}

/*
	<str> Request:GetFirstPartyForCookies()
*/
static int luacef_request_get_first_party_for_cookies(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_first_party_for_cookies(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);

	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<void> Request:SetFirstPartyForCokkies(
		<str> url
	)
*/
static int luacef_request_set_first_party_for_cookies(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);
	const char *cs = lua_tostring(L, 2);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	p->set_first_party_for_cookies(p, &s);

	return 0;
}

/*
	<int> Request:GetResourceType()
*/
static int luacef_request_get_resource_type(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_resource_type(p));
	return 1;
}

/*
	<int> Request:GetTransitionType()
*/
static int luacef_request_get_transition_type(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_transition_type(p));
	return 1;
}

/*
	<int> Request:GetIdentifier()
*/
static int luacef_request_get_identifier(lua_State* L)
{
	cef_request_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_identifier(p));
	return 1;
}

static const luaL_Reg luacef_request_m[] = {
	{ "IsReadOnly" , luacef_request_is_read_only },
	{ "get_url", luacef_request_get_url },
	{ "set_url", luacef_request_set_url },
	{ "get_method", luacef_request_get_method },
	{ "set_method", luacef_request_set_method },
	{ "set_referrer", luacef_request_set_referrer },
	{ "get_referrer_url", luacef_request_get_referrer_url },
	{ "get_referrer_policy", luacef_request_get_referrer_policy },
	{ "get_flags", luacef_request_get_flags },
	{ "set_flags", luacef_request_set_flags },
	{ "get_first_party_for_cookies", luacef_request_get_first_party_for_cookies },
	{ "set_first_party_for_cookies", luacef_request_set_first_party_for_cookies },
	{ "get_resource_type", luacef_request_get_resource_type },
	{ "get_transition_type", luacef_request_get_transition_type },
	{ "get_identifier", luacef_request_get_identifier },
	{ "get_post_data", luacef_request_get_post_data },
	{ "set_post_data", luacef_request_set_post_data },
	{ "get_header_map", luacef_request_get_header_map },
	{ "set_header_map", luacef_request_set_header_map },
	{ "set", luacef_request_set },
	{ NULL, NULL }
};

// PostData // =============================================

/*
	<bool> PostData:IsReadOnly()
*/
static int luacef_post_data_is_read_only(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_read_only(p));
	return 1;
}

/*
	<bool> PostData:HasExcludedElements()
*/
static int luacef_post_data_has_excluded_elements(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->has_excluded_elements(p));
	return 1;
}

/*
	<int> PostData:GetElementCount()
*/
static int luacef_post_data_get_element_count(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_element_count(p));
	return 1;
}

/*
	<void> PostData:GetElements(
		<int>				size,
		<PostDataElement>	elements
	)
*/
static int luacef_post_data_get_elements(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);
	size_t sz = lua_tointeger(L, 2);
	cef_post_data_element_t *e = luacef_checkudata(L, 3, __post_data_element__);

	p->get_elements(p, &sz, &e);

	return 0;
}

/*
	<int> PostData:RemoveElement(
		<PostDataElement>	element
	)
*/
static int luacef_post_data_remove_element(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);
	cef_post_data_element_t *p2 = luacef_checkudata(L, 2, __post_data_element__);

	int r = p->remove_element(p, p2);
	
	lua_pushinteger(L, r);
	return 1;
}

/*
	<int> PostData:AddElement(
		<PostDataElement>	element
	)
*/
static int luacef_post_data_add_element(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);
	cef_post_data_element_t *p2 = luacef_checkudata(L, 2, __post_data_element__);

	int r = p->add_element(p, p2);
	
	lua_pushinteger(L, r);
	return 1;
}

/*
	<void> PostData:RemoveElements()
*/
static int luacef_post_data_remove_elements(lua_State* L)
{
	cef_post_data_t *p = luacef_touserdata(L, 1);

	p->remove_elements(p);

	return 0;
}

static const luaL_Reg luacef_post_data_m[] = {
	{ "IsReadOnly", luacef_post_data_is_read_only },
	{ "HasExcludedElements", luacef_post_data_has_excluded_elements },
	{ "GetElements", luacef_post_data_get_elements },
	{ "GetElementCount", luacef_post_data_get_element_count },
	{ "RemoveElement", luacef_post_data_remove_element },
	{ "AddElement", luacef_post_data_add_element },
	{ "RemoveElements", luacef_post_data_remove_elements },
	{ NULL, NULL }
};

// PostDataElement //===================================


/*
	<bool> PostDataElement:IsReadOnly()
*/
static int luacef_post_data_element_is_read_only(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_read_only(p));
	return 1;
}

/*
	<void> PostDataElement:SetToEmpty()
*/
static int luacef_post_data_element_set_to_empty(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);

	p->set_to_empty(p);

	return 0;
}

/*
	<void> PostDataElement:SetToFile(
		<str> file_name
	)
*/
static int luacef_post_data_element_set_to_file(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);
	const char* cs = lua_tostring(L, 2);

	cef_string_t s = { 0 };
	cef_string_from_utf8(cs, strlen(cs), &s);
	p->set_to_file(p, &s);

	return 0;
}

/*
	<void> PostDataElement:SetToFile(
		<int>	size,
		<udata>	bytes
	)
*/
static int luacef_post_data_element_set_to_bytes(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);
	int sz = lua_tointeger(L, 2);
	const void *b = lua_touserdata(L, 3);

	p->set_to_bytes(p, sz, b);

	return 0;
}

/*
	<int> PostDataElement:GetType()
*/
static int luacef_post_data_element_get_type(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_type(p));
	return 1;
}

/*
	<str> PostDataElement:GetFile()
*/
static int luacef_post_data_element_get_file(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_file(p);
	cef_string_utf8_t s2 = { 0 };
	cef_string_to_utf8(s->str, s->length, &s2);
	
	lua_pushstring(L, s2.str);
	return 1;
}

/*
	<int> PostDataElement:GetBytesCount()
*/
static int luacef_post_data_element_get_bytes_count(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_bytes_count(p));
	return 1;
}

/*
	<int> PostDataElement:GetBytes(
		<int>	size,
		<udata>	bytes
	)
*/
static int luacef_post_data_element_get_bytes(lua_State* L)
{
	cef_post_data_element_t *p = luacef_touserdata(L, 1);
	int sz = lua_tointeger(L, 2);
	void *b = lua_touserdata(L, 3);

	int ret = p->get_bytes(p, sz, b);

	lua_pushinteger(L, ret);
	return 1;
}

static const luaL_Reg luacef_post_data_element_data_m[] = {
	{ "IsReadOnly", luacef_post_data_element_is_read_only },
	{ "SetToEmpty", luacef_post_data_element_set_to_empty },
	{ "SetToFile", luacef_post_data_element_set_to_file },
	{ "SetToBytes", luacef_post_data_element_set_to_bytes },
	{ "GetType", luacef_post_data_element_get_type },
	{ "GetFile", luacef_post_data_element_get_file },
	{ "GetBytesCount", luacef_post_data_element_get_bytes_count },
	{ "GetBytes", luacef_post_data_element_get_bytes },
	{ NULL, NULL }
};
