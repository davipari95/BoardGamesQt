#ifndef TO_STRINGABLE_H
#define TO_STRINGABLE_H

class QString;

class ToStringable
{
    public:
        virtual QString toString() = 0;
};

#endif // TO_STRINGABLE_H
