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

/**
 * @brief This is the main window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        //Properties
        /**
         * @brief Initialize this class.
         * @param parent The parent where this class is initialized.
         */
        MainWindow(QWidget *parent = nullptr);

        //Destructors
        ~MainWindow();

        //Functions
        /**
         * @brief Get the MDI area in this form.
         * @return The MDI area in this form.
         */
        static QMdiArea *getMainMdiArea();

    private:
        //Properties
        /**
         * @brief User interface of this window.
         */
        Ui::MainWindow *ui;
        /**
         * @brief The main instance of this window.
         */
        static MainWindow *m_mainInstance;

        //Functions
        /**
         * @brief Connect all signals with the right slots.
         * @return This function returns always `true`.
         */
        bool connectSlots();
        /**
         * @brief Set lighter icons if the programm is in dark mode, darker icon if the program is in light mode.
         */
        void setIcons();
        /**
         * @brief Open the window for showing the rules of the game given in `gameName`.
         * @param gameName The name of the game which you want to open the rules.
         */
        void openRulesForm(QString gameName);
        /**
         * @brief Overrided function that is used just before the window is closing.
         * @param event Parameters that describes the close event.
         */
        void closeEvent(QCloseEvent *event) override;

    private slots:
        /**
         * @brief Slot that manage the signal `QAction::triggered()` of `fileExitAction`.
         * @param checked If checkable, `true` if checked, `false` otherwise.
         */
        void onFileExitActionTriggered(bool checked);
        /**
         * @brief Slot that manage the signal `QAction::triggered()` of `gamesTicTacToeLocalAction`.
         * @param checked If checkable, `true` if checked, `false` otherwise.
         */
        void onGamesTicTacToeLocalActionTriggered(bool checked);
        /**
         * @brief Slot that manage the signal `QAction::triggered()` of `gamesTicTacToeRulesAction`.
         * @param checked If checkable, `true` if checked, `false` otherwise.
         */
        void onGamesTicTacToeRulesActionTriggered(bool checked);
        /**
         * @brief Slot that manage the signal `QAction::triggered()` of `gamesTicTacToeLANCreateAction`.
         * @param checked If checkable, `true` if checked, `false` otherwise.
         */
        void onGamesTicTacToeLANCreateActionTriggered(bool checked);
        /**
         * @brief Slot that manage the signal `QAction::triggered()` of `gamesTicTacToeLANJoinAction`.
         * @param checked If checkable, `true` if checked, `false` otherwise.
         */
        void onGamesTicTacToeLANJoinActionTriggered(bool checked);
};
#endif // MAIN_WINDOW_H
