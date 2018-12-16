#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_drag_data_capi.h"

//    _                _             _ _         
//  _| |___ ___ ___   | |_ ___ ___ _| | |___ ___ 
// | . |  _| .'| . |  |   | .'|   | . | | -_|  _|
// |___|_| |__,|_  |  |_|_|__,|_|_|___|_|___|_|  
//=============|___|==============================


// drag_handler =======================
// implement

typedef struct luacef_DragHandler {

	cef_base_ref_counted_t base;

	int(CEF_CALLBACK* on_drag_enter)(struct luacef_DragHandler* self,
		struct _cef_browser_t* browser,
		struct _cef_drag_data_t* dragData,
		cef_drag_operations_mask_t mask);

	void(CEF_CALLBACK* on_draggable_regions_changed)(
		struct luacef_DragHandler* self,
		struct _cef_browser_t* browser,
		size_t regionsCount,
		cef_draggable_region_t const* regions);

	lua_State *L;
	int ref;

} luacef_DragHandler;

/*
	<int> DragHandler:OnDragEnter(
		<Browser> browser,
		<DragData> dragData,
		<int> mask
	)
*/
int CEF_CALLBACK luacef_DragHandler_OnDragEnter(
	struct luacef_DragHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_drag_data_t* dragData,
	cef_drag_operations_mask_t mask)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnDragEnter)) {

		luacef_pushuserdata(self->L, self, __drag_handler__);
		luacef_pushuserdata(self->L, browser, __CefBrowser);
		luacef_pushuserdata(self->L, dragData, __drag_data__);
		lua_pushinteger(self->L, mask);

		lua_pcall(self->L, 4, 1, 0);
		lua_pop(self->L, 1);
		return lua_tointeger(self->L, -1);
	}

	return 0;
}

/*
	<void> DragHandler:OnDragEnter(
		<Browser> browser,
		<uint> regionsCount,
		<DraggableRegion> regions
	)
*/
void CEF_CALLBACK luacef_DragHandler_OnDraggableRegionsChanged(
	struct luacef_DragHandler* self,
	struct _cef_browser_t* browser,
	size_t regionsCount,
	cef_draggable_region_t const* regions)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnDraggableRegionsChanged)) {

		luacef_pushuserdata(self->L, self, __drag_handler__);
		luacef_pushuserdata(self->L, browser, __CefBrowser);
		lua_pushinteger(self->L, regionsCount);

		// todo array
		//luacef_pushuserdata(self->L, regions, );
		// <DraggableRegion> regions[4], array count 1 -> 4

		//lua_createtable(self->L, 4, 0);


		lua_pcall(self->L, 4, 0, 0);
		lua_pop(self->L, 1);
	}
}

static int luacef_DragHandler_new(lua_State *L)
{
	size_t sz = sizeof(luacef_DragHandler);
	luacef_DragHandler *p = luacef_alloc(sz);
	p->base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, -1, __OnDragEnter))
			p->on_drag_enter = luacef_DragHandler_OnDragEnter;

		if (lua_getfield(L, -1, __OnDraggableRegionsChanged))
			p->on_draggable_regions_changed = luacef_DragHandler_OnDraggableRegionsChanged;
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushuserdata(L, p, __drag_handler__);
	return 1;
}

static int luacef_DragHandler_release(lua_State *L)
{
	if (lua_isnoneornil(L, 1)) return 0;
	void **ud = (void**)lua_touserdata(L, 1);
	if (ud && *ud) {
		luaL_unref(L, LUA_REGISTRYINDEX, ((luacef_DragHandler*)*ud)->ref); //
		free(*ud);
		*ud = NULL;
	}
	return 0;
}

static int luacef_DragHandler_index(lua_State *L)
{
	luacef_DragHandler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);

	if (!strcmp(i, __OnDragEnter))
		lua_pushcfunction(L, luacef_DragHandler_release);

	else if (!strcmp(i, __OnDragEnter))
		lua_getfield(L, -1, __OnDragEnter);

	else if (!strcmp(i, __OnDraggableRegionsChanged))
		lua_getfield(L, -1, __OnDraggableRegionsChanged);

	else return 0;

	return 1;
}

static int luacef_DragHandler_newindex(lua_State *L)
{
	luacef_DragHandler *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __OnDragEnter)) {
		lua_setfield(L, -2, __OnDragEnter);
		p->on_drag_enter = (void*)luacef_DragHandler_OnDragEnter;
	}
		
	else if (!strcmp(i, __OnDraggableRegionsChanged)) {
		lua_setfield(L, -2, __OnDraggableRegionsChanged);
		p->on_drag_enter = (void*)luacef_DragHandler_OnDraggableRegionsChanged;
	}

	return 0;
}

static int luacef_DragHandler_len(lua_State *L)
{
	lua_pushinteger(L, sizeof(luacef_DragHandler));
	return 1;
}

static const luaL_Reg luacef_DragHandler_m[] = {
	{ "__index", luacef_DragHandler_index },
	{ "__newindex", luacef_DragHandler_newindex },
	{ "__len", luacef_DragHandler_len },
	{ "__eq", luacef_eq },
	{ NULL, NULL }
};

// register =====================================

void luacef_DragHandler_reg(lua_State *L)
{
	luaL_newmetatable(L, __drag_handler__);
	luaL_setfuncs(L, luacef_DragHandler_m, 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, luacef_DragHandler_new);
	lua_setfield(L, -2, "newDragHandler");
}