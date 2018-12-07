#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_image_capi.h"
#include "include/capi/cef_stream_capi.h"


///
// Structure used to represent drag data. The functions of this structure may be
// called on any thread.
///
typedef struct __cef_drag_data_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Returns a copy of the current object.
	///
	struct _cef_drag_data_t*(CEF_CALLBACK* clone)(struct _cef_drag_data_t* self);

	///
	// Returns true (1) if this object is read-only.
	///
	int(CEF_CALLBACK* is_read_only)(struct _cef_drag_data_t* self);

	///
	// Returns true (1) if the drag data is a link.
	///
	int(CEF_CALLBACK* is_link)(struct _cef_drag_data_t* self);

	///
	// Returns true (1) if the drag data is a text or html fragment.
	///
	int(CEF_CALLBACK* is_fragment)(struct _cef_drag_data_t* self);

	///
	// Returns true (1) if the drag data is a file.
	///
	int(CEF_CALLBACK* is_file)(struct _cef_drag_data_t* self);

	///
	// Return the link URL that is being dragged.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_link_url)(
		struct _cef_drag_data_t* self);

	///
	// Return the title associated with the link being dragged.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_link_title)(
		struct _cef_drag_data_t* self);

	///
	// Return the metadata, if any, associated with the link being dragged.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_link_metadata)(
		struct _cef_drag_data_t* self);

	///
	// Return the plain text fragment that is being dragged.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_fragment_text)(
		struct _cef_drag_data_t* self);

	///
	// Return the text/html fragment that is being dragged.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_fragment_html)(
		struct _cef_drag_data_t* self);

	///
	// Return the base URL that the fragment came from. This value is used for
	// resolving relative URLs and may be NULL.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_fragment_base_url)(
		struct _cef_drag_data_t* self);

	///
	// Return the name of the file being dragged out of the browser window.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_file_name)(
		struct _cef_drag_data_t* self);

	///
	// Write the contents of the file being dragged out of the web view into
	// |writer|. Returns the number of bytes sent to |writer|. If |writer| is NULL
	// this function will return the size of the file contents in bytes. Call
	// get_file_name() to get a suggested name for the file.
	///
	size_t(CEF_CALLBACK* get_file_contents)(struct _cef_drag_data_t* self,
		struct _cef_stream_writer_t* writer);

	///
	// Retrieve the list of file names that are being dragged into the browser
	// window.
	///
	int(CEF_CALLBACK* get_file_names)(struct _cef_drag_data_t* self,
		cef_string_list_t names);

	///
	// Set the link URL that is being dragged.
	///
	void(CEF_CALLBACK* set_link_url)(struct _cef_drag_data_t* self,
		const cef_string_t* url);

	///
	// Set the title associated with the link being dragged.
	///
	void(CEF_CALLBACK* set_link_title)(struct _cef_drag_data_t* self,
		const cef_string_t* title);

	///
	// Set the metadata associated with the link being dragged.
	///
	void(CEF_CALLBACK* set_link_metadata)(struct _cef_drag_data_t* self,
		const cef_string_t* data);

	///
	// Set the plain text fragment that is being dragged.
	///
	void(CEF_CALLBACK* set_fragment_text)(struct _cef_drag_data_t* self,
		const cef_string_t* text);

	///
	// Set the text/html fragment that is being dragged.
	///
	void(CEF_CALLBACK* set_fragment_html)(struct _cef_drag_data_t* self,
		const cef_string_t* html);

	///
	// Set the base URL that the fragment came from.
	///
	void(CEF_CALLBACK* set_fragment_base_url)(struct _cef_drag_data_t* self,
		const cef_string_t* base_url);

	///
	// Reset the file contents. You should do this before calling
	// cef_browser_host_t::DragTargetDragEnter as the web view does not allow us
	// to drag in this kind of data.
	///
	void(CEF_CALLBACK* reset_file_contents)(struct _cef_drag_data_t* self);

	///
	// Add a file that is being dragged into the webview.
	///
	void(CEF_CALLBACK* add_file)(struct _cef_drag_data_t* self,
		const cef_string_t* path,
		const cef_string_t* display_name);

	///
	// Get the image representation of drag data. May return NULL if no image
	// representation is available.
	///
	struct _cef_image_t*(CEF_CALLBACK* get_image)(struct _cef_drag_data_t* self);

	///
	// Get the image hotspot (drag start location relative to image dimensions).
	///
	cef_point_t(CEF_CALLBACK* get_image_hotspot)(struct _cef_drag_data_t* self);

	///
	// Returns true (1) if an image representation of drag data is available.
	///
	int(CEF_CALLBACK* has_image)(struct _cef_drag_data_t* self);
} _cef_drag_data_t;




//#include "include/cef_drag_data.h"

///
// Create a new cef_drag_data_t object.
///
CEF_EXPORT cef_drag_data_t* cef_drag_data_create();

static int luacef_drag_data_create(lua_State *L)
{
	cef_drag_data_t *p = cef_drag_data_create();

	luacef_pushuserdata(L, p, __drag_data__);
	return 1;
}



// register ==========================

void luacef_drag_data_reg(lua_State *L)
{



}