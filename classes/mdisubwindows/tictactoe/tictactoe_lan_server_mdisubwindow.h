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
        explicit TicTacToeLanServerMdiSubWindow(QString playerName, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerMdiSubWindow();

    private:
        //Variables
        Ui::TicTacToeLanServerMdiSubWindow *ui;
        QHostAddress m_primaryAddress;
        QTcpServer *m_server;
        std::unique_ptr<Match> m_match;

        //Functions
        void initializeComponents();
        void initialize();
        void writeLog(QString logMessage);
        void waitClients();
        qint32 manageTcpIncomingMessage(QTcpSocket* client);
        bool manageIncomingGetPlayerInfo(QTcpSocket *client, QStringList args);
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTestPushButtonClicked(bool checked);
        void onClearPushButtonClicked(bool checked);
        void onTCPServerNewConnection();
        void onTcpSocketReadyRead();
        void onTcpSocketDisconnected();
};

#endif // TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
