#ifndef U_NETWORK_H
#define U_NETWORK_H

#include <QList>
#include <QHostAddress>

/**
 * @brief Class that contains static functions useful for networking.
 */
class UNetwork
{
    public:
        /**
         * @brief Get all local IP addresses.
         * @return A list containin all local IP addresses.
         */
        static QList<QHostAddress> getLocalIPAddresses();
        /**
         * @brief Retrieve the main IP address of this system.
         * @param[out] out_primaryIpAddress The primary IP address of this system.
         * @return Return `true` if a primary IP address is found, `false` otherwise.
         */
        static bool getPrimaryIPAddress(QHostAddress &out_primaryIpAddress);
        /**
         * @brief Try to parse a string of the IP address given in `strIpAddress` and return a validated IP address in `out_ipAddress`.
         * @param[in] strIpAddress String with the IP address to validate.
         * @param[out] out_ipAddress Validated IP address, converted from `strIpAddress`.
         * @return Return `true` if the string given in `strIpAddress` was valid, `false` otherwise.
         */
        static bool tryParseIpAddress(const QString strIpAddress, QHostAddress &out_ipAddress);
};

#endif // U_NETWORK_H
