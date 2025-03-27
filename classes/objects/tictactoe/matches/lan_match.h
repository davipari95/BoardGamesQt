#ifndef LAN_MATCH_H
#define LAN_MATCH_H

#include <QObject>
#include <classes/objects/tictactoe/match.h>

class LanMatch : public Match
{
        Q_OBJECT
    public:
        //Constructor
        explicit LanMatch(const TicTacToePlayerEnum clientToken, const QString &clientPlayerName, QObject *parent = nullptr);

        //Functions
        bool setPlayerName(const TicTacToePlayerEnum token, const QString &playerName);
        TicTacToePlayerEnum getClientToken() const;
        bool setClientToken(const TicTacToePlayerEnum &value);
        bool getClientPlayerInfo(TicTacToePlayerEnum &out_token, QString &out_playerName) const;
        bool isGameReady() const;
        bool setGameIsReady(const bool &value);
        bool setActualTurn(const TicTacToePlayerEnum &value);

    private:
        //Variables
        TicTacToePlayerEnum m_clientToken;
        bool m_gameIsReady;

        //Functions
        bool initialize(const TicTacToePlayerEnum &clientToken, const QString &clientPlayerName);
};

#endif // LAN_MATCH_H
