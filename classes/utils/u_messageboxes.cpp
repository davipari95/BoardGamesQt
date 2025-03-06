#include "u_messageboxes.h"

QMessageBox::StandardButton UMessageBoxes::showCustomMessageBox(const QString &title, const QString &message, const QPixmap &customIcon, const QMessageBox::StandardButtons &buttons, const int &iconSize)
{
    QMessageBox box;

    box.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    box.setWindowTitle(title);
    box.setText(message);
    box.setIconPixmap(customIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    box.setStandardButtons(buttons);

    return static_cast<QMessageBox::StandardButton>(box.exec());
}
