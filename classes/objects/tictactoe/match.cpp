#include "match.h"

Match::Match(const QString &xPlayerName, const QString &oPlayerName, QObject *parent)
    : QObject{parent}
{
    initialize(xPlayerName, oPlayerName);
}

Match::~Match()
{

}

TicTacToePlayerEnum Match::getActualTurn()
{
    return m_actTurn;
}

void Match::switchTurn()
{
    setActualTurn(!m_actTurn);
}

Board *Match::getBoard()
{
    return m_board;
}

TicTacToePlayerEnum Match::checkGameOver()
{
    std::array<QString, 8> sequences = m_board->getAllSequences();
    bool full = true;

    for (QString sequence : sequences)
    {
        if (sequence.contains(' '))
        {
            full = false;
        }
        else if (sequence[0] == sequence[1] && sequence[1] == sequence[2])
        {
            return getTokenByChar(sequence[0].toLatin1());
        }
    }

    return full ?
               TicTacToePlayerEnum::Circle | TicTacToePlayerEnum::Cross :
               TicTacToePlayerEnum::None;
}

bool Match::getPlayerName(const TicTacToePlayerEnum token, QString &out_payerName) const
{
    if (token == TicTacToePlayerEnum::Cross || token == TicTacToePlayerEnum::Circle)
    {
        out_payerName = m_playerNames.value(token);

        return true;
    }
    else return false;
}

void Match::restart(const TicTacToePlayerEnum &gameStartsWith)
{
    setActualTurn(gameStartsWith);

    m_board->clearContent();
}

void Match::stopsGame()
{
    m_gameStopped = true;

    emit gameStoppedSignal(this);
}

bool Match::isGameStopped() const
{
    return m_gameStopped;
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
    m_board = new Board(this, this);

    //Game over
    m_gameStopped = false;
}

void Match::setActualTurn(TicTacToePlayerEnum turn)
{
    if (m_actTurn != turn)
    {
        m_actTurn = turn;

        emit Match::actualTurnChangedSignal(this, turn);
    }
}
