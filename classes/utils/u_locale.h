#ifndef U_LOCALE_H
#define U_LOCALE_H

class QString;

/**
 * @brief Class that contains static functions useful for languages and translations.
 */
class ULocale
{
    public:
        /**
         * @brief Retrieve the langauge code of the system with dialect.
         * @return A string with the language code of the system in format `xx_YY`.
         */
        static QString getSystemLocale();
        /**
         * @brief Retrieve the language code of the system.
         * @return A string with two characters that is the langauge active on the system.
         */
        static QString getTwoCharSystemLocale();
};

#endif // U_LOCALE_H
