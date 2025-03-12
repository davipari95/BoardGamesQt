#include "tictactoe_lan_client_settings_mdisubwindow.h"
#include "ui_tictactoe_lan_client_settings_mdisubwindow.h"

#include <QRegularExpressionValidator>

#include <classes/utils/u_frames.h>
#include <classes/utils/u_network.h>
#include <variables/v_regex.h>
#include <variables/v_styles.h>

TicTacToeLanClientSettingsMdiSubWindow::TicTacToeLanClientSettingsMdiSubWindow(QWidget *parent)
    : QMdiSubWindow(parent),
    ui(new Ui::TicTacToeLanClientSettingsMdiSubWindow)
{
    initializeComponenets();
}

TicTacToeLanClientSettingsMdiSubWindow::~TicTacToeLanClientSettingsMdiSubWindow()
{
    delete ui;
}

void TicTacToeLanClientSettingsMdiSubWindow::initializeComponenets()
{
    //Flags and attributes
    UFrames::setFlagsAndAttributes(this, true, false);

    //Content
    QWidget *content = new QWidget(this);
    ui->setupUi(content);
    setWidget(content);

    //Size
    UFrames::adaptSubMdiSizesByContent(this, content->width(), content->height(), true);

    //Validators
    //IP
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(VRegex::getIp(), this);
    ui->ipAddressLineEdit->setValidator(ipValidator);
    //Port
    ui->portLineEdit->setValidator(new QIntValidator(0, std::numeric_limits<quint16>::max()));

    //Connect slots
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &TicTacToeLanClientSettingsMdiSubWindow::onCancelPushButtonClicked);
    connect(ui->playPushButton, &QPushButton::clicked, this, &TicTacToeLanClientSettingsMdiSubWindow::onPlayPushButtonClicked);
}

bool TicTacToeLanClientSettingsMdiSubWindow::checkIPAddressLineEdit(QHostAddress &out_hostAddress) const
{
    QString ipAddress = ui->ipAddressLineEdit->text();

    if (ipAddress.trimmed().isEmpty())
    {
        return false;
    }
    else
    {
        if (!UNetwork::tryParseIpAddress(ipAddress, out_hostAddress))
        {
            return false;
        }
    }

    return true;
}

bool TicTacToeLanClientSettingsMdiSubWindow::checkPortLineEdit(quint16 &out_port) const
{
    QString strPortNr = ui->portLineEdit->text();

    if (strPortNr.trimmed().isEmpty())
    {
        return false;
    }
    else
    {
        bool ok;
        out_port = strPortNr.toUShort(&ok);

        return ok;
    }
}

bool TicTacToeLanClientSettingsMdiSubWindow::checkUsernameLineEdit(QString &out_username) const
{
    out_username = ui->usernameLineEdit->text();

    return !(out_username.trimmed().isEmpty());
}

void TicTacToeLanClientSettingsMdiSubWindow::highlightErrorsInField(qint8 checkResult)
{
    if (checkResult & 1 << 0)
    {
        ui->ipAddressLineEdit->setStyleSheet(VStyles::lineEditEmpty);
    }

    if (checkResult & 1 << 1)
    {
        ui->portLineEdit->setStyleSheet(VStyles::lineEditEmpty);
    }

    if (checkResult & 1 << 2)
    {
        ui->usernameLineEdit->setStyleSheet(VStyles::lineEditEmpty);
    }
}

void TicTacToeLanClientSettingsMdiSubWindow::plainTextEdits()
{
    ui->ipAddressLineEdit->setStyleSheet(VStyles::plain);
    ui->portLineEdit->setStyleSheet(VStyles::plain);
    ui->usernameLineEdit->setStyleSheet(VStyles::plain);
}

qint8 TicTacToeLanClientSettingsMdiSubWindow::checkLineEdits(QHostAddress &out_hostAddress, quint16 &out_port, QString &out_username) const
{
    qint8 result = 0b000;

    if (!checkIPAddressLineEdit(out_hostAddress))
    {
        result |= 1 << 0;
    }

    if (!checkPortLineEdit(out_port))
    {
        result |= 1 << 1;
    }

    if (!checkUsernameLineEdit(out_username))
    {
        result |= 1 << 2;
    }

    return result;
}

void TicTacToeLanClientSettingsMdiSubWindow::onCancelPushButtonClicked(bool checked)
{
    (void) checked;

    close();
}

void TicTacToeLanClientSettingsMdiSubWindow::onPlayPushButtonClicked(bool checked)
{
    (void) checked;

    plainTextEdits();

    QHostAddress hostAddress;
    quint16 port;
    QString username;

    qint16 errors = checkLineEdits(hostAddress, port, username);

    if (errors)
    {
        highlightErrorsInField(errors);
    }
    else
    {
        //Open socket and check connection.
    }
}
