#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QMap>
#include <enums/tictactoe/tictactoe_players_enum.h>
#include <classes/objects/tictactoe/board.h>

class Match : public QObject
{
    Q_OBJECT

    private:
        //Variables
        QMap<TicTacToePlayerEnum, QString> m_playerNames;
        TicTacToePlayerEnum m_actTurn;
        std::unique_ptr<Board> m_board;
        bool m_gameStopped;

        //Functions
        void initialize(const QString &xPlayerName, const QString &oPlayerName);
        void setActualTurn(TicTacToePlayerEnum turn);

    public:
        //Constructors
        explicit Match(const QString &xPlayerName, const QString &oPlayerName, QObject *parent = nullptr);

        //Functions
        TicTacToePlayerEnum getActualTurn();
        void switchTurn();
        Board* getBoard();
        TicTacToePlayerEnum checkGameOver();
        bool getPlayerName(const TicTacToePlayerEnum token, QString &out_payerName) const;
        void restart(const TicTacToePlayerEnum &gameStartsWith);
        void stopsGame();
        bool isGameStopped() const;

    signals:
        void actualTurnChangedSignal(Match *sender, TicTacToePlayerEnum actualTurn);
        void gameStoppedSignal(Match *sender);
};

#endif // MATCH_H
