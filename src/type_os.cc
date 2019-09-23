#include "types_os.h"

using namespace LUACEF;

int MainArgs::__new(State& L)
{
	MainArgs *self = new MainArgs();
	
	if (L.isTable(1)) {
		if (L.getField(1, "instance")) {
			self->instance = (HINSTANCE)L.toUserdata(-1);
		}
	}

	pushUPtr(L, self, "CefMainArgs");
	return 1;
}

int MainArgs::__index(State& L)
{
	MainArgs *self; toUPtr(L, self);

	const char *idx = L.toString(2);

	switch (hash(idx)) {
		case hash("instance"):
			L.push((void*)self->instance);
			break;
		default:
			return 0;
	}

	return 1;
}

int MainArgs::__newindex(State& L)
{
	MainArgs *self; toUPtr(L, self);
	if (!self) return 0;

	const char *idx = L.toString(2);
	L.pushValue(3);
	
	switch (hash(idx)) {
		case hash("instance"):
			self->instance = (HINSTANCE)L.toUserdata(-1);
			break;
	}

	return 0;
}

int MainArgs::__gc(State& L)
{
	MainArgs *self;
	
	if (toUPtr(L, self)) {
		delete(self);
	}

	return 0;
}


void MainArgs::__reg(State& L)
{
	static const Reg meta[] = {
		{ "__index", __index },
		{ "__newindex", __newindex },
		{ "__gc", __gc },
		{ NULL, NULL }
	};

	L.newMetatable("CefMainArgs");
	L.setFuncs(meta, 0);
	L.pop(1);

	L.push(__new);
	L.setField(-2, "MainArgs");
}




/*
	CefWindowInfo:SetAsChild(
		<CefWindowHandle> parent,
		<RECT> windowRect
	) -> nil
*/
int WindowInfo::__SetAsChild(State& L)
{
	WindowInfo *self; toUPtr(L, self);

	CefWindowHandle parent;
	RECT windowRect;

	self->SetAsChild(parent, windowRect);

	return 0;
}

/*
	CefWindowInfo:SetAsPopup(
		<CefWindowHandle> parent,
		<CefString> windowName
	) -> nil
*/
int WindowInfo::__SetAsPopup(State& L)
{
	WindowInfo *self; toUPtr(L, self);

	CefWindowHandle parent;
	const CefString& windowName = CefString();

	self->SetAsPopup(parent, windowName);

	return 0;
}

/*
	CefWindowInfo:SetAsWindowless(
		<CefWindowHandle> parent
	) -> nil
*/
int WindowInfo::__SetAsWindowless(State& L)
{
	WindowInfo *self; toUPtr(L, self);

	CefWindowHandle parent;

	self->SetAsWindowless(parent);

	return 0;
}







int WindowInfo::__new(State& L)
{
	WindowInfo *self = new WindowInfo();

	if (L.isTable(1)) {
		
	}

	//
	return 1;
}

int WindowInfo::__index(State& L)
{
	WindowInfo *self; toUPtr(L, self);

	const char *idx = L.toString(2);

	switch (hash(idx)) {
		case hash("SetAsChild"):
			L.push(__SetAsChild);
			break;
		case hash("SetAsPopup"):
			L.push(__SetAsPopup);
			break;
		case hash("SetAsWindowless"):
			L.push(__SetAsWindowless);
			break;
			
		default:
			return 0;
	}

	return 1;
}

int WindowInfo::__newindex(State& L)
{
	WindowInfo *self; toUPtr(L, self);

	const char *idx = L.toString(2);

	switch (hash(idx)) {
		case hash(""):
			break;
	}

	return 0;
}

int WindowInfo::__gc(State &L)
{
	WindowInfo *self;

	if (toUPtr(L, self)) {
		delete(self);
	}

	return 0;
}

void WindowInfo::__reg(State& L)
{
	static const Reg meta[] = {
		{ "__index", __index },
		{ "__newindex", __newindex },
		{ "__gc", __gc },
		{ NULL, NULL }
	};

	L.newMetatable("CefWindowInfo");
	L.setFuncs(meta, 0);
	L.pop(1);

	L.push(__new);
	L.setField(-2, "WindowInfo");
}











