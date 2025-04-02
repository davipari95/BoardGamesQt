#ifndef U_FRAMES_H
#define U_FRAMES_H

class QWidget;
class QMdiSubWindow;

/**
 * @brief Class that contains static functions useful for windows.
 */
class UFrames
{
    public:
        //Constructors
        UFrames();

        //Functions
        /**
         * @brief Retrieve the border size (Frame size - content size) of the widget given in `baseWidget`.
         * @param[in] baseWidget Widget where you want to retrieve the border size.
         * @param[out] out_topPx Board height on the top in pixel.
         * @param[out] out_bottomPx Board height on botton in pixel.
         * @param[out] out_leftPx Board width on left in pixel.
         * @param[out] out_rightPx Board width on right in pixel.
         */
        static void getSubMdiFrameBorderSizes(const QWidget* baseWidget, int &out_topPx, int &out_bottomPx, int &out_leftPx, int &out_rightPx);
        /**
         * @brief Adapt the size of the `QMdiSubWindow` window given in `window` with the content size given in `width` and `height`.
         * @param[in] window Window which you what to adapt size.
         * @param[in] width Width of the content of the window.
         * @param[in] height Height of the content of the windoe.
         * @param[in] fixedSize Set `true` if you don't want that the window is resizable, `false` if you do.
         * @return This function returns always `true`.
         */
        static bool adaptSubMdiSizesByContent(QMdiSubWindow* window, int width, int height, bool fixedSize = false);
        /**
         * @brief Centre the window given in `window` at the center of the main MDI area.
         * @param[in] window Window that you want to centre into the main MDI area.
         * @return This function return always `true`.
         */
        static bool centreFormInMdiArea(QMdiSubWindow *window);
        /**
         * @brief Check if the software is running in dark mode.
         * @return Return `true` if the software is running in dark mode, `false` in light mode.
         */
        static bool isDarkMode();
        /**
         * @brief Set some flags and attributes of the window given in `window`.
         * @param[in] window Window where you want to set flags and attributes.
         * @param[in] deleteOnClose Set `true` if you want to delete the window after it is closed, `false` if not.
         * @param[in] showMaximiseButton Set `true` if you want to show the maximise button of the frame, `false` if not.
         */
        static void setFlagsAndAttributes(QMdiSubWindow *window, bool deleteOnClose = true, bool showMaximiseButton = false);


};

#endif // U_FRAMES_H
