#ifndef V_REGEX_H
#define V_REGEX_H

class QRegularExpression;

/**
 * @brief Class that contains regex variables.
 */
class VRegex
{
    public:
        /**
         * @brief Function that return a regular expression useful for validate an IPv4 address.
         * @return A regular expression useful for validate an IPv4 address.
         */
        static QRegularExpression &getIp();

};

#endif // V_REGEX_H
