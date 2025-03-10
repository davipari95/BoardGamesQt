#include "tictactoe_lan_server_mdisubwindow.h"
#include "ui_tictactoe_lan_server_mdisubwindow.h"

#include <classes/utils/u_frames.h>
#include <classes/utils/u_network.h>

#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>

TicTacToeLanServerMdiSubWindow::TicTacToeLanServerMdiSubWindow(QString playerName, int portNr, QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::TicTacToeLanServerMdiSubWindow)
{
    (void) playerName;

    initialize(portNr);
    initializeComponents();
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
    QHostAddress primaryHostAddress;

    if (UNetwork::getPrimaryIPAddress(primaryHostAddress))
    {
        ui->ipAddressLabel->setText(primaryHostAddress.toString());
    }

    //Show port number
    ui->portLabel->setText(QString::number(m_portNumber));
}

void TicTacToeLanServerMdiSubWindow::initialize(int portNr)
{
    m_portNumber = portNr;
}

void TicTacToeLanServerMdiSubWindow::writeLog(QString logMessage)
{
    QString message = QString("[%0] >> %1").arg(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss.zzz"), logMessage);
    ui->logPlainTextEdit->appendPlainText(message);
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
