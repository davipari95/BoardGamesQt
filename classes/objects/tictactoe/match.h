#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QMap>
#include <enums/tictactoe/tictactoe_players_enum.h>
#include <classes/objects/tictactoe/board.h>

/**
 * @brief Class that represents the Tic-Tac-Toe match.
 */
class Match : public QObject
{
    Q_OBJECT

    protected:
        //Variables
        /**
         * @brief Players of the match.
         */
        QMap<TicTacToePlayerEnum, QString> m_playerNames;
        /**
         * @brief Actual turn (cross or circle).
         */
        TicTacToePlayerEnum m_actTurn;

    private:
        //Variables
        /**
         * @brief Game is stopped (`true` is stopped, `false` is not).
         */
        bool m_gameStopped;
        /**
         * @brief Board of the match
         */
        Board *m_board;

        //Functions
        /**
         * @brief Initialize the variables of this class.
         *
         * This function will initialize the player names with the names given in `xPlayerName` and `oPlayerName`, the `m_board` with
         * an empty board and set the game stopped (`m_gameStopped`) to `false`.
         *
         * @param[in] xPlayerName Name of the player that plays cross.
         * @param[in] oPlayerName Name of the player that plays circle.
         */
        void initialize(const QString &xPlayerName, const QString &oPlayerName);
        /**
         * @brief Set the actual turn.
         *
         * This function will emit the signal `actualTurnChangedSignal()`.
         *
         * @param[in] turn New turn (cross or circle).
         */
        void setActualTurn(TicTacToePlayerEnum turn);

    public:
        //Constructors
        /**
         * @brief Class initializer
         *
         * @param[in] xPlayerName The name of the player that plays cross.
         * @param[in] oPlayerName The name of the player that plays circle.
         * @param[in] parent The parent where this class is initialized.
         */
        explicit Match(const QString &xPlayerName, const QString &oPlayerName, QObject *parent = nullptr);

        //Destructor
        virtual ~Match();

        //Functions
        /**
         * @brief Retrieve the actual turn (cross or circle).
         * @return The actual turn (cross or circle).
         */
        TicTacToePlayerEnum getActualTurn();
        /**
         * @brief Change the turn from cross to circle and vice versa.
         */
        void switchTurn();
        /**
         * @brief Retrieve the board of this match.
         * @return Return a pointer that point at the board of this match.
         */
        Board* getBoard();
        /**
         * @brief Check if there is a game over.
         * @return Return the winner of the match or:
         * <ul>
         *  <li>`TicTacToePlayerEnum::None` if the game is not finished yet;</li>
         *  <li>`TicTacToePlayerEnum::Cross | TicTacToePlayerEnum::Circle` if the game is finished with drawn.</li>
         * </ul>
         */
        TicTacToePlayerEnum checkGameOver();
        /**
         * @brief Retrieve the player name that plays token give in `token`.
         * @param[in] token The token that is played by the player whic you want to retrieve the name.
         * @param[out] out_payerName The name of the player that plays the token given in `token`.
         * @return Return `true` if `token` is a valid value, `false` otherwise.
         */
        bool getPlayerName(const TicTacToePlayerEnum token, QString &out_payerName) const;
        /**
         * @brief Start a new match.
         *
         * This function will clear all board and set the actual turn with the value given in `gameStartsWith`.
         *
         * @param[in] gameStartsWith The turn wich the game restart with.
         */
        void restart(const TicTacToePlayerEnum &gameStartsWith);
        /**
         * @brief Stops the game.
         */
        void stopsGame();
        /**
         * @brief Check if the game is stopped.
         *
         * This function will emit the signal `gameStoppedSignal()`
         *
         * @return Return `true` if the game is stopped, `false` if is not.
         */
        bool isGameStopped() const;

    signals:
        /**
         * @brief Signal that is emitted after the turn is changed.
         * @param actualTurn The actual turn.
         */
        void actualTurnChangedSignal(TicTacToePlayerEnum actualTurn);
        /**
         * @brief Signal that is used when the came is completely stopped.
         */
        void gameStoppedSignal();
};

#endif // MATCH_H
