#include "v_lan_ports.h"

QMap<GamesEnum, Range*> &VLanPorts::getPortsRange()
{
    static QMap<GamesEnum, Range*> ranges = QMap<GamesEnum, Range*>();

    ranges.insert(GamesEnum::TicTacToe, new Range(49152, 49161));

    return ranges;
}

bool VLanPorts::getPortRangeByGame(GamesEnum game, Range *out_Range)
{
    QMap<GamesEnum, Range*> ports = getPortsRange();

    if (ports.contains(game))
    {
        out_Range = ports[game];
        return true;
    }
    else
    {
        out_Range = nullptr;
        return false;
    }
}
