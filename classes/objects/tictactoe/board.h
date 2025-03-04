#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <enums/tictactoe/tictactoe_players_enum.h>

class Match;

class Board : public QObject
{
    Q_OBJECT

    public:
        //Constructors
        explicit Board(Match *matchParent, QObject *parent = nullptr);

        //Functions
        const std::array<std::array<TicTacToePlayerEnum, 3>, 3> getContent();
        qint8 insertToken(int row, int column, TicTacToePlayerEnum token);

    private:
        //Variables
        Match* m_matchParent;
        std::array<std::array<TicTacToePlayerEnum, 3>, 3> m_content;

        //Functions
        void initialize(Match *matchParent);
        void clearContent();

signals:
};

#endif // BOARD_H
