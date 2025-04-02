#ifndef TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <classes/objects/custom_components/qgridlabel.h>
#include <enums/tictactoe/tictactoe_players_enum.h>

namespace Ui {
class TicTacToeLocalGame;
}

class Match;

/**
 * @brief Window of the Tic-Tac-Toe local game.
 */
class TicTacToeLocalGame : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        /**
         * @brief Initialize this class with players given in `xPlayerName` and `oPlayerName`.
         * @param[in] xPlayerName Name of the player that plays cross.
         * @param[in] oPlayerName Name of the player that plays circle.
         * @param[in] parent Parent where this class is initialized.
         */
        explicit TicTacToeLocalGame(const QString &xPlayerName, const QString &oPlayerName, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLocalGame();

    private:
        //Variables
        /**
         * @brief User interface
         */
        Ui::TicTacToeLocalGame *ui;
        /**
         * @brief Match of the game
         */
        Match* m_match;
        /**
         * @brief UI grid.
         */
        QGridLabel* m_cells[3][3];

        //Functions
        /**
         * @brief Initialize all variables in this class.
         *
         * This function will initialize the variable `m_match` with player names with names given in `xPlayerName` and `oPlayerName`.
         *
         * @param[in] xPlayerName Name of the player that plays cross.
         * @param[in] oPlayerName Name of the player that plays circle.
         */
        void initialize(const QString &xPlayerName, const QString &oPlayerName);
        /**
         * @brief Initialize all UI components that cannot be intialized in designer.
         */
        void initializeComponents();
        /**
         * @brief Update the UI board.
         */
        void updateGraphics();
        /**
         * @brief Connect all slots.
         */
        void connectAllSlots();

    private slots:
        /**
         * @brief Slot that manage the signal `QGridLabel::clicked()` of `m_cells`.
         */
        void onGridLabelClicked();
        /**
         * @brief Slot that manage the signal `Match::actualTurnChangedSignal()` of `m_match`.
         * @param[out] actualTurn The actual turn (cross or circle).
         */
        void onActualTurnChanged(TicTacToePlayerEnum actualTurn);
        /**
         * @brief Slot that manage the signal `Match::gameStoppedSignl()` of `m_match`.
         */
        void onGameStopped();
};

#endif // TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
