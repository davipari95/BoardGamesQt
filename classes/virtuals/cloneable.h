#ifndef CLONEABLE_H
#define CLONEABLE_H

template <class T>
class Cloneable
{
    public:
        virtual T clone() = 0;
};

#endif // CLONEABLE_H
