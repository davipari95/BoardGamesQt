#include "tictactoe_lan_server_settings_mdisubwindow.h"
#include "ui_tictactoe_lan_server_settings_mdisubwindow.h"

#include <main_window.h>
#include <classes/utils/u_frames.h>
#include <classes/objects/range.h>
#include <classes/mdisubwindows/tictactoe/tictactoe_lan_server_mdisubwindow.h>
#include <variables/v_styles.h>
#include <enums/games_enum.h>
#include <QMessageBox>
#include <QMdiArea>

TicTacToeLanServerSettingsMdiSubWindow::TicTacToeLanServerSettingsMdiSubWindow(QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLanServerSettingsMdiSubWindow)
{
    initializeComponents();
}

TicTacToeLanServerSettingsMdiSubWindow::~TicTacToeLanServerSettingsMdiSubWindow()
{
    delete ui;
}

void TicTacToeLanServerSettingsMdiSubWindow::initializeComponents()
{
    //Set flags and attributes
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    setWindowIcon(QIcon(UFrames::isDarkMode() ? ":/application/gear_light" : ":/application/gear_dark"));

    //Add content
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Adapt frame at content
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), true);

    //Connect all signals
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &TicTacToeLanServerSettingsMdiSubWindow::onCancelPushButtonClicked);
    connect(ui->openServerPushButton, &QPushButton::clicked, this, &TicTacToeLanServerSettingsMdiSubWindow::onOpenServerPushButtonClicked);
}

void TicTacToeLanServerSettingsMdiSubWindow::onCancelPushButtonClicked(bool checked)
{
    (void) checked;

    close();
}

void TicTacToeLanServerSettingsMdiSubWindow::onOpenServerPushButtonClicked(bool checked)
{
    (void) checked;

    QString playerName = ui->playerNameLineEdit->text();

    if (playerName.trimmed().isEmpty())
    {
        ui->playerNameLineEdit->setStyleSheet(VStyles::lineEditEmpty);
        QMessageBox::information(this, tr("Player name missing"), tr("The player name is missing.\nPlease check again."), QMessageBox::StandardButton::Ok);
    }
    else
    {
        ui->playerNameLineEdit->setStyleSheet(VStyles::plain);

        //Open server window
        TicTacToeLanServerMdiSubWindow *w = new TicTacToeLanServerMdiSubWindow(playerName);
        MainWindow::getMainMdiArea()->addSubWindow(w);
        UFrames::centreFormInMdiArea(w);
        w->show();

        //Close this form
        close();
    }
}
