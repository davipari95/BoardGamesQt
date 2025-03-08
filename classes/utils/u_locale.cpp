#include "u_locale.h"

#include <QLocale>
#include <QString>


QString ULocale::getSystemLocale()
{
    return QLocale::system().name();
}

QString ULocale::getTwoCharSystemLocale()
{
    QString locale = getSystemLocale();
    return locale.split("_")[0];
}
