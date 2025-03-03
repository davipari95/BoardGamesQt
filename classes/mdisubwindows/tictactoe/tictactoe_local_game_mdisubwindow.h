#ifndef TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
#define TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
class TicTacToeLocalGame;
}

class TicTacToeLocalGame : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit TicTacToeLocalGame(QString xPlayerName, QString oPlayerName, QWidget *parent = nullptr);
    ~TicTacToeLocalGame();

private:
    Ui::TicTacToeLocalGame *ui;
};

#endif // TICTACTOE_LOCAL_GAME_MDISUBWINDOW_H
