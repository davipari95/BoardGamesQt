#include "tictactoe_local_game_settings_mdisubwindow.h"
#include "ui_tictactoe_local_game_settings_mdisubwindow.h"

#include <QMessageBox>
#include <QMdiArea>
#include <main_window.h>
#include <classes/utils/u_frames.h>
#include <classes/mdisubwindows/tictactoe/tictactoe_local_game_mdisubwindow.h>
#include <variables/v_styles.h>

TicTacToeLocalGameSettingsMdiSubWindow::TicTacToeLocalGameSettingsMdiSubWindow( QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLocalGameSettingsMdiSubWindow)
{
    setAttribute(Qt::WA_DeleteOnClose); //Delete everything on closing form
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);  //Remove maximize button
    setWindowIcon(QIcon(UFrames::isDarkMode() ? ":/application/gear_light" : ":/application/gear_dark"));

    QWidget *m_widget = new QWidget(this);
    ui->setupUi(m_widget);
    setWidget(m_widget);


    UFrames::adaptSubMdiSizesByContent(this, m_widget->width(), m_widget->height(), true);

    connectAllSlots();
}

TicTacToeLocalGameSettingsMdiSubWindow::~TicTacToeLocalGameSettingsMdiSubWindow()
{
    delete ui;
}

bool TicTacToeLocalGameSettingsMdiSubWindow::connectAllSlots()
{
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &TicTacToeLocalGameSettingsMdiSubWindow::onCancelPushButtonClicked);
    connect(ui->playPushButton, &QPushButton::clicked, this, &TicTacToeLocalGameSettingsMdiSubWindow::onPlayPushButtonClicked);

    return true;
}

bool TicTacToeLocalGameSettingsMdiSubWindow::checkInsertedNames(TicTacToePlayerEnum &out_missingNames, QString &out_xPlayerName, QString &out_oPlayerName)
{
    out_xPlayerName = ui->xPlayerNameLineEdit->text();
    out_oPlayerName = ui->oPlayerNameLineEdit->text();

    return checkInsertedNames(out_xPlayerName, out_oPlayerName, out_missingNames);
}

bool TicTacToeLocalGameSettingsMdiSubWindow::checkInsertedNames(QString xPlayerName, QString oPlayerName, TicTacToePlayerEnum &out_missingNames)
{
    bool ok = true;
    out_missingNames = TicTacToePlayerEnum::None;

    if (xPlayerName.isEmpty())
    {
        ok = false;
        set(out_missingNames, TicTacToePlayerEnum::Cross);
    }

    if (oPlayerName.isEmpty())
    {
        ok = false;
        set(out_missingNames, TicTacToePlayerEnum::Circle);
    }

    return ok;
}

bool TicTacToeLocalGameSettingsMdiSubWindow::resetLineEditsBackground()
{
    ui->xPlayerNameLineEdit->setStyleSheet(VStyles::plain);
    ui->oPlayerNameLineEdit->setStyleSheet(VStyles::plain);

    return true;
}

void TicTacToeLocalGameSettingsMdiSubWindow::onCancelPushButtonClicked(bool checked)
{
    (void) checked;

    close();
}

void TicTacToeLocalGameSettingsMdiSubWindow::onPlayPushButtonClicked(bool checked)
{
    (void) checked;

    resetLineEditsBackground();
    TicTacToePlayerEnum missingNames;

    QString xPlayerName;
    QString oPlayerName;

    if (!checkInsertedNames(missingNames, xPlayerName, oPlayerName))
    {
        if (isSet(missingNames, TicTacToePlayerEnum::Cross))
        {
            ui->xPlayerNameLineEdit->setStyleSheet(VStyles::lineEditEmpty);
        }

        if (isSet(missingNames, TicTacToePlayerEnum::Circle))
        {
            ui->oPlayerNameLineEdit->setStyleSheet(VStyles::lineEditEmpty);
        }

        QMessageBox::information(this, tr("Name are missing"), tr("One or more names are missing. Please, check again."));
    }
    else
    {
        TicTacToeLocalGame *game = new TicTacToeLocalGame(xPlayerName, oPlayerName);
        MainWindow::getMainMdiArea()->addSubWindow(game);

        game->show();
        UFrames::centreFormInMdiArea(game);

        close();
    }
}
