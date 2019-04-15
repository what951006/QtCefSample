#include "QtCefSample.h"

QtCefSample::QtCefSample(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}





void QtCefSample::closeEvent(QCloseEvent *event)
{
	emit sigClose();
	__super::closeEvent(event);
}
