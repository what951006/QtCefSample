#ifndef QBROWSERWINDOW_H
#define QBROWSERWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include "QCefWebView.h"

class EXPORT QBrowserWindow :public QMainWindow
{
	Q_OBJECT

public:
	QBrowserWindow(QMainWindow *parent = 0);
	~QBrowserWindow();

	void init();

private slots:
	void updateBtnState(bool isLoading, bool canGoBack, bool canGoForward);
	void loadWebUrl();
	void onWebViewGotFocus();
	void onTitleChanged(const QString& title);

protected:
	virtual void closeEvent(QCloseEvent* event);

private:
	QCefWebView* webView;

	QLineEdit* urlEdit;

	QPushButton* backBtn;
	QPushButton* forwardBtn;
	QPushButton* refreshBtn;
	QPushButton* stopBtn;
};

#endif // QBROWSERWINDOW_H
