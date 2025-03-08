#ifndef U_LOCALE_H
#define U_LOCALE_H

class QString;

class ULocale
{
    public:
        static QString getSystemLocale();
        static QString getTwoCharSystemLocale();
};

#endif // U_LOCALE_H
