#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_frame_capi.h"
#include "include/capi/cef_task_capi.h"

struct _cef_v8exception_t;
struct _cef_v8handler_t;
struct _cef_v8stack_frame_t;
struct _cef_v8value_t;

//      ___ 
//  _ _| . |
// | | | . |
//  \_/|___|
//===========

/*
	<TaskRunner> V8Context:GetTaskRunner()
*/
static int luacef_v8context_get_task_runner(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	cef_task_runner_t *p2 = p->get_task_runner(p);

	luacef_pushuserdata(L, p2, __task_runner__);
	return 1;
}

/*
	<bool>	V8Context:IsValid()
*/
static int luacef_v8context_is_valid(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_valid(p));
	return 1;
}

/*
	<Browser> V8Context:GetBrowser()
*/
static int luacef_v8context_get_browser(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	cef_browser_t *p2 = p->get_browser(p);

	luacef_pushuserdata(L, p2, __browser__);
	return 1;
}

/*
	<Frame> V8Context:GetFrame()
*/
static int luacef_v8context_get_frame(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	cef_frame_t *p2 = p->get_frame(p);

	luacef_pushuserdata(L, p2, __frame__);
	return 1;
}

/*
	<V8Value> V8Context:GetGlobal()
*/
static int luacef_v8context_get_global(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	cef_v8value_t *p2 = p->get_global(p);

	luacef_pushuserdata(L, p2, __v8value__);
	return 1;
}

/*
	<int> V8Context:Enter()
*/
static int luacef_v8context_enter(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->enter(p));
	return 1;
}

/*
	<int> V8Context:Exit()
*/
static int luacef_v8context_exit(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->exit(p));
	return 1;
}

/*
	<bool> V8Context:IsSame(
		<V8Context>	that
	)
*/
static int luacef_v8context_is_same(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);
	cef_v8context_t *p2 = luacef_checkudata(L, 2, __v8context__);

	lua_pushboolean(L, p->is_same(p, p2));
	return 1;
}

/*
	<int> V8Context:Eval(
		<str>			code,
		<str>			script_url,
		<int>			start_line,
		<V8Value>		retval,
		<V8Excaption>	exception
	)
*/
static int luacef_v8context_eval(lua_State *L)
{
	cef_v8context_t *p = luacef_touserdata(L, 1);
	cef_string_t s1 = luacef_tostring(L, 2);
	cef_string_t s2 = luacef_tostring(L, 3);
	int i = lua_tointeger(L, 4);
	cef_v8value_t *rv = luacef_checkudata(L, 5, __v8value__);
	cef_v8exception_t *e = luacef_checkudata(L, 6, __v8exception__);

	int r = p->eval(p, &s1, &s2, i, &rv, &e);

	lua_pushinteger(L, r);
	return 1;
}

static const luaL_Reg luacef_v8context_m[] = {
	{ "GetTaskRunner", luacef_v8context_get_task_runner },
	{ "IsValid", luacef_v8context_is_valid },
	{ "GetBrowser", luacef_v8context_get_browser },
	{ "GetFrame", luacef_v8context_get_frame },
	{ "GetGlobal", luacef_v8context_get_global },
	{ "Enter", luacef_v8context_enter },
	{ "Exit", luacef_v8context_exit },
	{ "IsSame", luacef_v8context_is_same },
	{ "Eval", luacef_v8context_eval },
	{ NULL, NULL}
};

/*
	<V8Context> V8Context.GetCurrentContext()
*/
static int luacef_v8context_get_current_context(lua_State *L)
{
	cef_v8context_t *p = cef_v8context_get_current_context();

	luacef_pushuserdata(L, p, __v8context__);
	return 1;
}

/*
	<V8Context> V8Context.GetEnteredContext()
*/
static int luacef_v8context_get_entered_context(lua_State *L)
{
	cef_v8context_t *p = cef_v8context_get_entered_context();

	luacef_pushuserdata(L, p, __v8context__);
	return 1;
}

/*
	<bool> V8Context.GetEnteredContext()
*/
static int luacef_v8context_in_context(lua_State *L)
{
	lua_pushboolean(L, cef_v8context_in_context());
	return 1;
}

// v8handler /////////////////////////////////
//////////////////////////////////////

// owned
typedef struct luacef_v8handler {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* execute)(struct luacef_v8handler* self,
		const cef_string_t* name,
		struct _cef_v8value_t* object,
		size_t argumentsCount,
		struct _cef_v8value_t* const* arguments,
		struct _cef_v8value_t** retval,
		cef_string_t* exception);

	lua_State *L;
	int ref;

} luacef_v8handler;

int CEF_CALLBACK v8h_execute(
	struct luacef_v8handler*	self,
	const cef_string_t*			name,
	struct _cef_v8value_t*		object,
	size_t						argumentsCount,
	struct _cef_v8value_t* const* arguments,
	struct _cef_v8value_t**		retval,
	cef_string_t*				exception)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __execute)) {

		luacef_pushuserdata(self->L, self, __v8handler__); // self, 1

		luacef_pushstring(self->L, name); // 2

		luacef_pushuserdata(self->L, object, __v8value__); // 3

		lua_pushinteger(self->L, argumentsCount); // 4

		luacef_pushuserdata(self->L, arguments, __v8value__); // 5

		luacef_pushuserdata(self->L, *retval, __v8value__); // 6

		luacef_pushstring(self->L, exception); // 7

		lua_pcall(self->L, 7, 1, 8); // call

		return lua_tonumber(self->L, -1);
	}

	return 0;
}

static int luacef_v8handler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_v8handler);
	luacef_v8handler *p = luacef_alloc(sz);
	p->base.size = sz;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __execute))
			p->execute = v8h_execute;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __v8handler__);
	return 1;
}

static int luacef_v8handler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_v8handler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_v8handler_index(lua_State *L)
{
	luacef_v8handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_v8handler_release);

	else if (!strcmp(i, __execute))
		lua_getfield(L, -1, __execute);

	else return 0;

	return 1;
}

static int luacef_v8handler_newindex(lua_State *L)
{
	luacef_v8handler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __execute)) {
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, __execute);
		p->execute = v8h_execute;
	}

	return 0;
}

static const luaL_Reg luacef_v8handler_m[] = {
	// gc
	{ "index", luacef_v8handler_index },
	{ "newindex", luacef_v8handler_newindex },
	{ NULL, NULL}
};




/////////////////////////////////////////////
////////////////////////////////////////////



///
// Structure that should be implemented to handle V8 accessor calls. Accessor
// identifiers are registered by calling cef_v8value_t::set_value(). The
// functions of this structure will be called on the thread associated with the
// V8 accessor.
///
typedef struct __v8accessor_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Handle retrieval the accessor value identified by |name|. |object| is the
	// receiver ('this' object) of the accessor. If retrieval succeeds set
	// |retval| to the return value. If retrieval fails set |exception| to the
	// exception that will be thrown. Return true (1) if accessor retrieval was
	// handled.
	///
	int(CEF_CALLBACK* get)(struct _cef_v8accessor_t* self,
		const cef_string_t* name,
		struct _cef_v8value_t* object,
		struct _cef_v8value_t** retval,
		cef_string_t* exception);

	///
	// Handle assignment of the accessor value identified by |name|. |object| is
	// the receiver ('this' object) of the accessor. |value| is the new value
	// being assigned to the accessor. If assignment fails set |exception| to the
	// exception that will be thrown. Return true (1) if accessor assignment was
	// handled.
	///
	int(CEF_CALLBACK* set)(struct _cef_v8accessor_t* self,
		const cef_string_t* name,
		struct _cef_v8value_t* object,
		struct _cef_v8value_t* value,
		cef_string_t* exception);
} _v8accessor_t;

///
// Structure that should be implemented to handle V8 interceptor calls. The
// functions of this structure will be called on the thread associated with the
// V8 interceptor. Interceptor's named property handlers (with first argument of
// type CefString) are called when object is indexed by string. Indexed property
// handlers (with first argument of type int) are called when object is indexed
// by integer.
///
typedef struct __v8interceptor_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Handle retrieval of the interceptor value identified by |name|. |object| is
	// the receiver ('this' object) of the interceptor. If retrieval succeeds, set
	// |retval| to the return value. If the requested value does not exist, don't
	// set either |retval| or |exception|. If retrieval fails, set |exception| to
	// the exception that will be thrown. If the property has an associated
	// accessor, it will be called only if you don't set |retval|. Return true (1)
	// if interceptor retrieval was handled, false (0) otherwise.
	///
	int(CEF_CALLBACK* get_byname)(struct _cef_v8interceptor_t* self,
		const cef_string_t* name,
		struct _cef_v8value_t* object,
		struct _cef_v8value_t** retval,
		cef_string_t* exception);

	///
	// Handle retrieval of the interceptor value identified by |index|. |object|
	// is the receiver ('this' object) of the interceptor. If retrieval succeeds,
	// set |retval| to the return value. If the requested value does not exist,
	// don't set either |retval| or |exception|. If retrieval fails, set
	// |exception| to the exception that will be thrown. Return true (1) if
	// interceptor retrieval was handled, false (0) otherwise.
	///
	int(CEF_CALLBACK* get_byindex)(struct _cef_v8interceptor_t* self,
		int index,
		struct _cef_v8value_t* object,
		struct _cef_v8value_t** retval,
		cef_string_t* exception);

	///
	// Handle assignment of the interceptor value identified by |name|. |object|
	// is the receiver ('this' object) of the interceptor. |value| is the new
	// value being assigned to the interceptor. If assignment fails, set
	// |exception| to the exception that will be thrown. This setter will always
	// be called, even when the property has an associated accessor. Return true
	// (1) if interceptor assignment was handled, false (0) otherwise.
	///
	int(CEF_CALLBACK* set_byname)(struct _cef_v8interceptor_t* self,
		const cef_string_t* name,
		struct _cef_v8value_t* object,
		struct _cef_v8value_t* value,
		cef_string_t* exception);

	///
	// Handle assignment of the interceptor value identified by |index|. |object|
	// is the receiver ('this' object) of the interceptor. |value| is the new
	// value being assigned to the interceptor. If assignment fails, set
	// |exception| to the exception that will be thrown. Return true (1) if
	// interceptor assignment was handled, false (0) otherwise.
	///
	int(CEF_CALLBACK* set_byindex)(struct _cef_v8interceptor_t* self,
		int index,
		struct _cef_v8value_t* object,
		struct _cef_v8value_t* value,
		cef_string_t* exception);
} _v8interceptor_t;

///
// Structure representing a V8 exception. The functions of this structure may be
// called on any render process thread.
///
typedef struct __v8exception_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Returns the exception message.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_message)(
		struct _cef_v8exception_t* self);

	///
	// Returns the line of source code that the exception occurred within.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_source_line)(
		struct _cef_v8exception_t* self);

	///
	// Returns the resource name for the script from where the function causing
	// the error originates.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_script_resource_name)(
		struct _cef_v8exception_t* self);

	///
	// Returns the 1-based number of the line where the error occurred or 0 if the
	// line number is unknown.
	///
	int(CEF_CALLBACK* get_line_number)(struct _cef_v8exception_t* self);

	///
	// Returns the index within the script of the first character where the error
	// occurred.
	///
	int(CEF_CALLBACK* get_start_position)(struct _cef_v8exception_t* self);

	///
	// Returns the index within the script of the last character where the error
	// occurred.
	///
	int(CEF_CALLBACK* get_end_position)(struct _cef_v8exception_t* self);

	///
	// Returns the index within the line of the first character where the error
	// occurred.
	///
	int(CEF_CALLBACK* get_start_column)(struct _cef_v8exception_t* self);

	///
	// Returns the index within the line of the last character where the error
	// occurred.
	///
	int(CEF_CALLBACK* get_end_column)(struct _cef_v8exception_t* self);
} _v8exception_t;


// v8value =====================================================================


/*
	<bool> V8Value:IsValid()
*/
static int luacef_v8value_is_valid(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_valid(p));
	return 1;
}

/*
	<bool> V8Value:IsUndefined()
*/
static int luacef_v8value_is_undefined(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_undefined(p));
	return 1;
}

/*
	<bool> V8Value:IsNull()
*/
static int luacef_v8value_is_null(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_null(p));
	return 1;
}

/*
	<bool> V8Value:IsBool()
*/
static int luacef_v8value_is_bool(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_bool(p));
	return 1;
}

/*
	<bool> V8Value:IsInt()
*/
static int luacef_v8value_is_int(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_int(p));
	return 1;
}

/*
	<bool> V8Value:IsUInt()
*/
static int luacef_v8value_is_uint(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_uint(p));
	return 1;
}

/*
	<bool> V8Value:IsDouble()
*/
static int luacef_v8value_is_double(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_double(p));
	return 1;
}

/*
	<bool> V8Value:IsDate()
*/
static int luacef_v8value_is_date(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_date(p));
	return 1;
}

/*
	<bool> V8Value:IsString()
*/
static int luacef_v8value_is_string(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_string(p));
	return 1;
}

/*
	<bool> V8Value:IsObject()
*/
static int luacef_v8value_is_object(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_object(p));
	return 1;
}

/*
	<bool> V8Value:IsArray()
*/
static int luacef_v8value_is_array(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_array(p));
	return 1;
}

/*
	<bool> V8Value:IsFunction()
*/
static int luacef_v8value_is_function(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_function(p));
	return 1;
}

/*
	<bool> V8Value:IsSame(
		<V8Value>	that
	)
*/
static int luacef_v8value_is_same(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);
	cef_v8value_t *p2 = luacef_checkudata(L, 2, __v8value__);

	lua_pushboolean(L, p->is_same(p, p2));
	return 1;
}

/*
	<bool> V8Value:GetBoolValue()
*/
static int luacef_v8value_get_bool_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->get_bool_value(p));
	return 1;
}

/*
	<int> V8Value:GetIntValue()
*/
static int luacef_v8value_get_int_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_int_value(p));
	return 1;
}

/*
	<uint> V8Value:GetUIntValue()
*/
static int luacef_v8value_get_uint_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_uint_value(p));
	return 1;
}

/*
	<double> V8Value:GetDoubleValue()
*/
static int luacef_v8value_get_double_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushnumber(L, p->get_double_value(p));
	return 1;
}

/*
	<Time> V8Value:GetDateValue()
*/
static int luacef_v8value_get_date_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_time_t t = p->get_date_value(p);

	luacef_pushuserdata(L, &t, __time__);
	return 1;
}

/*
	<str> V8Value:GetStringValue()
*/
static int luacef_v8value_get_string_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_string_value(p);

	luacef_pushstring(L, s);
	return 1;
}

/*
	<bool> V8Value:IsUserCreated()
*/
static int luacef_v8value_is_user_created(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_user_created(p));
	return 1;
}

/*
	<bool> V8Value:()
*/
static int luacef_v8value_has_exception(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->has_exception(p));
	return 1;
}

/*
	<V8Exception> V8Value:GetException()
*/
static int luacef_v8value_get_exception(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_v8exception_t *e = p->get_exception(p);

	luacef_pushuserdata(L, e, __v8exception__);
	return 1;
}

/*
	<int> V8Value:ClearException()
*/
static int luacef_v8value_clear_exception(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->clear_exception(p));
	return 1;
}

/*
	<int> V8Value:WillRethrowExceptions()
*/
static int luacef_v8value_will_rethrow_exceptions(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->will_rethrow_exceptions(p));
	return 1;
}

/*
	<int> V8Value:SetRethrowExceptions(
		<int>	rethrow
	)
*/
static int luacef_v8value_set_rethrow_exceptions(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);
	int i = lua_tointeger(L, 2);

	int r = p->set_rethrow_exceptions(p, i);

	lua_pushinteger(L, r);
	return 1;
}

/////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

/*
	<bool> V8Value:HasValue(
		<str> key
	)

	<bool> V8Value:HasValue(
		<int> index	
	)
*/
static int luacef_v8value_has_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	if (lua_isstring(L, 2)) {
		cef_string_t s = luacef_tostring(L, 2);
		lua_pushboolean(L, p->has_value_bykey(p, &s));
	}
	else if (lua_isnumber(L, 2)) {
		int i = lua_tointeger(L, 2);
		lua_pushboolean(L, p->has_value_byindex(p, i));
	}
	else return 0;

	return 1;
}

/*
	<int> V8Value:DeleteValue(
		<str> key
	)

	<int> V8Value:DeleteValue(
		<int> index
	)
*/
static int luacef_v8value_delete_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	if (lua_isstring(L, 2)) {
		cef_string_t s = luacef_tostring(L, 2);
		lua_pushinteger(L, p->delete_value_bykey(p, &s));
	}
	else if (lua_isnumber(L, 2)) {
		int i = lua_tointeger(L, 2);
		lua_pushinteger(L, p->delete_value_byindex(p, i));
	}
	else return 0;

	return 1;
}

/*
	<V8Value> V8Value:GetValue(
		<str> key
	)

	<V8Value> V8Value:GetValue(
		<int> index
	)
*/
static int luacef_v8value_get_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_v8value_t *r = NULL;

	if (lua_isstring(L, 2)) {
		cef_string_t s = luacef_tostring(L, 2);
		r = p->get_value_bykey(p, &s);
	}
	else if (lua_isnumber(L, 2)) {
		int i = lua_tointeger(L, 2);
		r = p->get_value_byindex(p, i);
	}
	else return 0;

	luacef_pushuserdata(L, r, __v8value__);
	return 1;
}

/*
	<int> V8Value:SetValue(
		<str>		key,
		<V8Value>	value,
		<int>		attribute
	)

	<int> V8Value:SetValue(
		<int>		index,
		<V8Value>	value,
	)

	<int> V8Value:SetValue(
		<str>		key,
		<int>		settings,
		<int>		attribute
	)
*/
static int luacef_v8value_set_value(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	if (lua_isstring(L, 2)) {
		cef_string_t s = luacef_tostring(L, 2);
		cef_v8value_t *p2 = luacef_touserdata(L, 3);
		int a = lua_tointeger(L, 4);

		lua_pushinteger(L, p->set_value_bykey(p, &s, p2, a));
	}
	else if (lua_isnumber(L, 2)) {
		int i = lua_tointeger(L, 2);
		cef_v8value_t *p2 = luacef_touserdata(L, 3);

		lua_pushinteger(L, p->set_value_byindex(p, i, p2));
	}
	else {
		cef_string_t s = luacef_tostring(L, 2);
		int i = lua_tointeger(L, 3);
		int i2 = lua_tointeger(L, 4);

		lua_pushinteger(L, p->set_value_byaccessor(p, &s, i, i2));
	}

	return 1;
}

//////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int(CEF_CALLBACK* get_keys)(struct _cef_v8value_t* self,
		cef_string_list_t keys);
/*
	<> V8Value:()
*/
static int luacef_v8value_get_keys(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	// todo

	return 1;
}

/*
	<int> V8Value:SetUserData(
		<Base>	user_data
	)
*/
static int luacef_v8value_set_user_data(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);
	cef_base_ref_counted_t *u = luacef_checkudata(L, 2, __base__);

	int ret = p->set_user_data(p, u);

	lua_pushinteger(L, ret);
	return 1;
}

/*
	<Base> V8Value:GetUserData()
*/
static int luacef_v8value_get_user_data(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_base_ref_counted_t *r = p->get_user_data(p);

	luacef_pushuserdata(L, r, __base__);
	return 1;
}

/*
	<int> V8Value:GetExternallyAllocatedMemory()
*/
static int luacef_v8value_get_externally_allocated_memory(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_externally_allocated_memory(p));
	return 1;
}

/*
	<int> V8Value:AdjustExternallyAllocatedMemory(
		<int>	change_in_bytes
	)
*/
static int luacef_v8value_adjust_externally_allocated_memory(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);
	int i = lua_tointeger(L, 2);

	lua_pushinteger(L, p->adjust_externally_allocated_memory(p, i));
	return 1;
}

/*
	<int> V8Value:GetArrayLength()
*/
static int luacef_v8value_get_array_length(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_array_length(p));
	return 1;
}

/*
	<str> V8Value:GetFunctionName()
*/
static int luacef_v8value_get_function_name(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_string_t *s = p->get_function_name(p);

	luacef_pushstring(L, s);
	return 1;
}

/*
	<V8Handler> V8Value:GetFunctionHandler()
*/
static int luacef_v8value_get_function_handler(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);

	cef_v8handler_t *r = p->get_function_handler(p);

	luacef_pushuserdata(L, r, __v8handler__);
	return 1;
}

/*
	<V8Value> V8Value:ExecuteFunction(
		<V8Value>	object,
		<int>		argumentsCount,
		<V8Value>	arguments
	)
*/
static int luacef_v8value_execute_function(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);
	cef_v8value_t *o = luacef_checkudata(L, 2, __v8value__);
	int c = lua_tointeger(L, 3);
	cef_v8value_t *a  = luacef_checkudata(L, 4, __v8value__);

	cef_v8value_t *r = p->execute_function(p, o, c, a);

	luacef_pushuserdata(L, r, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value:ExecuteFunctionWithContext(
		<V8Context>	context,
		<V8Value>	object,
		<int>		argumentsCount,
		<V8Value>	arguments
	)
*/
static int luacef_v8value_execute_function_with_context(lua_State* L)
{
	cef_v8value_t *p = luacef_touserdata(L, 1);
	cef_v8context_t *ctx = luacef_checkudata(L, 2, __v8context__);
	cef_v8value_t *o = luacef_checkudata(L, 3, __v8value__);
	int c = lua_tointeger(L, 4);
	cef_v8value_t *a = luacef_checkudata(L, 5, __v8value__);

	cef_v8value_t *r = p->execute_function_with_context(p, ctx, o, c, a);

	luacef_pushuserdata(L, r, __v8value__);
	return 1;
}

// static function ========================================

/*
	<V8Value> V8Value.CreateUndefined()
*/
static int luacef_v8value_create_undefined(lua_State *L)
{
	cef_v8value_t *p = cef_v8value_create_undefined();

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateNull()
*/
static int luacef_v8value_create_null(lua_State *L)
{
	cef_v8value_t *p = cef_v8value_create_null();

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateBool(
		<bool>	value
	)
*/
static int luacef_v8value_create_bool(lua_State *L)
{
	int i = lua_tointeger(L, 1);

	cef_v8value_t *p = cef_v8value_create_bool(i);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateInt(
		<int>	value
	)
*/
static int luacef_v8value_create_int(lua_State *L)
{
	int i = lua_tointeger(L, 1);

	cef_v8value_t *p = cef_v8value_create_int(i);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateUInt(
		<int>	value
	)
*/
static int luacef_v8value_create_uint(lua_State *L)
{
	unsigned int i = lua_tointeger(L, 1);

	cef_v8value_t *p = cef_v8value_create_uint(i);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateDouble(
		<double>	value
	)
*/
static int luacef_v8value_create_double(lua_State *L)
{
	double i = lua_tonumber(L, 1);

	cef_v8value_t *p = cef_v8value_create_double(i);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateDate(
		<Time>	date
	)
*/
static int luacef_v8value_create_date(lua_State *L)
{
	cef_time_t *t = luacef_checkudata(L, 1, __time__);

	cef_v8value_t *p = cef_v8value_create_date(&t);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateString(
		<str>	value
	)
*/
static int luacef_v8value_create_string(lua_State *L)
{
	cef_string_t s = luacef_tostring(L, 1);

	cef_v8value_t *p = cef_v8value_create_string(&s);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateObject(
		<V8Accessor>	accessor,
		<V8Interceptor>	interceptor
	)
*/
static int luacef_v8value_create_object(lua_State *L)
{
	cef_v8accessor_t *p = luacef_checkudata(L, 1, __v8accessor__);
	cef_v8interceptor_t *p2 = luacef_checkudata(L, 2, __v8interceptor__);

	cef_v8value_t *p3 = cef_v8value_create_object(p, p2);

	luacef_pushuserdata(L, p3, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateArray(
		<int>	length
	)
*/
static int luacef_v8value_create_array(lua_State *L)
{
	int i = lua_tointeger(L, 1);

	cef_v8value_t *p = cef_v8value_create_array(i);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

/*
	<V8Value> V8Value.CreateFunction(
		<str>		name,
		<V8Handler>	handler
	)
*/
static int luacef_v8value_create_function(lua_State *L)
{
	cef_string_t s = luacef_tostring(L, 1);
	cef_v8handler_t *p1 = luacef_checkudata(L, 2, __v8handler__);

	cef_v8value_t *p = cef_v8value_create_function(&s, p1);

	luacef_pushuserdata(L, p, __v8value__);
	return 1;
}

static const luaL_Reg luacef_v8value_m[] = {
	{ "IsValid", luacef_v8value_is_valid },
	{ "IsUndefined", luacef_v8value_is_undefined },
	{ "IsNull", luacef_v8value_is_null },
	{ "IsBool", luacef_v8value_is_bool },
	{ "IsInt", luacef_v8value_is_int },
	{ "IsUInt", luacef_v8value_is_uint },
	{ "IsDouble", luacef_v8value_is_double },
	{ "IsDate", luacef_v8value_is_date },
	{ "IsString", luacef_v8value_is_string },
	{ "IsObject", luacef_v8value_is_object },
	{ "IsArray", luacef_v8value_is_array },
	{ "IsFunction", luacef_v8value_is_function },
	{ "IsSame", luacef_v8value_is_same },
	{ "GetBoolValue", luacef_v8value_get_bool_value },
	{ "GetIntValue", luacef_v8value_get_int_value },
	{ "GetUintValue", luacef_v8value_get_uint_value },
	{ "GetDoubleValue", luacef_v8value_get_double_value },
	{ "GetDateValue", luacef_v8value_get_date_value },
	{ "GetStringValue", luacef_v8value_get_string_value },
	{ "IsUserCreated", luacef_v8value_is_user_created },
	{ "HasException", luacef_v8value_has_exception },
	{ "GetException", luacef_v8value_get_exception },
	{ "ClearException", luacef_v8value_clear_exception },
	{ "WillRethrowExceptions", luacef_v8value_will_rethrow_exceptions },
	{ "SetRethrowExceptions", luacef_v8value_set_rethrow_exceptions },
	{ "HasValue", luacef_v8value_has_value },
	{ "DeleteValue", luacef_v8value_delete_value },
	{ "GetValue", luacef_v8value_get_value },
	{ "SetValue", luacef_v8value_set_value },
	{ "GetKeys", luacef_v8value_get_keys },
	{ "SetUserData", luacef_v8value_set_user_data },
	{ "GetUserData", luacef_v8value_get_user_data },
	{ "GetExternallyAllocatedMemory", luacef_v8value_get_externally_allocated_memory },
	{ "AdjustExternallyAllocatedMemory", luacef_v8value_adjust_externally_allocated_memory },
	{ "GetArrayLength", luacef_v8value_get_array_length },
	{ "GetFunctionName", luacef_v8value_get_function_name },
	{ "GetFunctionHandler", luacef_v8value_get_function_handler },
	{ "ExecuteFunction", luacef_v8value_execute_function },
	{ "ExecuteFunctionWithContext", luacef_v8value_execute_function_with_context },

	/// static

	{ "CreateUndefined", luacef_v8value_create_undefined },
	{ "CreateNull", luacef_v8value_create_null },
	{ "CreateBool", luacef_v8value_create_bool },
	{ "CreateInt", luacef_v8value_create_int },
	{ "CreateUInt", luacef_v8value_create_uint },
	{ "CreateDouble", luacef_v8value_create_double },
	{ "CreateDate", luacef_v8value_create_date },
	{ "CreateString", luacef_v8value_create_string },
	{ "CreateObject", luacef_v8value_create_object },
	{ "CreateArray", luacef_v8value_create_array },
	{ "CreateFunction", luacef_v8value_create_function },

	{ NULL, NULL }
};

static const luaL_Reg luacef_v8value_ms[] = {
	{ "CreateUndefined", luacef_v8value_create_undefined },
	{ "CreateNull", luacef_v8value_create_null },
	{ "CreateBool", luacef_v8value_create_bool },
	{ "CreateInt", luacef_v8value_create_int },
	{ "CreateUInt", luacef_v8value_create_uint },
	{ "CreateDouble", luacef_v8value_create_double },
	{ "CreateDate", luacef_v8value_create_date },
	{ "CreateString", luacef_v8value_create_string },
	{ "CreateObject", luacef_v8value_create_object },
	{ "CreateArray", luacef_v8value_create_array },
	{ "CreateFunction", luacef_v8value_create_function },
	{ NULL, NULL}
};

// v8stack_trace ===================================================================

/*
	<bool> V8StackTrace:IsValid()
*/
static int luacef_v8stack_trace_is_valid(lua_State *L)
{
	cef_v8stack_trace_t *p = luacef_touserdata(L, 1);

	lua_pushboolean(L, p->is_valid(p));
	return 1;
}

/*
	<int> V8StackTrace:GetFrameCount()
*/
static int luacef_v8stack_trace_get_frame_count(lua_State *L)
{
	cef_v8stack_trace_t *p = luacef_touserdata(L, 1);

	lua_pushinteger(L, p->get_frame_count(p));
	return 1;
}

/*
	<Frame> V8StackTrace:GetFrame(
		<int>	index
	)
*/
static int luacef_v8stack_trace_get_frame(lua_State *L)
{
	cef_v8stack_trace_t *p = luacef_touserdata(L, 1);
	int i = lua_tointeger(L, 2);

	cef_frame_t *fr = p->get_frame(p, i);

	lua_pushinteger(L, fr);
	return 1;
}

// ============= static

/*
	<V8StackTrace> V8StackTrace.GetCurrent(
		<int>	frame_limit
	)
*/
static int luacef_v8stack_trace_get_current(lua_State *L)
{
	int i = lua_tointeger(L, 1);

	cef_v8stack_trace_t *p = cef_v8stack_trace_get_current(i);

	luacef_pushuserdata(L, p, __v8stack_trace__);
	return 1;
}

///
// Structure representing a V8 stack frame handle. V8 handles can only be
// accessed from the thread on which they are created. Valid threads for
// creating a V8 handle include the render process main thread (TID_RENDERER)
// and WebWorker threads. A task runner for posting tasks on the associated
// thread can be retrieved via the cef_v8context_t::get_task_runner() function.
///
typedef struct __v8stack_frame_t {
	///
	// Base structure.
	///
	cef_base_ref_counted_t base;

	///
	// Returns true (1) if the underlying handle is valid and it can be accessed
	// on the current thread. Do not call any other functions if this function
	// returns false (0).
	///
	int(CEF_CALLBACK* is_valid)(struct _cef_v8stack_frame_t* self);

	///
	// Returns the name of the resource script that contains the function.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_script_name)(
		struct _cef_v8stack_frame_t* self);

	///
	// Returns the name of the resource script that contains the function or the
	// sourceURL value if the script name is undefined and its source ends with a
	// "//@ sourceURL=..." string.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_script_name_or_source_url)(
		struct _cef_v8stack_frame_t* self);

	///
	// Returns the name of the function.
	///
	// The resulting string must be freed by calling cef_string_userfree_free().
	cef_string_userfree_t(CEF_CALLBACK* get_function_name)(
		struct _cef_v8stack_frame_t* self);

	///
	// Returns the 1-based line number for the function call or 0 if unknown.
	///
	int(CEF_CALLBACK* get_line_number)(struct _cef_v8stack_frame_t* self);

	///
	// Returns the 1-based column offset on the line for the function call or 0 if
	// unknown.
	///
	int(CEF_CALLBACK* get_column)(struct _cef_v8stack_frame_t* self);

	///
	// Returns true (1) if the function was compiled using eval().
	///
	int(CEF_CALLBACK* is_eval)(struct _cef_v8stack_frame_t* self);

	///
	// Returns true (1) if the function was called as a constructor via "new".
	///
	int(CEF_CALLBACK* is_constructor)(struct _cef_v8stack_frame_t* self);
} _v8stack_frame_t;

/*
	<int> RegisterExtension(
		<str>		extension_name,
		<str>		js_code,
		<V8Handler>	handler
	)
*/
static int luacef_register_extension(lua_State *L)
{
	cef_string_t s1 = luacef_tostring(L, 1);
	cef_string_t s2 = luacef_tostring(L, 2);
	cef_v8handler_t *p = luacef_checkudata(L, 3, __v8handler__);

	int ret = cef_register_extension(&s1, &s2, p);

	return 1;
}

// ======================================================================================================

void luacef_v8_reg(lua_State *L)
{
	// v8value

	luaL_newmetatable(L, __v8value__);
	luaL_setfuncs(L, luacef_v8value_m, 0);
	lua_setfield(L, -1, __index__);

	lua_newtable(L);
	luaL_setfuncs(L, luacef_v8value_ms, 0);
	lua_setfield(L, -2, __v8value__);

	lua_pushcfunction(L, luacef_register_extension);
	lua_setfield(L, -2, "RegisterExtension");
}