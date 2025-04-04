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
        /**
         * @brief Contains the rematch result retrieved from clients, where:
         * <ul>
         *  <li>`[-2]` → Game is running.</li>
         *  <li>`[0]` → Waiting for rematch.</li>
         *  <li>`[-1]` → Client don't want rematch.</li>
         *  <li>`[1]` → Client want rematch</li>
         * </ul>
         */
        QHash<QTcpSocket*, qint8> m_rematchClientsResult;

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
         * @brief Write log on `logPlainTextEdit`.
         *
         * This function will append automatically the date time.
         *
         * @param logMessage Message to write in `logPlainTextEdit`.
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
         *  <li>`[0]` → `get-player-info`</li>
         *  <li>`[1]` → `get-game`</li>
         *  <li>`[2]` → `insert-token`</li>
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
         * @param[in] client Client that had sent the message. Server will responds here.
         * @param[in] args Arguments containing the token informations (token, row and column).
         * @return Returns `true` if the commands is correctly managed, `false` otherwise.
         */
        bool manageInsertToken(QTcpSocket *client, QStringList &args);
        /**
         * @brief Manage the message `game-over` from the client.
         * @param[in] client The client that sent the message.
         * @param[in] args Arguments of the message.
         * @return asdasd
         */
        bool manageGameOver(QTcpSocket *client, QStringList &args);
        /**
         * @brief Insert a new player given in `player` into `m_connectedPlayers` and emit the signal `connectedPlayerListManaged()`.
         * @param[in] player A `PlayerInfoStruct` containing all informations of the player to add.
         * @return An integer value that is the number of connected players.
         */
        qint32 insertNewConnectedPlayer(PlayerInfoStruct player);
        /**
         * @brief Remove the player given in `player` from `m_connectedPlayers` and emit the signal `connectedPlayerListManaged()`.
         * @param[in] player A `PlayerInfoStruct` containing all informations of the player to remove.
         * @return An integer value that is the number of connected players.
         */
        qint32 removeConnectedPlayer(PlayerInfoStruct player);
        /**
         * @brief Retrieve the player name from `out_playerName` by the token given in `token`.
         * @param[in] token Player token which you want retrieve the player name.
         * @param[out] out_playerName The player name of the given token.
         * @return If the player with the given token exists return `true`, `false` otherwise.
         */
        bool getPlayerNameByToken(TicTacToePlayerEnum token, QString &out_playerName) const;
        /**
         * @brief Retrieve the player informations from `out_playerInfo` by the socket given in `socket`.
         * @param[in] socket The socket which you want retrieve the player name.
         * @param[out] out_playerInfo The player information of the given token.
         * @return If the player with given socket exists return `true`, `false` otherwise.
         */
        bool getPlayerInfoBySocket(QTcpSocket* socket, PlayerInfoStruct &out_playerInfo) const;
        /**
         * @brief Broadcast the message given in `message` to all connected clients.
         * @param message The message that you want to broadcast.
         * @return This function return always `true`.
         */
        bool broadcastMessage(const QString message) const;
        /**
         * @brief Open a client socket that will connect on this server.
         * @return This function return always `true`.
         */
        bool openClient() const;
        /**
         * @brief Set the variable `m_rematchClientsResult` to `0`, that means that the server is waiting for rematch.
         * @return This function returns always `true`.
         */
        bool waitingForRematch();
        /**
         * @brief Set if the client given in `clientSocket` want to rematch the game.
         * @param clientSocket The client that sends the rematch result.
         * @param rematch Set `true` if client want to rematch, `false` otherwise.
         * @return One of the following result:
         * <ul>
         *  <li>`[-1]` → At leaast one client doesn't want to rematch.</li>
         *  <li>`[0]` → Still waiting for all clients.</li>
         *  <li>`[1]` → All clients want to rematch.</li>
         * </ul>
         */
        qint8 setClientRematch(QTcpSocket* clientSocket, bool rematch);
        /**
         * @brief Get an integer that retrieve the rematch state.
         * @return One of the following result:
         * <ul>
         *  <li>`[-1]` → At leaast one client doesn't want to rematch.</li>
         *  <li>`[0]` → Still waiting for all clients.</li>
         *  <li>`[1]` → All clients want to rematch.</li>
         * </ul>
         */
        qint8 getRematchState();
        /**
         * @brief Set the variable `m_rematchClientsResult` at "gaming" state.
         * @return This function returns always `true`.
         */
        bool setRematchInitialState();
        /**
         * @brief Overrided function of `QWidget::closeEvent()` for managing the form closing.
         * @param event Parameters that describe the close event.
         */
        void closeEvent(QCloseEvent *event) override;

    private slots:
        /**
         * @brief Manage the signal `QAbstractButton::clicked()` of the button `testPushButton`.
         * @param checked If the button is checkable: `true` if checked, `false` otherwise.
         */
        void onTestPushButtonClicked(bool checked);
        /**
         * @brief Manage the signal `QAbstractButton::clicked()` of the button `clearPushButton`.
         * @param checked If the button is checkable: `true` if checked, `false` otherwise.
         */
        void onClearPushButtonClicked(bool checked);
        /**
         * @brief Manage the signal `QTcpServer::newConnection()` of `m_server`.
         */
        void onTCPServerNewConnection();
        /**
         * @brief Manage the signal `QIODevice::readyRead()` of connected client.
         */
        void onTcpSocketReadyRead();
        /**
         * @brief Manage the signal `QAbstractSocket::disconnected()` of connected client.
         */
        void onTcpSocketDisconnected();
        /**
         * @brief Manage the signal `connectedPlayerListManaged()`.
         * @param nrOfConnectedPlayers The number of connected player.
         */
        void onConnectedPlayerListManaged(int &nrOfConnectedPlayers);
        /**
         * @brief Manage the signal `gameIsReady()`.
         */
        void onGameIsReady();
        /**
         * @brief Manage the event `QAbstractSocket::connected()` of the socket of the client that server is opening.
         */
        void onClientTcpSocketConnected();
        /**
         * @brief Mange the event `QAbstractSocket::errorOccurred()` of the socket of the client that server is opening.
         */
        void onClientTcpSocketErrorOccured();
        /**
         * @brief Manage the event `Match::actualTurnChangedSignal()` of the match `m_match`.
         * @param[out] turn The actual turn.
         */
        void onActualTurnChangedSignal(TicTacToePlayerEnum turn);

    signals:
        /**
         * @brief Signal that is emitted when the list `m_connectedPlayers` is edited.
         * @param nrOfConnectedPlayers The number of actual connected players.
         */
        void connectedPlayerListManaged(int &nrOfConnectedPlayers);
        /**
         * @brief Signal that is emitted when the game is ready.
         */
        void gameIsReady();
};

#endif // TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
