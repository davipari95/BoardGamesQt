#ifndef V_LAN_PORTS_H
#define V_LAN_PORTS_H

#include <QMap>
#include <enums/games_enum.h>
#include <classes/objects/range.h>

class VLanPorts
{
    public:
        static QMap<GamesEnum, Range*> &getPortsRange();
        bool getPortRangeByGame(GamesEnum game, Range *out_Range);
};

#endif // V_LAN_PORTS_H
