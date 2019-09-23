#include "browser.h"
#include "client.h"

using namespace LUACEF;

typedef cef_drag_operations_mask_t DragOperationsMask;
typedef cef_file_dialog_mode_t FileDialogMode;
typedef cef_mouse_button_type_t MouseButtonType;
typedef cef_paint_element_type_t PaintElementType;

namespace
{
	//virtual CefRefPtr<CefBrowserHost> GetHost() = 0;
	static int GetHost(State& L)
	{
		Browser *self; toUPtr(L, self);

		BrowserHost *ret;
		LUACEF_CAST_PTR(ret, self->GetHost());
		pushUPtr(L, ret, "CefBrowserHost");
		return 1;
	}

	//virtual bool CanGoBack() = 0;
	static int CanGoBack(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += self->CanGoBack();
		return 1;
	}

	//virtual void GoBack() = 0;
	static int GoBack(State& L)
	{
		Browser *self; toUPtr(L, self);

		self->GoBack();
		return 0;
	}

	//virtual bool CanGoForward() = 0;
	static int CanGoForward(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += self->CanGoForward();
		return 1;
	}

	//virtual void GoForward() = 0;
	static int GoForward(State& L)
	{
		Browser *self; toUPtr(L, self);

		self->GoForward();
		return 0;
	}

	//virtual bool IsLoading() = 0;
	static int IsLoading(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += self->IsLoading();
		return 1;
	}

	//virtual void Reload() = 0;
	static int Reload(State& L)
	{
		Browser *self; toUPtr(L, self);

		self->Reload();
		return 0;
	}

	//virtual void ReloadIgnoreCache() = 0;
	static int ReloadIgnoreCache(State& L)
	{
		Browser *self; toUPtr(L, self);

		self->ReloadIgnoreCache();
		return 0;
	}

	//virtual void StopLoad() = 0;
	static int StopLoad(State& L)
	{
		Browser *self; toUPtr(L, self);

		self->StopLoad();
		return 0;
	}

	//virtual int GetIdentifier() = 0;
	static int GetIdentifier(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += self->GetIdentifier();
		return 1;
	}

	//virtual bool IsSame(CefRefPtr<CefBrowser> that) = 0;
	static int IsSame(State& L)
	{
		Browser *self; toUPtr(L, self);
		Browser *that; toUPtr(L, that, 2);

		L += self->IsSame(that);
		return 1;
	}

	//virtual bool IsPopup() = 0;
	static int IsPopup(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += self->IsPopup();
		return 1;
	}

	//virtual bool HasDocument() = 0;
	static int HasDocument(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += self->HasDocument();
		return 1;
	}

	//virtual CefRefPtr<CefFrame> GetMainFrame() = 0;
	static int GetMainFrame(State& L)
	{
		Browser *self; toUPtr(L, self);
		// todo
	}

	//virtual CefRefPtr<CefFrame> GetFocusedFrame() = 0;
	static int GetFocusedFrame(State& L)
	{
		Browser *self; toUPtr(L, self);
		// todo
	}

	//virtual CefRefPtr<CefFrame> GetFrame(int64 identifier) = 0;
	//virtual CefRefPtr<CefFrame> GetFrame(const CefString& name) = 0;
	static int GetFrame(State& L)
	{
		Browser *self; toUPtr(L, self);
		// todo
	}

	//virtual size_t GetFrameCount() = 0;
	static int GetFrameCount(State& L)
	{
		Browser *self; toUPtr(L, self);

		L += (int64_t)self->GetFrameCount();
		return 1;
	}

	//virtual void GetFrameIdentifiers(std::vector<int64>& identifiers) = 0;
	static int GetFrameIdentifiers(State& L)
	{
		// todo
	}

	//virtual void GetFrameNames(std::vector<CefString>& names) = 0;
	static int GetFrameNames(State& L)
	{
		// todo
	}

	//virtual bool SendProcessMessage(CefProcessId target_process,
	//	CefRefPtr<CefProcessMessage> message) = 0;
	static int SendProcessMessage(State& L)
	{
		// todo
	}

	



}

namespace
{
	/*
	static bool CreateBrowser(const CefWindowInfo& windowInfo,
		CefRefPtr<CefClient> client,
		const CefString& url,
		const CefBrowserSettings& settings,
		CefRefPtr<CefRequestContext> request_context);
	*/
	static int CreateBrowser(State& L)
	{
		const CefWindowInfo& windowInfo = {};
		CefRefPtr<CefClient> client;
		const CefString& url = {};
		const CefBrowserSettings& settings = {};
		CefRefPtr<CefRequestContext> request_context;

		L += BrowserHost::CreateBrowser(windowInfo, client, url, settings, request_context);
		return 1;
	}

	/*
	static CefRefPtr<CefBrowser> CreateBrowserSync(
		const CefWindowInfo& windowInfo,
		CefRefPtr<CefClient> client,
		const CefString& url,
		const CefBrowserSettings& settings,
		CefRefPtr<CefRequestContext> request_context);
	*/
	static int CreateBrowserSync(State& L)
	{
		const CefWindowInfo& windowInfo = {};
		CefRefPtr<CefClient> client;
		const CefString& url = {};
		const CefBrowserSettings& settings = {};
		CefRefPtr<CefRequestContext> request_context;

		//Browser *ret;
		//ret = CreateBrowserSync(windowInfo, client, url, settings, request_context);
		//lua_pushboolean(L, ret);
		return 1;
	}


	//////////////


	//virtual CefRefPtr<CefBrowser> GetBrowser() = 0;
	static int GetBrowser(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		auto ret = self->GetBrowser();
		pushUPtr(L, ret, "CefBrowser");
		return 1;
	}

	//virtual void CloseBrowser(bool force_close) = 0;
	static int CloseBrowser(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool force_close = L.toBool(2);

		self->CloseBrowser(force_close);
		return 0;
	}

	//virtual bool TryCloseBrowser() = 0;
	static int TryCloseBrowser(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->TryCloseBrowser();
		return 1;
	}

	//virtual void SetFocus(bool focus) = 0;
	static int SetFocus(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool focus = L.toBool(2);

		self->SetFocus(focus);
		return 0;
	}

	//virtual CefWindowHandle GetWindowHandle() = 0;

	//virtual CefWindowHandle GetOpenerWindowHandle() = 0;

	//virtual bool HasView() = 0;
	static int HasView(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->HasView();
		return 1;
	}

	//virtual CefRefPtr<CefClient> GetClient() = 0;
	static int GetClient(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		auto ret = self->GetClient();
		pushUPtr(L, ret, "CefClient");
		return 1;
	}

	//virtual CefRefPtr<CefRequestContext> GetRequestContext() = 0;

	//virtual double GetZoomLevel() = 0;
	static int GetZoomLevel(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->GetZoomLevel();
		return 1;
	}

	//virtual void SetZoomLevel(double zoomLevel) = 0;
	static int SetZoomLevel(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		double zoomLevel = L.toNum(20);

		self->SetZoomLevel(zoomLevel);
		return 0;
	}

	/*
	virtual void RunFileDialog(FileDialogMode mode,
		const CefString& title,
		const CefString& default_file_path,
		const std::vector<CefString>& accept_filters,
		int selected_accept_filter,
		CefRefPtr<CefRunFileDialogCallback> callback) = 0;
		*/

	//virtual void StartDownload(const CefString& url) = 0;

	/*
	virtual void DownloadImage(const CefString& image_url,
		bool is_favicon,
		uint32 max_image_size,
		bool bypass_cache,
		CefRefPtr<CefDownloadImageCallback> callback) = 0;
		*/

	//virtual void Print() = 0;
	static int Print(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->Print();
		return 0;
	}

	/*
	virtual void PrintToPDF(const CefString& path,
		const CefPdfPrintSettings& settings,
		CefRefPtr<CefPdfPrintCallback> callback) = 0;
		*/

	/*
	virtual void Find(int identifier,
		const CefString& searchText,
		bool forward,
		bool matchCase,
		bool findNext) = 0;
		*/

	//virtual void StopFinding(bool clearSelection) = 0;
	static int StopFinding(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool clearSelection = L.toBool(2);

		self->StopFinding(clearSelection);
		return 0;
	}

	/*
	virtual void ShowDevTools(const CefWindowInfo& windowInfo,
		CefRefPtr<CefClient> client,
		const CefBrowserSettings& settings,
		const CefPoint& inspect_element_at) = 0;
		*/

	//virtual void CloseDevTools() = 0;
	static int CloseDevTools(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->CloseDevTools();
		return 0;
	}

	//virtual bool HasDevTools() = 0;
	static int HasDevTools(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->HasDevTools();
		return 1;
	}

	/*
	virtual void GetNavigationEntries(
		CefRefPtr<CefNavigationEntryVisitor> visitor,
		bool current_only) = 0;
		*/

	//virtual void SetMouseCursorChangeDisabled(bool disabled) = 0;
	static int SetMouseCursorChangeDisabled(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool disabled = L.toBool(2);

		self->SetMouseCursorChangeDisabled(disabled);
		return 0;
	}

	//virtual bool IsMouseCursorChangeDisabled() = 0;
	static int IsMouseCursorChangeDisabled(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->IsMouseCursorChangeDisabled();
		return 1;
	}

	//virtual void ReplaceMisspelling(const CefString& word) = 0;

	//virtual void AddWordToDictionary(const CefString& word) = 0;

	//virtual bool IsWindowRenderingDisabled() = 0;
	static int IsWindowRenderingDisabled(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->IsWindowRenderingDisabled();
		return 1;
	}

	//virtual void WasResized() = 0;
	static int WasResized(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->WasResized();
		return 0;
	}

	//virtual void WasHidden(bool hidden) = 0;
	static int WasHidden(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool hidden = L.toBool(2);

		self->WasHidden(hidden);
		return 0;
	}

	//virtual void NotifyScreenInfoChanged() = 0;
	static int NotifyScreenInfoChanged(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->NotifyScreenInfoChanged();
		return 0;
	}

	//virtual void Invalidate(PaintElementType type) = 0;
	static int Invalidate(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		PaintElementType type = PaintElementType(L.toInt(2));

		self->Invalidate(type);
		return 0;
	}

	//virtual void SendExternalBeginFrame() = 0;
	static int SendExternalBeginFrame(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->SendExternalBeginFrame();
		return 0;
	}

	//virtual void SendKeyEvent(const CefKeyEvent& event) = 0;

	/*
	virtual void SendMouseClickEvent(const CefMouseEvent& event,
		MouseButtonType type,
		bool mouseUp,
		int clickCount) = 0;
		*/

	/*
	virtual void SendMouseMoveEvent(const CefMouseEvent& event,
		bool mouseLeave) = 0;
		*/

	/*
	virtual void SendMouseWheelEvent(const CefMouseEvent& event,
		int deltaX,
		int deltaY) = 0;
		*/

	//virtual void SendTouchEvent(const CefTouchEvent& event) = 0;

	//virtual void SendFocusEvent(bool setFocus) = 0;
	static int SendFocusEvent(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool setFocus = L.toBool(2);

		self->SendFocusEvent(setFocus);
		return 0;
	}

	//virtual void SendCaptureLostEvent() = 0;
	static int SendCaptureLostEvent(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->SendCaptureLostEvent();
		return 0;
	}

	//virtual void NotifyMoveOrResizeStarted() = 0;
	static int NotifyMoveOrResizeStarted(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->NotifyMoveOrResizeStarted();
		return 0;
	}

	//virtual int GetWindowlessFrameRate() = 0;
	static int GetWindowlessFrameRate(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->GetWindowlessFrameRate();
		return 1;
	}

	//virtual void SetWindowlessFrameRate(int frame_rate) = 0;
	static int SetWindowlessFrameRate(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		int frame_rate = L.toInt(2);

		self->SetWindowlessFrameRate(frame_rate);
		return 0;
	}

	/*
	virtual void ImeSetComposition(
		const CefString& text,
		const std::vector<CefCompositionUnderline>& underlines,
		const CefRange& replacement_range,
		const CefRange& selection_range) = 0;
		*/

	/*
	virtual void ImeCommitText(const CefString& text,
		const CefRange& replacement_range,
		int relative_cursor_pos) = 0;
		*/

	//virtual void ImeFinishComposingText(bool keep_selection) = 0;
	static int ImeFinishComposingText(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool keep_selection = L.toBool(2);

		self->ImeFinishComposingText(keep_selection);
		return 0;
	}

	//virtual void ImeCancelComposition() = 0;
	static int ImeCancelComposition(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->ImeCancelComposition();
		return 0;
	}

	/*
	virtual void DragTargetDragEnter(CefRefPtr<CefDragData> drag_data,
		const CefMouseEvent& event,
		DragOperationsMask allowed_ops) = 0;
		*/

	/*
	virtual void DragTargetDragOver(const CefMouseEvent& event,
		DragOperationsMask allowed_ops) = 0;
		*/

	//virtual void DragTargetDragLeave() = 0;
	static int DragTargetDragLeave(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->DragTargetDragLeave();
		return 0;
	}

	//virtual void DragTargetDrop(const CefMouseEvent& event) = 0;

	//virtual void DragSourceEndedAt(int x, int y, DragOperationsMask op) = 0;

	//virtual void DragSourceSystemDragEnded() = 0;
	static int DragSourceSystemDragEnded(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		self->DragSourceSystemDragEnded();
		return 0;
	}

	//virtual CefRefPtr<CefNavigationEntry> GetVisibleNavigationEntry() = 0;

	//virtual void SetAccessibilityState(cef_state_t accessibility_state) = 0;

	/*
	virtual void SetAutoResizeEnabled(bool enabled,
		const CefSize& min_size,
		const CefSize& max_size) = 0;
		*/

	//virtual CefRefPtr<CefExtension> GetExtension() = 0;

	//virtual bool IsBackgroundHost() = 0;
	static int IsBackgroundHost(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->IsBackgroundHost();
		return 1;
	}

	//virtual void SetAudioMuted(bool mute) = 0;
	static int SetAudioMuted(State& L)
	{
		BrowserHost *self; toUPtr(L, self);
		bool mute = L.toBool(2);

		self->SetAudioMuted(mute);
		return 0;
	}

	//virtual bool IsAudioMuted() = 0;
	static int IsAudioMuted(State& L)
	{
		BrowserHost *self; toUPtr(L, self);

		L += self->IsAudioMuted();
		return 1;
	}
}