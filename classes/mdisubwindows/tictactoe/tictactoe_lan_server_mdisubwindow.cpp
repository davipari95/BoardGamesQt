#include "tictactoe_lan_server_mdisubwindow.h"
#include "ui_tictactoe_lan_server_mdisubwindow.h"

#include <classes/utils/u_frames.h>
#include <classes/utils/u_network.h>
#include <classes/mdisubwindows/tictactoe/tictactoe_lan_client_mdisubwindow.h>
#include <main_window.h>

#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTcpSocket>
#include <QHash>
#include <QMdiArea>

TicTacToeLanServerMdiSubWindow::TicTacToeLanServerMdiSubWindow(QString playerName, QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::TicTacToeLanServerMdiSubWindow)
{
    (void) playerName;

    initialize(playerName);
    initializeComponents();

    waitClients();
    openClient();
}

TicTacToeLanServerMdiSubWindow::~TicTacToeLanServerMdiSubWindow()
{
    delete ui;
}

void TicTacToeLanServerMdiSubWindow::initializeComponents()
{
    //Set flags and attributes
    UFrames::setFlagsAndAttributes(this, true, false);

    //Content
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Adjust size
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), true);

    //Connect slots
    connect(ui->testPushButton, &QPushButton::clicked, this, &TicTacToeLanServerMdiSubWindow::onTestPushButtonClicked);
    connect(ui->clearPushButton, &QPushButton::clicked, this, &TicTacToeLanServerMdiSubWindow::onClearPushButtonClicked);

    //Show IP address
    if (UNetwork::getPrimaryIPAddress(m_primaryAddress))
    {
        ui->ipAddressLabel->setText(m_primaryAddress.toString());
    }
}

void TicTacToeLanServerMdiSubWindow::initialize(const QString &clientPlayerName)
{
    m_clientPlayerName = clientPlayerName;
    m_server = new QTcpServer(this);
    m_connectedPlayers = QList<PlayerInfoStruct>();
    m_gameIsReady = false;

    //Connect local slots
    connect(this, &TicTacToeLanServerMdiSubWindow::connectedPlayerListManaged, this, &TicTacToeLanServerMdiSubWindow::onConnectedPlayerListManaged);
    connect(this, &TicTacToeLanServerMdiSubWindow::gameIsReady, this, &TicTacToeLanServerMdiSubWindow::onGameIsReady);
}

void TicTacToeLanServerMdiSubWindow::writeLog(QString logMessage)
{
    QString message = QString("[%0] >> %1").arg(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss.zzz"), logMessage);
    ui->logPlainTextEdit->appendPlainText(message);
}

void TicTacToeLanServerMdiSubWindow::waitClients()
{
    if (m_server->listen(m_primaryAddress, 0))
    {        
        writeLog("Server started.");
        ui->portLabel->setText(QString::number(m_server->serverPort()));
        connect(m_server, &QTcpServer::newConnection, this, &TicTacToeLanServerMdiSubWindow::onTCPServerNewConnection);
    }
    else
    {
        writeLog("Server error: unable to start the server.");
    }
}

quint64 TicTacToeLanServerMdiSubWindow::manageTcpIncomingMessage(QTcpSocket *client)
{
    quint64 result = 0;

    QString incoming = client->readAll();

    QStringList messages = incoming.split("\r\n", Qt::SkipEmptyParts);

    for (QString &message : messages)
    {
        QStringList command = message.split("\n");

        if (command[0] == "get-player-info")
        {
            if (manageIncomingGetPlayerInfo(client, command))
            {
                result |= 1 << 0;
            }
        }
        else if (command[0] == "get-game")
        {
            if (manageIncomingGetGame(client))
            {
                result |= 1 << 1;
            }
        }
        else if (command[0] == "insert-token")
        {

        }
    }

    if (result == 0)
    {
        throw "Invalid data received";
    }

    return result;
}

bool TicTacToeLanServerMdiSubWindow::manageIncomingGetPlayerInfo(QTcpSocket *client, QStringList args)
{
    PlayerInfoStruct playerInfo;

    char symbol = args[1][0].toLatin1();
    QString playerName = args[2];

    playerInfo.socket = client;
    playerInfo.token = getTokenByChar(symbol);
    playerInfo.name = playerName;

    insertNewConnectedPlayer(playerInfo);

    return true;
}

bool TicTacToeLanServerMdiSubWindow::manageIncomingGetGame(QTcpSocket *client)
{
    client->write("get-game\ntic-tac-toe\r\n");

    return true;
}

bool TicTacToeLanServerMdiSubWindow::manageInsertToken(QTcpSocket *client, QStringList &args)
{
    PlayerInfoStruct player;

    if (getPlayerInfoBySocket(client, player))
    {
        QString message = "insert-token\n%0\r\n";

        if (m_match->getActualTurn() == player.token)
        {
            bool rowOk, colOk;

            int row = args[1].toInt(&rowOk);
            int col = args[2].toInt(&colOk);

            if (rowOk && colOk)
            {
                qint8 result = m_match->getBoard()->insertToken(row, col, player.token);

                if (result == 0)
                {
                    message = message.arg("OK");

                    //Aware all clients that a token is inserted correctly
                    QString broadcast = QString("token-inserted\n%0\n%1\n%2\r\n").arg(getTokenChar(player.token)).arg(row).arg(col);
                    broadcastMessage(broadcast);
                }
                else
                {
                    message = message.arg("BUSY");
                }
            }
            else
            {
                throw "Unable to convert row or column";
            }
        }
        else
        {
            message = message.arg("NYT");
        }

        client->write(message.toLatin1());

        return true;
    }
    else
    {
        throw "Unable to retrieve player";
    }
}

qint32 TicTacToeLanServerMdiSubWindow::insertNewConnectedPlayer(PlayerInfoStruct player)
{
    m_connectedPlayers.append(player);

    int connectedPlayers = m_connectedPlayers.count();

    writeLog(QString("Player info: [%0][%1]").arg(player.name).arg(getTokenChar(player.token)));

    emit connectedPlayerListManaged(connectedPlayers);

    return connectedPlayers;
}

qint32 TicTacToeLanServerMdiSubWindow::removeConnectedPlayer(PlayerInfoStruct player)
{
    m_connectedPlayers.removeOne(player);

    int connectedPlayers = m_connectedPlayers.count();
    emit connectedPlayerListManaged(connectedPlayers);

    return connectedPlayers;
}

bool TicTacToeLanServerMdiSubWindow::getPlayerNameByToken(TicTacToePlayerEnum token, QString &out_playerName) const
{
    QList<PlayerInfoStruct>::const_iterator res = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), [token](const PlayerInfoStruct &player)
    {
        return player.token == token;
    });

    if (res != m_connectedPlayers.end())
    {
        out_playerName = res->name;
        return true;
    }
    else
    {
        return false;
    }
}

bool TicTacToeLanServerMdiSubWindow::getPlayerInfoBySocket(QTcpSocket *socket, PlayerInfoStruct &out_playerInfo) const
{
    QList<PlayerInfoStruct>::const_iterator res = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), [socket](const PlayerInfoStruct &player)
    {
        return player.socket == socket;
    });

    if (res != m_connectedPlayers.end())
    {
        out_playerInfo = res[0];
        return true;
    }
    else
    {
        return false;
    }
}

bool TicTacToeLanServerMdiSubWindow::broadcastMessage(const QString message) const
{
    for (const PlayerInfoStruct& player : m_connectedPlayers)
    {
        player.socket->write(message.toUtf8());
    }

    return true;
}

bool TicTacToeLanServerMdiSubWindow::openClient() const
{
    QTcpSocket *clientSocket = new QTcpSocket();

    connect(clientSocket, &QTcpSocket::connected, this, &TicTacToeLanServerMdiSubWindow::onClientTcpSocketConnected);
    connect(clientSocket, &QTcpSocket::errorOccurred, this, &TicTacToeLanServerMdiSubWindow::onClientTcpSocketErrorOccured);

    clientSocket->connectToHost(m_server->serverAddress(), m_server->serverPort());

    return true;
}

void TicTacToeLanServerMdiSubWindow::closeEvent(QCloseEvent *event)
{
    QString title = tr("Server is closing");
    QString message = tr("You are closing the server for this game. This will close every single connection tied to this server.\nAre you sure you want to proceed?");

    QMessageBox::StandardButton response = QMessageBox::question(this, title, message);

    if (response != QMessageBox::StandardButton::Yes)
    {
        event->ignore();
    }
    else
    {
        QList<QTcpSocket*> clients = m_server->findChildren<QTcpSocket*>();

        for (QTcpSocket* &client : clients)
        {
            client->disconnectFromHost();
        }

        if (m_server->isListening())
        {
            m_server->close();
        }
    }
}

void TicTacToeLanServerMdiSubWindow::onTestPushButtonClicked(bool checked)
{
    (void) checked;

    writeLog("Test!");
}

void TicTacToeLanServerMdiSubWindow::onClearPushButtonClicked(bool checked)
{
    (void) checked;

    QString title = tr("Log clear");
    QString message = tr("You are going to clear the log message.\nDo you want to proceed?");


    QMessageBox::StandardButton msgBoxResult = QMessageBox::question(this, title, message);

    if (msgBoxResult == QMessageBox::StandardButton::Yes)
    {
        ui->logPlainTextEdit->clear();
    }
}

void TicTacToeLanServerMdiSubWindow::onTCPServerNewConnection()
{
    QTcpSocket *client = m_server->nextPendingConnection();

    writeLog(QString("New client connected. IP: %0 .").arg(client->localAddress().toString()));

    connect(client, &QTcpSocket::readyRead, this, &TicTacToeLanServerMdiSubWindow::onTcpSocketReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &TicTacToeLanServerMdiSubWindow::onTcpSocketDisconnected);

    client->write("get-player-info\r\n");
}

void TicTacToeLanServerMdiSubWindow::onTcpSocketReadyRead()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());

    manageTcpIncomingMessage(senderSocket);
}

void TicTacToeLanServerMdiSubWindow::onTcpSocketDisconnected()
{
    QTcpSocket *m_sender = qobject_cast<QTcpSocket*>(sender());

    writeLog(QString("Client [%0] disconnected.").arg(m_sender->localAddress().toString()));
}

void TicTacToeLanServerMdiSubWindow::onConnectedPlayerListManaged(int &nrOfConnectedPlayers)
{
    if (!m_gameIsReady && nrOfConnectedPlayers == 2)
    {
        m_gameIsReady = true;
        emit gameIsReady();
    }
}

void TicTacToeLanServerMdiSubWindow::onGameIsReady()
{
    //Initializee match
    QString xPlayerName, oPlayerName;

    bool ok =
        getPlayerNameByToken(TicTacToePlayerEnum::Cross, xPlayerName) &&
        getPlayerNameByToken(TicTacToePlayerEnum::Circle, oPlayerName);

    if (ok)
    {
        m_match = new Match(xPlayerName, oPlayerName, this);

        broadcastMessage("game-ready\r\n");
        writeLog("Game is ready!");
    }
    else
    {
        qDebug() << "How can we suppose how we reach this point?!";
    }
}

void TicTacToeLanServerMdiSubWindow::onClientTcpSocketConnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());

    disconnect(clientSocket, &QTcpSocket::connected, this, &TicTacToeLanServerMdiSubWindow::onClientTcpSocketConnected);
    disconnect(clientSocket, &QTcpSocket::errorOccurred, this, &TicTacToeLanServerMdiSubWindow::onClientTcpSocketErrorOccured);

    TicTacToeLANClientMdiSubWindow *window = new TicTacToeLANClientMdiSubWindow(clientSocket, m_clientPlayerName, TicTacToePlayerEnum::Cross, MainWindow::getMainMdiArea());
    MainWindow::getMainMdiArea()->addSubWindow(window);
    UFrames::centreFormInMdiArea(window);
    window->show();
}

void TicTacToeLanServerMdiSubWindow::onClientTcpSocketErrorOccured()
{
    disconnect(qobject_cast<QTcpSocket*>(sender()), &QTcpSocket::connected, this, &TicTacToeLanServerMdiSubWindow::onClientTcpSocketConnected);
    disconnect(qobject_cast<QTcpSocket*>(sender()), &QTcpSocket::errorOccurred, this, &TicTacToeLanServerMdiSubWindow::onClientTcpSocketErrorOccured);

    QString title = tr("Open client error.");
    QString message = tr("Unable to open the client.\nThe server will be close.");
    QMessageBox::critical(this, title, message);

    this->close();
}
