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

    signals:
        void actualTurnChangedSignal(Match *sender, TicTacToePlayerEnum actualTurn);
};

#endif // MATCH_H
