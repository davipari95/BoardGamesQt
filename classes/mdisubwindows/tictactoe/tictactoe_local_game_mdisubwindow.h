#ifndef TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
class TicTacToeLocalGame;
}

class Match;

class TicTacToeLocalGame : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        explicit TicTacToeLocalGame(const QString &xPlayerName,const QString &oPlayerName, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLocalGame();

    private:
        //Variables
        Ui::TicTacToeLocalGame *ui;
        std::unique_ptr<Match> m_match;

        //Functions
        void initialize(const QString &xPlayerName, const QString &oPlayerName);
        void initializeComponents();
};

#endif // TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
