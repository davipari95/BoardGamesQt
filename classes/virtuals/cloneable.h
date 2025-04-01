#ifndef CLONEABLE_H
#define CLONEABLE_H

/**
 * @brief A virtual class that is used for representing a cloneable class.
 */
template <class T>
class Cloneable
{
    public:
        /**
         * @brief Clone the class which this function is overrided.
         * @return A clone of the class where this function is overrided.
         */
        virtual T clone() = 0;
};

#endif // CLONEABLE_H
