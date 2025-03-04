#ifndef EQUATABLE_H
#define EQUATABLE_H

template <class T>
class Equatable
{
    public:
        virtual bool equals(const T &item) const = 0;
};

#endif // EQUATABLE_H
