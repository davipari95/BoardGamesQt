#ifndef TICTACTOE_LAN_CLIENT_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LAN_CLIENT_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QTcpSocket>
#include <enums/tictactoe/tictactoe_players_enum.h>

namespace Ui {
class TicTacToeLanClientSettingsMdiSubWindow;
}

class TicTacToeLanClientSettingsMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        explicit TicTacToeLanClientSettingsMdiSubWindow(QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanClientSettingsMdiSubWindow();

    private:
        //Variables
        Ui::TicTacToeLanClientSettingsMdiSubWindow *ui;

        //Functions
        void initializeComponenets();
        qint8 checkLineEdits(QHostAddress &out_hostAddress, quint16 &out_port, QString &out_username) const;
        bool checkIPAddressLineEdit(QHostAddress &out_hostAddress) const;
        bool checkPortLineEdit(quint16 &out_port) const;
        bool checkUsernameLineEdit(QString &out_username) const;
        void highlightErrorsInField(qint8 checkResult);
        void plainTextEdits();

    private slots:
        void onCancelPushButtonClicked(bool checked);
        void onPlayPushButtonClicked(bool checked);
};

#endif // TICTACTOE_LAN_CLIENT_SETTINGS_MDISUBWINDOW_H
