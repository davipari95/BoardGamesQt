#ifndef TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
#define TICTACTOE_LAN_SERVER_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QTcpServer>
#include <classes/objects/tictactoe/match.h>

namespace Ui {
class TicTacToeLanServerMdiSubWindow;
}

class TicTacToeLanServerMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        explicit TicTacToeLanServerMdiSubWindow(QString playerName, int portNr, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerMdiSubWindow();

    private:
        //Variables
        Ui::TicTacToeLanServerMdiSubWindow *ui;
        int m_portNumber;
        QHostAddress m_primaryAddress;
        std::unique_ptr<QTcpServer> m_server;
        std::unique_ptr<Match> m_match;

        //Functions
        void initializeComponents();
        void initialize(int portNr);
        void writeLog(QString logMessage);
        void waitClients();
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTestPushButtonClicked(bool checked);
        void onClearPushButtonClicked(bool checked);
        void onTCPServerNewConnection();
};

#endif // TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
