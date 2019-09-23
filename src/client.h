#pragma once

#include "luacef.h"
#include "include/cef_client.h"

namespace LUACEF
{
	class Client : public CefClient
	{
	public:
		Client(State &L);
		virtual ~Client();

		virtual CefRefPtr<CefAudioHandler> GetAudioHandler() override;
		virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;
		virtual CefRefPtr<CefDialogHandler> GetDialogHandler() override;
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
		virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() override;
		virtual CefRefPtr<CefDragHandler> GetDragHandler() override;
		virtual CefRefPtr<CefFindHandler> GetFindHandler() override;
		virtual CefRefPtr<CefFocusHandler> GetFocusHandler() override;
		virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override;
		virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override;
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;
		virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override;
		virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override;
		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message) override;

		static int __new(State& L);
		static int __index(State& L);
		static int __newindex(State& L);
		static int __gc(State& L);
		static void __reg(State& L);

	private:
		int m_ref;
		State *m_state;
		IMPLEMENT_REFCOUNTING(Client);
	};
}