#include "QtCefView.h"

#include <QPainter>
#include <thread>
#include "include\base\cef_bind.h"


QtCefView::QtCefView(QWidget * parent)
	:QWidget(parent)
{


}


QtCefView::~QtCefView()
{
	handler_ = nullptr;

	printf("~QtCefView\n");
}

void QtCefView::CreateBrowser(const QString & url)
{
	CefWindowInfo window_info;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width();
	rect.bottom = height();

	window_info.SetAsChild((HWND)winId(), rect);

	handler_ = CefRefPtr<SimpleHandler>(new SimpleHandler(this));

	CefBrowserSettings browser_settings;

	CefBrowserHost::CreateBrowser(window_info, handler_, url.toStdString().c_str(),
		browser_settings, NULL);
}

void QtCefView::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.fillRect(rect(),Qt::red);
}

void QtCefView::resizeEvent(QResizeEvent *event)
{
	if (handler_)
	{
		if (handler_->GetBrowser())
		{
			HWND hwnd = handler_->GetBrowser()->GetHost()->GetWindowHandle();
			SetWindowPos(hwnd, NULL, 0, 0,
				width(),
				height(),
				SWP_NOZORDER
			);
		}
	}
	__super::resizeEvent(event);
}


void QtCefView::OnBrowserClosing()
{
	is_browser_destoryed_ = false;
	is_closing = true;	
}


void QtCefView::OnBrowserClosed()
{
	is_browser_destoryed_ = true;
	is_closing = false;

	DestroyWindow((HWND)winId());
	
	//CloseBrowser(true);
	//this->close();
}


void QtCefView::CloseBrowser(bool force)
{
	if(handler_)
		handler_->CloseBrowsers(force);
}



bool QtCefView::OnWindowClose()
{
	if (handler_ && !is_closing)
	{
		CloseBrowser(false);
		return false;
	}
	return true;
}

void QtCefView::OnWindowDestory()
{
	
}
