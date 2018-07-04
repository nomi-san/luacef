#pragma once

#include "../luacef.h"
// todo

typedef struct luacef_browser_process_handler {

	cef_base_t base;

	void (CEF_CALLBACK *on_context_initialized)(
		struct luacef_browser_process_handler*	self);

	void (CEF_CALLBACK *on_before_child_process_launch)(
		struct luacef_browser_process_handler*	self,
		struct _cef_command_line_t*				command_line);

	void (CEF_CALLBACK *on_render_process_thread_created)(
		struct luacef_browser_process_handler*	self,
		struct _cef_list_value_t*				extra_info);

	struct _cef_print_handler_t* (CEF_CALLBACK *get_print_handler)(
		struct luacef_browser_process_handler*	self);

	void (CEF_CALLBACK *on_schedule_message_pump_work)(
		struct luacef_browser_process_handler*	self,
		int64									delay_ms);

	lua_State *L;
	int ref;

} luacef_browser_process_handler;

