#ifndef _ILUA_HEADER
#define _ILUA_HEADER
#pragma once

#include <cstdarg>
#include <cstdint>
#include "compat-5.3.h"

namespace ILua
{
	// lua_CFunction
	typedef int (* CFunc)(class State& L);
	
	// luaL_Reg
	typedef struct Reg {
		const char *name;
		CFunc func;
	} Reg;

	// lua_State
	class State
	{
	public:

		// create State interface from lua_State
		static State *create(lua_State *L) {
			return reinterpret_cast<State*>(L);
		}

		// create new independent State
		static State *create() {
			lua_State *L = luaL_newstate();
			return reinterpret_cast<State*>(L);
		}
		
// ==============================
// ==============================

		// static::create(L) -> State*
		State(lua_State *L) {
			*reinterpret_cast<void**>(this) = L;	
		}

		operator State *() {
			return reinterpret_cast<State*>(*(intptr_t*)this);
		}

// ==============================
// ==============================

		// get lua_State
		lua_State *L() {
			return reinterpret_cast<lua_State*>(this);
		}

		// lua_close
		void close() {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_close(L);
		}

		// lua_newthread
		State *newThread() {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_State *t = lua_newthread(L);
			return reinterpret_cast<State*>(L);
		}
		
// ==============================
// ==============================

		// lua_absindex
		int absIndex(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_absindex(L, idx);
		}

		// lua_gettop
		int getTop() {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_gettop(L);
		}

		// lua_settop
		void setTop(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_settop(L, idx);
		}

		// lua_pushvalue
		void pushValue(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushvalue(L, idx);
		}
		
		// lua_rotate
		void rotate(int idx = -1, int n = 1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_rotate(L, idx, n);
		}

		// lua_copy
		void copy(int fromidx, int toidx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_copy(L, fromidx, toidx);
		}

		// lua_checkstack
		int checkStack(int n = 1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_checkstack(L, n);
		}

// ==============================
// ==============================

		// lua_type
		int type(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_type(L, idx);
		}

		// lua_typename
		const char *typeName(int tp) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_typename(L, tp);
		}

		// lua_isnil
		bool isNil(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isnil(L, idx);
		}

		// lua_isnone
		bool isNone(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isnone(L, idx);
		}

		// lua_isnoneornil
		bool isNoneOrNil(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isnoneornil(L, idx);
		}

		// lua_isboolean
		bool isBool(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isboolean(L, idx);
		}

		// lua_isinteger
		bool isInt(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isinteger(L, idx);
		}

		// lua_isnumber
		bool isNum(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isnumber(L, idx);
		}

		// lua_isstring
		bool isString(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isstring(L, idx);
		}

		// lua_isfunction
		bool isFunc(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isfunction(L, idx);
		}

		// lua_iscfunction
		bool isCFunc(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_iscfunction(L, idx);
		}

		// lua_isuserdata
		bool isUserdata(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isuserdata(L, idx);
		}

		// lua_islightuserdata
		bool isLightUserdata(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_islightuserdata(L, idx);
		}

		// lua_istable
		bool isTable(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_istable(L, idx);
		}

		// lua_isthread
		bool isThread(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isthread(L, idx);
		}

		// check type
		template<typename T>
		bool is(int idx = -1) {
			return isNoneOrNil(idx);
		}
		template<>
		bool is<bool>(int idx) {
			return isBool(idx);
		}
		template<>
		bool is<int>(int idx) {
			return isInt(idx);
		}
		template<>
		bool is<int64_t>(int idx) {
			return isInt(idx);
		}
		template<>
		bool is<double>(int idx) {
			return isNum(idx);
		}
		template<>
		bool is<const char*>(int idx) {
			return isString(idx);
		}
		template<>
		bool is<CFunc>(int idx) {
			return isCFunc(idx);
		}

// ==============================
// ==============================

		// lua_rawlen
		size_t rawlen(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_rawlen(L, idx);
		}

		// lua_toboolean, C styled
		bool toBool(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			switch (lua_type(L, idx)) {
				case LUA_TNIL:
					return false;
				case LUA_TNUMBER:
					return lua_tonumber(L, idx) != 0;
				case LUA_TUSERDATA:
				case LUA_TLIGHTUSERDATA:
					return lua_touserdata(L, idx) != NULL;
				case LUA_TBOOLEAN:
					return lua_toboolean(L, idx);
				default:
					return true;
			}
		}

		// lua_tointeger 32
		int toInt(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return static_cast<int>(lua_tointeger(L, idx));
		}
		// lua_tointegerx 32
		int toInt(int idx, int &isnum) {
			auto L = reinterpret_cast<lua_State*>(this);
			return static_cast<int>(lua_tointegerx(L, idx, &isnum));
		}

		// lua_tointeger 64
		int64_t toInt64(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tointeger(L, idx);
		}
		// lua_tointegerx 64
		int64_t toInt64(int idx, int &isnum) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tointegerx(L, idx, &isnum);
		}

		// lua_tonumber
		double toNum(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tonumber(L, idx);
		}
		// lua_tonumberx
		double toNum(int idx, int& isnum) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tonumberx(L, idx, &isnum);
		}

		// lua_tostring
		const char *toString(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tostring(L, idx);
		}

		// lua_tolstring
		const char *toString(int idx, size_t& len) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tolstring(L, idx, &len);
		}

		// lua_tocfunction
		CFunc toCFunc(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return (CFunc)lua_tocfunction(L, idx);
		}

		// lua_touserdata
		void *toUserdata(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_touserdata(L, idx);
		}

		// lua_tothread
		State *toThread(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return reinterpret_cast<State*>(lua_tothread(L, idx));
		}

		// lua_topointer
		const void *toPointer(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_topointer(L, idx);
		}

		// get value
		template<typename T>
		T to(int idx = -1) {
			return toInt(idx);
		}
		template<>
		bool to<bool>(int idx) {
			return toBool(idx);
		}
		template<>
		int to<int>(int idx) {
			return toInt(idx);
		}
		template<>
		int64_t to<int64_t>(int idx) {
			return toInt64(idx);
		}
		template<>
		double to<double>(int idx) {
			return toNum(idx);
		}
		template<>
		const char *to<const char*>(int idx) {
			return toString(idx);
		}
		template<>
		CFunc to<CFunc>(int idx) {
			return toCFunc(idx);
		}
		template<>
		void *to<void *>(int idx) {
			return toUserdata(idx);
		}
		template<>
		const void *to<const void *>(int idx) {
			return toPointer(idx);
		}

// ==============================
// ==============================

		// lua_pushnil
		void push() {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushnil(L);
		}

		// lua_pushboolean
		void push(bool b) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushboolean(L, b);
		}

		// lua_pushinteger 32
		void push(int i) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushinteger(L, i);
		}

		// lua_pushinteger 64
		void push(int64_t i64) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushinteger(L, i64);
		}

		// lua_pushnumber
		void push(double n) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushnumber(L, n);
		}

		// lua_pushstring
		const char *push(const char *s) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_pushstring(L, s);
		}
		// lua_pushlstring
		const char *push(const char *s, size_t l) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_pushlstring(L, s, l);
		}

		// lua_pushvfstring
		const char *push(const char *fmt, ...) {
			auto L = reinterpret_cast<lua_State*>(this);
			va_list ap;
			va_start(ap, fmt);
			const char *ret = lua_pushvfstring(L, fmt, ap);
			va_end(ap);
			return ret;
		}

		// lua_pushlightuserdata
		void push(void *p) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushlightuserdata(L, p);
		}

		// lua_pushcclosure
		void push(CFunc func, int n = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushcclosure(L, (lua_CFunction)func, n);
		}

		// lua_pushthread
		int pushThread() {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_pushthread(L);
		}

// ==============================
// ==============================

		// lua_getglobal
		int getGlobal(const char *name) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_getglobal(L, name);
		}

		// lua_gettable
		int getTable(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_gettable(L, idx);
		}

		// lua_getfield
		int getField(int idx, const char *k) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_getfield(L, idx, k);
		}

		// lua_geti
		int get(int idx, lua_Integer n) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_geti(L, idx, n);
		}

		// lua_rawget
		int rawget(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_rawget(L, idx);
		}

		// lua_rawgeti
		int rawget(int idx, lua_Integer n) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_rawgeti(L, idx, n);
		}

		// lua_rawgetp
		int rawget(int idx, const void *p) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_rawgetp(L, idx, p);
		}

		// lua_createtable
		void createTable(int narr = 0, int nrec = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_createtable(L, narr, nrec);
		}

		// lua_newuserdata
		void *newUserdata(size_t sz) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_newuserdata(L, sz);
		}

		// lua_getmetatable
		int getMetatable(int objindex) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_getmetatable(L, objindex);
		}

		// lua_getuservalue
		int getUservalue(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_getuservalue(L, idx);
		}

// ==============================
// ==============================

		// lua_setglobal
		void setGlobal(const char *name) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_setglobal(L, name);
		}

		// lua_settable
		void setTabble(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_settable(L, idx);
		}

		// lua_setfield
		void setField(int idx, const char *k) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_setfield(L, idx, k);
		}

		// lua_seti
		void set(int idx, lua_Integer n) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_seti(L, idx, n);
		}

		// lua_rawset
		void rawset(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_rawset(L, idx);
		}

		// lua_rawseti
		void rawset(int idx, lua_Integer n) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_rawseti(L, idx, n);
		}

		// lua_rawsetp
		void rawset(int idx, const void *p) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_rawsetp(L, idx, p);
		}
		
		// lua_setmetatable
		int setMetatable(int objindex) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_setmetatable(L, objindex);
		}

		// lua_setuservalue
		void setUservalue(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_setuservalue(L, idx);
		}

// ==============================
// ==============================

		// lua_callk
		void call(int nargs, int nresults, lua_KContext ctx = 0, lua_KFunction k = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_callk(L, nargs, nresults, ctx, k);
		}

		// lua_pcallk
		int pcall(int nargs, int nresults, int errfunc, lua_KContext ctx = 0, lua_KFunction k = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_pcallk(L, nargs, nresults, errfunc, ctx, k);
		}

		// lua_load
		int load(lua_Reader reader, void *dt, const char *chunkname, const char *mode) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_load(L, reader, dt, chunkname, mode);
		}

		// lua_dump
		int dump(lua_Writer writer, void *data, int strip) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_dump(L, writer, data, strip);
		}

// ==============================
// ==============================

		// lua_yieldk
		int yield(int nresults, lua_KContext ctx = 0, lua_KFunction k = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_yieldk(L, nresults, ctx, k);
		}

		// lua_resume
		int resume(lua_State *from, int narg = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_resume(L, from, narg);
		}
		// lua_resume
		int resume(State& from, int narg = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_resume(L, from.L(), narg);
		}
		// lua_resume
		int resume(State *from, int narg = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_resume(L, from->L(), narg);
		}

		// lua_status
		int status() {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_status(L);
		}

		// lua_isyieldable
		bool isYieldable() {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_isyieldable(L);
		}

// ==============================
// ==============================

		// lua_gc
		int gc(int what, int data) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_gc(L, what, data);
		}

// ==============================
// ==============================

		// lua_error
		int error() {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_error(L);
		}

		// lua_next
		int next(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_next(L, idx);
		}

		// lua_concat
		void concat(int n) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_concat(L, n);
		}

		// lua_len
		void len(int idx) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_len(L, idx);
		}

		// lua_stringtonumber
		size_t stringToNum(const char *s) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_stringtonumber(L, s);
		}

// ==============================
// ==============================

		// lua_pop
		void pop(int n = 1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pop(L, n);
		}

		// lua_version
		auto version() {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_version(L);
		}

		// lua_register
		void reg(const char *name, CFunc func) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_register(L, name, (lua_CFunction)func);
		}

		// lua_newtable
		void newTable() {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_newtable(L);
		}

		// lua_pushglobaltable
		void push_G() {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_pushglobaltable(L);
		}

		// lua_insert
		void insert(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_insert(L, idx);
		}

		// lua_remove
		void remove(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_remove(L, idx);
		}

		// lua_replace
		void replace(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			lua_replace(L, idx);
		}

// ==============================
// ==============================

		// luaL_checkversion
		void checkVersion() {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_checkversion(L);
		}

		// luaL_getmetafield
		int getMetaField(int obj, const char *e) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_getmetafield(L, obj, e);
		}

		// luaL_callmeta
		int callMeta(int obj, const char *e) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_callmeta(L, obj, e);
		}

		// luaL_tostring
		const char *toStringL(int idx = -1) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tostring(L, idx);
		}
		// luaL_tolstring
		const char *toStringL(int idx, size_t& l) {
			auto L = reinterpret_cast<lua_State*>(this);
			return lua_tolstring(L, idx, &l);
		}

		// luaL_argerror
		int argError(int arg, const char *extramsg) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_argerror(L, arg, extramsg);
		}

		// luaL_checklstring
		const char *checkString(int arg) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_checklstring(L, arg, NULL);
		}
		// luaL_checklstring
		const char *checkString(int arg, size_t& l) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_checklstring(L, arg, &l);
		}

		// luaL_checkinteger 32
		int checkInt(int arg) {
			auto L = reinterpret_cast<lua_State*>(this);
			return static_cast<int>(luaL_checkinteger(L, arg));
		}
		// luaL_checkinteger 64
		uint64_t checkInt64(int arg) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_checkinteger(L, arg);
		}

		// luaL_checknumber
		double checkNum(int arg) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_checknumber(L, arg);
		}

		// luaL_checkstack
		void checkStack(int sz, const char *msg) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_checkstack(L, sz, msg);
		}

		// luaL_checktype
		void checkType(int arg, int t) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_checktype(L, arg, t);
		}

		// luaL_checkany
		void checkType(int arg) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_checkany(L, arg);
		}

		// luaL_newmetatable
		int newMetatable(const char *name) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_newmetatable(L, name);
		}

		// luaL_setmetatable
		void setMetatable(const char *name) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_setmetatable(L, name);
		}

		// luaL_testudata
		void *testUdata(int ud, const char *tname) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_testudata(L, ud, tname);
		}

		// luaL_testudata
		void checkUdata(int ud, const char *tname) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_testudata(L, ud, tname);
		}

		// luaL_where
		void where(int lvl) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_where(L, lvl);
		}

		// luaL_error
		int error(const char *fmt, ...) {
			// forward calling <this -> L, fmt, ...>
			return (reinterpret_cast
				<int (*)()>
				(luaL_error))();
		}

		// luaL_checkoption
		int checkOption(int arg, const char *def, const char *const lst[]) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_checkoption(L, arg, def, lst);
		}

		// luaL_ref
		int ref(int t = LUA_REGISTRYINDEX) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_ref(L, t);
		}

		// luaL_unref
		void unref(int t, int ref) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_unref(L, t, ref);
		}

		// luaL_setfuncs
		void setFuncs(const Reg *funcs, int nup = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_setfuncs(L, (const luaL_Reg*)funcs, nup);
		}
		// luaL_setfuncs
		void setFuncs(const luaL_Reg *l, int nup = 0) {
			auto L = reinterpret_cast<lua_State*>(this);
			luaL_setfuncs(L, l, nup);
		}

		// luaL_dofile
		int doFile(const char *fn) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_dofile(L, fn);
		}

		// luaL_dostring
		int doString(const char *src) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_dostring(L, src);
		}

		// luaL_getmetatable
		int getMetatable(const char *n) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_getmetatable(L, n);
		}

		// luaL_typename
		const char *typeNameL(int i) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_typename(L, i);
		}

		// luaL_len
		lua_Integer lenL(int i) {
			auto L = reinterpret_cast<lua_State*>(this);
			return luaL_len(L, i);
		}

// ==============================
// ==============================

		// get pointer
		State *operator ->() {
			return this;
		}

		// get pointer
		State* operator &() {
			return this;
		}

		bool operator ==(State& that) {
			return this->L() == that.L();
		}
		bool operator ==(State *that) {
			return this->L() == that->L();
		}
		bool operator ==(lua_State *that) {
			return this->L() == that;
		}

		// pop 1
		void operator --() {
			pop(1);
		}

		// pop n
		void operator -=(int n) {
			pop(n);
		}

		// push nil
		void operator ++() {
			push();
		}

		// push type
		template<typename  T>
		void operator +=(T val) {
			push(val);
		}
	};

	// compile time hash string | FNV-1a 32 | C++ 11
	constexpr uint32_t hash(const char *src, int len = -1) {
		uint32_t hash = 2166136261u;
		if (len == -1) for (; *src; src++) {
			hash ^= *src;
			hash *= 16777619u;
		}
		else for (int i = 0; i < len; i++) {
			hash ^= src[i];
			hash *= 16777619u;
		}
		return hash;
	}

	/* hash example:
		[...]
		const char *idx = L.toString(2);
		switch (ILua::hash(idx)) {
			case ILua::hash("abc"):
				L.push(10);
				return 1;
			case hash("xyz"):
				L.push(true);
				return 1;
			[...]
		}
		[...]
	*/
}

#endif