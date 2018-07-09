#include "../luacef.h"

///
// Structure to implement for visiting the DOM. The functions of this structure
// will be called on the render process main thread.
///
typedef struct luacef_domvisitor {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Method executed for visiting the DOM. The document object passed to this
	// function represents a snapshot of the DOM at the time this function is
	// executed. DOM objects are only valid for the scope of this function. Do not
	// keep references to or attempt to access any DOM objects outside the scope
	// of this function.
	///
	void(CEF_CALLBACK* visit)(struct _cef_domvisitor_t* self,
		struct _cef_domdocument_t* document);
} luacef_domvisitor;

///
// Structure used to represent a DOM document. The functions of this structure
// should only be called on the render process main thread thread.
///
typedef struct luacef_domdocument {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Returns the document type.
	///
	cef_dom_document_type_t(CEF_CALLBACK* get_type)(
		struct _cef_domdocument_t* self);

	///
	// Returns the root document node.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_document)(
		struct _cef_domdocument_t* self);

	///
	// Returns the BODY node of an HTML document.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_body)(
		struct _cef_domdocument_t* self);

	///
	// Returns the HEAD node of an HTML document.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_head)(
		struct _cef_domdocument_t* self);

	///
	// Returns the title of an HTML document.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_title)(
		struct _cef_domdocument_t* self);

	///
	// Returns the document element with the specified ID value.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_element_by_id)(
		struct _cef_domdocument_t* self,
		const cef_string_t* id);

	///
	// Returns the node that currently has keyboard focus.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_focused_node)(
		struct _cef_domdocument_t* self);

	///
	// Returns true (1) if a portion of the document is selected.
	///
	int(CEF_CALLBACK* has_selection)(struct _cef_domdocument_t* self);

	///
	// Returns the selection offset within the start node.
	///
	int(CEF_CALLBACK* get_selection_start_offset)(
		struct _cef_domdocument_t* self);

	///
	// Returns the selection offset within the end node.
	///
	int(CEF_CALLBACK* get_selection_end_offset)(struct _cef_domdocument_t* self);

	///
	// Returns the contents of this selection as markup.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_selection_as_markup)(
		struct _cef_domdocument_t* self);

	///
	// Returns the contents of this selection as text.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_selection_as_text)(
		struct _cef_domdocument_t* self);

	///
	// Returns the base URL for the document.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_base_url)(
		struct _cef_domdocument_t* self);

	///
	// Returns a complete URL based on the document base URL and the specified
	// partial URL.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_complete_url)(
		struct _cef_domdocument_t* self,
		const cef_string_t* partialURL);
} luacef_domdocument;

///
// Structure used to represent a DOM node. The functions of this structure
// should only be called on the render process main thread.
///
typedef struct luacef_domnode {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Returns the type for this node.
	///
	cef_dom_node_type_t(CEF_CALLBACK* get_type)(struct _cef_domnode_t* self);

	///
	// Returns true (1) if this is a text node.
	///
	int(CEF_CALLBACK* is_text)(struct _cef_domnode_t* self);

	///
	// Returns true (1) if this is an element node.
	///
	int(CEF_CALLBACK* is_element)(struct _cef_domnode_t* self);

	///
	// Returns true (1) if this is an editable node.
	///
	int(CEF_CALLBACK* is_editable)(struct _cef_domnode_t* self);

	///
	// Returns true (1) if this is a form control element node.
	///
	int(CEF_CALLBACK* is_form_control_element)(struct _cef_domnode_t* self);

	///
	// Returns the type of this form control element node.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_form_control_element_type)(
		struct _cef_domnode_t* self);

	///
	// Returns true (1) if this object is pointing to the same handle as |that|
	// object.
	///
	int(CEF_CALLBACK* is_same)(struct _cef_domnode_t* self,
		struct _cef_domnode_t* that);

	///
	// Returns the name of this node.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_name)(struct _cef_domnode_t* self);

	///
	// Returns the value of this node.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_value)(struct _cef_domnode_t* self);

	///
	// Set the value of this node. Returns true (1) on success.
	///
	int(CEF_CALLBACK* set_value)(struct _cef_domnode_t* self,
		const cef_string_t* value);

	///
	// Returns the contents of this node as markup.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_as_markup)(
		struct _cef_domnode_t* self);

	///
	// Returns the document associated with this node.
	///
	struct _cef_domdocument_t*(CEF_CALLBACK* get_document)(
		struct _cef_domnode_t* self);

	///
	// Returns the parent node.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_parent)(struct _cef_domnode_t* self);

	///
	// Returns the previous sibling node.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_previous_sibling)(
		struct _cef_domnode_t* self);

	///
	// Returns the next sibling node.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_next_sibling)(
		struct _cef_domnode_t* self);

	///
	// Returns true (1) if this node has child nodes.
	///
	int(CEF_CALLBACK* has_children)(struct _cef_domnode_t* self);

	///
	// Return the first child node.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_first_child)(
		struct _cef_domnode_t* self);

	///
	// Returns the last child node.
	///
	struct _cef_domnode_t*(CEF_CALLBACK* get_last_child)(
		struct _cef_domnode_t* self);

	// The following functions are valid only for element nodes.

	///
	// Returns the tag name of this element.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_element_tag_name)(
		struct _cef_domnode_t* self);

	///
	// Returns true (1) if this element has attributes.
	///
	int(CEF_CALLBACK* has_element_attributes)(struct _cef_domnode_t* self);

	///
	// Returns true (1) if this element has an attribute named |attrName|.
	///
	int(CEF_CALLBACK* has_element_attribute)(struct _cef_domnode_t* self,
		const cef_string_t* attrName);

	///
	// Returns the element attribute named |attrName|.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_element_attribute)(
		struct _cef_domnode_t* self,
		const cef_string_t* attrName);

	///
	// Returns a map of all element attributes.
	///
	void(CEF_CALLBACK* get_element_attributes)(struct _cef_domnode_t* self,
		cef_string_map_t attrMap);

	///
	// Set the value for the element attribute named |attrName|. Returns true (1)
	// on success.
	///
	int(CEF_CALLBACK* set_element_attribute)(struct _cef_domnode_t* self,
		const cef_string_t* attrName,
		const cef_string_t* value);

	///
	// Returns the inner text of the element.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_element_inner_text)(
		struct _cef_domnode_t* self);

	///
	// Returns the bounds of the element.
	///
	cef_rect_t(CEF_CALLBACK* get_element_bounds)(struct _cef_domnode_t* self);
} luacef_domnode;
