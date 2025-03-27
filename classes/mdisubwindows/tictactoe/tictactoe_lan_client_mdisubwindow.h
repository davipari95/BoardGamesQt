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

class TicTacToeLANClientMdiSubWindow : public QMdiSubWindow
{
        Q_OBJECT

    public:
        explicit TicTacToeLANClientMdiSubWindow(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken, QWidget *parent = nullptr);
        ~TicTacToeLANClientMdiSubWindow();

    private:
        //Variables
        Ui::TicTacToeLANClientMdiSubWindow *ui;
        QTcpSocket *m_socket;
        LanMatch *m_match;
        QGridLabel* m_board[3][3];

        //Functions
        void initialize(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken);
        void initializeComponents();
        quint64 manageIncomingTcpMessage(QTcpSocket *socket);
        bool manageGetPlayerInfo(QTcpSocket *socket);
        bool manageGameReady();
        bool manageSetTurn(QStringList data);
        bool manageTokenInserted(QStringList data);

    private slots:
        void onTcpSocketReadyRead();
        void onTcpSocketDisconnected();
        void onBoardCellClicked();
};

#endif // TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H
