#include "CefBrowser.h"

//#ifdef NDEBUG
//#pragma comment(lib,"QCefBrowser")
//#else
//#pragma comment(lib,"QCefBrowser_d")
//#endif

// Entry point function for all processes.
int main(int argc, char *argv[])
{
	QCefProcessStart();
	//--- main process -----
	QApplication qapp(argc, argv);
	//create window;
	QBrowserWindow* cefWebWindow = new QBrowserWindow(NULL);
	cefWebWindow->init();
	cefWebWindow->show();

	//
	QCefMessageLoop();
	//
	int qt_exit_code = qapp.exec();
	//
	QCefProcessExit();

	return qt_exit_code;
}
