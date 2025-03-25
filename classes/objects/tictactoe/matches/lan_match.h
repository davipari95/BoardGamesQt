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
        explicit LanMatch(const TicTacToePlayerEnum clientToken, const QString &clientPlayerName, QObject *parent = nullptr);

        //Functions
        bool setPlayerName(const TicTacToePlayerEnum token, const QString &playerName) const;
        TicTacToePlayerEnum getClientToken() const;
        bool setClientToken(const TicTacToePlayerEnum &value);
        bool getClientPlayerInfo(TicTacToePlayerEnum &out_token, QString &out_playerName) const;

    private:
        TicTacToePlayerEnum m_clientToken;
};

#endif // LAN_MATCH_H
