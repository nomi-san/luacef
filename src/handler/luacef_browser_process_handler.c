#include "luacef_browser_process_handler.h"

const char	
	*_bph_on_context_initialized			= "OnContextInitialized",
	*_bph_on_before_child_process_launch	= "OnBeforeChildProcessLaunch",
	*_bph_on_render_process_thread_created	= "OnRenderProcessThreadCreated",
	*_bph_on_schedule_message_pump_work		= "OnScheduleMessagePumpWork",
	*_bph_get_print_handler					= "PrintHandler";

void CEF_CALLBACK bph_on_context_initialized(
	struct luacef_browser_process_handler*	self)
{

}

void CEF_CALLBACK bph_on_before_child_process_launch(
	struct luacef_browser_process_handler*	self,
	struct _cef_command_line_t*				command_line)
{

}

void CEF_CALLBACK bph_on_render_process_thread_created(
	struct luacef_browser_process_handler*	self,
	struct _cef_list_value_t*				extra_info)
{

}

struct _cef_print_handler_t* CEF_CALLBACK bph_get_print_handler(
	struct luacef_browser_process_handler*	self)
{

}

void CEF_CALLBACK bph_on_schedule_message_pump_work(
	struct luacef_browser_process_handler*	self,
	int64									delay_ms)
{

}