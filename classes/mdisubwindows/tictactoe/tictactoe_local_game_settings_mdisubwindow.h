#ifndef TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class TicTacToeLocalGameSettingsMdiSubWindow;
}

class TicTacToeLocalGameSettingsMdiSubWindow : public QMdiSubWindow
{
        Q_OBJECT

    public:
        //Constructor
        explicit TicTacToeLocalGameSettingsMdiSubWindow(QWidget *parent = nullptr);

        //Destructor
        ~TicTacToeLocalGameSettingsMdiSubWindow();

    private:
        //Properties
        Ui::TicTacToeLocalGameSettingsMdiSubWindow *ui;
};

#endif // TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H
