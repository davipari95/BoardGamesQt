#ifndef V_STYLES_H
#define V_STYLES_H

#include <QString>

/**
 * @brief Class that contains stylesheet variables.
 */
class VStyles
{
    public:
        VStyles();
        /**
         * @brief Empty string. Pass it to the stylesheet of the widget for return back to the original style.
         */
        static QString plain;
        /**
         * @brief Style that is used for highlight the line edit that is empty.
         */
        static QString lineEditEmpty;
};

#endif // V_STYLES_H
