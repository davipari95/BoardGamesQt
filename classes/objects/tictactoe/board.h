#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <enums/tictactoe/tictactoe_players_enum.h>

class Match;
class GridPosition;

class Board : public QObject
{
    Q_OBJECT

    public:
        //Constructors
        explicit Board(Match *matchParent, QObject *parent = nullptr);

        //Functions
        const std::array<std::array<TicTacToePlayerEnum, 3>, 3> getContent();
        qint8 insertToken(const int &row, const int &column, TicTacToePlayerEnum token);
        qint8 insertToken(const GridPosition &position, TicTacToePlayerEnum token);
        /**
         * @brief Retrieves the token at the given row and column.
         *
         * @param row The row position (0-based).
         * @param column The column position (0-based).
         * @return The token in the specified cell.
         */
        TicTacToePlayerEnum getTokenByPosition(const qint32 &row, const qint32 &column);
        TicTacToePlayerEnum getTokenByPosition(const GridPosition &position);
        std::array<QString, 8> getAllSequences();
        void clearContent();

    private:
        //Variables
        Match* m_matchParent;
        std::array<std::array<TicTacToePlayerEnum, 3>, 3> m_content;

        //Functions
        void initialize(Match *matchParent);

signals:
};

#endif // BOARD_H
