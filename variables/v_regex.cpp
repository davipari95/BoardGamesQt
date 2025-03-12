#include "v_regex.h"

#include <QRegularExpression>


QRegularExpression &VRegex::getIp()
{
    static QRegularExpression ipRegex(R"(^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$)");
    return ipRegex;
}
