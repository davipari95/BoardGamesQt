#ifndef LAN_MATCH_H
#define LAN_MATCH_H

#include <QObject>
#include <classes/objects/tictactoe/match.h>

/**
 * @brief This class represents a Tic-Tac-Toe LAN match.
 */
class LanMatch : public Match
{
        Q_OBJECT
    public:
        //Constructor
        /**
         * @brief Class constructor.
         * @param clientToken The token of the client where this class is initialized.
         * @param clientPlayerName The username of the client where this class is initialized
         * @param parent The object where this class is initialized.
         */
        explicit LanMatch(const TicTacToePlayerEnum clientToken, const QString &clientPlayerName, QObject *parent = nullptr);

        //Functions
        /**
         * @brief Set the player name of the player that plays the token given in `token`.
         * @param[in] token The token of the player you want to change the name of.
         * @param[in] playerName The name of the player of the token given in `token`.
         * @return This function returns always `true`.
         */
        bool setPlayerName(const TicTacToePlayerEnum token, const QString &playerName);
        /**
         * @brief Retrieve the token of the client where this class is initialized.
         * @return The token of the client where this class is initialized.
         */
        TicTacToePlayerEnum getClientToken() const;
        /**
         * @brief Set the token of the client where this class is initialized.
         * @param[in] value The token of the client where this class is initialized.
         * @return Return `true` if the value is different from the previous one, `false` otherwise.
         */
        bool setClientToken(const TicTacToePlayerEnum &value);
        /**
         * @brief Retrieve the token and the name of the player that is managing the client where this class is initialized.
         * @param[out] out_token The token of the player.
         * @param[out] out_playerName The name of the player.
         * @return Return `true` if the player name exists in this contest, `false` otherwise.
         */
        bool getClientPlayerInfo(TicTacToePlayerEnum &out_token, QString &out_playerName) const;
        /**
         * @brief Check if game is ready.
         * @return Return `true` if game is ready, `false` otherwise.
         */
        bool isGameReady() const;
        /**
         * @brief Set the game ready with the value given in `value`.
         * @param[in] value The value of game ready to set.
         * @return Return `true` if value is different from the previous one, `false` otherwise.
         */
        bool setGameIsReady(const bool &value);
        /**
         * @brief Set the actual turn of this match.
         * @param[in] value The new turn of this match.
         * @return Return `true` if the value is different from the previous one, `false` otherwise.
         */
        bool setActualTurn(const TicTacToePlayerEnum &value);

    private:
        //Variables
        /**
         * @brief The token of the client player where this class is intialized.
         */
        TicTacToePlayerEnum m_clientToken;
        /**
         * @brief The state of game ready.
         */
        bool m_gameIsReady;

        //Functions
        /**
         * @brief Initialize all variables of this class.
         * @param[in] clientToken The token of the client player where this class is initialized.
         * @param[in] clientPlayerName The name of the client player where this class is initialized.
         * @return This function returns always `true`.
         */
        bool initialize(const TicTacToePlayerEnum &clientToken, const QString &clientPlayerName);
};

#endif // LAN_MATCH_H
