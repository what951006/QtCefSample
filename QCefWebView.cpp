#include <QCloseEvent>
#include <QDebug>
#include "CefBrowserHandlerImp.h"
#include "QBrowserWindow.h"

#include <QtWidgets/QApplication>

#define DEFAULT_URL "http://www.baidu.com"


static CefRefPtr<CefBrowserHandlerImp> s_browserHandler = NULL;

CefRefPtr<CefBrowser> GetBrowser()
{
	CefRefPtr<CefBrowser> browser = nullptr;
	if (s_browserHandler.get()) {
		browser = s_browserHandler->GetBrowser();
	}
	return browser;
}

QCefWebView::QCefWebView(QWidget *parent) :
	QWidget(parent),
	_browserState(None),
	_needResize(false),
	_needLoad(false),
	_url(DEFAULT_URL)
{
	setAttribute(Qt::WA_NativeWindow);
	setAttribute(Qt::WA_DontCreateNativeAncestors);
	if (!s_browserHandler) {
		s_browserHandler = new CefBrowserHandlerImp();
		connect(s_browserHandler, &CefBrowserHandlerImp::browserCreated, this, &QCefWebView::onBrowserCreated, Qt::QueuedConnection);
		connect(s_browserHandler, &CefBrowserHandlerImp::urlChanged, this, &QCefWebView::urlChanged, Qt::QueuedConnection);
		connect(s_browserHandler, &CefBrowserHandlerImp::titleChanged, this, &QCefWebView::titleChanged, Qt::QueuedConnection);
		connect(s_browserHandler, &CefBrowserHandlerImp::loadingStateChanged, this, &QCefWebView::loadStateChanged, Qt::QueuedConnection);
		connect(s_browserHandler, &CefBrowserHandlerImp::webViewGotFocus, this, &QCefWebView::webViewGotFocus, Qt::QueuedConnection);
	}
}

QCefWebView::~QCefWebView()
{
}

void QCefWebView::closeBrowser(QCloseEvent* event)
{
	qDebug() << "-->>" << __FUNCTION__;
	if (s_browserHandler && !s_browserHandler->IsClosing()) {
		auto browser = s_browserHandler->GetBrowser();
		if (browser.get()) {
			browser->GetHost()->CloseBrowser(false);
		}
		event->ignore();
	}
	else {
		event->accept();
	}
}

void QCefWebView::loadUrl(const QString& url)
{
	_url = url;
	switch (_browserState) {
	case None:
		CreateBrowser(size());
		break;

	case Creating:
		_needLoad = true;
		break;

	default:
		BrowserLoadUrl(url);
	}
}

void QCefWebView::back()
{
	auto browser = GetBrowser();
	if (browser.get()) {
		browser->GoBack();
	}
}

void QCefWebView::forward()
{
	auto browser = GetBrowser();
	if (browser.get()) {
		browser->GoForward();
	}
}

void QCefWebView::refresh()
{
	auto browser = GetBrowser();
	if (browser.get()) {
		browser->Reload();
	}
}

void QCefWebView::stop()
{
	auto browser = GetBrowser();
	if (browser.get()) {
		browser->StopLoad();
	}
}

void QCefWebView::onBrowserCreated()
{
	_browserState = Created;
	if (_needResize) {
		ResizeBrowser(size());
		_needResize = false;
	}
}

void QCefWebView::resizeEvent(QResizeEvent* event)
{
	switch (_browserState) {
	case None:
		CreateBrowser(event->size());
		break;

	case Creating:
		_needResize = true;
		break;

	default:
		ResizeBrowser(event->size());
	}
}

bool QCefWebView::CreateBrowser(const QSize& size)
{
	if (_browserState != None || size.isEmpty()) {
		return false;
	}

	if (_browserState != None) {
		return false;
	}



// 	CefWindowInfo windowInfo;
// 	CefBrowserSettings browserSettings;

// #ifdef _WIN32
// 	RECT rect;
// 	rect.left = 0;
// 	rect.top = 0;
// 	rect.right = size.width();
// 	rect.bottom = size.height();
// 	windowInfo.SetAsChild(reinterpret_cast<HWND>(this->winId()), rect);
// #endif

	CefWindowHandle hWnd = (CefWindowHandle)this->winId();

    CefWindowInfo info;
    CefBrowserSettings _settings;
    _settings.file_access_from_file_urls = STATE_ENABLED;
    _settings.universal_access_from_file_urls = STATE_ENABLED;
    _settings.javascript_access_clipboard = STATE_ENABLED;

    _settings.plugins = STATE_DISABLED;

    // Initialize window info to the defaults for a child window.

#ifdef Q_OS_WIN
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = this->width()*qApp->devicePixelRatio();
    rect.bottom = this->height()*qApp->devicePixelRatio();
    info.SetAsChild(hWnd, rect);
#endif

#if defined(_LINUX) && !defined(_MAC)
    CefRect rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 10;
    rect.height = 10;
    info.SetAsChild(hWnd, rect);
#endif

#ifdef Q_OS_MAC
    info.SetAsChild(hWnd, 0, 0, this->width(), this->height());
#endif

	QString url = _url.isEmpty() ? (DEFAULT_URL) : _url.toString();
	CefBrowserHost::CreateBrowser(info, s_browserHandler.get(), CefString(url.toStdWString()), _settings, NULL);
	_browserState = Creating;

	return true;
}


void QCefWebView::ResizeBrowser(const QSize& size)
{
	if (s_browserHandler.get() && s_browserHandler->GetBrowser()) {
		auto windowHandle = s_browserHandler->GetBrowser()->GetHost()->GetWindowHandle();

		if (windowHandle) {
#ifdef _WIN32
			auto hdwp = BeginDeferWindowPos(1);
			hdwp = DeferWindowPos(hdwp, windowHandle, nullptr, 0, 0, 
				qApp->devicePixelRatio()*size.width(), qApp->devicePixelRatio()*size.height(), SWP_NOZORDER);
			EndDeferWindowPos(hdwp);
#endif
		}
	}
}

bool QCefWebView::BrowserLoadUrl(const QUrl& url)
{
	if (!url.isEmpty() && GetBrowser()) {
		CefString cefurl(url.toString().toStdWString());
		GetBrowser()->GetMainFrame()->LoadURL(cefurl);
		return true;
	}
	return false;
}
