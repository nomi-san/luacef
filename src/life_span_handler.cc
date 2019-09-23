#include "life_span_hadler.h"

using namespace LUACEF;

LifeSpanHandler::LifeSpanHandler(State& L) : m_state(&L)
{
}

LifeSpanHandler::~LifeSpanHandler()
{
}

bool LifeSpanHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& target_url,
	const CefString& target_frame_name,
	WindowOpenDisposition target_disposition,
	bool user_gesture,
	const CefPopupFeatures& popupFeatures,
	CefWindowInfo& windowInfo,
	CefRefPtr<CefClient>& client,
	CefBrowserSettings& settings,
	bool* no_javascript_access)
{
	return false;
}

void LifeSpanHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{

}

bool LifeSpanHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	return false;
}

void LifeSpanHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{

}




int LifeSpanHandler::__new(State& L)
{
	LifeSpanHandler *self = new LifeSpanHandler(L);
	
	if (L.isTable(1)) {
		L.push();  // first key
		while (L.next(1) != 0) {
			if (L.isString(-2) && L.isFunc(-1)) {
				const char *idx = L.toString(-2);
				switch (hash(idx)) {
					case hash("OnBeforePopup"):
					case hash("OnAfterCreated"):
					case hash("DoClose"):
					case hash("OnBeforeClose"):
						break;
				}
			}
			L.pop(1);
		}
		L.pushValue(1); // push table
	}
	else {
		L.newTable();
	}

	self->m_ref = L.ref(LUA_REGISTRYINDEX); // store table
	pushUPtr(L, self);
	return 1;
}

int LifeSpanHandler::__index(State& L)
{
	LifeSpanHandler *self; toUPtr(L, self);

	const char *idx = L.toString(2);

	L.rawget(LUA_REGISTRYINDEX, self->m_ref);
	L.pushValue(-1);

	switch (hash(idx)) {
		case hash("OnBeforePopup"):
		case hash("OnAfterCreated"):
		case hash("DoClose"):
		case hash("OnBeforeClose"):
			L.getField(-1, idx);
			break;

		default:
			return 0;
	}

	return 1;
}

int LifeSpanHandler::__newindex(State& L)
{
	LifeSpanHandler *self; toUPtr(L, self);

	if (!L.isFunc(3)) return 0;
	const char *idx = L.toString(2);

	L.rawget(LUA_REGISTRYINDEX, self->m_ref);
	L.pushValue(3);

	switch (hash(idx)) {
		case hash("OnBeforePopup"):
		case hash("OnAfterCreated"):
		case hash("DoClose"):
		case hash("OnBeforeClose"):
			L.setField(-2, idx);
			break;
	}

	return 0;
}

int LifeSpanHandler::__gc(State& L)
{
	LifeSpanHandler *self; 
	
	if (toUPtr(L, self)) {
		L.unref(LUA_REGISTRYINDEX, self->m_ref);
		delete(self);
	}

	return 0;
}

const char *LifeSpanHandler::__name = "CefLifeSpanHandler";

void LifeSpanHandler::__reg(State& L)
{
	static const Reg meta[] = {
		{ "__index", __index },
		{ "__newindex", __newindex },
		{ "__gc", __gc },
		{ NULL, NULL }
	};

	L.newMetatable(__name);
	L.setFuncs(meta);
	L.pop();

	L.push(__new);
	L.setField(-2, "LifeSpanHandler");
}