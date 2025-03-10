#ifndef TICTACTOE_LAN_SERVER_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LAN_SERVER_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
class TicTacToeLanServerSettingsMdiSubWindow;
}

class TicTacToeLanServerSettingsMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        explicit TicTacToeLanServerSettingsMdiSubWindow(QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerSettingsMdiSubWindow();

    private:
        //Variables
        Ui::TicTacToeLanServerSettingsMdiSubWindow *ui;

        //Functions
        void initializeComponents();

    private slots:
        void onCancelPushButtonClicked(bool checked);
        void onOpenServerPushButtonClicked(bool checked);
};

#endif // TICTACTOE_LAN_SERVER_SETTINGS_MDISUBWINDOW_H
