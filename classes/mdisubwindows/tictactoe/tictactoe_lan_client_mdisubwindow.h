#ifndef TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H
#define TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <enums/tictactoe/tictactoe_players_enum.h>

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

        //Functions
        void initialize(QTcpSocket *socket, const QString &playerName, const TicTacToePlayerEnum &playerToken);
};

#endif // TICTACTOE_LAN_CLIENT_MDISUBWINDOW_H
