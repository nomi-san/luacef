#include "../luacef.h"

#include "include/capi/cef_render_handler_capi.h"

#define SELF luacef_RenderHandler

typedef struct SELF {

	cef_render_handler_t self;

	lua_State *L;
	int ref;

} SELF;

#define API(fn) \
	LCEF_API(RenderHandler, fn)

#define API_N(fn) \
	LCEF_API_N(RenderHandler, fn)

#define API_M(mname) \
	LCEF_M(RenderHandler, mname)

struct _cef_accessibility_handler_t* CEF_CALLBACK API_N(GetAccessibilityHandler)
	(struct luacef_RenderHandler* self)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetAccessibilityHandler)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1

		lua_pcall(self->L, 1, 1, 8); // call

		return lua_isnil(self->L, -1) ? NULL : luacef_touserdata(self->L, -1);
	}

	return NULL;
}

int CEF_CALLBACK API_N(GetRootScreenRect) 
	(struct luacef_RenderHandler* self, struct _cef_browser_t* browser, cef_rect_t* rect)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetRootScreenRect)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, rect, __rect__); // 3

		lua_pcall(self->L, 3, 1, 8); // call

		int ret = lua_tointeger(self->L, -1);
		return ret;
	}

	return 0;
}

int CEF_CALLBACK API_N(GetViewRect)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	cef_rect_t* rect)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetViewRect)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, rect, __rect__); // 3

		lua_pcall(self->L, 3, 1, 8); // call

		int ret = lua_tointeger(self->L, -1);
		return ret;
	}

	return 0;
}

int CEF_CALLBACK API_N(GetScreenPoint) (struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	int viewX,
	int viewY,
	int* screenX,
	int* screenY)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetScreenPoint)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		lua_pushinteger(self->L, viewX); // 3
		lua_pushinteger(self->L, viewY); // 4
		luacef_pushudata(self->L, screenX, __IntPtr__); // 5
		luacef_pushudata(self->L, screenY, __IntPtr__); // 6

		lua_pcall(self->L, 6, 1, 8); // call

		int ret = lua_tointeger(self->L, -1);
		return ret;
	}

	return 0;
}


int CEF_CALLBACK API_N(GetScreenInfo)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_screen_info_t* screen_info)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __GetScreenInfo)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, screen_info, __screen_info__); // 3

		lua_pcall(self->L, 3, 1, 8); // call

		int ret = lua_tointeger(self->L, -1);
		return ret;
	}

	return 0;
}

void CEF_CALLBACK API_N(OnPopupShow)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	int show)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnPopupShow)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		lua_pushinteger(self->L, show); // 3

		lua_pcall(self->L, 3, 0, 8); // call
	}
}

void CEF_CALLBACK API_N(OnPopupSize)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	const cef_rect_t* rect)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnPopupSize)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, rect, __rect__); // 3

		lua_pcall(self->L, 3, 0, 8); // call
	}
}

void CEF_CALLBACK API_N(OnPaint)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	cef_paint_element_type_t type,
	size_t dirtyRectsCount,
	cef_rect_t const* dirtyRects,
	const void* buffer,
	int width,
	int height)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnPaint)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		lua_pushinteger(self->L, type); // 3
		lua_pushinteger(self->L, dirtyRectsCount); // 4
		luacef_pushuserdata(self->L, dirtyRects, __rect__); // 5

		lua_pushlightuserdata(self->L, buffer); // 6

		lua_pushinteger(self->L, width); // 7
		lua_pushinteger(self->L, height); // 8

		lua_pcall(self->L, 8, 0, 8); // call
	}
}

void CEF_CALLBACK API_N(OnCursorChange)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	cef_cursor_handle_t cursor,
	cef_cursor_type_t type,
	const struct _cef_cursor_info_t* custom_cursor_info)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnCursorChange)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		lua_pushlightuserdata(self->L, cursor); // 3
		lua_pushinteger(self->L, type); // 4
		luacef_pushuserdata(self->L, custom_cursor_info, __cursor_info__); // 5

		lua_pcall(self->L, 5, 0, 8); // call
	}
}

int CEF_CALLBACK API_N(StartDragging)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	struct _cef_drag_data_t* drag_data,
	cef_drag_operations_mask_t allowed_ops,
	int x,
	int y)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __StartDragging)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, drag_data, __CefDragData); // 3
		lua_pushinteger(self->L, allowed_ops); // 4
		lua_pushinteger(self->L, x); // 5
		lua_pushinteger(self->L, y); // 6

		lua_pcall(self->L, 6, 1, 8); // call
		int ret = lua_tointeger(self->L, -1);
		return ret;
	}

	return 0;
}

void CEF_CALLBACK API_N(UpdateDragCursor)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	cef_drag_operations_mask_t operation)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __StartDragging)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		lua_pushinteger(self->L, operation); // 3

		lua_pcall(self->L, 3, 0, 8); // call
	}
}

void CEF_CALLBACK API_N(OnScrollOffsetChanged)(struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	double x,
	double y)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnScrollOffsetChanged)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		lua_pushnumber(self->L, x); // 3
		lua_pushnumber(self->L, y); // 4

		lua_pcall(self->L, 4, 0, 8); // call
	}
}

void CEF_CALLBACK API_N(OnIMECompositionRangeChanged)(
	struct luacef_RenderHandler* self,
	struct _cef_browser_t* browser,
	const cef_range_t* selected_range,
	size_t character_boundsCount,
	cef_rect_t const* character_bounds)
{
	lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->ref);
	if (lua_getfield(self->L, -1, __OnScrollOffsetChanged)) {

		luacef_pushuserdata(self->L, self, __CefRenderHandler); // 1
		luacef_pushuserdata(self->L, browser, __CefBrowser); // 2
		luacef_pushuserdata(self->L, selected_range, __range__); // 2
		lua_pushinteger(self->L, character_boundsCount);
		luacef_pushuserdata(self->L, character_bounds, __rect__); // 2

		lua_pcall(self->L, 5, 0, 8); // call
	}
}

// api =========================

API(new)
{
	size_t sz = sizeof(SELF);
	SELF *p = calloc(1, sz);
	p->self.base.size = sz;
	p->L = L;

	if (lua_istable(L, 1)) {
		lua_pushvalue(L, 1);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);

		if (lua_getfield(L, 1, __GetAccessibilityHandler))
			p->self.get_accessibility_handler = (void*)API_N(GetAccessibilityHandler);

		if (lua_getfield(L, 1, __GetRootScreenRect))
			p->self.get_root_screen_rect = (void*)API_N(GetRootScreenRect);

		if (lua_getfield(L, 1, __GetViewRect))
			p->self.get_view_rect = (void*)API_N(GetViewRect);

		if (lua_getfield(L, 1, __GetScreenPoint))
			p->self.get_screen_point = (void*)API_N(GetScreenPoint);

		if (lua_getfield(L, 1, __GetScreenInfo))
			p->self.get_screen_info = (void*)API_N(GetScreenInfo);

		if (lua_getfield(L, 1, __OnPopupShow))
			p->self.on_popup_show = (void*)API_N(OnPopupShow);

		if (lua_getfield(L, 1, __OnPopupSize))
			p->self.on_popup_size = (void*)API_N(OnPopupSize);

		if (lua_getfield(L, 1, __OnPaint))
			p->self.on_paint = (void*)API_N(OnPaint);

		if (lua_getfield(L, 1, __OnCursorChange))
			p->self.on_cursor_change = (void*)API_N(OnCursorChange);

		if (lua_getfield(L, 1, __StartDragging))
			p->self.start_dragging = (void*)API_N(StartDragging);

		if (lua_getfield(L, 1, __UpdateDragCursor))
			p->self.update_drag_cursor = (void*)API_N(UpdateDragCursor);

		if (lua_getfield(L, 1, __OnScrollOffsetChanged))
			p->self.on_scroll_offset_changed = (void*)API_N(OnScrollOffsetChanged);

		if (lua_getfield(L, 1, __OnIMECompositionRangeChanged))
			p->self.on_ime_composition_range_changed = (void*)API_N(OnIMECompositionRangeChanged);
	}
	else {
		lua_newtable(L);
		p->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	luacef_pushudata(L, p, __CefRenderHandler);
	return 1;
}

API(index)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char *i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	lua_pushvalue(L, -1);

	if (!strcmp(i, __release__))
		;// free

	else if (!strcmp(i, __GetAccessibilityHandler))
		lua_getfield(L, -1, __GetAccessibilityHandler);

	else if (!strcmp(i, __GetRootScreenRect))
		lua_getfield(L, -1, __GetRootScreenRect);

	else if (!strcmp(i, __GetViewRect))
		lua_getfield(L, -1, __GetViewRect);

	else if (!strcmp(i, __GetScreenPoint))
		lua_getfield(L, -1, __GetScreenPoint);

	else if (!strcmp(i, __GetScreenInfo))
		lua_getfield(L, -1, __GetScreenInfo);

	else if (!strcmp(i, __OnPopupShow))
		lua_getfield(L, -1, __OnPopupShow);

	else if (!strcmp(i, __OnPopupSize))
		lua_getfield(L, -1, __OnPopupSize);

	else if (!strcmp(i, __OnPaint))
		lua_getfield(L, -1, __OnPaint);

	else if (!strcmp(i, __OnCursorChange))
		lua_getfield(L, -1, __OnCursorChange);

	else if (!strcmp(i, __StartDragging))
		lua_getfield(L, -1, __StartDragging);

	else if (!strcmp(i, __UpdateDragCursor))
		lua_getfield(L, -1, __UpdateDragCursor);

	else if (!strcmp(i, __OnScrollOffsetChanged))
		lua_getfield(L, -1, __OnScrollOffsetChanged);

	else if (!strcmp(i, __OnIMECompositionRangeChanged))
		lua_getfield(L, -1, __OnIMECompositionRangeChanged);

	else return 0;

	return 1;
}

API(newindex)
{
	SELF *p = luacef_touserdata(L, 1);
	if (!p) return 0;

	const char* i = lua_tostring(L, 2);

	lua_rawgeti(L, LUA_REGISTRYINDEX, p->ref);
	if (!lua_isfunction(L, 3)) return 0;
	lua_pushvalue(L, 3);

	if (!strcmp(i, __GetAccessibilityHandler)) {
		lua_setfield(L, -2, __GetAccessibilityHandler);
		p->self.get_accessibility_handler = (void*)API_N(GetAccessibilityHandler);
	}

	else if (!strcmp(i, __GetRootScreenRect)) {
		lua_setfield(L, -2, __GetRootScreenRect);
		p->self.get_root_screen_rect = (void*)API_N(GetRootScreenRect);
	}

	else if (!strcmp(i, __GetViewRect)) {
		lua_setfield(L, -2, __GetViewRect);
		p->self.get_view_rect = (void*)API_N(GetViewRect);
	}

	else if (!strcmp(i, __GetScreenPoint)) {
		lua_setfield(L, -2, __GetScreenPoint);
		p->self.get_screen_point = (void*)API_N(GetScreenPoint);
	}

	else if (!strcmp(i, __GetScreenInfo)) {
		lua_setfield(L, -2, __GetScreenInfo);
		p->self.get_screen_info = (void*)API_N(GetScreenInfo);
	}

	else if (!strcmp(i, __OnPopupShow)) {
		lua_setfield(L, -2, __OnPopupShow);
		p->self.on_popup_show = (void*)API_N(OnPopupShow);
	}

	else if (!strcmp(i, __OnPopupSize)) {
		lua_setfield(L, -2, __OnPopupSize);
		p->self.on_popup_size = (void*)API_N(OnPopupSize);
	}

	else if (!strcmp(i, __OnPaint)) {
		lua_setfield(L, -2, __OnPaint);
		p->self.on_paint = (void*)API_N(OnPaint);
	}

	else if (!strcmp(i, __OnCursorChange)) {
		lua_setfield(L, -2, __OnCursorChange);
		p->self.on_cursor_change = (void*)API_N(OnCursorChange);
	}

	else if (!strcmp(i, __StartDragging)) {
		lua_setfield(L, -2, __StartDragging);
		p->self.start_dragging = (void*)API_N(StartDragging);
	}

	else if (!strcmp(i, __UpdateDragCursor)) {
		lua_setfield(L, -2, __UpdateDragCursor);
		p->self.update_drag_cursor = (void*)API_N(UpdateDragCursor);
	}

	else if (!strcmp(i, __OnScrollOffsetChanged)) {
		lua_setfield(L, -2, __OnScrollOffsetChanged);
		p->self.on_scroll_offset_changed = (void*)API_N(OnScrollOffsetChanged);
	}

	else if (!strcmp(i, __OnIMECompositionRangeChanged)) {
		lua_setfield(L, -2, __OnIMECompositionRangeChanged);
		p->self.get_accessibility_handler = (void*)API_N(OnIMECompositionRangeChanged);
	}

	return 0;
}

API(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

API(unm)
{
	SELF *p = luacef_toudata(L, 1);

	lua_pushlightuserdata(L, p);
	return 1;
}

API_M(meta)
{
	{ "__unm", API_N(unm) },
	{ "__len", API_N(len) },
	{ "__index", API_N(index) },
	{ "__newindex", API_N(newindex) },

	LUAREGEND
};

// register =========================

void API_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, __CefRenderHandler);
	luaL_setfuncs(L, API_N(meta), 0);
	lua_pop(L, 1);

	lua_pushcfunction(L, API_N(new));
	lua_setfield(L, -2, "newRenderHandler");
}