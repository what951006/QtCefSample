#include "QtCefSample.h"
#include <QCloseEvent>
#include "QtCefView.h"
#include <windows.h>

QtCefSample::QtCefSample(QWidget *parent, WindowDelegate *delegate)
	: QMainWindow(parent)
	, delegate_(delegate)
{
	save_hwnd_ = (HWND)winId();
}


void QtCefSample::closeEvent(QCloseEvent *event)
{
	if (delegate_)
		if (!delegate_->OnWindowClose())
		{
			event->ignore();
		}
	__super::closeEvent(event);
}

bool QtCefSample::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
	return false;
	//MSG * msg = (MSG *)message;
	//if (msg->hwnd != save_hwnd_)
	//{
	//	return false;
	//}

	/*switch (msg->message)
	{
	case WM_CREATE:
	{
		printf("WM_CREATE");
	}
	break;
	case WM_CLOSE:
	{
		if (delegate_)
			if (!delegate_->OnWindowClose())
				return true;
	}
	break;
	case WM_NCDESTROY:
	{
		if (delegate_)
			delegate_->OnWindowDestory();	
	}
	break;
	default:
		break;
	}

	return false;*/
	//return __super::nativeEventFilter(eventType, message, result);
}

