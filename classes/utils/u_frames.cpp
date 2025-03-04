#include "u_frames.h"

#include <QStyle>
#include <QWidget>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <main_window.h>

UFrames::UFrames() {}

void UFrames::getSubMdiFrameBorderSizes(const QWidget *baseWidget, int &out_topPx, int &out_bottomPx, int &out_leftPx, int &out_rightPx)
{
    int t = baseWidget->style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int lrb = baseWidget->style()->pixelMetric(QStyle::PM_MdiSubWindowFrameWidth);

    out_topPx = t;
    out_bottomPx = out_leftPx = out_rightPx = lrb;
}

bool UFrames::adaptSubMdiSizesByContent(QMdiSubWindow *window, int width, int height, bool fixedSize)
{
    int top, left, right, bottom;

    getSubMdiFrameBorderSizes(window, top, bottom, left, right);

    int real_width = width + left + right;
    int real_height = height + top + bottom;

    if (fixedSize)
    {
        window->setFixedSize(real_width, real_height);
    }
    else
    {
        window->resize(real_width, real_height);
    }

    return true;
}

bool UFrames::centreFormInMdiArea(QMdiSubWindow *window)
{
    int x = (MainWindow::getMainMdiArea()->width() - window->width()) / 2;
    int y = (MainWindow::getMainMdiArea()->height() - window->height()) / 2;

    window->move(x, y);

    return true;
}
