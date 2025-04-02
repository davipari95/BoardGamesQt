#ifndef U_MESSAGEBOXES_H
#define U_MESSAGEBOXES_H

#include <QObject>
#include <QMessageBox>

class QPixmap;

/**
 * @brief Class that contains static functions useful for message boxes.
 */
class UMessageBoxes : public QObject
{
    Q_OBJECT
    public:
        /**
         * @brief Show a custom message box.
         * @param[in] title The title of the message box.
         * @param[in] message The message of the message box.
         * @param[in] customIcon The icon of the message box.
         * @param[in] buttons Buttons to show on message box.
         * @param[in] iconSize Size of the icon.
         * @return The button that is pressed just before the message box is closed.
         */
        static QMessageBox::StandardButton showCustomMessageBox(const QString &title, const QString &message, const QPixmap &customIcon, const QMessageBox::StandardButtons &buttons, const int &iconSize = 64);

};

#endif // U_MESSAGEBOXES_H
