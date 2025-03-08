#include "rules_viewer.h"
#include "ui_rules_viewer.h"

#include <classes/utils/u_frames.h>
#include <classes/utils/u_locale.h>
#include <QFile>

RulesViewer::RulesViewer(const QString gameName, QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::RulesViewer)
{
    initializeComponents();
    showRules(gameName);
}

RulesViewer::~RulesViewer()
{
    delete ui;
}

void RulesViewer::initializeComponents()
{
    //Window
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(UFrames::isDarkMode() ? ":/application/book_light" : ":/application/book_dark"));

    //Content
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Size
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), false);
}

void RulesViewer::showRules(const QString gameName)
{
    QString ruleResourceLanguage = QString(":/rules/%0/%1").arg(gameName).arg(ULocale::getTwoCharSystemLocale());
    QString ruleResourceNative = QString(":/rules/%0/en").arg(gameName);

    ui->mainTextBrowser->setSource(QUrl::fromLocalFile(QFile::exists(ruleResourceLanguage) ? ruleResourceLanguage : ruleResourceNative));
}
