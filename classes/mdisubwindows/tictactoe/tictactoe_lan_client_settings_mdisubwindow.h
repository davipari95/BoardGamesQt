#ifndef TICTACTOE_LAN_CLIENT_SETTINGS_MDISUBWINDOW_H
#define TICTACTOE_LAN_CLIENT_SETTINGS_MDISUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QTcpSocket>
#include <enums/tictactoe/tictactoe_players_enum.h>

namespace Ui {
class TicTacToeLanClientSettingsMdiSubWindow;
}

/**
 * @brief Window for setting the IP address, port and username of the client for tic tac toc game.
 */
class TicTacToeLanClientSettingsMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

    public:
        //Constructors
        /**
         * @brief Initialize the class given the parent in `parent`.
         * @param parent The parent of the window.
         *
         */
        explicit TicTacToeLanClientSettingsMdiSubWindow(QWidget *parent = nullptr);

        //Destructors
        ~TicTacToeLanClientSettingsMdiSubWindow();

    private:
        //Variables
        /**
         * @brief User interface of the window
         */
        Ui::TicTacToeLanClientSettingsMdiSubWindow *ui;
        /**
         * @brief State of the socket. Is `true` if the socket is connecting, `false` if not.
         */
        bool m_connecting;

        //Functions
        /**
         * @brief Initialize all component that are not initialized into `ui`.
         */
        void initializeComponenets();
        /**
         * @brief Initialize the variables of this class.
         */
        void initialize();
        /**
         * @brief Check the validity of input fields for the server connection.
         *
         * This function check if input fields (`ipAddressLineEdit`, `portLineEdit` and `usernameLineEdit`) on user interface (IP, port and username) contains valid values.
         * If a value is not valid, the corrisponding bit will be set to 1.
         * <ul>
         *  <li>`[0]` → IP address is not valid.</li>
         *  <li>`[1]` → Port is not valid.</li>
         *  <li>`[2]` → Username is not valid.</li>
         * </ul>
         *
         * @param[out] out_hostAddress A validated IP address.
         * @param[out] out_port A validated port.
         * @param[out] out_username A validated username.
         * @return 3 bits value that indicates which fields are not valid (`0` if all fields are valid).
         */
        qint8 checkLineEdits(QHostAddress &out_hostAddress, quint16 &out_port, QString &out_username) const;
        /**
         * @brief Check if the content of the IP address field (`ipAddressLineEdit`) is valid.
         * @param[out] out_hostAddress The validated IP address.
         * @return Return `true` if the content is valid, `false` otherwise.
         */
        bool checkIPAddressLineEdit(QHostAddress &out_hostAddress) const;
        /**
         * @brief Check if the content of the port field (`portLineEdit`) is valid.
         * @param[out] out_port The validated port number.
         * @return Return `true` if the content is valid, `false` otherwise.
         */
        bool checkPortLineEdit(quint16 &out_port) const;
        /**
         * @brief Check if the content of the username field (`usernameLineEdit`) is valid.
         * @param[out] out_username The validated username.
         * @return Return `true` if the content is valid, `false` otherwise.
         */
        bool checkUsernameLineEdit(QString &out_username) const;
        /**
         * @brief Highlight the fields where the error is.
         * @param[in] checkResult The result after the fields check. Check the function `checkLineEdits()` for that.
         */
        void highlightErrorsInField(qint8 checkResult);
        /**
         * @brief Set the plain stylesheet on all fields.
         */
        void plainTextEdits();
        /**
         * @brief Set the value of variable `m_connecting`. If the previous value is different, the signal `connectingChangedValue()` will be emitted.
         * @param[in] value The value to set to the variable `m_connecting`.
         */
        void setConnecting(const bool value);
        /**
         * @brief Retrieve the value of the variable `m_connecting`.
         * @return Return `true` if the socket is connecting, `false` otherwise.
         */
        bool getConnecting() const;
        /**
         * @brief This event is used when the window is closing. Manage this event.
         * @param closeEvent Variable that contains all parameters that descrive a close event.
         */
        void closeEvent(QCloseEvent *closeEvent) override;

    private slots:
        /**
         * @brief Manage the event `QAbstractButton::clicked(bool)` of the button `cancelPushButton`.
         * @param checked If the button is checkable, `true` if is checked, `false` otherwise.
         */
        void onCancelPushButtonClicked(bool checked);
        /**
         * @brief Manage the event `QAbstractButton::clicked(bool)` of the button `playPushButton`.
         * @param checked If the button is checkable, `true` if is checked, `false` otherwise.
         */
        void onPlayPushButtonClicked(bool checked);
        /**
         * @brief Manage the value chang
         * @param value The actual value of the variable `m_connecting`.
         */
        void onConnectingChangedValue(bool value);

    signals:
        /**
         * @brief Signal that is used when the variable `m_connecting` changes.
         * @param value The actual value of `m_connecting`.
         */
        void connectingChangedValue(bool value);
};

#endif // TICTACTOE_LAN_CLIENT_SETTINGS_MDISUBWINDOW_H
