#ifndef TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H
#define TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

#include <enums/tictactoe/tictactoe_players_enum.h>
#include <classes/objects/custom_components/qgridlabel.h>

namespace Ui {
class TicTacToeLANClientMdiSubWindow;
}

class QTcpSocket;
class LanMatch;

/**
 * @brief Form that contains the client of LAN of Tic Tac Toe game.
 */
class TicTacToeLANClientMdiSubWindow : public QMdiSubWindow
{
        Q_OBJECT

    public:
        /**
         * @brief Initialize the window giving the connected socket in `socket`, the player name in `playerName`, the token in `playerToken` and the parent (usually the MDI area) in `parent`.
         * @param socket The socket that is connected to the server.
         * @param playerName The name of the player.
         * @param playerToken The token of the player (cross of circle).
         * @param parent The parent where this class is initialized.
         */
        explicit TicTacToeLANClientMdiSubWindow(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken, QWidget *parent = nullptr);
        ~TicTacToeLANClientMdiSubWindow();

    private:
        //Variables
        /**
         * @brief User interface of this window.
         */
        Ui::TicTacToeLANClientMdiSubWindow *ui;
        /**
         * @brief Socket that is connected to the server.
         */
        QTcpSocket *m_socket;
        /**
         * @brief Match of the window.
         */
        LanMatch *m_match;
        /**
         * @brief A grid of labels used for showing the token to user.
         */
        QGridLabel* m_board[3][3];

        //Functions
        /**
         * @brief Initialize the variables of this class.
         * @param socket The socket that is connected to server.
         * @param playerName The name of the player.
         * @param playerToken The token of the player (cross or circle).
         */
        void initialize(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken);
        /**
         * @brief Initialize all graphical elements that are not contained into `ui`.
         */
        void initializeComponents();
        /**
         * @brief Update all UI board.
         * @return This function will returns always `true`.
         */
        bool updateGraphics();
        /**
         * @brief Manage all incoming messages from server.
         * @param socket Socket needed for replying to server.
         * @return A bit-to-bit result, where each bit has this meaning:
         * <ul>
         *  <li>`[0]` = `get-player-info` message managed.</li>
         *  <li>`[1]` = `game-ready` message managed correctly.</li>
         *  <li>`[2]` = `set-turn` message managed correctly.</li>
         *  <li>`[3]` = `token-inserted` message managed correctly.</li>
         * </ul>
         */
        quint64 manageIncomingTcpMessage(QTcpSocket *socket);
        /**
         * @brief Manage the command `get-player-info` from server.
         * @param socket The socket where to respond to the server.
         * @return Return `true` if the command is managed correctly, otherwise `false`.
         */
        bool manageGetPlayerInfo(QTcpSocket *socket);
        /**
         * @brief Manage the command `game-ready` from server.
         * @return Return `true` if the command is managed correctly, otherwise `false`.
         */
        bool manageGameReady();
        /**
         * @brief Manage the command `set-turn` from server.
         * @param data The arguments of the command `set-turn`.
         * @return Return `true` if the command is managed correctly, `false` otherwise.
         */
        bool manageSetTurn(QStringList data);
        /**
         * @brief Manage the command `token-inserted` from server.
         * @param data The arguments of the command `token-inserted`.
         * @return Return `true` if the command is managed correctly, `false` otherwise.
         */
        bool manageTokenInserted(QStringList data);
        /**
         * @brief Manage the command `insert-token` from server.
         * @param args The arguments of the command `insert-token`.
         * @return Return `true` if the command is managed correctly, `false` otherwise.
         */
        bool manageInsertToken(QStringList args);
        /**
         * @brief Manage the command `game-over` from server.
         * @param[in] socket The socket used for responding to server.
         * @param[in] args Arguments of the command, where:
         * <ul>
         *  <li>
         *      `args[1]` → Game over result, where
         *      <ul>
         *          <li>`X` → The player that plays cross wins;</li>
         *          <li>`O` → The player that plays circle wins;</li>
         *          <li>`#` → Drawn game.</li>
         *      </ul>
         *  </li>
         * </ul>
         * @return Return `true` if the command is managed correctly, `false` otherwise.
         */
        bool manageGameOver(QTcpSocket *socket, QStringList args);

    private slots:
        /**
         * @brief Slot that manage the signal `QIODevice::readyRead()`.
         */
        void onTcpSocketReadyRead();
        /**
         * @brief Slot that manage the signal `QIODevice::readyRead()`.
         */
        void onTcpSocketDisconnected();
        /**
         * @brief Slot that manage the signal `QGridLabel::clicked()`.
         */
        void onBoardCellClicked();
};

#endif // TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H
