#ifndef RANGE_H
#define RANGE_H

#include <QObject>

/**
 * @brief This class represent numeric range.
 */
class Range : public QObject
{
        Q_OBJECT

    public:
        //Constructor
        /**
         * @brief Initialize this class.
         * @param[in] min The lower side of this range.
         * @param[in] max The higher side of this range.
         * @param[in] parent The parent where this class is initialized.
         */
        explicit Range(const qint32 min, const qint32 max, QObject *parent = nullptr);

        //Functions
        /**
         * @brief Retrieve the lower side of this range.
         * @return  The lower side of this range.
         */
        qint32 getMin() const;
        /**
         * @brief Retrieve the higher side of this range.
         * @return The higher side of this range.
         */
        qint32 getMax() const;
        /**
         * @brief Check if the number given in `value` is in reange.
         * @param[in] value The value to check.
         * @return Return `true` if the numer is in range (`value` greater or equals than min AND less or equals than max).
         */
        bool isInRange(const qint32 &value) const;
        /**
         * @brief Retrieve the width between the lower side and higher side.
         * @return The width between the lower side and higher side.
         */
        qint32 getGap() const;

        //Static functions
        /**
         * @brief Check if number given in `value` is in range between `min` and `max`.
         *
         * If `min` and `max` are swapped, this function will considers the `min` as `max` and the `max` as `min`.
         *
         * @param[in] min The lower side of the gap.
         * @param[in] max The higher side of the gap.
         * @param[in] value The value to check if is metween `min` and `max`.
         * @return Return `true` if the number is between `min` and `max`, `false` if it's not.
         */
        static bool isInRange(const qint32 &min, const qint32 &max, const qint32 &value);

    private:
        //Variables
        /**
         * @brief Lower side of this range.
         */
        qint32 m_min;
        /**
         * @brief Higher side of this range.
         */
        qint32 m_max;

        //Functions
        /**
         * @brief Initialize the variables of this class.
         *
         * This function will set the variable `m_min` with the value given in `min` and `m_max` with the value given in `max`.
         *
         * @param[in] min The lower side of the range.
         * @param[in] max The higher side of the range.
         */
        void initialize(const qint32 min, const qint32 max);

    signals:
};

#endif // RANGE_H
