#pragma once
#include <QWidget>
#include "include\internal\cef_ptr.h"
#include "simple_app.h"
#include "simple_handler.h"


class WindowDelegate
{
public:
	virtual bool OnWindowClose() = 0;

	virtual void OnWindowDestory() = 0;
};


class QtCefView : public QWidget
				, public SimpleHandler::BrowserHanderDelegate
				, public WindowDelegate
{
	Q_OBJECT
public:

	QtCefView(QWidget * parent=nullptr);
	~QtCefView();

	void CreateBrowser(const QString & url);
	
	void CloseBrowser(bool force);

	virtual void paintEvent(QPaintEvent *event) override;

	virtual void resizeEvent(QResizeEvent *event) override;

	virtual void OnBrowserClosing() override;

	virtual void OnBrowserClosed() override;
	
protected:
	
	CefRefPtr<SimpleHandler> handler_=nullptr;

private:
	virtual bool OnWindowClose() override;

	virtual void OnWindowDestory() override;

	bool is_browser_destoryed_ = false;
	bool is_closing = false;
	bool is_closed_ = false;
};

