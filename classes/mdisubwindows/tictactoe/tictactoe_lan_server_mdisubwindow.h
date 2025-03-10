#ifndef TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
#define TICTACTOE_LAN_SERVER_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
class TicTacToeLanServerMdiSubWindow;
}

class TicTacToeLanServerMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        explicit TicTacToeLanServerMdiSubWindow(QString playerName, int portNr, QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerMdiSubWindow();

    private:
        //Variables
        Ui::TicTacToeLanServerMdiSubWindow *ui;
        int m_portNumber;

        //Functions
        void initializeComponents();
        void initialize(int portNr);
        void writeLog(QString logMessage);
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTestPushButtonClicked(bool checked);
        void onClearPushButtonClicked(bool checked);
};

#endif // TICTACTOE_LAN_SERVER_MDISUBWINDOW_H
