#include "main_window.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleHints>
#include <QLibraryInfo>
#include <variables/v_widget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Load system translations
    QTranslator qtTranslator;
    if (qtTranslator.load(QLocale::system(), "qtbase", "_", QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        a.installTranslator(&qtTranslator);
    }

    //Load other translations
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "BoardGamesQt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.showMaximized();
    return a.exec();
}
