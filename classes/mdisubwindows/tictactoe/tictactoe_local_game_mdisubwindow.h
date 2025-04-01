#ifndef TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <classes/objects/custom_components/qgridlabel.h>
#include <enums/tictactoe/tictactoe_players_enum.h>

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
        Match* m_match;
        QGridLabel* m_cells[3][3];

        //Functions
        void initialize(const QString &xPlayerName, const QString &oPlayerName);
        void initializeComponents();
        void updateGraphics();
        void connectAllSlots();

    private slots:
        void onGridLabelClicked();
        void onActualTurnChanged(TicTacToePlayerEnum actualTurn);
        void onGameStopped();
};

#endif // TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
