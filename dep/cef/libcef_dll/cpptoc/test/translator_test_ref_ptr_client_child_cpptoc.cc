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
// $hash=9b0984f489348c8d182ec919db8e56a2567b583b$
//

#include "libcef_dll/cpptoc/test/translator_test_ref_ptr_client_child_cpptoc.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK translator_test_ref_ptr_client_child_get_other_value(
    struct _cef_translator_test_ref_ptr_client_child_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  int _retval =
      CefTranslatorTestRefPtrClientChildCppToC::Get(self)->GetOtherValue();

  // Return type: simple
  return _retval;
}

int CEF_CALLBACK translator_test_ref_ptr_client_child_get_value(
    struct _cef_translator_test_ref_ptr_client_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  int _retval =
      CefTranslatorTestRefPtrClientChildCppToC::Get(
          reinterpret_cast<cef_translator_test_ref_ptr_client_child_t*>(self))
          ->GetValue();

  // Return type: simple
  return _retval;
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefTranslatorTestRefPtrClientChildCppToC::
    CefTranslatorTestRefPtrClientChildCppToC() {
  GetStruct()->get_other_value =
      translator_test_ref_ptr_client_child_get_other_value;
  GetStruct()->base.get_value = translator_test_ref_ptr_client_child_get_value;
}

template <>
CefRefPtr<CefTranslatorTestRefPtrClientChild>
CefCppToCRefCounted<CefTranslatorTestRefPtrClientChildCppToC,
                    CefTranslatorTestRefPtrClientChild,
                    cef_translator_test_ref_ptr_client_child_t>::
    UnwrapDerived(CefWrapperType type,
                  cef_translator_test_ref_ptr_client_child_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount CefCppToCRefCounted<
    CefTranslatorTestRefPtrClientChildCppToC,
    CefTranslatorTestRefPtrClientChild,
    cef_translator_test_ref_ptr_client_child_t>::DebugObjCt ATOMIC_DECLARATION;
#endif

template <>
CefWrapperType CefCppToCRefCounted<
    CefTranslatorTestRefPtrClientChildCppToC,
    CefTranslatorTestRefPtrClientChild,
    cef_translator_test_ref_ptr_client_child_t>::kWrapperType =
    WT_TRANSLATOR_TEST_REF_PTR_CLIENT_CHILD;