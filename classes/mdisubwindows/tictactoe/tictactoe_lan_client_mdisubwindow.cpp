#include "tictactoe_lan_client_mdisubwindow.h"
#include "ui_tictactoe_lan_client_mdisubwindow.h"

#include <QTcpSocket>

#include <classes/objects/tictactoe/matches/lan_match.h>
#include <classes/utils/u_frames.h>

#define CELL_SIZE 100
#define MARGIN 5

#define REAL_CELL_SIZE (CELL_SIZE - (2 * MARGIN))

TicTacToeLANClientMdiSubWindow::TicTacToeLANClientMdiSubWindow(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken, QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::TicTacToeLANClientMdiSubWindow)
{
    initialize(socket, playerName, playerToken);
    initializeComponents();
}

TicTacToeLANClientMdiSubWindow::~TicTacToeLANClientMdiSubWindow()
{
    delete ui;
}

void TicTacToeLANClientMdiSubWindow::initialize(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken)
{
    //Match
    m_match = new LanMatch(playerToken, playerName, this);

    //Socket
    this->m_socket = socket;
    this->m_socket->setParent(this);
    connect(m_socket, &QTcpSocket::readyRead, this, &TicTacToeLANClientMdiSubWindow::onTcpSocketReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TicTacToeLANClientMdiSubWindow::onTcpSocketDisconnected);
}

void TicTacToeLANClientMdiSubWindow::initializeComponents()
{
    //Flags
    UFrames::setFlagsAndAttributes(this);

    //Content
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Adapt content
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), true);

    //Add cells
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            m_board[r][c] = new QGridLabel(r, c, ui->boardLabel);

            int x = (c * CELL_SIZE) + MARGIN;
            int y = (r * CELL_SIZE) + MARGIN;

            m_board[r][c]->setGeometry(x, y, REAL_CELL_SIZE, REAL_CELL_SIZE);

            connect(m_board[r][c], &QGridLabel::clicked, this, &TicTacToeLANClientMdiSubWindow::onBoardCellClicked);
        }
    }
}

quint64 TicTacToeLANClientMdiSubWindow::manageIncomingTcpMessage(QTcpSocket *socket)
{
    quint64 result = 0;

    QString message = socket->readAll();

    QStringList commands = message.split("\r\n", Qt::SkipEmptyParts);

    for (QString &command : commands)
    {
        QStringList data = command.split("\n");

        if (data[0] == "get-player-info")
        {
            if (manageGetPlayerInfo(socket))
            {
                result |= 1 << 0;
            }
        }
        else if (data[0] == "game-ready")
        {
            if (manageGameReady())
            {
                result |= 1 << 1;
            }
        }
        else if (data[0] == "set-turn")
        {
            if (manageSetTurn(data))
            {
                result |= 1 << 2;
            }
        }
        else if (data[0] == "token-inserted")
        {
            if (manageTokenInserted(data))
            {
                result |= 1 << 3;
            }
        }
    }

    return result;
}

bool TicTacToeLANClientMdiSubWindow::manageGetPlayerInfo(QTcpSocket *socket)
{
    TicTacToePlayerEnum clientToken;
    QString clientPlayerName;

    if (m_match->getClientPlayerInfo(clientToken, clientPlayerName))
    {
        QString message = QString("get-player-info\n%0\n%1\r\n").arg(getTokenChar(clientToken)).arg(clientPlayerName);
        return socket->write(message.toLatin1()) != -1;
    }
    else
    {
        throw "Errore retrieving client player info";
    }
}

bool TicTacToeLANClientMdiSubWindow::manageGameReady()
{
    return m_match->setGameIsReady(true);
}

bool TicTacToeLANClientMdiSubWindow::manageSetTurn(QStringList data)
{
    return m_match->setActualTurn(getTokenByChar(data[1][0].toLatin1()));
}

bool TicTacToeLANClientMdiSubWindow::manageTokenInserted(QStringList data)
{
    bool rowOk, colOk;

    TicTacToePlayerEnum token = getTokenByChar(data[1].toLatin1());
    int row = data[2].toInt(&rowOk);
    int col = data[3].toInt(&colOk);

    if (rowOk && colOk)
    {
        return m_match->getBoard()->insertToken(row, col, token) == 0;
    }
    else return false;
}

void TicTacToeLANClientMdiSubWindow::onTcpSocketReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    manageIncomingTcpMessage(socket);
}

void TicTacToeLANClientMdiSubWindow::onTcpSocketDisconnected()
{

}

void TicTacToeLANClientMdiSubWindow::onBoardCellClicked()
{
    QGridLabel* m_sender = qobject_cast<QGridLabel*>(sender());

    if (m_match->getActualTurn() == m_match->getClientToken())
    {
        int row = m_sender->getGridPosition()->getRow();
        int col = m_sender->getGridPosition()->getColumn();

        if (m_match->getBoard()->getTokenByPosition(row, col) == TicTacToePlayerEnum::None)
        {
            QString message = QString("insert-token\n%0\n%1").arg(row).arg(col);
            m_socket->write(message.toLatin1());
        }
    }
}
