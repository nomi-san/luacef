#pragma once

#include "luacef.h"
#include "include/cef_life_span_handler.h"

namespace LUACEF
{
	class LifeSpanHandler : public CefLifeSpanHandler
	{
	public:
		LifeSpanHandler(State& L);
		virtual ~LifeSpanHandler();

		virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			const CefString& target_url,
			const CefString& target_frame_name,
			WindowOpenDisposition target_disposition,
			bool user_gesture,
			const CefPopupFeatures& popupFeatures,
			CefWindowInfo& windowInfo,
			CefRefPtr<CefClient>& client,
			CefBrowserSettings& settings,
			bool* no_javascript_access) override;
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
		virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

		static int __new(State& L);
		static int __index(State& L);
		static int __newindex(State& L);
		static int __gc(State& L);
		static void __reg(State& L);

		static const char *__name;

	private:
		int m_ref;
		State *m_state;
		IMPLEMENT_REFCOUNTING(LifeSpanHandler);
	};
}