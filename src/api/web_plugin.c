#include "../luacef.h"
#include "include/capi/cef_base_capi.h"

//#include "include/cef_app.h"
//#include "include/cef_browser.h"

/*
	<str> WebPluginInfo:GetName()
*/
static int luacef_WebPluginInfo_GetName(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_userfree_t s = p->get_name(p);

	luacef_pushstring_free(L, s);
	return 1;
}

/*
	<str> WebPluginInfo:GetPath()
*/
static int luacef_WebPluginInfo_GetPath(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_userfree_t s = p->get_path(p);

	luacef_pushstring_free(L, s);
	return 1;
}

/*
	<str> WebPluginInfo:GetVersion()
*/
static int luacef_WebPluginInfo_GetVersion(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_userfree_t s = p->get_version(p);

	luacef_pushstring_free(L, s);
	return 1;
}

/*
	<str> WebPluginInfo:GetDescription()
*/
static int luacef_WebPluginInfo_GetDescription(lua_State* L)
{
	cef_web_plugin_info_t *p = lua_touserdata(L, 1);

	cef_string_userfree_t s = p->get_description(p);

	luacef_pushstring_free(L, s);
	return 1;
}


typedef struct __cef_web_plugin_info_visitor_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Method that will be called once for each plugin. |count| is the 0-based
	// index for the current plugin. |total| is the total number of plugins.
	// Return false (0) to stop visiting plugins. This function may never be
	// called if no plugins are found.
	///
	int(CEF_CALLBACK* visit)(struct _cef_web_plugin_info_visitor_t* self,
		struct _cef_web_plugin_info_t* info,
		int count,
		int total);
} _cef_web_plugin_info_visitor_t;

///
// Structure to implement for receiving unstable plugin information. The
// functions of this structure will be called on the browser process IO thread.
///
typedef struct __cef_web_plugin_unstable_callback_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Method that will be called for the requested plugin. |unstable| will be
	// true (1) if the plugin has reached the crash count threshold of 3 times in
	// 120 seconds.
	///
	void(CEF_CALLBACK* is_unstable)(
		struct _cef_web_plugin_unstable_callback_t* self,
		const cef_string_t* path,
		int unstable);
} _cef_web_plugin_unstable_callback_t;

///
// Implement this structure to receive notification when CDM registration is
// complete. The functions of this structure will be called on the browser
// process UI thread.
///
typedef struct __cef_register_cdm_callback_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Method that will be called when CDM registration is complete. |result| will
	// be CEF_CDM_REGISTRATION_ERROR_NONE if registration completed successfully.
	// Otherwise, |result| and |error_message| will contain additional information
	// about why registration failed.
	///
	void(CEF_CALLBACK* on_cdm_registration_complete)(
		struct _cef_register_cdm_callback_t* self,
		cef_cdm_registration_error_t result,
		const cef_string_t* error_message);
} _cef_register_cdm_callback_t;

// static functions =======================================

/*
	<void> VisitWebPluginInfo(
		<WebPluginInfoVisitor> visitor
	)
*/
static int luacef_WebPluginInfoVisitor(lua_State *L)
{
	cef_web_plugin_info_visitor_t *visitor = luacef_checkudata(L, 1, __web_plugin_info_visitor__);

	cef_visit_web_plugin_info(visitor);

	return 0;
}

/*
	<void> RefreshWebPlugins()
*/
static int luacef_RefreshWebPlugins(lua_State *L)
{
	cef_refresh_web_plugins();

	return 0;
}

/*
	<void> UnregisterInternalWebPlugin(
		<str> path
	)
*/
static int luacef_UnregisterInternalWebPlugin(lua_State *L)
{
	cef_string_t s = luacef_tostring(L, 1);

	cef_unregister_internal_web_plugin(&s);

	return 0;
}

/*
	<void> RegisterWebPluginCrash(
		<str> path
	)
*/
static int luacef_RegisterWebPluginCrash(lua_State *L)
{
	cef_string_t s = luacef_tostring(L, 1);

	cef_register_web_plugin_crash(&s);

	return 0;
}

/*
	<void> IsWebPluginUnstable(
		<str> path,
		<WebPluginUnstableCallback> callback
	)
*/
static int luacef_IsWebPluginUnstable(lua_State *L)
{
	const cef_string_t s = luacef_tostring(L, 1);
	cef_web_plugin_unstable_callback_t *callback = luacef_checkudata(L, 2, __web_plugin_unstable_callback__);

	cef_is_web_plugin_unstable(&s, callback);

	return 0;
}

/*
	<void> RegisterWidevineCdm(
		<str> path,
		<RegisterCdmCallback> callback
	)
*/
static int luacef_RegisterWidevineCdm(lua_State *L)
{
	const cef_string_t s = luacef_tostring(L, 1);
	cef_register_cdm_callback_t *callback = luacef_checkudata(L, 2, __register_cdm_callback__);

	cef_register_widevine_cdm(&s, callback);

	return 0;
}
