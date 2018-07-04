#include "luacef_resource_bunble_handler.h"

const char	
	*_rbh_get_localized_string = "LocalizedString",
	*_rbh_get_data_resource = "DataResource",
	*_rbh_get_data_resource_for_scale = "DataResourceForScale";


int CEF_CALLBACK rbh_get_localized_string(
	struct luacef_resource_bundle_handler*	self,
	int										string_id,
	cef_string_t*							string)
{
	return 0;
}

int CEF_CALLBACK rbh_get_data_resource(
	struct luacef_resource_bundle_handler*	self,
	int										resource_id,
	void**									data,
	size_t*									data_size)
{
	return 0;
}

int CEF_CALLBACK rbh_get_data_resource_for_scale(
	struct luacef_resource_bundle_handler*	self,
	int										resource_id,
	cef_scale_factor_t						scale_factor,
	void**									data,
	size_t*									data_size)
{
	return 0;
}

