#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QMap>
#include <enums/tictactoe/tictactoe_players_enum.h>
#include <classes/objects/tictactoe/board.h>

class Match : public QObject
{
    Q_OBJECT

    protected:
        //Variables
        QMap<TicTacToePlayerEnum, QString> m_playerNames;


    private:
        //Variables
        TicTacToePlayerEnum m_actTurn;
        Board *m_board;
        bool m_gameStopped;

        //Functions
        void initialize(const QString &xPlayerName, const QString &oPlayerName);
        void setActualTurn(TicTacToePlayerEnum turn);

    public:
        //Constructors
        explicit Match(const QString &xPlayerName, const QString &oPlayerName, QObject *parent = nullptr);

        //Destructor
        virtual ~Match();

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
