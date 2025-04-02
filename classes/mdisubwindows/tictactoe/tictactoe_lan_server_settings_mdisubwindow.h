#ifndef TICTACTOE_LAN_SERVER_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LAN_SERVER_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
class TicTacToeLanServerSettingsMdiSubWindow;
}

/**
 * @brief Window used for set the server informations.
 */
class TicTacToeLanServerSettingsMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        /**
         * @brief Initialize this class.
         * @param[in] parent The parent where this class is initialized.
         */
        explicit TicTacToeLanServerSettingsMdiSubWindow(QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanServerSettingsMdiSubWindow();

    private:
        //Variables
        /**
         * @brief User interface
         */
        Ui::TicTacToeLanServerSettingsMdiSubWindow *ui;

        //Functions
        /**
         * @brief Initialize all components that cannot be initialized in designer.
         */
        void initializeComponents();

    private slots:
        /**
         * @brief Manage the event `QAbstractButton::clicked()` of the component `cancelPushButton`.
         * @param checked If the button is checkable, `true` if checked, `false` if not.
         */
        void onCancelPushButtonClicked(bool checked);
        /**
         * @brief Manage the event `QAbstractButton::clicked()` of the component `openServerPushButton`.
         * @param checked If the button is checkable, `true` if checked, `false` if not.
         */
        void onOpenServerPushButtonClicked(bool checked);
};

#endif // TICTACTOE_LAN_SERVER_SETTINGS_MDISUBWINDOW_H
