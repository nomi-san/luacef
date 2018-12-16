#include "../luacef.h"

#include "include/capi/cef_base_capi.h"

/*
	<bool>	DownloadItem:IsValid()
*/
static int luacef_download_item_is_valid(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushboolean(L, p->is_valid(p));
	return 1;
}

/*
	<bool>	DownloadItem:IsInProgress()
*/
static int luacef_download_item_is_in_progress(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushboolean(L, p->is_in_progress(p));
	return 1;
}

/*
	<bool>	DownloadItem:IsComplete()
*/
static int luacef_download_item_is_complete(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushboolean(L, p->is_complete(p));
	return 1;
}

/*
	<bool>	DownloadItem:IsCanceled()
*/
static int luacef_download_item_is_canceled(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushboolean(L, p->is_canceled(p));
	return 1;
}

/*
	<int>	DownloadItem:GetCurrentSpeed()
	-- speed is bytes/s
*/
static int luacef_download_item_get_current_speed(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushinteger(L, p->get_current_speed(p));
	return 1;
}

/*
	<int>	DownloadItem:GetPercentComplete()
	-- return -1 if the receive total size is unknown.
*/
static int luacef_download_item_get_percent_complete(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushinteger(L, p->get_percent_complete(p));
	return 1;
}

/*
	<int>	DownloadItem:GetTotalBytes()
*/
static int luacef_download_item_get_total_bytes(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushinteger(L, p->get_total_bytes(p));
	return 1;
}

/*
	<int>	DownloadItem:GetReceivedBytes()
*/
static int luacef_download_item_get_received_bytes(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushinteger(L, p->get_received_bytes(p));
	return 1;
}

/*
	<Time>	DownloadItem:GetStartTime()
*/
static int luacef_download_item_get_start_time(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_time_t t = p->get_start_time(p);

	luacef_pushuserdata(L, &t, __CefTime);
	return 1;
}

/*
	<Time>	DownloadItem:GetEndTime()
*/
static int luacef_download_item_get_end_time(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_time_t t = p->get_end_time(p);

	luacef_pushuserdata(L, &t, __CefTime);
	return 1;
}

/*
	<str>	DownloadItem:GetFullPath()
*/
static int luacef_download_item_get_full_path(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_string_userfree_t s = p->get_full_path(p);

	luacef_pushstring(L, s);
	//cef_string_userfree_free(s);
	return 1;
}

/*
	<int>	DownloadItem:GetId()
*/
static int luacef_download_item_get_id(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	lua_pushinteger(L, p->get_id(p));
	return 1;
}

/*
	<str>	DownloadItem:GetURL()
*/
static int luacef_download_item_get_url(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_string_userfree_t s = p->get_url(p);

	luacef_pushstring(L, s);
	//cef_string_userfree_free(s);
	return 1;
}

/*
	<str>	DownloadItem:GetOriginalURL()
*/
static int luacef_download_item_get_original_url(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_string_userfree_t s = p->get_original_url(p);

	luacef_pushstring(L, s);
	//cef_string_userfree_free(s);
	return 1;
}

/*
	<str>	DownloadItem:GetSuggestedFileName()
*/
static int luacef_download_item_get_suggested_file_name(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_string_userfree_t s = p->get_suggested_file_name(p);

	luacef_pushstring(L, s);
	//cef_string_userfree_free(s);
	return 1;
}

/*
	<str>	DownloadItem:GetContentDisposition()
*/
static int luacef_download_item_get_content_disposition(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_string_userfree_t s = p->get_content_disposition(p);

	luacef_pushstring(L, s);
	//cef_string_userfree_free(s);
	return 1;
}

/*
	<str>	DownloadItem:GetMimeType()
*/
static int luacef_download_item_get_mime_type(lua_State *L)
{
	cef_download_item_t *p = luacef_touserdata(L, -1);

	cef_string_userfree_t s = p->get_mime_type(p);

	luacef_pushstring(L, s);
	//cef_string_userfree_free(s); //luacef_pushstring_userfree(L, s);
	return 1;
}

static luaL_Reg luacef_download_item_m[] = {
	{ "IsValid", luacef_download_item_is_valid },
	{ "IsInProgress", luacef_download_item_is_in_progress },
	{ "IsComplete", luacef_download_item_is_complete },
	{ "IsCanceled", luacef_download_item_is_canceled },
	{ "GetCurrentSpeed", luacef_download_item_get_current_speed },
	{ "GetPercentComplete", luacef_download_item_get_percent_complete },
	{ "GetTotalBytes", luacef_download_item_get_total_bytes },
	{ "GetReceivedBytes", luacef_download_item_get_received_bytes },
	{ "GetStartTime", luacef_download_item_get_start_time },
	{ "GetEndTime", luacef_download_item_get_end_time },
	{ "GetFullPath", luacef_download_item_get_full_path },
	{ "GetId", luacef_download_item_get_id },
	{ "GetURL", luacef_download_item_get_url },
	{ "GetOriginalURL", luacef_download_item_get_url },
	{ "GetSuggestedFileName", luacef_download_item_get_suggested_file_name },
	{ "GetContentDisposition", luacef_download_item_get_content_disposition },
	{ "GetMimeType", luacef_download_item_get_mime_type },
	{ NULL, NULL }
};

void luacef_download_item_reg(lua_State *L)
{
	luaL_newmetatable(L, __CefDownloadItem);
	luaL_setfuncs(L, luacef_download_item_m, 0);
	lua_setfield(L, -1, __index__);
}