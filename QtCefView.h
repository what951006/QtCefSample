#pragma once
#include <QWidget>
#include "include\internal\cef_ptr.h"
#include "simple_app.h"
#include "simple_handler.h"



class QtCefView : public QWidget
{
	Q_OBJECT
public:
	QtCefView(QWidget * parent=nullptr);
	~QtCefView();

	void CreateBrowser(const QString & url);
	
	virtual void paintEvent(QPaintEvent *event) override;

	virtual void resizeEvent(QResizeEvent *event) override;

public slots:
	void CloseBrowser();
protected:
	
	SimpleHandler *handler_=nullptr;

	virtual void closeEvent(QCloseEvent *event) override;

};

