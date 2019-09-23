#include "types.h"

using namespace LUACEF;

int Settings::__new(State& L)
{
	Settings *self = new Settings();

	if (L.isTable(1)) {
		L.push(L);
		while (L.next(1) != 0) {
			if (L.isString(-2)) {
				const char *idx = L.toString(-2);
				switch (hash(idx)) {		
					case hash("no_sandbox"): // int no_sandbox;
						self->no_sandbox = L.toBool(-1);
						break;	
					case hash("browser_subprocess_path"): // cef_string_t browser_subprocess_path;
						// todo
						break;		
					case hash("framework_dir_path"): // cef_string_t framework_dir_path;
						// todo
						break;				
					case hash("multi_threaded_message_loop"): // int multi_threaded_message_loop;
						self->multi_threaded_message_loop = L.toBool(-1);
						break;
					case hash("external_message_pump"): // int external_message_pump;
						self->external_message_pump = L.toInt(-1);
						break;			
					case hash("windowless_rendering_enabled"): // int windowless_rendering_enabled;

					// int command_line_args_disabled;
					case hash("command_line_args_disabled"):

					// cef_string_t cache_path;
					case hash("cache_path"):

					// cef_string_t user_data_path;
					case hash("user_data_path"):

					// int persist_session_cookies;
					case hash("persist_session_cookies"):

					// int persist_user_preferences;
					case hash("persist_user_preferences"):

					// cef_string_t user_agent;
					case hash("user_agent"):

					// cef_string_t product_version;
					case hash("product_version"):

					// cef_string_t locale;
					case hash("locale"):

					// cef_string_t log_file;
					case hash("log_file"):

					// cef_log_severity_t log_severity;
					case hash("log_severity"):

					// cef_string_t javascript_flags;
					case hash("javascript_flags"):

					// cef_string_t resources_dir_path;
					case hash("resources_dir_path"):

					// cef_string_t locales_dir_path;
					case hash("locales_dir_path"):

					// int pack_loading_disabled;
					case hash("pack_loading_disabled"):

					// int remote_debugging_port;
					case hash("remote_debugging_port"):

					// int uncaught_exception_stack_size;
					case hash("uncaught_exception_stack_size"):

					// int ignore_certificate_errors;
					case hash("ignore_certificate_errors"):

					// int enable_net_security_expiration;
					case hash("enable_net_security_expiration"):

					// cef_color_t background_color;
					case hash("background_color"):

					// cef_string_t accept_language_list;
					case hash("accept_language_list"):
						break;
				}
			}
		}
	}

	pushUPtr(L, self, "CefSettings");
	return 1;
}

int Settings::__index(State& L)
{

}

int Settings::__newindex(State& L)
{

}

int Settings::__gc(State& L)
{
	
}


void Settings::__reg(State& L)
{

}