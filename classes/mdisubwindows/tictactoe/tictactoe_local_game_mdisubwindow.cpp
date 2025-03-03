#include "tictactoe_local_game_mdisubwindow.h"
#include "ui_tictactoe_local_game_mdisubwindow.h"

#include <classes/utils/u_frames.h>

TicTacToeLocalGame::TicTacToeLocalGame(QString xPlayerName, QString oPlayerName, QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLocalGame)
{
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height());
}

TicTacToeLocalGame::~TicTacToeLocalGame()
{
    delete ui;
}
