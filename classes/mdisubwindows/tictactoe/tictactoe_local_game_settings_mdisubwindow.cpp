#include "tictactoe_local_game_settings_mdisubwindow.h"
#include "ui_tictactoe_local_game_settings_mdisubwindow.h"

#include <QTimer>

TicTacToeLocalGameSettingsMdiSubWindow::TicTacToeLocalGameSettingsMdiSubWindow(QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLocalGameSettingsMdiSubWindow)
{
    QWidget *widget = new QWidget(this);
    ui->setupUi(widget);
    setWidget(widget);

    widget->setSizeIncrement(300, 112);
    adjustSize();
}

TicTacToeLocalGameSettingsMdiSubWindow::~TicTacToeLocalGameSettingsMdiSubWindow()
{
    delete ui;
}
