#include "../luacef.h"
#include "include/capi/cef_image_capi.h"

typedef cef_image_t luacef_Image;

#define IMG(fn) \
	LCEF_API(Image, fn)

#define IMG_N(fn) \
	LCEF_API_N(Image, fn)

#define IMG_M(mname) \
	LCEF_M(Image, mname)

#define SELF luacef_Image

/*
	<CefImage> Image;

	-- create new Image
	<CefImage> cef.Image.Create()
	<CefImage> Image.Create()

	-- check is empty
	<int> Image:IsEmpty()

	-- check is same between two Image
	<int> Image:IsSame(<CefImage> that)

	-- add Bitmap
	<int> Image:AddBitmap(
		<num>   scale_factor,
		<int>   pixel_width, 
		<int>   pixel_height, 
		<int>   color_type, 
		<int>   alpha_type, 
		<udata> pixel_data,
		<int>   pixel_data_size
	)

	-- add PNG
	<int> Image:AddPNG(
		<num>   scale_factor,
		<udata> png_data,
		<int>   png_data_size
	)

	-- add JPEG
	<int> Image:AddJPEG(
		<num>   scale_factor,
		<udata> jpeg_data,
		<int>   jpeg_data_size
	)

	-- get width
	<int> Image:GetWidth()

	-- get height
	<int> Image:GetHeight()

	-- check if has representation
	<int> Image:HasRepresentation(
		<num> scale_factor
	)

	-- remove representation
	<int> Image:RemoveRepresentation(
		<num> scale_factor
	)

	-- get representation info
	<table> GetRepresentationInfo(
		<num> scale_factor
	)
		-> table { .scale, .width, .height }

	-- get as Bitmap
	<CefBinaryValue> Image:GetAsBitmap(
		<num>    scale_factor,
		<int>    color_type,
		<int>    alpha_type,
		<IntPtr> pixel_width, -- in/out
		<IntPtr> pixel_heigh  -- in/out
	)

	-- get as PNG
	<CefBinaryValue> Image:GetAsPNG(
		<num>    scale_factor,
		<int>    quality,
		<IntPtr> pixel_width, -- in/out
		<IntPtr> pixel_heigh  -- in/out
	)

	-- get as JPEG
	<CefBinaryValue> Image:GetAsJPEG(
		<num>    scale_factor,
		<int>    quality,
		<IntPtr> pixel_width, -- in/out
		<IntPtr> pixel_heigh  -- in/out
	)

	-- get sizeof
	<int> #Image

	-- get pointer
	<udata> -Image
*/

// api

IMG(IsEmpty)
{
	SELF *p = luacef_toudata(L, 1);

	int ret = p->is_empty(p);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(IsSame)
{
	SELF *p = luacef_toudata(L, 1);
	SELF *that = luacef_toudata(L, 2);

	int ret = p->is_same(p, that);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(AddBitmap)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);
	int pixel_width = lua_tointeger(L, 3);
	int pixel_height = lua_tointeger(L, 4);
	cef_color_type_t color_type = lua_tointeger(L, 5);
	cef_alpha_type_t alpha_type = lua_tointeger(L, 6);
	const void* pixel_data = lua_touserdata(L, 7);
	size_t pixel_data_size = lua_tointeger(L, 8);

	int ret = p->add_bitmap(
		p,
		scale_factor,
		pixel_width,
		pixel_height,
		color_type,
		alpha_type,
		pixel_data,
		pixel_data_size
	);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(AddPNG)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);
	const void* png_data = lua_touserdata(L, 3);
	size_t png_data_size = lua_tointeger(L, 4);

	int ret = p->add_png(
		p,
		scale_factor,
		png_data,
		png_data_size
	);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(AddJPEG)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);
	const void* jpeg_data = lua_touserdata(L, 3);
	size_t jpeg_data_size = lua_tointeger(L, 4);
	
	int ret = p->add_jpeg(
		p,
		scale_factor,
		jpeg_data,
		jpeg_data_size
	);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(GetWidth)
{
	SELF *p = luacef_toudata(L, 1);

	size_t ret = p->get_width(p);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(GetHeight)
{
	SELF *p = luacef_toudata(L, 1);

	size_t ret = p->get_height(p);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(HasRepresentation)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);

	int ret = p->has_representation(
		p,
		scale_factor
	);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(RemoveRepresentation)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);

	int ret = p->remove_representation(
		p,
		scale_factor
	);

	lua_pushinteger(L, ret);
	return 1;
}

IMG(GetRepresentationInfo)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);

	float actual_scale_factor;
	int pixel_width;
	int pixel_height;

	int ret = p->get_representation_info(
		p,
		scale_factor,
		&actual_scale_factor,
		&pixel_width,
		&pixel_height
	);

	if (ret) {
		lua_newtable(L);
		lua_pushnumber(L, actual_scale_factor);
		lua_setfield(L, -2, "scale");
		lua_pushinteger(L, pixel_width);
		lua_setfield(L, -2, "width");
		lua_pushinteger(L, pixel_height);
		lua_setfield(L, -2, "height");
	}
	else
		return 0;

	return 1;
}

IMG(GetAsBitmap)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);
	cef_color_type_t color_type = lua_tointeger(L, 3);
	cef_alpha_type_t alpha_type = lua_tointeger(L, 4);
	IntPtr pixel_width = luacef_toudata(L, 5);
	IntPtr pixel_heigh = luacef_toudata(L, 6);

	cef_binary_value_t *ret = p->get_as_bitmap(
		p,
		scale_factor,
		color_type,
		alpha_type,
		pixel_width,
		pixel_heigh
	);

	luacef_pushudata(L, ret, __binary_value__);
	return 1;
}

IMG(GetAsPNG)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);
	int with_transparency = lua_tointeger(L, 3);
	IntPtr pixel_width = luacef_toudata(L, 4);
	IntPtr pixel_heigh = luacef_toudata(L, 5);

	cef_binary_value_t *ret = p->get_as_png(
		p,
		scale_factor,
		with_transparency,
		pixel_width,
		pixel_heigh
	);

	luacef_pushudata(L, ret, __binary_value__);
	return 1;
}

IMG(GetAsJPEG)
{
	SELF *p = luacef_toudata(L, 1);
	float scale_factor = lua_tonumber(L, 2);
	int quality = lua_tointeger(L, 3);
	IntPtr pixel_width = luacef_toudata(L, 4);
	IntPtr pixel_heigh = luacef_toudata(L, 5);

	cef_binary_value_t *ret = p->get_as_jpeg(
		p,
		scale_factor,
		quality,
		pixel_width,
		pixel_heigh
	);

	luacef_pushudata(L, ret, __binary_value__);
	return 1;
}

// static

IMG(Create)
{
	SELF *p = cef_image_create();

	luacef_pushudata(L, p, __binary_value__);
	return 1;
}

// =========================

IMG(len)
{
	lua_pushinteger(L, sizeof(SELF));
	return 1;
}

IMG(unm)
{
	SELF *p = cef_image_create();

	lua_pushlightuserdata(L, p);
	return 1;
}

// =========================

IMG_M(meta)
{
	{ "__len", IMG_N(len) },
	{ "__unm", IMG_N(unm) },

	{ "IsEmpty", IMG_N(IsEmpty) },
	{ "IsSame", IMG_N(IsSame) },
	{ "AddBitmap", IMG_N(AddBitmap) },
	{ "AddPNG", IMG_N(AddPNG) },
	{ "AddJPEG", IMG_N(AddJPEG) },
	{ "GetWidth", IMG_N(GetWidth) },
	{ "GetHeight", IMG_N(GetHeight) },
	{ "HasRepresentation", IMG_N(HasRepresentation) },
	{ "RemoveRepresentation", IMG_N(RemoveRepresentation) },
	{ "GetRepresentationInfo", IMG_N(GetRepresentationInfo) },
	{ "GetAsBitmap", IMG_N(GetAsBitmap) },
	{ "GetAsPNG", IMG_N(GetAsPNG) },
	{ "GetAsJPEG", IMG_N(GetAsJPEG) },

	{ "Create", IMG_N(Create) },

	LUAREGEND
};

IMG_M(meta_static)
{
	{ "Create", IMG_N(Create) },

	LUAREGEND
};

// =========================

void IMG_N(reg)(lua_State *L)
{
	luaL_newmetatable(L, __image__);
	luaL_setfuncs(L, IMG_N(meta), 0);
	lua_setfield(L, -1, __index__);

	lua_newtable(L);
	luaL_setfuncs(L, IMG_N(meta_static), 0);
	lua_setfield(L, -2, "Image");
}