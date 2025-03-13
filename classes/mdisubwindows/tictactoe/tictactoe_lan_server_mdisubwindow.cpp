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
    else
    {
        qDebug() << "Invalid data received.";
        return -1;
    }
}

bool TicTacToeLanServerMdiSubWindow::manageIncomingGetPlayerInfo(QTcpSocket *client, QStringList args)
{
    char symbol = args[1][0].toLatin1();
    QString playerName = args[2];

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
