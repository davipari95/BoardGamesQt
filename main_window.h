#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        //Properties
        MainWindow(QWidget *parent = nullptr);

        //Destructors
        ~MainWindow();

    private:
        //Properties
        Ui::MainWindow *ui;

        //Functions
        bool connectSlots();
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onFileExitActionTriggered(bool checked);
        void onGamesTicTacToeLocalActionTriggered(bool checked);
};
#endif // MAIN_WINDOW_H
