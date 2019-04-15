// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"
#include "include/wrapper/cef_message_router.h"
#include "simple_handler.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp
				,public CefBrowserProcessHandler 
				,public CefRenderProcessHandler {
 public:
  SimpleApp(HWND hwnd);

  // CefApp methods:
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
      OVERRIDE {
    return this;
  }
  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
	  OVERRIDE {
	  return this;
  }
  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() OVERRIDE;


  virtual void OnWebKitInitialized() OVERRIDE;

  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) OVERRIDE;

  SimpleHandler* GetClientHandler()
  {
	  return handler_;
  }
 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleApp);

  HWND parent_;

  CefRefPtr<CefMessageRouterRendererSide> message_router_;

  SimpleHandler *handler_ = nullptr;
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
