#include "QtCefSample.h"
#include <QApplication>

#include "include/cef_app.h"

#include "QtCefView.h"



int main(int argc, char *argv[])
{
	// Provide CEF with command-line arguments.
	CefMainArgs main_args(GetModuleHandle(NULL));
	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.

	CefRefPtr<SimpleApp> app(new SimpleApp(NULL));
	int exit_code = CefExecuteProcess(main_args, NULL, nullptr);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = TRUE;
	// Initialize CEF.
	CefInitialize(main_args, settings, app.get(), NULL);


	QApplication a(argc, argv);

	QtCefSample *w = new QtCefSample;
	QtCefView * view = new QtCefView;

	//QObject::connect(&w, &QtCefSample::sigClose, view, &QtCefView::CloseBrowser);

	view->CreateBrowser("www.baidu.com");
	view->resize(800, 600);
	w->setCentralWidget(view);
	w->show();
	a.exec();

	delete w;
	CefShutdown();
	return 0;
}
