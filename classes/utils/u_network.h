#ifndef U_NETWORK_H
#define U_NETWORK_H

#include <QList>
#include <QHostAddress>

class UNetwork
{
    public:
        static QList<QHostAddress> getLocalIPAddresses();
        static bool getPrimaryIPAddress(QHostAddress &out_primaryIpAddress);
};

#endif // U_NETWORK_H
