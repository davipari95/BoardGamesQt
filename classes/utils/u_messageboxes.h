#ifndef U_MESSAGEBOXES_H
#define U_MESSAGEBOXES_H

#include <QObject>
#include <QMessageBox>

class QPixmap;

class UMessageBoxes : public QObject
{
    Q_OBJECT
    public:
        static QMessageBox::StandardButton showCustomMessageBox(const QString &title, const QString &message, const QPixmap &customIcon, const QMessageBox::StandardButtons &buttons, const int &iconSize = 64);

};

#endif // U_MESSAGEBOXES_H
