#ifndef TO_STRINGABLE_H
#define TO_STRINGABLE_H

class QString;

/**
 * @class ToStringable
 * @brief A virtual class that contains all methods for representing the element into string.
 */
class ToStringable
{
    public:
        /**
         * @fn toString()
         * @brief Retrieve a string that represents the element.
         * @return A string that represents the element.
         */
        virtual QString toString() = 0;
};

#endif // TO_STRINGABLE_H
