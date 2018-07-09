#include "../luacef.h"

static int luacef_request_callback_new(lua_State* L)
{


	return 1;
}

typedef struct luacef_request_callback {

	cef_base_t base;

	void (CEF_CALLBACK *cont)(
		struct luacef_request_callback* self, 
		int								allow);

	void (CEF_CALLBACK *cancel)(
		struct luacef_request_callback* self);

	lua_State *L;
	void *self;
	int ref;

} luacef_request_callback;

/*
	<void> RequestCallback:Cont(
		<bool>	allow
	)
*/
void CEF_CALLBACK cont(
	struct luacef_request_callback* self,
	int								allow)
{

}

/*
	<void> RequestCallback:Cancel()
*/
void CEF_CALLBACK cancel(
	struct luacef_request_callback* self)
{

}



// ==================================================



typedef struct luacef_request_handler {

	cef_base_t base;

	int (CEF_CALLBACK *on_before_browse)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request,
		int								is_redirect);

	int (CEF_CALLBACK *on_open_urlfrom_tab)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		const cef_string_t*				target_url,
		cef_window_open_disposition_t	target_disposition,
		int								user_gesture);

	int (CEF_CALLBACK *on_before_resource_load)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request,
		struct _cef_request_callback_t* callback);

	struct _cef_resource_handler_t* (CEF_CALLBACK *get_resource_handler)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request);

	void (CEF_CALLBACK *on_resource_redirect)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request,
		cef_string_t*					new_url);

	int (CEF_CALLBACK *on_resource_response)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request,
		struct _cef_response_t*			response);

	struct _cef_response_filter_t* (CEF_CALLBACK *get_resource_response_filter)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request,
		struct _cef_response_t*			response);

	void (CEF_CALLBACK *on_resource_load_complete)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		struct _cef_request_t*			request,
		struct _cef_response_t*			response,
		cef_urlrequest_status_t			status,
		int64							received_content_length);

	int (CEF_CALLBACK *get_auth_credentials)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		struct _cef_frame_t*			frame,
		int								isProxy,
		const cef_string_t*				host,
		int								port,
		const cef_string_t*				realm,
		const cef_string_t*				scheme,
		struct _cef_auth_callback_t*	callback);

	int (CEF_CALLBACK *on_quota_request)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		const cef_string_t*				origin_url,
		int64							new_size,
		struct _cef_request_callback_t* callback);

	void (CEF_CALLBACK *on_protocol_execution)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		const cef_string_t*				url,
		int*							allow_os_execution);

	int (CEF_CALLBACK *on_certificate_error)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		cef_errorcode_t					cert_error,
		const cef_string_t*				request_url,
		struct _cef_sslinfo_t*			ssl_info,
		struct _cef_request_callback_t*	callback);

	void (CEF_CALLBACK *on_plugin_crashed)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		const cef_string_t*				plugin_path);

	void (CEF_CALLBACK *on_render_view_ready)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser);

	void (CEF_CALLBACK *on_render_process_terminated)(
		struct luacef_request_handler*	self,
		struct _cef_browser_t*			browser,
		cef_termination_status_t		status);

	lua_State *L;
	void *self;
	int ref;

} luacef_request_handler;

// ==========================

/*
	<ResourceHandler> RequestHandler:GetResourceHandler(
		<Browser>	browser,
		<Frame>		frame,
		<Request>	request
	)
*/
struct _cef_resource_handler_t* (CEF_CALLBACK *request_handler_get_resource_handler)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request);

/*
	<ResponseFilter> RequestHandler:GetResourceResponseFilter(
		<Browser>	browser,
		<Frame>		frame,
		<Request>	request,
		<Response>	response
	)
*/
struct _cef_response_filter_t* (CEF_CALLBACK *request_handler_get_resource_response_filter)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request,
	struct _cef_response_t*			response);

/*
	<int> RequestHandler:OnBeforeBrowse(
		<Browser>	browser,
		<Frame>		frame,
		<Request>	request,
		<bool>		is_redirect
	)
*/
int CEF_CALLBACK request_handler_on_before_browse(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request,
	int								is_redirect)
{
	// todo
}

/*
	<int> RequestHandler:OnOpenURLFromTab(
		<Browser>	browser,
		<Frame>		frame,
		<str>		target_url,
		<int>		target_disposition,
		<int>		user_gesture
	)
*/
int (CEF_CALLBACK *request_handler_on_open_urlfrom_tab)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	const cef_string_t*				target_url,
	cef_window_open_disposition_t	target_disposition,
	int								user_gesture);

/*
	<int> RequestHandler:OnOpenURLFromTab(
		<Browser>			browser,
		<Frame>				frame,
		<Request>			request,
		<RequestCallback>	callback
	)
*/
int (CEF_CALLBACK *request_handler_on_before_resource_load)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request,
	struct _cef_request_callback_t* callback);

/*
	<void> RequestHandler:OnResourceRedirect(
		<Browser>	browser,
		<Frame>		frame,
		<Request>	request,
		<str>		new_url
	)
*/
void (CEF_CALLBACK *request_handler_on_resource_redirect)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request,
	cef_string_t*					new_url);

/*
	<int> RequestHandler:OnResourceResponse(
		<Browser>	browser,
		<Frame>		frame,
		<Request>	request,
		<Response>	response
	)
*/
int (CEF_CALLBACK *request_handler_on_resource_response)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request,
	struct _cef_response_t*			response);

/*
	<void> RequestHandler:OnResourceLoadComplete(
		<Browser>	browser,
		<Frame>		frame,
		<Request>	request,
		<Response>	response,
		<int>		status,
		<int>		received_content_length
	)
*/
void (CEF_CALLBACK *request_handler_on_resource_load_complete)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	struct _cef_request_t*			request,
	struct _cef_response_t*			response,
	cef_urlrequest_status_t			status,
	int64							received_content_length);

// todo
int (CEF_CALLBACK *request_handler_get_auth_credentials)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	struct _cef_frame_t*			frame,
	int								isProxy,
	const cef_string_t*				host,
	int								port,
	const cef_string_t*				realm,
	const cef_string_t*				scheme,
	struct _cef_auth_callback_t*	callback);

/*
	<void> RequestHandler:OnQuotaRequest(
		<Browser>			browser,
		<str>				origin_url,
		<int>				new_size,
		<RequestCallback>	callback
	)
*/
int (CEF_CALLBACK *request_handler_on_quota_request)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	const cef_string_t*				origin_url,
	int64							new_size,
	struct _cef_request_callback_t* callback);

/*
	<void> RequestHandler:OnProtocolExecution(
		<Browser>	browser,
		<str>		url,
		<int>		allow_os_execution
	)
*/
void (CEF_CALLBACK *request_handler_on_protocol_execution)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	const cef_string_t*				url,
	int*							allow_os_execution); // ptr to int

/*
	<int> RequestHandler:OnCertificateError(
		<Browser>			browser,
		<int>				cert_error_code,
		<str>				request_url,
		<SSLInfo>			ssl_info,
		<RequestCallback>	callback
	)
*/
int (CEF_CALLBACK *request_handler_on_certificate_error)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	cef_errorcode_t					cert_error,
	const cef_string_t*				request_url,
	struct _cef_sslinfo_t*			ssl_info,
	struct _cef_request_callback_t*	callback);

/*
	<void> RequestHandler:OnPluginCrashed(
		<Browser>	browser,
		<str>		plugin_path
	)
*/
void (CEF_CALLBACK *request_handler_on_plugin_crashed)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	const cef_string_t*				plugin_path);

/*
	<void> RequestHandler:OnRenderViewReady(
		<Browser>	browser
	)
*/
void (CEF_CALLBACK *request_handler_on_render_view_ready)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser);

/*
	<void> RequestHandler:OnRenderProcessTerminated(
		<Browser>	browser,
		<int>		status
	)
*/
void (CEF_CALLBACK *request_handler_on_render_process_terminated)(
	struct luacef_request_handler*	self,
	struct _cef_browser_t*			browser,
	cef_termination_status_t		status);

/*
	<RequestHandler> newRequestHandler 
	{
		<int>	OnBeforeBrowse(<Browser>, <Frame>, <Request>, <bool>)
		<int>	OnOpenURLFromTab(<Browser>, <Frame>, <str>, <int>, <int>)
		<int>	OnOpenURLFromTab(<Browser>, <Frame>, <Request>, <RequestCallback>)
		<void>	OnResourceRedirect(<Browser>, <Frame>, <Request>, <str>)
		<int>	OnResourceResponse(<Browser>, <Frame>, <Request>, <Response>)
		<void>	OnResourceLoadComplete(<Browser>, <Frame>, <Request>, <Response>, <int>, <int>)
		<void>	OnQuotaRequest(<Browser>, <str>, <int>, <RequestCallback>)
		<void>	OnProtocolExecution(<Browser>, <str>, <int>)
		<int>	OnCertificateError(<Browser>, <int>, <str>, <SSLInfo>, <RequestCallback>)
		<void>	OnPluginCrashed(<Browser>, <str>)
		<void>	OnRenderViewReady(<Browser>)
		<void>	OnRenderProcessTerminated(<Browser>, <int>)
	}
*/
static int luacef_request_handler_new(lua_State* L)
{

	return 1;
}