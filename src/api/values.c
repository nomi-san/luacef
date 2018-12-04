#include "../luacef.h"

#include "include/capi/cef_base_capi.h"

/*
	<bool> Value:IsValid()
*/
static int luacef_Value_IsValid(lua_State *L)
{
	cef_value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_valid(p));
	return 1;
}

/*
	<bool> Value:IsOwned()
*/
static int luacef_Value_IsOwned(lua_State *L)
{
	cef_value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_owned(p));
	return 1;
}

/*
	<bool> Value:IsReadOnly()
*/
static int luacef_Value_IsReadOnly(lua_State *L)
{
	cef_value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_read_only(p));
	return 1;
}

/*
	<bool> Value:IsSame(
		<Value> that
	)
*/
static int luacef_Value_IsSame(lua_State *L)
{
	cef_value_t *p = luacef_touserdata(L, 1);
	cef_value_t *that = luacef_checkudata(L, 2, __value__);

	lua_pushboolean(L, p->is_same(p, that));
	return 1;
}

/*
	<bool> Value:IsEqual(
		<Value> that
	)
*/
static int luacef_Value_IsEqual(lua_State *L)
{
	cef_value_t *p = luacef_touserdata(L, 1);
	cef_value_t *that = luacef_checkudata(L, 2, __value__);

	lua_pushboolean(L, p->is_equal(p, that));
	return 1;
}

/*
	<Value> Value:Copy()
*/
static int luacef_Value_Copy(lua_State *L)
{
	cef_value_t *p = luacef_touserdata(L, 1);

	cef_value_t *cop = p->copy(p);

	luacef_pushuserdata(L, cop, __value__);
	return 1;
}





cef_value_type_t(CEF_CALLBACK* get_type)(struct _cef_value_t* self);

int(CEF_CALLBACK* get_bool)(struct _cef_value_t* self);

int(CEF_CALLBACK* get_int)(struct _cef_value_t* self);

double(CEF_CALLBACK* get_double)(struct _cef_value_t* self);

cef_string_userfree_t(CEF_CALLBACK* get_string)(struct _cef_value_t* self);

struct _cef_binary_value_t*(CEF_CALLBACK* get_binary)(
	struct _cef_value_t* self);

struct _cef_dictionary_value_t*(CEF_CALLBACK* get_dictionary)(
	struct _cef_value_t* self);

struct _cef_list_value_t*(CEF_CALLBACK* get_list)(struct _cef_value_t* self);

int(CEF_CALLBACK* set_null)(struct _cef_value_t* self);

int(CEF_CALLBACK* set_bool)(struct _cef_value_t* self, int value);

int(CEF_CALLBACK* set_int)(struct _cef_value_t* self, int value);

int(CEF_CALLBACK* set_double)(struct _cef_value_t* self, double value);

int(CEF_CALLBACK* set_string)(struct _cef_value_t* self,
	const cef_string_t* value);

int(CEF_CALLBACK* set_binary)(struct _cef_value_t* self,
	struct _cef_binary_value_t* value);

int(CEF_CALLBACK* set_dictionary)(struct _cef_value_t* self,
	struct _cef_dictionary_value_t* value);

int(CEF_CALLBACK* set_list)(struct _cef_value_t* self,
	struct _cef_list_value_t* value);

/*
	<bool> Value:SetList(
		<ListValue> value
	)
*/
static int luacef_Value_SetList(lua_State *L)
{

}

// static member =============================

static int luacef_Value_Create(lua_State *L)
{
	cef_value_t *r = cef_value_create();

	luacef_pushuserdata(L, r, __value__);
	return 1;
}


// binary_value ==============================

	typedef struct luacef_binary_value {
		///
		// Base structure.
		///
		cef_base_ref_counted_t base;

		///
		// Returns true (1) if this object is valid. This object may become invalid if
		// the underlying data is owned by another object (e.g. list or dictionary)
		// and that other object is then modified or destroyed. Do not call any other
		// functions if this function returns false (0).
		///
		int(CEF_CALLBACK* is_valid)(struct _cef_binary_value_t* self);

		///
		// Returns true (1) if this object is currently owned by another object.
		///
		int(CEF_CALLBACK* is_owned)(struct _cef_binary_value_t* self);

		///
		// Returns true (1) if this object and |that| object have the same underlying
		// data.
		///
		int(CEF_CALLBACK* is_same)(struct _cef_binary_value_t* self,
			struct _cef_binary_value_t* that);

		///
		// Returns true (1) if this object and |that| object have an equivalent
		// underlying value but are not necessarily the same object.
		///
		int(CEF_CALLBACK* is_equal)(struct _cef_binary_value_t* self,
			struct _cef_binary_value_t* that);

		///
		// Returns a copy of this object. The data in this object will also be copied.
		///
		struct _cef_binary_value_t*(CEF_CALLBACK* copy)(
			struct _cef_binary_value_t* self);

		///
		// Returns the data size.
		///
		size_t(CEF_CALLBACK* get_size)(struct _cef_binary_value_t* self);

		///
		// Read up to |buffer_size| number of bytes into |buffer|. Reading begins at
		// the specified byte |data_offset|. Returns the number of bytes read.
		///
		size_t(CEF_CALLBACK* get_data)(struct _cef_binary_value_t* self,
			void* buffer,
			size_t buffer_size,
			size_t data_offset);
	} luacef_binary_value;


// static members ============================================

//CEF_EXPORT cef_binary_value_t* cef_binary_value_create(const void* data, size_t data_size);


	typedef struct luacef_dictionary_value {
		///
		// Base structure.
		///
		cef_base_ref_counted_t base;

		///
		// Returns true (1) if this object is valid. This object may become invalid if
		// the underlying data is owned by another object (e.g. list or dictionary)
		// and that other object is then modified or destroyed. Do not call any other
		// functions if this function returns false (0).
		///
		int(CEF_CALLBACK* is_valid)(struct _cef_dictionary_value_t* self);

		///
		// Returns true (1) if this object is currently owned by another object.
		///
		int(CEF_CALLBACK* is_owned)(struct _cef_dictionary_value_t* self);

		///
		// Returns true (1) if the values of this object are read-only. Some APIs may
		// expose read-only objects.
		///
		int(CEF_CALLBACK* is_read_only)(struct _cef_dictionary_value_t* self);

		///
		// Returns true (1) if this object and |that| object have the same underlying
		// data. If true (1) modifications to this object will also affect |that|
		// object and vice-versa.
		///
		int(CEF_CALLBACK* is_same)(struct _cef_dictionary_value_t* self,
			struct _cef_dictionary_value_t* that);

		///
		// Returns true (1) if this object and |that| object have an equivalent
		// underlying value but are not necessarily the same object.
		///
		int(CEF_CALLBACK* is_equal)(struct _cef_dictionary_value_t* self,
			struct _cef_dictionary_value_t* that);

		///
		// Returns a writable copy of this object. If |exclude_NULL_children| is true
		// (1) any NULL dictionaries or lists will be excluded from the copy.
		///
		struct _cef_dictionary_value_t*(CEF_CALLBACK* copy)(
			struct _cef_dictionary_value_t* self,
			int exclude_empty_children);

		///
		// Returns the number of values.
		///
		size_t(CEF_CALLBACK* get_size)(struct _cef_dictionary_value_t* self);

		///
		// Removes all values. Returns true (1) on success.
		///
		int(CEF_CALLBACK* clear)(struct _cef_dictionary_value_t* self);

		///
		// Returns true (1) if the current dictionary has a value for the given key.
		///
		int(CEF_CALLBACK* has_key)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Reads all keys for this dictionary into the specified vector.
		///
		int(CEF_CALLBACK* get_keys)(struct _cef_dictionary_value_t* self,
			cef_string_list_t keys);

		///
		// Removes the value at the specified key. Returns true (1) is the value was
		// removed successfully.
		///
		int(CEF_CALLBACK* remove)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value type for the specified key.
		///
		cef_value_type_t(CEF_CALLBACK* get_type)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key. For simple types the returned value
		// will copy existing data and modifications to the value will not modify this
		// object. For complex types (binary, dictionary and list) the returned value
		// will reference existing data and modifications to the value will modify
		// this object.
		///
		struct _cef_value_t*(CEF_CALLBACK* get_value)(
			struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type bool.
		///
		int(CEF_CALLBACK* get_bool)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type int.
		///
		int(CEF_CALLBACK* get_int)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type double.
		///
		double(CEF_CALLBACK* get_double)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type string.
		///
		// The resulting string must be freed by calling cef_string_userfree_free().
		cef_string_userfree_t(CEF_CALLBACK* get_string)(
			struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type binary. The returned value
		// will reference existing data.
		///
		struct _cef_binary_value_t*(CEF_CALLBACK* get_binary)(
			struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type dictionary. The returned
		// value will reference existing data and modifications to the value will
		// modify this object.
		///
		struct _cef_dictionary_value_t*(CEF_CALLBACK* get_dictionary)(
			struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Returns the value at the specified key as type list. The returned value
		// will reference existing data and modifications to the value will modify
		// this object.
		///
		struct _cef_list_value_t*(CEF_CALLBACK* get_list)(
			struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Sets the value at the specified key. Returns true (1) if the value was set
		// successfully. If |value| represents simple data then the underlying data
		// will be copied and modifications to |value| will not modify this object. If
		// |value| represents complex data (binary, dictionary or list) then the
		// underlying data will be referenced and modifications to |value| will modify
		// this object.
		///
		int(CEF_CALLBACK* set_value)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			struct _cef_value_t* value);

		///
		// Sets the value at the specified key as type null. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_null)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key);

		///
		// Sets the value at the specified key as type bool. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_bool)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			int value);

		///
		// Sets the value at the specified key as type int. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_int)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			int value);

		///
		// Sets the value at the specified key as type double. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_double)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			double value);

		///
		// Sets the value at the specified key as type string. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_string)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			const cef_string_t* value);

		///
		// Sets the value at the specified key as type binary. Returns true (1) if the
		// value was set successfully. If |value| is currently owned by another object
		// then the value will be copied and the |value| reference will not change.
		// Otherwise, ownership will be transferred to this object and the |value|
		// reference will be invalidated.
		///
		int(CEF_CALLBACK* set_binary)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			struct _cef_binary_value_t* value);

		///
		// Sets the value at the specified key as type dict. Returns true (1) if the
		// value was set successfully. If |value| is currently owned by another object
		// then the value will be copied and the |value| reference will not change.
		// Otherwise, ownership will be transferred to this object and the |value|
		// reference will be invalidated.
		///
		int(CEF_CALLBACK* set_dictionary)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			struct _cef_dictionary_value_t* value);

		///
		// Sets the value at the specified key as type list. Returns true (1) if the
		// value was set successfully. If |value| is currently owned by another object
		// then the value will be copied and the |value| reference will not change.
		// Otherwise, ownership will be transferred to this object and the |value|
		// reference will be invalidated.
		///
		int(CEF_CALLBACK* set_list)(struct _cef_dictionary_value_t* self,
			const cef_string_t* key,
			struct _cef_list_value_t* value);
	} luacef_dictionary_value;

/*
	<DictionaryValue> DictionaryValue.Create()
*/
static int luacef_DictionaryValue_Create(lua_State *L)
{
	cef_dictionary_value_t *r = cef_dictionary_value_create();

	luacef_pushuserdata(L, r, __dictionary_value__);
	return 1;
}


	typedef struct luacef_list_value {
		///
		// Base structure.
		///
		cef_base_ref_counted_t base;

		///
		// Returns true (1) if this object is valid. This object may become invalid if
		// the underlying data is owned by another object (e.g. list or dictionary)
		// and that other object is then modified or destroyed. Do not call any other
		// functions if this function returns false (0).
		///
		int(CEF_CALLBACK* is_valid)(struct _cef_list_value_t* self);

		///
		// Returns true (1) if this object is currently owned by another object.
		///
		int(CEF_CALLBACK* is_owned)(struct _cef_list_value_t* self);

		///
		// Returns true (1) if the values of this object are read-only. Some APIs may
		// expose read-only objects.
		///
		int(CEF_CALLBACK* is_read_only)(struct _cef_list_value_t* self);

		///
		// Returns true (1) if this object and |that| object have the same underlying
		// data. If true (1) modifications to this object will also affect |that|
		// object and vice-versa.
		///
		int(CEF_CALLBACK* is_same)(struct _cef_list_value_t* self,
			struct _cef_list_value_t* that);

		///
		// Returns true (1) if this object and |that| object have an equivalent
		// underlying value but are not necessarily the same object.
		///
		int(CEF_CALLBACK* is_equal)(struct _cef_list_value_t* self,
			struct _cef_list_value_t* that);

		///
		// Returns a writable copy of this object.
		///
		struct _cef_list_value_t*(CEF_CALLBACK* copy)(struct _cef_list_value_t* self);

		///
		// Sets the number of values. If the number of values is expanded all new
		// value slots will default to type null. Returns true (1) on success.
		///
		int(CEF_CALLBACK* set_size)(struct _cef_list_value_t* self, size_t size);

		///
		// Returns the number of values.
		///
		size_t(CEF_CALLBACK* get_size)(struct _cef_list_value_t* self);

		///
		// Removes all values. Returns true (1) on success.
		///
		int(CEF_CALLBACK* clear)(struct _cef_list_value_t* self);

		///
		// Removes the value at the specified index.
		///
		int(CEF_CALLBACK* remove)(struct _cef_list_value_t* self, size_t index);

		///
		// Returns the value type at the specified index.
		///
		cef_value_type_t(CEF_CALLBACK* get_type)(struct _cef_list_value_t* self,
			size_t index);

		///
		// Returns the value at the specified index. For simple types the returned
		// value will copy existing data and modifications to the value will not
		// modify this object. For complex types (binary, dictionary and list) the
		// returned value will reference existing data and modifications to the value
		// will modify this object.
		///
		struct _cef_value_t*(CEF_CALLBACK* get_value)(struct _cef_list_value_t* self,
			size_t index);

		///
		// Returns the value at the specified index as type bool.
		///
		int(CEF_CALLBACK* get_bool)(struct _cef_list_value_t* self, size_t index);

		///
		// Returns the value at the specified index as type int.
		///
		int(CEF_CALLBACK* get_int)(struct _cef_list_value_t* self, size_t index);

		///
		// Returns the value at the specified index as type double.
		///
		double(CEF_CALLBACK* get_double)(struct _cef_list_value_t* self,
			size_t index);

		///
		// Returns the value at the specified index as type string.
		///
		// The resulting string must be freed by calling cef_string_userfree_free().
		cef_string_userfree_t(
			CEF_CALLBACK* get_string)(struct _cef_list_value_t* self, size_t index);

		///
		// Returns the value at the specified index as type binary. The returned value
		// will reference existing data.
		///
		struct _cef_binary_value_t*(
			CEF_CALLBACK* get_binary)(struct _cef_list_value_t* self, size_t index);

		///
		// Returns the value at the specified index as type dictionary. The returned
		// value will reference existing data and modifications to the value will
		// modify this object.
		///
		struct _cef_dictionary_value_t*(CEF_CALLBACK* get_dictionary)(
			struct _cef_list_value_t* self,
			size_t index);

		///
		// Returns the value at the specified index as type list. The returned value
		// will reference existing data and modifications to the value will modify
		// this object.
		///
		struct _cef_list_value_t*(
			CEF_CALLBACK* get_list)(struct _cef_list_value_t* self, size_t index);

		///
		// Sets the value at the specified index. Returns true (1) if the value was
		// set successfully. If |value| represents simple data then the underlying
		// data will be copied and modifications to |value| will not modify this
		// object. If |value| represents complex data (binary, dictionary or list)
		// then the underlying data will be referenced and modifications to |value|
		// will modify this object.
		///
		int(CEF_CALLBACK* set_value)(struct _cef_list_value_t* self,
			size_t index,
			struct _cef_value_t* value);

		///
		// Sets the value at the specified index as type null. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_null)(struct _cef_list_value_t* self, size_t index);

		///
		// Sets the value at the specified index as type bool. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_bool)(struct _cef_list_value_t* self,
			size_t index,
			int value);

		///
		// Sets the value at the specified index as type int. Returns true (1) if the
		// value was set successfully.
		///
		int(CEF_CALLBACK* set_int)(struct _cef_list_value_t* self,
			size_t index,
			int value);

		///
		// Sets the value at the specified index as type double. Returns true (1) if
		// the value was set successfully.
		///
		int(CEF_CALLBACK* set_double)(struct _cef_list_value_t* self,
			size_t index,
			double value);

		///
		// Sets the value at the specified index as type string. Returns true (1) if
		// the value was set successfully.
		///
		int(CEF_CALLBACK* set_string)(struct _cef_list_value_t* self,
			size_t index,
			const cef_string_t* value);

		///
		// Sets the value at the specified index as type binary. Returns true (1) if
		// the value was set successfully. If |value| is currently owned by another
		// object then the value will be copied and the |value| reference will not
		// change. Otherwise, ownership will be transferred to this object and the
		// |value| reference will be invalidated.
		///
		int(CEF_CALLBACK* set_binary)(struct _cef_list_value_t* self,
			size_t index,
			struct _cef_binary_value_t* value);

		///
		// Sets the value at the specified index as type dict. Returns true (1) if the
		// value was set successfully. If |value| is currently owned by another object
		// then the value will be copied and the |value| reference will not change.
		// Otherwise, ownership will be transferred to this object and the |value|
		// reference will be invalidated.
		///
		int(CEF_CALLBACK* set_dictionary)(struct _cef_list_value_t* self,
			size_t index,
			struct _cef_dictionary_value_t* value);

		///
		// Sets the value at the specified index as type list. Returns true (1) if the
		// value was set successfully. If |value| is currently owned by another object
		// then the value will be copied and the |value| reference will not change.
		// Otherwise, ownership will be transferred to this object and the |value|
		// reference will be invalidated.
		///
		int(CEF_CALLBACK* set_list)(struct _cef_list_value_t* self,
			size_t index,
			struct _cef_list_value_t* value);
	} luacef_list_value;


// static members ===================================

/*
	<ListValue> ListValue.Create()
*/
static int luacef_ListValue_Create(lua_State *L)
{
	cef_list_value_t *r = cef_list_value_create();

	luacef_pushuserdata(L, r, __list_value__);
	return 1;
}