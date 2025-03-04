#include "match.h"

Match::Match(const QString &xPlayerName, const QString &oPlayerName, QObject *parent)
    : QObject{parent}
{
    initialize(xPlayerName, oPlayerName);
}

TicTacToePlayerEnum Match::getActualTurn()
{
    return m_actTurn;
}

void Match::switchTurn()
{
    setActualTurn(!m_actTurn);
}

void Match::initialize(const QString &xPlayerName, const QString &oPlayerName)
{
    //Actual turn
    m_actTurn = TicTacToePlayerEnum::Cross;

    //Player names
    m_playerNames = QMap<TicTacToePlayerEnum, QString>();

    m_playerNames.insert(TicTacToePlayerEnum::Cross, xPlayerName);
    m_playerNames.insert(TicTacToePlayerEnum::Circle, oPlayerName);

    //Board
    m_board = std::make_unique<Board>(this);
}

void Match::setActualTurn(TicTacToePlayerEnum turn)
{
    if (m_actTurn != turn)
    {
        m_actTurn = turn;

        emit Match::actualTurnChangedSignal(this, turn);
    }
}
