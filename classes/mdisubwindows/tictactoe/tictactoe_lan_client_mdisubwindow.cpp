#include "tictactoe_lan_client_mdisubwindow.h"
#include "ui_tictactoe_lan_client_mdisubwindow.h"

#include <QTcpSocket>

#include <classes/objects/tictactoe/matches/lan_match.h>

TicTacToeLANClientMdiSubWindow::TicTacToeLANClientMdiSubWindow(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken, QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLANClientMdiSubWindow)
{
    initialize(socket, playerName, playerToken);
}

TicTacToeLANClientMdiSubWindow::~TicTacToeLANClientMdiSubWindow()
{
    delete ui;
}

void TicTacToeLANClientMdiSubWindow::initialize(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken)
{
    //Socket
    this->m_socket = socket;
    this->m_socket->setParent(this);

    //Match
    m_match = new LanMatch(this);
    m_match->setPlayerName(playerToken, playerName);
}
