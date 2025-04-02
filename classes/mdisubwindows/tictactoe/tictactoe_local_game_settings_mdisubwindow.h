#ifndef TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <enums/tictactoe/tictactoe_players_enum.h>

namespace Ui {
    class TicTacToeLocalGameSettingsMdiSubWindow;
}

/**
 * @brief Window that is used for set the local game.
 */
class TicTacToeLocalGameSettingsMdiSubWindow : public QMdiSubWindow
{
        Q_OBJECT

    public:
        //Constructor
        /**
         * @brief Initialize this class
         * @param[in] parent The parent where this class is initialized.
         */
        explicit TicTacToeLocalGameSettingsMdiSubWindow(QWidget *parent = nullptr);

        //Destructor
        ~TicTacToeLocalGameSettingsMdiSubWindow();

    private:
        //Properties
        /**
         * @brief User interface.
         */
        Ui::TicTacToeLocalGameSettingsMdiSubWindow *ui;

        //Functions
        /**
         * @brief Connect all slots with relative signals.
         * @return This function returns always `true`.
         */
        bool connectAllSlots();
        /**
         * @brief Retrieve player names from `xPlayerNameLineEdit` and `oPlayerNameLineEdit` and check if the names are valid.
         * @param[out] out_missingNames Players token which names are not valid.
         * @param[out] out_xPlayerName Validated name of the player that plays cross.
         * @param[out] out_oPlayerName Validated name of the player that plays circle.
         * @return Return `true` if both names are valid, `false` otherwise.
         */
        bool checkInsertedNames(TicTacToePlayerEnum &out_missingNames, QString &out_xPlayerName, QString &out_oPlayerName);
        /**
         * @brief Check if names given in `xPlayerName` and in `oPlayerName` are valid.
         * @param[in] xPlayerName The name of the player that plays cross.
         * @param[in] oPlayerName The name of the player that plays circle.
         * @param[out] out_missingNames The tokens of the players which names are not valid.
         * @return Return `true` if both names are valid, `false` otherwise.
         */
        bool checkInsertedNames(QString xPlayerName, QString oPlayerName, TicTacToePlayerEnum &out_missingNames);
        /**
         * @brief Reset the line edit with the plain stylesheet.
         *
         * The plain stylesheet is in `VStyles::plain`.
         *
         * @return This function returns always `true`.
         */
        bool resetLineEditsBackground();

    private slots:
        /**
         * @brief Slot that manage the signal `QAbstractButton::clicked()` of the button `cancelPushButton`.
         *
         * Clicking on this button, the window will close.
         *
         * @param[out] checked If the button is checkable, `true` if checked, `false` otherwise.
         */
        void onCancelPushButtonClicked(bool checked);
        /**
         * @brief Slot that manage the signal `QAbstractButton::clicked()` of the button `playPushButton`.
         *
         * This slot will check if names in `xPlayerNameLineEdit` and `oPlayerNameLineEdit` are valid, and in case are
         * not, highlight the line edits whith invalid values.
         *
         * @param[out] checked If the button is checkable, `true` if checked, `false` otherwise.
         */
        void onPlayPushButtonClicked(bool checked);
};

#endif // TICTACTOE_LOCAL_GAME_SETTINGS_MDISUBWINDOW_H
