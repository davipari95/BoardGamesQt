#ifndef TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <enums/tictactoe/tictactoe_players_enum.h>

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

        //Functions
        bool connectAllSlots();
        bool checkInsertedNames(TicTacToePlayerEnum &out_missingNames, QString &out_xPlayerName, QString &out_oPlayerName);
        bool checkInsertedNames(QString xPlayerName, QString oPlayerName, TicTacToePlayerEnum &out_missingNames);
        bool resetLineEditsBackground();

    private slots:
        void onCancelPushButtonClicked(bool checked);
        void onPlayPushButtonClicked(bool checked);
};

#endif // TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H
