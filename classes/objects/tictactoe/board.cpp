#include "board.h"

#include <classes/objects/gridposition.h>

/**
 * @brief Initialize the class giving the match parent in <tt>matchParent</tt> and the object parent in <tt>parent</tt>.
 * @param matchParent the match where this class is initialized.
 * @param parent the QObject parent that will deallocate this class.
 */
Board::Board(Match *matchParent, QObject *parent)
    : QObject{parent}
{
    initialize(matchParent);
}

/**
 * @brief Board::insertToken Insert the token into the specified position, giving the row position in <tt>row</tt>, the column position in <tt>column</tt> and the token to insert in <tt>token</tt>.
 * @param row the row position (starting from 0) where you want to insert the token.
 * @param column the column position (starting from 0) where you want to insert the token.
 * @param token the token that you want to insert.
 * @return a number that represents the result:
 * <ul>
 *  <li><tt>0</tt> - The token is inserted correctly.</li>
 *  <li><tt>1</tt> - The cell is busy with the same token.</li>
 *  <li><tt>2</tt> - The cell is busy with another token.</li>
 * </ul>
 */
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

/**
 * @brief Insert the token given the position in <tt>position</tt>.
 * @param position position, 0 based, where you want to insert the token.
 * @param token the token that you want to insert.
 * @return a number that represents the result:
 * <ul>
 *  <li><tt>0</tt> - The token is inserted correctly.</li>
 *  <li><tt>1</tt> - The cell is busy with the same token.</li>
 *  <li><tt>2</tt> - The cell is busy with another token.</li>
 * </ul>
 */
qint8 Board::insertToken(const GridPosition &position, TicTacToePlayerEnum token)
{
    return insertToken(position.getRow(), position.getColumn(), token);
}

/**
 * @brief Initialize the variables of this class.
 * @param matchParent the <tt>Match</tt> class where this class is initialized.
 */
void Board::initialize(Match *matchParent)
{
    //Match parent
    m_matchParent = matchParent;

    //Initialize content
    clearContent();
}

/**
 * @brief Clear all content of the board
 */
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

    sequences[6] = "";
    sequences[7] = "";

    for (int i = 0; i < 3; i++)
    {
        sequences[i*2] = "";
        sequences[(i*2)+1] = "";

        for (int j = 0; j < 3; j++)
        {
            sequences[i*2] += getTokenChar(m_content[i][j]);
            sequences[(i*2)+1] += getTokenChar(m_content[j][i]);
        }

        sequences[6] += getTokenChar(m_content[i][i]);
        sequences[7] += getTokenChar(m_content[i][2 - i]);
    }

    return sequences;
}
