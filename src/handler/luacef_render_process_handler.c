
#include "luacef_render_process_handler.h"

const char	
	*_rph_on_render_thread_created = "OnRenderThreadCreated",
	*_rph_on_web_kit_initialized = "OnWebKitInitialized",
	*_rph_on_browser_created = "OnBrowserCreated",
	*_rph_on_browser_destroyed = "OnBrowserDestroyed",
	*_rph_get_load_handler = "LoadHandler",
	*_rph_on_before_navigation = "OnBeforeNavigation",
	*_rph_on_context_created = "OnContextCreated",
	*_rph_on_context_released = "OnContextReleased",
	*_rph_on_uncaught_exception = "OnUncaughtException",
	*_rph_on_focused_node_changed = "OnFocusedNodeChanged",
	*_rph_on_process_message_received = "OnProcessMessageReceived";

typedef struct luacef_render_process_handler {

	cef_base_t base;

	void (CEF_CALLBACK *on_render_thread_created)(
		struct luacef_render_process_handler*	self,
		struct _cef_list_value_t*				extra_info);

	void (CEF_CALLBACK *on_web_kit_initialized)(
		struct luacef_render_process_handler*	 self);

	void (CEF_CALLBACK *on_browser_created)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser);

	void (CEF_CALLBACK *on_browser_destroyed)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser);

	struct _cef_load_handler_t* (CEF_CALLBACK *get_load_handler)(
		struct luacef_render_process_handler*	self);

	int (CEF_CALLBACK *on_before_navigation)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_request_t*					request,
		cef_navigation_type_t					navigation_type,
		int										is_redirect);

	void (CEF_CALLBACK *on_context_created)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_v8context_t*				context);

	void (CEF_CALLBACK *on_context_released)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_v8context_t*				context);

	void (CEF_CALLBACK *on_uncaught_exception)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_v8context_t*				context,
		struct _cef_v8exception_t*				exception,
		struct _cef_v8stack_trace_t*			stackTrace);

	void (CEF_CALLBACK *on_focused_node_changed)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		struct _cef_frame_t*					frame,
		struct _cef_domnode_t*					node);

	int (CEF_CALLBACK *on_process_message_received)(
		struct luacef_render_process_handler*	self,
		struct _cef_browser_t*					browser,
		cef_process_id_t						source_process,
		struct _cef_process_message_t*			message);

	lua_State* L;
	int ref;

} luacef_render_process_handler;

void CEF_CALLBACK rph_on_render_thread_created(
	struct luacef_render_process_handler*	self,
	struct _cef_list_value_t*				extra_info)
{

}

void CEF_CALLBACK rph_on_web_kit_initialized(
	struct luacef_render_process_handler*	 self)
{

}

void CEF_CALLBACK rph_on_browser_created(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser)
{

}

void CEF_CALLBACK rph_on_browser_destroyed(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser)
{

}


struct _cef_load_handler_t* CEF_CALLBACK rph_get_load_handler(
	struct luacef_render_process_handler*	self)
{

}


int CEF_CALLBACK rph_on_before_navigation(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_request_t*					request,
	cef_navigation_type_t					navigation_type,
	int										is_redirect)
{

}

void CEF_CALLBACK rph_on_context_created(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_v8context_t*				context)
{

}

void CEF_CALLBACK rph_on_context_released(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_v8context_t*				context)
{

}

void CEF_CALLBACK rph_on_uncaught_exception(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_v8context_t*				context,
	struct _cef_v8exception_t*				exception,
	struct _cef_v8stack_trace_t*			stackTrace)
{

}

void CEF_CALLBACK rph_on_focused_node_changed(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	struct _cef_frame_t*					frame,
	struct _cef_domnode_t*					node)
{

}


int CEF_CALLBACK rph_on_process_message_received(
	struct luacef_render_process_handler*	self,
	struct _cef_browser_t*					browser,
	cef_process_id_t						source_process,
	struct _cef_process_message_t*			message)
{

}