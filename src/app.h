#pragma once

#include "luacef.h"
#include "include/cef_app.h"

namespace LUACEF
{
	class App : public CefApp
	{
	public:
		App(State& L);
		virtual ~App();

		virtual void OnBeforeCommandLineProcessing(
			const CefString& process_type,
			CefRefPtr<CefCommandLine> command_line) override;
		virtual void OnRegisterCustomSchemes(
			CefRawPtr<CefSchemeRegistrar> registrar) override;
		virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override;
		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
		virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

		static int __new(State& L);
		static int __index(State& L);
		static int __newindex(State& L);
		static int __gc(State& L);
		static void __reg(State& L);

		static const char *__name;

	private:
		int m_ref;
		State *m_state;
		IMPLEMENT_REFCOUNTING(App);
	};

	/*
	int CefExecuteProcess(const CefMainArgs& args,
		CefRefPtr<CefApp> application,
		void* windows_sandbox_info);
	*/
	static int ExecuteProcess(lua_State *L)
	{
		const CefMainArgs& args = CefMainArgs();
		CefRefPtr<CefApp> application;
		void* windows_sandbox_info();
		//
		int ret = CefExecuteProcess(args, application, windows_sandbox_info);
		//
		
		lua_pushinteger(L, ret);
		return 1;
	}

	/*
	bool CefInitialize(const CefMainArgs& args,
		const CefSettings& settings,
		CefRefPtr<CefApp> application,
		void* windows_sandbox_info);
	*/
	static int Initialize(lua_State *L)
	{
		// todo
		const CefMainArgs& args = CefMainArgs();
		const CefSettings& settings = CefSettings();
		CefRefPtr<CefApp> application;
		void* windows_sandbox_info();
		//
		bool ret = CefInitialize(args, settings, application, windows_sandbox_info);
		//
		lua_pushboolean(L, ret);
		return 1;
	}

	//void CefShutdown();
	static int Shutdown(lua_State *L)
	{
		CefShutdown();
		return 0;
	}

	//void CefDoMessageLoopWork();
	static int DoMessageLoopWork()
	{
		CefDoMessageLoopWork();
		return 0;
	}

	//void CefRunMessageLoop();
	static int RunMessageLoop()
	{
		CefRunMessageLoop();
		return 0;
	}

	//void CefQuitMessageLoop();
	static int QuitMessageLoop(lua_State *L)
	{
		CefQuitMessageLoop();
		return 0;
	}

	//void CefSetOSModalLoop(bool osModalLoop);
	static int SetOSModalLoop(lua_State *L)
	{
		bool b = lua_toboolean(L, 1);
		CefSetOSModalLoop(b);
		return 0;
	}
	
	//void CEnableHighDPISupport();
	static int EnableHighDPISupport(lua_State *L)
	{
		CefEnableHighDPISupport();
		return 0;
	}
}
