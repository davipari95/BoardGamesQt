#include "board.h"

#include <classes/objects/gridposition.h>

Board::Board(Match *matchParent, QObject *parent)
    : QObject{parent}
{
    initialize(matchParent);
}

qint8 Board::insertToken(const int &row, const int &column, TicTacToePlayerEnum token)
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

qint8 Board::insertToken(const GridPosition &position, TicTacToePlayerEnum token)
{
    return insertToken(position.getRow(), position.getColumn(), token);
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

char Board::getTokenChar(TicTacToePlayerEnum token)
{
    switch (token)
    {
        case TicTacToePlayerEnum::Circle:
            return 'O';
        case TicTacToePlayerEnum::Cross:
            return 'X';
        case TicTacToePlayerEnum::None:
            return ' ';
    }
}

TicTacToePlayerEnum Board::getTokenByPosition(const qint32 &row, const qint32 &column)
{
    return m_content[row][column];
}

TicTacToePlayerEnum Board::getTokenByPosition(const GridPosition &position)
{
    return getTokenByPosition(position.getRow(), position.getColumn());
}

std::array<QString, 8> Board::getAllSequences()
{
    std::array<QString, 8> sequences = std::array<QString, 8>();

    sequences[7] = "";
    sequences[8] = "";

    for (int i = 0; i < 3; i++)
    {
        sequences[i*2] = "";
        sequences[(i*2)+1] = "";

        for (int j = 0; j < 3; j++)
        {
            sequences[i*2] += getTokenChar(m_content[i][j]);
            sequences[(i*2)+1] += getTokenChar(m_content[j][i]);
        }

        sequences[7] += getTokenChar(m_content[i][i]);
        sequences[8] += getTokenChar(m_content[i][2 - i]);
    }

    return sequences;
}
