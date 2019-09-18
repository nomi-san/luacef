// Copyright (c) 2019 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=c17ffc9433d72bc86a6ba0a5bd603ebb549bb18d$
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_CONTEXT_MENU_PARAMS_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_CONTEXT_MENU_PARAMS_CTOCPP_H_
#pragma once

#if !defined(WRAPPING_CEF_SHARED)
#error This file can be included wrapper-side only
#endif

#include <vector>
#include "include/capi/cef_context_menu_handler_capi.h"
#include "include/cef_context_menu_handler.h"
#include "libcef_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefContextMenuParamsCToCpp
    : public CefCToCppRefCounted<CefContextMenuParamsCToCpp,
                                 CefContextMenuParams,
                                 cef_context_menu_params_t> {
 public:
  CefContextMenuParamsCToCpp();

  // CefContextMenuParams methods.
  int GetXCoord() OVERRIDE;
  int GetYCoord() OVERRIDE;
  TypeFlags GetTypeFlags() OVERRIDE;
  CefString GetLinkUrl() OVERRIDE;
  CefString GetUnfilteredLinkUrl() OVERRIDE;
  CefString GetSourceUrl() OVERRIDE;
  bool HasImageContents() OVERRIDE;
  CefString GetTitleText() OVERRIDE;
  CefString GetPageUrl() OVERRIDE;
  CefString GetFrameUrl() OVERRIDE;
  CefString GetFrameCharset() OVERRIDE;
  MediaType GetMediaType() OVERRIDE;
  MediaStateFlags GetMediaStateFlags() OVERRIDE;
  CefString GetSelectionText() OVERRIDE;
  CefString GetMisspelledWord() OVERRIDE;
  bool GetDictionarySuggestions(std::vector<CefString>& suggestions) OVERRIDE;
  bool IsEditable() OVERRIDE;
  bool IsSpellCheckEnabled() OVERRIDE;
  EditStateFlags GetEditStateFlags() OVERRIDE;
  bool IsCustomMenu() OVERRIDE;
  bool IsPepperMenu() OVERRIDE;
};

#endif  // CEF_LIBCEF_DLL_CTOCPP_CONTEXT_MENU_PARAMS_CTOCPP_H_
