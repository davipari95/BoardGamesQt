#include "tictactoe_local_game_mdisubwindow.h"
#include "ui_tictactoe_local_game_mdisubwindow.h"

#include <classes/utils/u_frames.h>
#include <classes/objects/tictactoe/match.h>

TicTacToeLocalGame::TicTacToeLocalGame(const QString &xPlayerName, const QString &oPlayerName, QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLocalGame)
{
    initialize(xPlayerName, oPlayerName);
}

TicTacToeLocalGame::~TicTacToeLocalGame()
{
    delete ui;
}

void TicTacToeLocalGame::initialize(const QString &xPlayerName, const QString &oPlayerName)
{
    //Initialize variables
    m_match = std::make_unique<Match>(xPlayerName, oPlayerName);

    //Set flags and attributes
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    //Set GUI
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Adjust size
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), true);
}

void TicTacToeLocalGame::initializeComponents()
{

}
