#include "board.h"

Board::Board(Match *matchParent, QObject *parent)
    : QObject{parent}
{
    initialize(matchParent);
}

qint8 Board::insertToken(int row, int column, TicTacToePlayerEnum token)
{
    if (m_content[row][column] == TicTacToePlayerEnum::None)
    {
        m_content[row][column] = token;

        return 0;
    }
    else
    {
        return token == m_content[row][column] ? 1 << 0 : 1 << 1;
    }
}

void Board::initialize(Match *matchParent)
{
    //Match parent
    m_matchParent = matchParent;

    //Initialize content
    clearContent();
}

void Board::clearContent()
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            m_content[r][c] = TicTacToePlayerEnum::None;
        }
    }
}
