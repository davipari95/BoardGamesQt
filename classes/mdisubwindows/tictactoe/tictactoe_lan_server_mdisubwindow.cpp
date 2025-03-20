#include "tictactoe_lan_server_mdisubwindow.h"
#include "ui_tictactoe_lan_server_mdisubwindow.h"

#include <classes/utils/u_frames.h>
#include <classes/utils/u_network.h>

#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTcpSocket>
#include <QHash>

TicTacToeLanServerMdiSubWindow::TicTacToeLanServerMdiSubWindow(QString playerName, QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::TicTacToeLanServerMdiSubWindow)
{
    (void) playerName;

    initialize();
    initializeComponents();

    waitClients();
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

void TicTacToeLanServerMdiSubWindow::initialize()
{
    m_server = new QTcpServer(this);
    m_connectedPlayers = QList<PlayerInfoStruct>();
    m_gameIsReady = false;

    //Connect local slots
    connect(this, &TicTacToeLanServerMdiSubWindow::connectedPlayerListManaged, this, &TicTacToeLanServerMdiSubWindow::onConnectedPlayerListManaged);
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

qint32 TicTacToeLanServerMdiSubWindow::manageTcpIncomingMessage(QTcpSocket *client)
{
    QString incoming = client->readAll();

    QStringList datas = incoming.split("\r\n", Qt::SkipEmptyParts);
    QString command = datas[0];

    if (command == "get-player-info")
    {
        if (manageIncomingGetPlayerInfo(client, datas))
        {
            return 1;
        }
    }
    else if (command == "get-game")
    {
        if (manageIncomingGetGame(client))
        {
            return 2;
        }
    }

    qDebug() << "Invalid data received.";
    return -1;
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
    client->write("get-game\r\ntic-tac-toe\r\n");

    return true;
}

qint32 TicTacToeLanServerMdiSubWindow::insertNewConnectedPlayer(PlayerInfoStruct player)
{
    m_connectedPlayers.append(player);

    int connectedPlayers = m_connectedPlayers.count();
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

QString TicTacToeLanServerMdiSubWindow::getPlayerNameByToken(TicTacToePlayerEnum token)
{
    QList<PlayerInfoStruct>::iterator res = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), [token](const PlayerInfoStruct &player)
    {
        return player.token == token;
    });

    if (res != m_connectedPlayers.end())
    {
        return res->name;
    }
    else
    {
        return "ERROR";
    }
}

bool TicTacToeLanServerMdiSubWindow::getPlayerNameByToken(TicTacToePlayerEnum token, QString &out_playerName) const
{
    QList<PlayerInfoStruct>::iterator res = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), [token](const PlayerInfoStruct &player)
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

bool TicTacToeLanServerMdiSubWindow::broadcastMessage(const QString message) const
{
    for (PlayerInfoStruct player : m_connectedPlayers)
    {
        player.socket->write(message);
    }
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
        for (QTcpSocket *client : m_server->findChildren<QTcpSocket*>())
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
        m_match = std::make_unique<Match>(xPlayerName, oPlayerName);

        broadcastMessage("game-ready\r\n");
    }
    else
    {
        qDebug() << "How can we suppose how we reach this point?!";
    }
}
