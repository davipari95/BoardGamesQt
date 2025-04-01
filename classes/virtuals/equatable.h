#ifndef EQUATABLE_H
#define EQUATABLE_H

/**
 * @brief Virtual class.
 * Inherting this class means that the inherted class can be compared with another class of the same type.
 */
template <class T>
class Equatable
{
    public:
        /**
         * @brief Check if the content of the two classes are equals.
         * @param item Item used for compare to.
         * @return Returns `true` if the content are equals, `false` otherwise.
         */
        virtual bool equals(const T &item) const = 0;
};

#endif // EQUATABLE_H
