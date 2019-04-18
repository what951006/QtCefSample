

#pragma comment(lib,"libcef")
#ifdef NDEBUG
#pragma comment(lib,"libcef_dll_wrapper")
#else
#pragma comment(lib,"libcef_dll_wrapper")
#endif

#include "CefBrowser.h"
#include "CefAppImp.h"

int QCefProcessStart()
{
	CefEnableHighDPISupport();
	// Provide CEF with command-line arguments.
	CefMainArgs main_args;

	void* sandbox_info = NULL;

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	int exit_code = CefExecuteProcess(main_args, NULL, sandbox_info);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}
	//
	// Specify CEF global settings here.
	CefSettings settings;
	settings.no_sandbox = true;
#ifdef Q_OS_WIN
	settings.multi_threaded_message_loop = true;
#endif

	// CefAppImp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
	CefRefPtr<CefAppImp> app(new CefAppImp);

	// Initialize CEF.
	CefInitialize(main_args, settings, app.get(), sandbox_info);
}

void QCefMessageLoop()
{
#ifndef Q_OS_WIN
	CefRunMessageLoop();
#endif
}


void QCefProcessExit()
{
	// Shut down CEF.
	CefShutdown();
}

