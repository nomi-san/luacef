#include "../luacef.h"

#include <time.h>
#include "include/internal/cef_export.h"

static const char *__year = "year";
static const char *__month = "month";
static const char *__day_of_week = "day_of_week";
static const char *__day_of_month = "day_of_month";
static const char *__hour = "hour";
static const char *__minute = "minute";
static const char *__second = "second";
static const char *__millisecond = "millisecond";

static const char *__Delta = "Delta";
static const char *__GetDoubleT = "GetDoubleT";
static const char *__GetTimeT = "GetTimeT";
static const char *__SetDoubleT = "SetDoubleT";
static const char *__SetTimeT = "SetTimeT";
static const char *__Now = "Now";

static int luacef_Time_new(lua_State *L)
{
	size_t sz = sizeof(cef_time_t);
	cef_time_t *p = luacef_alloc(sz);

	if (lua_istable(L, 1)) {

		if (lua_getfield(L, 1, __year))
			p->year = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __month))
			p->month = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __day_of_week))
			p->day_of_week = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __day_of_month))
			p->day_of_month = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __hour))
			p->hour = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __minute))
			p->minute = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __second))
			p->second = lua_tointeger(L, -1);

		if (lua_getfield(L, 1, __millisecond))
			p->millisecond = lua_tointeger(L, -1);
	}
	else if (lua_isinteger(L, 1)) {
		int i = lua_tointeger(L, 1);
		cef_time_from_timet(i, p);
	}
	else if (lua_isnumber(L, 1)) {
		double d = lua_tonumber(L, 1);
		cef_time_from_doublet(d, p);
	}

	luacef_pushuserdata(L, p, __time__);
	return 1;
}

static int luacef_Time_GetTimeT(lua_State *L)
{
	cef_time_t *t = luacef_touserdata(L, 1);

	int i = 0;

	if (!cef_time_to_timet(t, &i))
		return 0;
	else
		lua_pushinteger(L, i);

	return 1;
}

static int luacef_Time_SetTimeT(lua_State *L)
{
	cef_time_t *t = luacef_touserdata(L, 1);
	int i = lua_tointeger(L, 2);

	cef_time_from_timet(i, t);
	return 0;
}

static int luacef_Time_GetDoubleT(lua_State *L)
{
	cef_time_t *t = luacef_touserdata(L, 1);

	double d = 0;

	if (!cef_time_to_doublet(t, &d))
		return 0;
	else
		lua_pushnumber(L, d);

	return 1;
}

static int luacef_Time_SetDoubleT(lua_State *L)
{
	cef_time_t *t = luacef_touserdata(L, 1);
	double d = lua_tonumber(L, 2);

	cef_time_from_doublet(d, t);
	return 0;
}

static int luacef_Time_Now(lua_State *L)
{
	cef_time_t *t = luacef_touserdata(L, 1);

	cef_time_now(t);

	return 0;
}

static int luacef_Time_Delta(lua_State *L)
{
	cef_time_t *t = luacef_touserdata(L, 1);
	cef_time_t *t2 = luacef_checkudata(L, 2, __time__);

	long long d;
	int r = cef_time_delta(t, t2, &d);

	lua_pushinteger(L, d);
	return 1;
}

//
static int luacef_Time_index(lua_State *L)
{
	cef_time_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __release__))
		lua_pushcfunction(L, luacef_release);

	else if (!strcmp(i, __year))
		lua_pushinteger(L, p->year);

	else if (!strcmp(i, __month))
		lua_pushinteger(L, p->month);

	else if (!strcmp(i, __day_of_week))
		lua_pushinteger(L, p->day_of_week);

	else if (!strcmp(i, __day_of_month))
		lua_pushinteger(L, p->day_of_month);

	else if (!strcmp(i, __hour))
		lua_pushinteger(L, p->hour);

	else if (!strcmp(i, __minute))
		lua_pushinteger(L, p->minute);

	else if (!strcmp(i, __second))
		lua_pushinteger(L, p->second);

	else if (!strcmp(i, __millisecond))
		lua_pushinteger(L, p->millisecond);

	// m
	else if (!strcmp(i, __GetTimeT))
		lua_pushcfunction(L, luacef_Time_GetTimeT);

	else if (!strcmp(i, __SetTimeT))
		lua_pushcfunction(L, luacef_Time_SetTimeT);

	else if (!strcmp(i, __GetDoubleT))
		lua_pushcfunction(L, luacef_Time_GetDoubleT);

	else if (!strcmp(i, __SetDoubleT))
		lua_pushcfunction(L, luacef_Time_SetDoubleT);

	else if (!strcmp(i, __Now))
		lua_pushcfunction(L, luacef_Time_Now);

	else if (!strcmp(i, __Delta))
		lua_pushcfunction(L, luacef_Time_Delta);
	//

	else return 0;

	return 1;
}

static int luacef_Time_newindex(lua_State *L)
{
	cef_time_t *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	if (!strcmp(i, __year))
		p->year = lua_tointeger(L, -1);

	else if (!strcmp(i, __month))
		p->month = lua_tointeger(L, -1);

	else if (!strcmp(i, __day_of_week))
		p->day_of_week = lua_tointeger(L, -1);

	else if (!strcmp(i, __day_of_month))
		p->day_of_month = lua_tointeger(L, -1);

	else if (!strcmp(i, __hour))
		p->hour = lua_tointeger(L, -1);

	else if (!strcmp(i, __minute))
		p->minute = lua_tointeger(L, -1);

	else if (!strcmp(i, __second))
		p->second = lua_tointeger(L, -1);

	else if (!strcmp(i, __millisecond))
		p->millisecond = lua_tointeger(L, -1);

	return 0;
}

static const luaL_Reg luacef_Time_m[] = {
	{ "__index", luacef_Time_index },
	{ "__newindex", luacef_Time_newindex },
	{ NULL, NULL}
};

// ===============================================================================

void luacef_Time_reg(lua_State *L)
{
	luaL_newmetatable(L, __time__);
	luaL_setfuncs(L, luacef_Time_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_Time_new);
	lua_setfield(L, -2, "newTime");
}