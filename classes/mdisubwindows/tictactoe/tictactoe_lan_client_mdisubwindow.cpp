#include "tictactoe_lan_client_mdisubwindow.h"
#include "ui_tictactoe_lan_client_mdisubwindow.h"

#include <QTcpSocket>
#include <QPixmap>

#include <classes/objects/tictactoe/matches/lan_match.h>
#include <classes/utils/u_frames.h>
#include <classes/utils/u_messageboxes.h>

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

bool TicTacToeLANClientMdiSubWindow::updateGraphics()
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            TicTacToePlayerEnum token = m_match->getBoard()->getTokenByPosition(r, c);
            QPixmap pixmap = QPixmap();

            if (token == TicTacToePlayerEnum::Cross)
            {
                pixmap = QPixmap(":/tictactoe/cross").scaled(REAL_CELL_SIZE, REAL_CELL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
            else if (token == TicTacToePlayerEnum::Circle)
            {
                pixmap = QPixmap(":/tictactoe/circle").scaled(REAL_CELL_SIZE, REAL_CELL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }

            m_board[r][c]->setPixmap(pixmap);
        }
    }

    return true;
}

quint64 TicTacToeLANClientMdiSubWindow::manageIncomingTcpMessage(QTcpSocket *socket)
{
    quint64 result = 0;

    QHash<QString, int> commandNrMap =
    {
         {"get-player-info", 0},
         {"game-ready", 1},
         {"set-turn", 2},
         {"token-inserted", 3},
         {"insert-token", 4},
         {"game-over", 5},
    };

    QString message = socket->readAll();

    QStringList commands = message.split("\r\n", Qt::SkipEmptyParts);

    for (QString &command : commands)
    {
        QStringList data = command.split("\n");

        switch (commandNrMap.value(data[0], -1))
        {
            case 0: //get-player-info
                if (manageGetPlayerInfo(socket)) result |= 1 << 0;
                break;

            case 1: //game-ready
                if (manageGameReady()) result |= 1 << 1;
                break;

            case 2: //set-turn
                if (manageSetTurn(data)) result |= 1 << 2;
                break;

            case 3: //token-inserted
                if (manageTokenInserted(data)) result |= 1 << 3;
                break;

            case 4: //insert-token
                if (manageInsertToken(data)) result |= 1 << 4;
                break;

            case 5: //game-over
                if (manageGameOver(socket, data)) result |= 1 << 5;
                break;

            case -1: //Invalid value
                qDebug() << "Invalid value!";
                break;

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

    TicTacToePlayerEnum token = getTokenByChar(data[1][0].toLatin1());
    int row = data[2].toInt(&rowOk);
    int col = data[3].toInt(&colOk);

    if (rowOk && colOk)
    {
        bool ok =  m_match->getBoard()->insertToken(row, col, token) == 0;

        if (ok)
        {
            updateGraphics();
        }

        return ok;
    }
    else return false;
}

bool TicTacToeLANClientMdiSubWindow::manageInsertToken(QStringList args)
{
    if (args[1] == "NYT")
    {
        ui->infoLabel->setText(tr("Not your turn!"));
    }
    else if (args[1] == "BUSY")
    {
        ui->infoLabel->setText(tr("The cell is busy!"));
    }
    else if (args[1] != "OK")
    {
        return false;
    }

    return true;
}

bool TicTacToeLANClientMdiSubWindow::manageGameOver(QTcpSocket *socket, QStringList args)
{
    bool ok = true;

    QMessageBox::StandardButtons buttons = QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No;
    QString title;
    QString message;
    QPixmap icon;
    QString playerName;

    char winner = args[1][0].toLatin1();

    switch (winner)
    {
        case 'X':
            ok = m_match->getPlayerName(TicTacToePlayerEnum::Cross, playerName);
            title = tr("Cross player wins!");
            message = tr("%0 wins that match!\n\nDo you want a rematch?").arg(playerName);
            break;
        case 'O':
            ok = m_match->getPlayerName(TicTacToePlayerEnum::Circle, playerName);
            title = tr("Circle player wins!");
            message = tr("%0 wins that match!\n\nDo you want a rematch?").arg(playerName);
            break;
        case '#':
            title = tr("Drawn match!");
            message = tr("Drawn match!\n\nDo you want a rematch?");
            break;
    }

    QMessageBox::StandardButton result = UMessageBoxes::showCustomMessageBox(title, message, icon, buttons);
    QString reply = QString("game-over\n%0\r\n").arg(result == QMessageBox::StandardButton::Yes ? "YES" : "NO");

    socket->write(reply.toLatin1());

    return ok;
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
    if (m_match->isGameReady())
    {
        QGridLabel* m_sender = qobject_cast<QGridLabel*>(sender());

        if (m_match->getActualTurn() == m_match->getClientToken())
        {
            int row = m_sender->getGridPosition()->getRow();
            int col = m_sender->getGridPosition()->getColumn();

            if (m_match->getBoard()->getTokenByPosition(row, col) == TicTacToePlayerEnum::None)
            {
                QString message = QString("insert-token\n%0\n%1\r\n").arg(row).arg(col);
                m_socket->write(message.toLatin1());
            }
        }
    }
}
