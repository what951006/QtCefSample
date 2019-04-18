#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>

#include "QBrowserWindow.h"

EXPORT int QCefProcessStart();
EXPORT void QCefMessageLoop();
EXPORT void QCefProcessExit();