#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class QMdiArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        //Properties
        MainWindow(QWidget *parent = nullptr);

        //Destructors
        ~MainWindow();

        //Functions
        static QMdiArea *getMainMdiArea();

    private:
        //Properties
        Ui::MainWindow *ui;
        static MainWindow *m_mainInstance;

        //Functions
        bool connectSlots();
        void setIcons();
        void openRulesForm(QString gameName);
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onFileExitActionTriggered(bool checked);
        void onGamesTicTacToeLocalActionTriggered(bool checked);
        void onGamesTicTacToeRulesActionTriggered(bool checked);
};
#endif // MAIN_WINDOW_H
