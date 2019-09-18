#include "app.h"

LUACEF_USING;

App::App()
{
	this->L = lState;
}

App::App(lua_State *L)
{
	this->L = L;
}

App::~App()
{

}

void App::OnBeforeCommandLineProcessing(
	const CefString& process_type,
	CefRefPtr<CefCommandLine> command_line)
{

}

void App::OnRegisterCustomSchemes(
	CefRawPtr<CefSchemeRegistrar> registrar)
{

}

CefRefPtr<CefResourceBundleHandler> App::GetResourceBundleHandler()
{
	return NULL;
}

CefRefPtr<CefBrowserProcessHandler> App::GetBrowserProcessHandler()
{
	return NULL;
}

CefRefPtr<CefRenderProcessHandler> App::GetRenderProcessHandler()
{
	return NULL;
}