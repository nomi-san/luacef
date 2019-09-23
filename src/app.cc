#include "app.h"

using namespace LUACEF;

App::App(State& L) : m_state(&L)
{
}

App::~App()
{
}

void App::OnBeforeCommandLineProcessing(
	const CefString& process_type,
	CefRefPtr<CefCommandLine> command_line)
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, m_ref);

	if (L.getField(-1, "OnBeforeCommandLineProcessing")) {

		pushUPtr(L, this); // p1 - self
		//pushUPtr(L, process_type, "CefString"); // p2
		//pushUPtr(L, command_line, "CefCommandLine"); // 3

		L.pcall(3, 0, 8); // returns 0
	}
}

void App::OnRegisterCustomSchemes(
	CefRawPtr<CefSchemeRegistrar> registrar)
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, m_ref);

	if (L.getField(-1, "OnRegisterCustomSchemes")) {

		pushUPtr(L, this); // p1 - self
		// p2

		L.pcall(2, 0, 8); // returns 0
	}
}

CefRefPtr<CefResourceBundleHandler> App::GetResourceBundleHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, m_ref);

	if (L.getField(-1, "GetResourceBundleHandler")) {

		pushUPtr(L, this); // p1 - self
		
		L.pcall(1, 1, 8); // returns 1
		//CefResourceBundleHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefBrowserProcessHandler> App::GetBrowserProcessHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, m_ref);

	if (L.getField(-1, "GetBrowserProcessHandler")) {

		pushUPtr(L, this); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefBrowserProcessHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefRenderProcessHandler> App::GetRenderProcessHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, m_ref);

	if (L.getField(-1, "GetRenderProcessHandler")) {

		pushUPtr(L, this); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefRenderProcessHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}




int App::__new(State& L)
{
	App *self = new App(L);
	
	if (L.isTable(1)) {
		L.push();  // first key
		while (L.next(1) != 0) {
			if (L.isString(-2) && L.isFunc(-1)) {
				const char *idx = L.toString(-2);
				switch (hash(idx)) {
					case hash("OnBeforeCommandLineProcessing"):
					case hash("OnRegisterCustomSchemes"):
					case hash("GetResourceBundleHandler"):
					case hash("GetBrowserProcessHandler"):
					case hash("GetRenderProcessHandler"):
						break;
				}
			}
			L.pop(1);
		}
		L.pushValue(1); // push table
	}
	else {
		L.createTable();
	}

	self->m_ref = L.ref(LUA_REGISTRYINDEX); // store table
	pushUPtr(L, self);
	return 1;
}

int App::__index(State& L)
{
	App *self; toUPtr(L, self);

	const char *idx = L.toString(2);

	L.rawget(LUA_REGISTRYINDEX, self->m_ref);
	L.pushValue(-1);

	switch (hash(idx)) {
		case hash("OnBeforeCommandLineProcessing"):
		case hash("OnRegisterCustomSchemes"):
		case hash("GetResourceBundleHandler"):
		case hash("GetBrowserProcessHandler"):
		case hash("GetRenderProcessHandler"):
			L.getField(-1, idx);
			break;

		default:
			return 0;
	}

	return 1;
}

int App::__newindex(State& L)
{
	App *self; toUPtr(L, self);

	if (!L.isFunc(3)) return 0;
	const char *idx = L.toString(2);

	L.rawget(LUA_REGISTRYINDEX, self->m_ref);
	L.pushValue(3);

	switch (hash(idx)) {
		case hash("OnBeforeCommandLineProcessing"):
		case hash("OnRegisterCustomSchemes"):
		case hash("GetResourceBundleHandler"):
		case hash("GetBrowserProcessHandler"):
		case hash("GetRenderProcessHandler"):
			L.setField(-2, idx);
			break;
	}

	return 0;
}

int App::__gc(State& L)
{
	App *self;

	if (toUPtr(L, self)) {
		L.unref(LUA_REGISTRYINDEX, self->m_ref);
		delete(self);
	}

	return 0;
}

const char *App::__name = "CefApp";

void App::__reg(State& L)
{
	static const Reg meta[] = {
		{ "__index", __index },
		{ "__newindex", __newindex },
		{ "__gc", __gc },
		{ NULL, NULL }
	};

	L.newMetatable(__name);
	L.setFuncs(meta, 0);
	L.pop(1);

	L.push(__new);
	L.setField(-2, "App");
}