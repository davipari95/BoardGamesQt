#ifndef U_FRAMES_H
#define U_FRAMES_H

class QWidget;
class QMdiSubWindow;

class UFrames
{
    public:
        //Constructors
        UFrames();

        //Functions
        static void getSubMdiFrameBorderSizes(const QWidget* baseWidget, int &out_topPx, int &out_bottomPx, int &out_leftPx, int &out_rightPx);
        static bool adaptSubMdiSizesByContent(QMdiSubWindow* window, int width, int height, bool fixedSize = false);
        static bool centreFormInMdiArea(QMdiSubWindow *window);
        static bool isDarkMode();

};

#endif // U_FRAMES_H
