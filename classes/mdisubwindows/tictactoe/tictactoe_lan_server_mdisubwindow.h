#ifndef TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
#define TICTACTOE_LAN_SERVER_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QTcpServer>
#include <classes/objects/tictactoe/match.h>
#include <enums/tictactoe/tictactoe_players_enum.h>

namespace Ui {
class TicTacToeLanServerMdiSubWindow;
}

class TicTacToeLanServerMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        explicit TicTacToeLanServerMdiSubWindow(QString playerName, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerMdiSubWindow();

    private:
        //Structs
        struct PlayerInfoStruct
        {
            QTcpSocket *socket;
            TicTacToePlayerEnum token;
            QString name;

            bool operator == (const PlayerInfoStruct &other) const
            {
                return
                        socket == other.socket &&
                        token == other.token &&
                        name == other.name;
            }
        };

        //Variables
        QList<PlayerInfoStruct> m_connectedPlayers;
        Ui::TicTacToeLanServerMdiSubWindow *ui;
        QHostAddress m_primaryAddress;
        QTcpServer *m_server;
        std::unique_ptr<Match> m_match;
        bool m_gameIsReady;

        //Functions
        void initializeComponents();
        void initialize();
        void writeLog(QString logMessage);
        void waitClients();
        qint32 manageTcpIncomingMessage(QTcpSocket* client);
        bool manageIncomingGetPlayerInfo(QTcpSocket *client, QStringList args);
        bool manageIncomingGetGame(QTcpSocket *client);
        qint32 insertNewConnectedPlayer(PlayerInfoStruct player);
        qint32 removeConnectedPlayer(PlayerInfoStruct player);
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTestPushButtonClicked(bool checked);
        void onClearPushButtonClicked(bool checked);
        void onTCPServerNewConnection();
        void onTcpSocketReadyRead();
        void onTcpSocketDisconnected();

    signals:
        void connectedPlayerListManaged(int &nrOfConnectedPlayers);
        void gameIsReady();
};

#endif // TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
