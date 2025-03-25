#include "tictactoe_lan_client_mdisubwindow.h"
#include "ui_tictactoe_lan_client_mdisubwindow.h"

#include <QTcpSocket>

#include <classes/objects/tictactoe/matches/lan_match.h>
#include <classes/utils/u_frames.h>

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

void TicTacToeLANClientMdiSubWindow::onTcpSocketReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    manageIncomingTcpMessage(socket);
}

void TicTacToeLANClientMdiSubWindow::onTcpSocketDisconnected()
{

}
