#ifndef LAN_MATCH_H
#define LAN_MATCH_H

#include <QObject>
#include <classes/objects/tictactoe/match.h>

class LanMatch : public Match
{
        Q_OBJECT
    public:
        //Constructor
        explicit LanMatch(QObject *parent = nullptr);

        //Functions
        bool setPlayerName(TicTacToePlayerEnum token, const QString &playerName) const;
};

#endif // LAN_MATCH_H
