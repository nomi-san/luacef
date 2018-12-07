#include "../luacef.h"

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_menu_model_delegate_capi.h"

//                                   _     _ 
//  _____ ___ ___ _ _    _____ ___ _| |___| |
// |     | -_|   | | |  |     | . | . | -_| |
// |_|_|_|___|_|_|___|  |_|_|_|___|___|___|_|
//============================================

// menu_model ===================================================

/*
	<bool> MenuModel:IsSubMenu()
*/
static int luacef_MenuModel_IsSubMenu(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);

	int r = p->is_sub_menu(p);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:Clear()
*/
static int luacef_MenuModel_Clear(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);

	int r = p->clear(p);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<int> MenuModel:GetCount()
*/
static int luacef_MenuModel_GetCount(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);

	int r = p->get_count(p);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<bool> MenuModel:AddSeparator()
*/
static int luacef_MenuModel_AddSeparator(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);

	int r = p->add_separator(p);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:AddItem(
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_AddItem(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	const cef_string_t label = luacef_tostring(L, 3);

	int r = p->add_item(p, command_id, &label);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:AddCheckItem(
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_AddCheckItem(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	const cef_string_t label = luacef_tostring(L, 3);

	int r = p->add_check_item(p, command_id, &label);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:AddRadioItem(
		<int> command_id,
		<str> label,
		<int> group_id
	)
*/
static int luacef_MenuModel_AddRadioItem(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	const cef_string_t label = luacef_tostring(L, 3);
	int group_id = lua_tointeger(L, 4);

	int r = p->add_radio_item(p, command_id, &label,  group_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<MenuModel> MenuModel:AddSubMenu(
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_AddSubMenu(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	const cef_string_t label = luacef_tostring(L, 3);

	cef_menu_model_t *r = p->add_sub_menu(p, command_id, &label);

	luacef_pushuserdata(L, r, __menu_model__);
	return 1;
}

/*
	<bool> MenuModel:InsertSeparatorAt(
		<int> index
	)
*/
static int luacef_MenuModel_InsertSeparatorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->insert_separator_at(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:InsertItemAt(
		<int> index,
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_InsertItemAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int command_id = lua_tointeger(L, 3);
	const cef_string_t label = luacef_tostring(L, 4);

	int r = p->insert_item_at(p, index, command_id, &label);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:InsertCheckItemAt(
		<int> index,
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_InsertCheckItemAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int command_id = lua_tointeger(L, 3);
	const cef_string_t label = luacef_tostring(L, 4);

	int r = p->insert_check_item_at(p, index, command_id, &label);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:InsertRadioItemAt(
		<int> index,
		<int> command_id,
		<str> label,
		<int> group_id
	)
*/
static int luacef_MenuModel_InsertRadioItemAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int command_id = lua_tointeger(L, 3);
	const cef_string_t label = luacef_tostring(L, 4);
	int group_id = lua_tointeger(L, 5);

	int r = p->insert_radio_item_at(p, index, command_id, &label, group_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<MenuModel> MenuModel:InsertSubMenuAt(
		<int> index,
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_InsertSubMenuAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int command_id = lua_tointeger(L, 3);
	const cef_string_t label = luacef_tostring(L, 4);

	cef_menu_model_t *r = p->insert_sub_menu_at(p, index, command_id, &label);

	luacef_pushuserdata(L, r, __menu_model__);
	return 1;
}

/*
	<bool> MenuModel:Remove(
		<int> command_id
	)
*/
static int luacef_MenuModel_Remove(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->remove(p, command_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:RemoveAt(
		<int> index
	)
*/
static int luacef_MenuModel_RemoveAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->remove_at(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:GetIndexOf(
		<int> command_id
	)
*/
static int luacef_MenuModel_GetIndexOf(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->get_index_of(p, command_id);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<bool> MenuModel:GetIndexOfAt(
		<int> index
	)
*/
static int luacef_MenuModel_GetCommandIdAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->get_index_of(p, index);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetCommandIdAt(
		<int> index,
		<int> command_id
	)
*/
static int luacef_MenuModel_SetCommandIdAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int command_id = lua_tointeger(L, 3);

	int r = p->set_command_id_at(p, index, command_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<str> MenuModel:GetLabel(
		<int> command_id
	)
*/
static int luacef_MenuModel_GetLabel(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	cef_string_userfree_t r = p->get_label(p, command_id);

	luacef_pushstring_free(L, r);
	return 1;
}

/*
	<str> MenuModel:GetLabelAt(
		<int> index
	)
*/
static int luacef_MenuModel_GetLabelAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	cef_string_userfree_t r = p->get_label_at(p, index);

	luacef_pushstring_free(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetLabel(
		<int> command_id,
		<str> label
	)
*/
static int luacef_MenuModel_SetLabel(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	cef_string_t label = luacef_tostring(L, 3);

	int r = p->set_label(p, command_id, &label);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetLabelAt(
		<int> index,
		<str> label
	)
*/
static int luacef_MenuModel_SetLabelAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	cef_string_t label = luacef_tostring(L, 3);

	int r = p->set_label_at(p, index, &label);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<int> MenuModel:GetType(
		<int> command_id
	)
*/
static int luacef_MenuModel_GetType(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	cef_menu_item_type_t r = p->get_type(p, command_id);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<int> MenuModel:GetTypeAt(
		<int> index
	)
*/
static int luacef_MenuModel_GetTypeAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	cef_menu_item_type_t r = p->get_type(p, index);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<int> MenuModel:GetGroupId(
		<int> command_id
	)
*/
static int luacef_MenuModel_GetGroupId(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	cef_menu_item_type_t r = p->get_group_id(p, command_id);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<int> MenuModel:GetGroupIdAt(
		<int> index
	)
*/
static int luacef_MenuModel_GetGroupIdAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	cef_menu_item_type_t r = p->get_group_id_at(p, index);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetGroupId(
		<int> command_id,
		<int> group_id
	)
*/
static int luacef_MenuModel_SetGroupId(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	int group_id = lua_tointeger(L, 3);

	int r = p->set_group_id(p, command_id, group_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetGroupIdAt(
		<int> index,
		<int> group_id
	)
*/
static int luacef_MenuModel_SetGroupIdAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int group_id = lua_tointeger(L, 3);

	int r = p->set_group_id_at(p, index, group_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<MenuModel> MenuModel:GetSubMenu(
		<int> command_id
	)
*/
static int luacef_MenuModel_GetSubMenu(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	cef_menu_model_t *r = p->get_sub_menu(p, command_id);

	luacef_pushuserdata(L, r, __menu_model__);
	return 1;
}

/*
	<MenuModel> MenuModel:GetSubMenuAt(
		<int> index
	)
*/
static int luacef_MenuModel_GetSubMenuAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	cef_menu_model_t *r = p->get_sub_menu_at(p, index);

	luacef_pushuserdata(L, r, __menu_model__);
	return 1;
}

/*
	<bool> MenuModel:IsVisible(
		<int> command_id
	)
*/
static int luacef_MenuModel_IsVisible(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->is_visible(p, command_id);
	
	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:IsVisibleAt(
		<int> index
	)
*/
static int luacef_MenuModel_IsVisibleAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->is_visible(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetVisible(
		<int> visible
	)
*/
static int luacef_MenuModel_SetVisible(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	int visible = lua_toboolean(L, 3);

	int r = p->set_visible(p, command_id, visible);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetVisibleAt(
		<int> index
	)
*/
static int luacef_MenuModel_SetVisibleAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int visible = lua_toboolean(L, 3);

	int r = p->set_visible_at(p, index, visible);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:IsEnabled(
		<int> command_id
	)
*/
static int luacef_MenuModel_IsEnabled(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->is_enabled(p, command_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:IsEnabledAt(
		<int> index
	)
*/
static int luacef_MenuModel_IsEnabledAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->is_enabled_at(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetEnabled(
		<int> command_id,
		<bool> enabled
	)
*/
static int luacef_MenuModel_SetEnabled(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	int enabled = lua_toboolean(L, 3);

	int r = p->set_enabled(p, command_id, enabled);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetEnabledAt(
		<int> index,
		<bool> enabled
	)
*/
static int luacef_MenuModel_SetEnabledAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int enabled = lua_toboolean(L, 3);

	int r = p->set_enabled_at(p, index, enabled);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:IsChecked(
		<int> command_id
	)
*/
static int luacef_MenuModel_IsChecked(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->is_checked(p, command_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:IsCheckedAt(
		<int> index
	)
*/
static int luacef_MenuModel_IsCheckedAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->is_checked_at(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetChecked(
		<int> command_id,
		<bool> checked
	)
*/
static int luacef_MenuModel_SetChecked(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	int checked = lua_toboolean(L, 3);

	int r = p->set_checked(p, command_id, checked);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetCheckedAt(
		<int> index,
		<bool> checked
	)
*/
static int luacef_MenuModel_SetCheckedAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int checked = lua_toboolean(L, 3);

	int r = p->set_checked_at(p, index, checked);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:HasAccelerator(
		<int> command_id
	)
*/
static int luacef_MenuModel_HasAccelerator(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->has_accelerator(p, command_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:HasAcceleratorAt(
		<int> index
	)
*/
static int luacef_MenuModel_HasAcceleratorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->has_accelerator_at(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetAccelerator(
		<int> command_id,
		<int> key_code,
		<bool> shift_pressed,
		<bool> ctrl_pressed,
		<bool> alt_pressed
	)
*/
static int luacef_MenuModel_SetAccelerator(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	int key_code = lua_tointeger(L, 3);
	int shift_pressed = lua_toboolean(L, 4);
	int ctrl_pressed = lua_toboolean(L, 5);
	int alt_pressed = lua_toboolean(L, 6);

	int r = p->set_accelerator(
		p,
		command_id,
		key_code,
		shift_pressed,
		ctrl_pressed,
		alt_pressed
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetAcceleratorAt(
		<int> index,
		<int> key_code,
		<bool> shift_pressed,
		<bool> ctrl_pressed,
		<bool> alt_pressed
	)
*/
static int luacef_MenuModel_SetAcceleratorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	int key_code = lua_tointeger(L, 3);
	int shift_pressed = lua_toboolean(L, 4);
	int ctrl_pressed = lua_toboolean(L, 5);
	int alt_pressed = lua_toboolean(L, 6);

	int r = p->set_accelerator_at(
		p,
		index,
		key_code,
		shift_pressed,
		ctrl_pressed,
		alt_pressed
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:RemoveAccelerator(
		<int> command_id
	)
*/
static int luacef_MenuModel_RemoveAccelerator(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);

	int r = p->remove_accelerator(p, command_id);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:RemoveAcceleratorAt(
		<int> index
	)
*/
static int luacef_MenuModel_RemoveAcceleratorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);

	int r = p->remove_accelerator_at(p, index);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:GetAccelerator(
		<int> command_id,
		<int*> key_code,
		<int*> shift_pressed,
		<int*> ctrl_pressed,
		<int*> alt_pressed
	)
*/
static int luacef_MenuModel_GetAccelerator(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	luacef_int *key_code = luacef_checkudata(L, 3, __int_ptr__);
	luacef_bool *shift_pressed = luacef_checkudata(L, 4, __int_ptr__);
	luacef_bool *ctrl_pressed = luacef_checkudata(L, 5, __int_ptr__);
	luacef_bool *alt_pressed = luacef_checkudata(L, 6, __int_ptr__);

	int r = p->get_accelerator(
		p,
		command_id,
		key_code,
		shift_pressed,
		ctrl_pressed,
		alt_pressed
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:GetAcceleratorAt(
		<int> index,
		<int*> key_code,
		<int*> shift_pressed,
		<int*> ctrl_pressed,
		<int*> alt_pressed
	)
*/
static int luacef_MenuModel_GetAcceleratorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	luacef_int *key_code = luacef_checkudata(L, 3, __int_ptr__);
	luacef_bool *shift_pressed = luacef_checkudata(L, 4, __int_ptr__);
	luacef_bool *ctrl_pressed = luacef_checkudata(L, 5, __int_ptr__);
	luacef_bool *alt_pressed = luacef_checkudata(L, 6, __int_ptr__);

	int r = p->get_accelerator_at(
		p,
		index,
		key_code,
		shift_pressed,
		ctrl_pressed,
		alt_pressed
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetColor(
		<int> command_id,
		<int> color_type,
		<uint> color
	)
*/
static int luacef_MenuModel_SetColor(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	cef_menu_color_type_t color_type = lua_tointeger(L, 3);
	cef_color_t color = lua_tointeger(L, 4);

	int r = p->set_color(
		p,
		command_id,
		color_type,
		color
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetColorAt(
		<int> index,
		<int> color_type,
		<uint> color
	)
*/
static int luacef_MenuModel_SetColorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	cef_menu_color_type_t color_type = lua_tointeger(L, 3);
	cef_color_t color = lua_tointeger(L, 4);

	int r = p->set_color_at(
		p,
		index,
		color_type,
		color
	);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:GetColor(
		<int> command_id,
		<int> color_type,
		<int*> color
	)
*/
static int luacef_MenuModel_GetColor(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	cef_menu_color_type_t color_type = lua_tointeger(L, 3);
	cef_color_t *color = luacef_checkudata(L, 4, __int_ptr__);
	
	int r = p->get_color(
		p,
		command_id,
		color_type,
		color
	);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<bool> MenuModel:GetColorAt(
		<int> index,
		<int> color_type,
		<int*> color
	)
*/
static int luacef_MenuModel_GetColorAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	cef_menu_color_type_t color_type = lua_tointeger(L, 3);
	cef_color_t *color = luacef_checkudata(L, 4, __int_ptr__);

	int r = p->get_color_at(
		p,
		index,
		color_type,
		color
	);

	lua_pushinteger(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetFontList(
		<int> command_id,
		<str> font_list
	)
*/
static int luacef_MenuModel_SetFontList(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int command_id = lua_tointeger(L, 2);
	const cef_string_t font_list = luacef_tostring(L, 3);

	int r = p->set_font_list(p, command_id, &font_list);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<bool> MenuModel:SetFontListAt(
		<int> index,
		<str> font_list
	)
*/
static int luacef_MenuModel_SetFontListAt(lua_State *L)
{
	cef_menu_model_t *p = luacef_touserdata(L, 1);
	int index = lua_tointeger(L, 2);
	const cef_string_t font_list = luacef_tostring(L, 3);

	int r = p->set_font_list_at(p, index, &font_list);

	lua_pushboolean(L, r);
	return 1;
}

/*
	<MenuModel> MenuModel.CreateMenuModel(
		<MenuModelDelegate> delegate
	)
*/
static int luacef_MenuModel_CreateMenuModel(lua_State *L);

static const luaL_Reg luacef_MenuModel_m[] = {
	{ "IsSubMenu", luacef_MenuModel_IsSubMenu },
	{ "Clear", luacef_MenuModel_Clear },
	{ "GetCount", luacef_MenuModel_GetCount },
	{ "AddSeparator", luacef_MenuModel_AddSeparator },
	{ "AddItem", luacef_MenuModel_AddItem },
	{ "AddCheckItem", luacef_MenuModel_AddCheckItem },
	{ "AddRadioItem", luacef_MenuModel_AddRadioItem },
	{ "AddSubMenu", luacef_MenuModel_AddSubMenu },
	{ "InsertSeparatorAt", luacef_MenuModel_InsertSeparatorAt },
	{ "InsertItemAt", luacef_MenuModel_InsertItemAt },
	{ "InsertCheckItemAt", luacef_MenuModel_InsertCheckItemAt },
	{ "InsertRadioItemAt", luacef_MenuModel_InsertRadioItemAt },
	{ "InsertSubMenuAt", luacef_MenuModel_InsertSubMenuAt },
	{ "Remove", luacef_MenuModel_Remove },
	{ "RemoveAt", luacef_MenuModel_RemoveAt },
	{ "GetIndexOf", luacef_MenuModel_GetIndexOf },
	{ "GetCommandIdAt", luacef_MenuModel_GetCommandIdAt },
	{ "SetCommandIdAt", luacef_MenuModel_SetCommandIdAt },
	{ "GetLabel", luacef_MenuModel_GetLabel },
	{ "GetLabelAt", luacef_MenuModel_GetLabelAt },
	{ "SetLabel", luacef_MenuModel_SetLabel },
	{ "SetLabelAt", luacef_MenuModel_SetLabelAt },
	{ "GetType", luacef_MenuModel_GetType },
	{ "GetTypeAt", luacef_MenuModel_GetTypeAt },
	{ "GetGroupId", luacef_MenuModel_GetGroupId },
	{ "GetGroupIdAt", luacef_MenuModel_GetGroupIdAt },
	{ "SetGroupId", luacef_MenuModel_SetGroupId },
	{ "SetGroupIdAt", luacef_MenuModel_SetGroupIdAt },
	{ "GetSubMenu", luacef_MenuModel_GetSubMenu },
	{ "GetSubMenuAt", luacef_MenuModel_GetSubMenuAt },
	{ "IsVisible", luacef_MenuModel_IsVisible },
	{ "IsVisibleAt", luacef_MenuModel_IsVisibleAt },
	{ "SetVisible", luacef_MenuModel_SetVisible },
	{ "SetVisibleAt", luacef_MenuModel_SetVisibleAt },
	{ "IsEnable", luacef_MenuModel_IsEnabled },
	{ "IsEnabledAt", luacef_MenuModel_IsEnabledAt },
	{ "SetEnabled", luacef_MenuModel_SetEnabled },
	{ "SetEnabledAt", luacef_MenuModel_SetEnabledAt },
	{ "IsChecked", luacef_MenuModel_IsChecked },
	{ "IsCheckedAt", luacef_MenuModel_IsCheckedAt },
	{ "SetChecked", luacef_MenuModel_SetChecked },
	{ "SetCheckedAt", luacef_MenuModel_SetCheckedAt },
	{ "HasAccelerator", luacef_MenuModel_HasAccelerator },
	{ "HasAcceleratorAt", luacef_MenuModel_HasAcceleratorAt },
	{ "SetAccelerator", luacef_MenuModel_SetAccelerator },
	{ "SetAcceleratorAt", luacef_MenuModel_SetAcceleratorAt },
	{ "RemoveAccelerator", luacef_MenuModel_RemoveAccelerator },
	{ "RemoveAcceleratorAt", luacef_MenuModel_RemoveAcceleratorAt },
	{ "GetAccelerator", luacef_MenuModel_GetAccelerator },
	{ "GetAcceleratorAt", luacef_MenuModel_GetAcceleratorAt },
	{ "SetColor", luacef_MenuModel_SetColor },
	{ "SetColorAt", luacef_MenuModel_SetColorAt },
	{ "GetColor", luacef_MenuModel_GetColor },
	{ "GetColorAt", luacef_MenuModel_GetColorAt },
	{ "SetFontList", luacef_MenuModel_SetFontList },
	{ "SetFontListAt", luacef_MenuModel_SetFontListAt },
	{ "CreateMenuModel", luacef_MenuModel_CreateMenuModel },
	{ NULL, NULL }
};

// static functions ========================================

static int luacef_MenuModel_CreateMenuModel(lua_State *L)
{
	cef_menu_model_delegate_t *p = luacef_checkudata(L, 1, __menu_model_delegate__);

	cef_menu_model_t *r = cef_menu_model_create(p);

	luacef_pushuserdata(L, r, __menu_model__);
	return 1;
}

// register ====================================

void luacef_MenuModel_reg(lua_State *L)
{
	luaL_newmetatable(L, __menu_model__);
	luaL_setfuncs(L, luacef_MenuModel_m, 0);
	lua_setfield(L, -1, __index__);

	lua_pushcfunction(L, luacef_MenuModel_CreateMenuModel);
	lua_setfield(L, -2, "MenuModelCreate");

	lua_newtable(L);
	luaL_setfuncs(L, luacef_MenuModel_m, 0);
	lua_setfield(L, -2, __menu_model__);
}