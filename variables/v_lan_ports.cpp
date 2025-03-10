#include "v_lan_ports.h"

QMap<GamesEnum, Range*> &VLanPorts::getPortsRange()
{
    static QMap<GamesEnum, Range*> ranges = QMap<GamesEnum, Range*>();

    ranges.insert(GamesEnum::TicTacToe, new Range(49152, 49161));

    return ranges;
}
