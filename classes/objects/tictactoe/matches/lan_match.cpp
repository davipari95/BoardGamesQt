#include "lan_match.h"

LanMatch::LanMatch(const TicTacToePlayerEnum clientToken, const QString &clientPlayerName, QObject *parent)
    : Match("", "", parent)
{
    initialize(clientToken, clientPlayerName);
}

bool LanMatch::setPlayerName(const TicTacToePlayerEnum token, const QString &playerName)
{
    m_playerNames[token] = playerName;

    return true;
}

TicTacToePlayerEnum LanMatch::getClientToken() const
{
    return m_clientToken;
}

bool LanMatch::setClientToken(const TicTacToePlayerEnum &value)
{
    if (value != m_clientToken)
    {
        m_clientToken = value;

        return true;
    }

    return false;
}

bool LanMatch::getClientPlayerInfo(TicTacToePlayerEnum &out_token, QString &out_playerName) const
{
    out_token = getClientToken();
    return getPlayerName(getClientToken(), out_playerName);
}

bool LanMatch::isGameReady() const
{
    return m_gameIsReady;
}

bool LanMatch::setGameIsReady(const bool &value)
{
    if (value != m_gameIsReady)
    {
        m_gameIsReady = value;

        return true;
    }
    else
    {
        return false;
    }
}

bool LanMatch::setActualTurn(const TicTacToePlayerEnum &value)
{
    if (m_actTurn != value)
    {
        m_actTurn = value;

        return true;
    }

    return false;
}

bool LanMatch::initialize(const TicTacToePlayerEnum &clientToken, const QString &clientPlayerName)
{
    setClientToken(clientToken);
    setPlayerName(getClientToken(), clientPlayerName);
    m_gameIsReady = false;

    return true;
}
