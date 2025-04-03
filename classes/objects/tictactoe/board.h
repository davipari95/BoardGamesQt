#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <enums/tictactoe/tictactoe_players_enum.h>

class Match;
class GridPosition;

/**
 * @brief Class that represents the board of Tic-Tac-Toe game.
 */
class Board : public QObject
{
    Q_OBJECT

    public:
        //Constructors
        /**
         * @brief Class constructor.
         * @param matchParent The match where this class is initialized.
         * @param parent The parent component where this baord is initialized.
         */
        explicit Board(Match *matchParent, QObject *parent = nullptr);

        //Functions
        /**
         * @brief Retrive the content of the board.
         * @return A 3x3 matrix that represents the board containing the tokens.
         */
        const std::array<std::array<TicTacToePlayerEnum, 3>, 3> getContent();
        /**
         * @brief Insert a new token given in `token` on the board, given the row in `row` and the column in `column`.
         * @param row The 0-based row where you want to insert the token.
         * @param column The 0-based column where you want to insert the token.
         * @param token The token that you want to insert (cross or circle).
         * @return A status code that represents the result of this function:
         * <ul>
         *  <li>`[0]` → The token is inserted correctly.</li>
         *  <li>`[1]` → The cell is busy with the same token given in `token`.</li>
         *  <li>`[2]` → The cell is busy with a different token given in `token`.</li>
         * </ul>
         */
        qint8 insertToken(const int &row, const int &column, TicTacToePlayerEnum token);
        /**
         * @brief Insert a new token given in `token` on the board, given the grid position in `position`.
         * @param position The position where you want to insert the token.
         * @param token The token that you want to insert.
         * @return A status code that represents the result of this function:
         * <ul>
         *  <li>`[0]` → The token is inserted correctly.</li>
         *  <li>`[1]` → The cell is busy with the same token given in `token`.</li>
         *  <li>`[2]` → The cell is busy with a different token given in `token`.</li>
         * </ul>
         */
        qint8 insertToken(const GridPosition &position, TicTacToePlayerEnum token);
        /**
         * @brief Retrieve the token into position with row given in `row` and the column given in `column`.
         * @param row The 0-based row where you want to retrieve the token.
         * @param column The 0-based column where you want to retrieve the token.
         * @return The token on given position.
         */
        TicTacToePlayerEnum getTokenByPosition(const qint32 &row, const qint32 &column);
        /**
         * @brief Retrieve the token into position given in `position`.
         * @param position The position where you want to retrieve the token.
         * @return The token on given position.
         */
        TicTacToePlayerEnum getTokenByPosition(const GridPosition &position);
        /**
         * @brief Retrieve all sequences that represents the content of rows, columns and diagonals.
         * On the string, the `X` represents the cross token, the `O` the circle token and the space means that the cell is empty.
         * @return An array of 8 elements, that contains all sequences of the board.
         */
        std::array<QString, 8> getAllSequences();
        /**
         * @brief Remove every tokens from the board.
         */
        void clearContent();

    private:
        //Variables
        /**
         * @brief `Match` parent where this class is initialized.
         */
        Match* m_matchParent;
        /**
         * @brief Content of this baord.
         */
        std::array<std::array<TicTacToePlayerEnum, 3>, 3> m_content;

        //Functions
        /**
         * @brief Initialize the variables of this class.
         * @param matchParent The `Match` parent where this class is initialized.
         */
        void initialize(Match *matchParent);

    signals:
};

#endif // BOARD_H
