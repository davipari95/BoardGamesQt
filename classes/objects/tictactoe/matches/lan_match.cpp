#include "lan_match.h"


LanMatch::LanMatch(QObject *parent)
    : Match("", "", parent)
{

}

bool LanMatch::setPlayerName(TicTacToePlayerEnum token, const QString &playerName) const
{
    m_playerNames[token] = playerName;

    return true;
}
