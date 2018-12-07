#include "../luacef.h"
#include "include/capi/cef_base_capi.h"

typedef struct luacef_cef_command_line {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* is_valid)(struct luacef_cef_command_line* self);

	int(CEF_CALLBACK* is_read_only)(struct luacef_cef_command_line* self);

	struct _cef_command_line_t*(CEF_CALLBACK* copy)(
		struct luacef_cef_command_line* self);

	void(CEF_CALLBACK* init_from_argv)(struct luacef_cef_command_line* self,
		int argc,
		const char* const* argv);

	void(CEF_CALLBACK* init_from_string)(struct luacef_cef_command_line* self,
		const cef_string_t* command_line);

	void(CEF_CALLBACK* reset)(struct luacef_cef_command_line* self);

	void(CEF_CALLBACK* get_argv)(struct luacef_cef_command_line* self,
		cef_string_list_t argv);

	cef_string_userfree_t(CEF_CALLBACK* get_command_line_string)(
		struct luacef_cef_command_line* self);

	cef_string_userfree_t(CEF_CALLBACK* get_program)(
		struct luacef_cef_command_line* self);

	void(CEF_CALLBACK* set_program)(struct luacef_cef_command_line* self,
		const cef_string_t* program);

	int(CEF_CALLBACK* has_switches)(struct luacef_cef_command_line* self);

	int(CEF_CALLBACK* has_switch)(struct luacef_cef_command_line* self,
		const cef_string_t* name);

	cef_string_userfree_t(CEF_CALLBACK* get_switch_value)(
		struct luacef_cef_command_line* self,
		const cef_string_t* name);

	void(CEF_CALLBACK* get_switches)(struct luacef_cef_command_line* self,
		cef_string_map_t switches);

	void(CEF_CALLBACK* append_switch)(struct luacef_cef_command_line* self,
		const cef_string_t* name);

	void(CEF_CALLBACK* append_switch_with_value)(struct luacef_cef_command_line* self,
		const cef_string_t* name,
		const cef_string_t* value);

	int(CEF_CALLBACK* has_arguments)(struct luacef_cef_command_line* self);

	void(CEF_CALLBACK* get_arguments)(struct luacef_cef_command_line* self,
		cef_string_list_t arguments);

	void(CEF_CALLBACK* append_argument)(struct luacef_cef_command_line* self,
		const cef_string_t* argument);

	void(CEF_CALLBACK* prepend_wrapper)(struct luacef_cef_command_line* self,
		const cef_string_t* wrapper);

} luacef_cef_command_line;



//CEF_EXPORT cef_command_line_t* cef_command_line_create();
//CEF_EXPORT cef_command_line_t* cef_command_line_get_global();
