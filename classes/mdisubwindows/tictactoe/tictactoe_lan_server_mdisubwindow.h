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

/**
 * @brief Server for the tic tac toe game.
 */
class TicTacToeLanServerMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        /**
         * @brief Class constructor.
         *
         * This class, once initialized, will open automatically a client.
         * The opened client will use as username the value passed through `playerName`.
         *
         * @param playerName The player username of the client player.
         * @param parent The parent where this form will be opened.
         */
        explicit TicTacToeLanServerMdiSubWindow(QString playerName, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerMdiSubWindow();

    private:
        //Structs
        /**
         * @brief A struct that contains all player informations.
         */
        struct PlayerInfoStruct
        {
            /**
             * @brief Socket of the player.
             */
            QTcpSocket *socket;
            /**
             * @brief Token of the player (cross or circle).
             */
            TicTacToePlayerEnum token;
            /**
             * @brief Name of the player.
             */
            QString name;

            /**
             * @brief Check if two structs are equals.
             * @param other The other struct.
             * @return Return `true` if the structs are equals, `false` otherwise.
             */
            bool operator == (const PlayerInfoStruct &other) const
            {
                return
                        socket == other.socket &&
                        token == other.token &&
                        name == other.name;
            }
        };

        //Variables
        /**
         * @brief A list that contains all connected players.
         */
        QList<PlayerInfoStruct> m_connectedPlayers;
        /**
         * @brief User interface of this window.
         */
        Ui::TicTacToeLanServerMdiSubWindow *ui;
        /**
         * @brief The IP address of this server.
         */
        QHostAddress m_primaryAddress;
        /**
         * @brief The TCP server used for managing the clients.
         */
        QTcpServer *m_server;
        /**
         * @brief Tic-Tac-Toe match
         */
        Match* m_match;
        /**
         * @brief Variables that check if game is ready.
         */
        bool m_gameIsReady;
        /**
         * @brief Player name of the client opened by the server.
         */
        QString m_clientPlayerName;

        //Functions
        /**
         * @brief Initialize components that are not initialized in 'ui'.
         */
        void initializeComponents();
        /**
         * @brief Initialize the variables of this class
         * @param clientPlayerName The player name of client that the server will open.
         */
        void initialize(const QString &clientPlayerName);
        /**
         * @brief Write log on 'logPlainTextEdit'.
         *
         * This function will append automatically the date time.
         *
         * @param logMessage Message to write in 'logPlainTextEdit'.
         */
        void writeLog(QString logMessage);
        /**
         * @brief Wait for clients.
         */
        void waitClients();
        /**
         * @brief Manage the message received from the client socket in 'client'.
         * @param client The client that sends the message.
         * @return Bit-to-bit value that indicates which message is managed.
         * <ul>
         *  <li>'[0]' → 'get-player-info'</li>
         *  <li>'[1]' → 'get-game'</li>
         *  <li>'[2]' → 'insert-token'</li>
         * </ul>
         */
        quint64 manageTcpIncomingMessage(QTcpSocket* client);
        /**
         * @brief Manage the command 'get-player-info' and reply to client.
         * @param client The client that sent the command. The server will reply to this socket.
         * @param args Arguments that contain the player info.
         * @return Returns `true` if the command is correctly managed, `false` otherwise.
         */
        bool manageIncomingGetPlayerInfo(QTcpSocket *client, QStringList args);
        /**
         * @brief Manage the command `get-game` and reply to client.
         *
         * This command will reply everytime with the following string:
         * `get-game\ntic-tac-toe\r\n`
         *
         * @param client Client that had sent the command. Server will reply to this socket.
         * @return Returns `true` if the command is correctly managed, `false` otherwise.
         */
        bool manageIncomingGetGame(QTcpSocket *client);
        /**
         * @brief Manage the command `insert-token` and reply to client.
         *
         * The client will receive one of the following answer:
         * <ul>
         *  <li>`OK` → The cell is free and a token will be inserted.
         *  <li>`BUSY` → The cell is busy by another token.
         *  <li>`NYT` → Is not the turn of the client.
         * </ul>
         *
         * @param client Client that had sent the message. Server will responds here.
         * @param args Arguments containing the token informations (token, row and column).
         * @return Returns `true` if the commands is correctly managed, `false` otherwise.
         */
        bool manageInsertToken(QTcpSocket *client, QStringList &args);
        qint32 insertNewConnectedPlayer(PlayerInfoStruct player);
        qint32 removeConnectedPlayer(PlayerInfoStruct player);
        bool getPlayerNameByToken(TicTacToePlayerEnum token, QString &out_playerName) const;
        bool getPlayerInfoBySocket(QTcpSocket* socket, PlayerInfoStruct &out_playerInfo) const;
        bool broadcastMessage(const QString message) const;
        bool openClient() const;
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTestPushButtonClicked(bool checked);
        void onClearPushButtonClicked(bool checked);
        void onTCPServerNewConnection();
        void onTcpSocketReadyRead();
        void onTcpSocketDisconnected();
        void onConnectedPlayerListManaged(int &nrOfConnectedPlayers);
        void onGameIsReady();
        void onClientTcpSocketConnected();
        void onClientTcpSocketErrorOccured();

    signals:
        void connectedPlayerListManaged(int &nrOfConnectedPlayers);
        void gameIsReady();
};

#endif // TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
