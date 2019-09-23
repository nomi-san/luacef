#include "client.h"

using namespace LUACEF;

Client::Client(State &L) : m_state(&L)
{
}

Client::~Client()
{
}

CefRefPtr<CefAudioHandler> Client::GetAudioHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetAudioHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefAudioHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefContextMenuHandler> Client::GetContextMenuHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetContextMenuHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefContextMenuHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefDialogHandler> Client::GetDialogHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);
	
	if (L.getField(-1, "GetDialogHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefDialogHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefDisplayHandler> Client::GetDisplayHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);
	
	if (L.getField(-1, "GetDisplayHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefDisplayHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefDownloadHandler> Client::GetDownloadHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);
	
	if (L.getField(-1, "GetDownloadHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefDownloadHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefDragHandler> Client::GetDragHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetDragHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefDragHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefFindHandler> Client::GetFindHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetFindHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefFindHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefFocusHandler> Client::GetFocusHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetFocusHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefFocusHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefJSDialogHandler> Client::GetJSDialogHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetJSDialogHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefJSDialogHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefKeyboardHandler> Client::GetKeyboardHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetKeyboardHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefKeyboardHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefLifeSpanHandler> Client::GetLifeSpanHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetLifeSpanHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefLifeSpanHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefLoadHandler> Client::GetLoadHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetLoadHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefLoadHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefRenderHandler> Client::GetRenderHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetRenderHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefRenderHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

CefRefPtr<CefRequestHandler> Client::GetRequestHandler()
{
	State& L = *m_state;
	L.rawget(LUA_REGISTRYINDEX, this->m_ref);

	if (L.getField(-1, "GetRequestHandler")) {

		pushUPtr(L, this, "CefClient"); // p1 - self

		L.pcall(1, 1, 8); // returns 1
		//CefRequestHandler *ret = toUPtr(L, -1);
		//return ret;
	}

	return NULL;
}

bool Client::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
	// todo
	return false;
}



int Client::__new(State& L)
{
	Client *self = new Client(L);

	if (L.isTable(1)) {
		L.push();  // first key
		while (L.next(1) != 0) {
			if (L.isString(-2) && L.isFunc(-1)) {
				const char *idx = L.toString(-2);
				switch (hash(idx)) {
					case hash("GetAudioHandler"):
					case hash("GetContextMenuHandler"):
					case hash("GetDialogHandler"):
					case hash("GetDisplayHandler"):
					case hash("GetDownloadHandler"):
					case hash("GetDragHandler"):
					case hash("GetFindHandler"):
					case hash("GetFocusHandler"):
					case hash("GetJSDialogHandler"):
					case hash("GetKeyboardHandler"):
					case hash("GetLifeSpanHandler"):
					case hash("GetLoadHandler"):
					case hash("GetRenderHandler"):
					case hash("GetRequestHandler"):
					case hash("OnProcessMessageReceived"):
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
	pushUPtr(L, self, "CefClient");
	return 1;
}

int Client::__index(State& L)
{
	Client *self; toUPtr(L, self);

	const char *idx = L.toString(2);

	L.rawget(LUA_REGISTRYINDEX, self->m_ref);
	L.pushValue(-1);

	switch (hash(idx)) {
		case hash("GetAudioHandler"):
		case hash("GetContextMenuHandler"):
		case hash("GetDialogHandler"):
		case hash("GetDisplayHandler"):
		case hash("GetDownloadHandler"):
		case hash("GetDragHandler"):
		case hash("GetFindHandler"):
		case hash("GetFocusHandler"):
		case hash("GetJSDialogHandler"):
		case hash("GetKeyboardHandler"):
		case hash("GetLifeSpanHandler"):
		case hash("GetLoadHandler"):
		case hash("GetRenderHandler"):
		case hash("GetRequestHandler"):
		case hash("OnProcessMessageReceived"):
			L.getField(-1, idx);
			break;

		default:
			return 0;
	}

	return 1;
}

int Client::__newindex(State& L)
{
	Client *self; toUPtr(L, self);

	if (!L.isFunc(3)) return 0;
	const char *idx = L.toString(2);

	L.rawget(LUA_REGISTRYINDEX, self->m_ref);
	L.pushValue(3);

	switch (hash(idx)) {
		case hash("GetAudioHandler"):
		case hash("GetContextMenuHandler"):
		case hash("GetDialogHandler"):
		case hash("GetDisplayHandler"):
		case hash("GetDownloadHandler"):
		case hash("GetDragHandler"):
		case hash("GetFindHandler"):
		case hash("GetFocusHandler"):
		case hash("GetJSDialogHandler"):
		case hash("GetKeyboardHandler"):
		case hash("GetLifeSpanHandler"):
		case hash("GetLoadHandler"):
		case hash("GetRenderHandler"):
		case hash("GetRequestHandler"):
		case hash("OnProcessMessageReceived"):
			L.setField(-2, idx);
			break;
	}

	return 0;
}

int Client::__gc(State& L)
{
	Client *self;
	
	if (toUPtr(L, self)) {
		L.unref(LUA_REGISTRYINDEX, self->m_ref);
		delete(self);
	}

	return 0;
}

void Client::__reg(State& L)
{
	static const Reg meta[] = {
		{ "__index", __index },
		{ "__newindex", __newindex },
		{ "__gc", __gc },
		{ NULL, NULL }
	};

	L.newMetatable("CefClient");
	L.setFuncs(meta);
	L.pop();

	L.push(__new);
	L.setField(-2, "Client");
}