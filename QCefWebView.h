#ifndef QCEFWEBWIDGET_H
#define QCEFWEBWIDGET_H

#include <QtWidgets/QWidget>
#include <QUrl>

//#define BUILD_LIB
//#define QT_BUILD_CORE_LIB
#define BUILD_STATIC

#ifdef BUILD_STATIC
#define EXPORT
#else
#if defined(BUILD_LIB)
#  undef EXPORT
#  define EXPORT Q_DECL_EXPORT
#else
#  undef EXPORT
#  define EXPORT Q_DECL_IMPORT //only for vc?
#endif
#endif //BUILD_QTAV_STATIC

class EXPORT QCefWebView :public QWidget
{
	Q_OBJECT

public:
	enum BrowserState {
		None,
		Creating,
		Created
	};

public:
	QCefWebView(QWidget *parent = 0);
	~QCefWebView();

	void closeBrowser(QCloseEvent* event);

	bool CreateBrowser(const QSize & size);

public slots:
	void loadUrl(const QString& url);
	void back();
	void forward();
	void refresh();
	void stop();

signals:
	void titleChanged(const QString& title);
	void urlChanged(const QString& url);
	void loadStateChanged(bool isLoading, bool canGoBack, bool canGoForward);
	void webViewGotFocus();

	void loadStarted();
	void loadFinished(bool loadSuccess);

private slots:
	void onBrowserCreated();

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

private:
	//CefRefPtr<CefBrowser> GetBrowser() const;
	void ResizeBrowser(const QSize & size);
	bool BrowserLoadUrl(const QUrl & url);

private:


	BrowserState _browserState;
	bool _needResize;
	bool _needLoad;
	QUrl _url;
};

#endif // QCEFWEBWIDGET_H
