#pragma once
#include <QMainWindow>
#include <QAbstractNativeEventFilter>
#include <functional>

#include "ui_QtCefSample.h"
#include "QtCefView.h"



class QtCefSample : public QMainWindow ,public QAbstractNativeEventFilter
{
	Q_OBJECT
public:
	QtCefSample(QWidget *parent = Q_NULLPTR , WindowDelegate *delegate = nullptr);

	virtual void closeEvent(QCloseEvent *event) override;

	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
	Ui::QtCefSampleClass ui;

	WindowDelegate * delegate_ = nullptr;

	HWND  save_hwnd_ = NULL;
};
