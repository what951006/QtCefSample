#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCefSample.h"

class QtCefSample : public QMainWindow
{
	Q_OBJECT

public:
	QtCefSample(QWidget *parent = Q_NULLPTR);
signals:
	void sigClose();
private:
	Ui::QtCefSampleClass ui;
protected:
	virtual void closeEvent(QCloseEvent *event) override;

};
