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
	/*if (handler_)
	{
		
		while (!handler_->can_close_)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}*/

	CloseBrowser();
	while (!handler_->can_close_)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	delete handler_;
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

	handler_ = new SimpleHandler();

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


void QtCefView::CloseBrowser()
{
	//if (!CefCurrentlyOn(TID_UI))
	//{
	//	// Execute on the UI thread.
	//	CefPostTask(TID_UI,
	//		base::Bind(&QtCefView::CloseBrowser, this));
	//	return;
	//}
	if(handler_)
		if(handler_->GetBrowser())
			handler_->GetBrowser()->GetHost()->CloseBrowser(true);
}

void QtCefView::closeEvent(QCloseEvent *event)
{
	
	__super::closeEvent(event);
}
