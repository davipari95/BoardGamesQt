#include "u_network.h"

#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QAbstractSocket>

QList<QHostAddress> UNetwork::getLocalIPAddresses()
{
    QList<QHostAddress> result;
    QList<QHostAddress> allAddresses = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : std::as_const(allAddresses))
    {
        if (address.protocol() == QHostAddress::IPv4Protocol && address != QHostAddress::LocalHost)
        {
            result.append(address);
        }
    }

    return result;
}

bool UNetwork::getPrimaryIPAddress(QHostAddress &out_primaryIpAddress)
{
    for (const QNetworkInterface &netInterface : QNetworkInterface::allInterfaces())
    {
        if (!(netInterface.flags() & QNetworkInterface::IsUp) || (netInterface.flags() & QNetworkInterface::IsLoopBack))
        {
            continue;
        }

        for (const QNetworkAddressEntry &entry : netInterface.addressEntries())
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                out_primaryIpAddress = entry.ip();
                return true;
            }
        }
    }

    return false;
}
