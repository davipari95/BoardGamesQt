#include "lan_match.h"


LanMatch::LanMatch(QObject *parent)
    : Match("", "", parent)
{

}

LanMatch::LanMatch(const TicTacToePlayerEnum clientToken, const QString &clientPlayerName, QObject *parent)
    : Match("", "", parent)
{
    setClientToken(clientToken);
    setPlayerName(getClientToken(), clientPlayerName);
}

bool LanMatch::setPlayerName(const TicTacToePlayerEnum token, const QString &playerName) const
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
