#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include <QObject>
#include <classes/virtuals/equatable.h>
#include <classes/virtuals/cloneable.h>
#include <classes/virtuals/to_stringable.h>

/**
 * @brief A class that represents a position on the grid, using row and column.
 */
class GridPosition : public QObject, Equatable<GridPosition>, Cloneable<GridPosition*>, ToStringable
{
    Q_OBJECT

    public:
        /**
         * @brief Class constructor.
         * Initialize this class into position `(0, 0)`.
         *
         * @param parent The object where this class is initialized.
         */
        explicit GridPosition(QObject *parent = nullptr);
        /**
         * @brief Class constructor.
         * Initialize this class into position `(row, column)`.
         *
         * @param row Row of the grid position.
         * @param column Column of the grid position.
         * @param parent The object where this class is initialized.
         */
        explicit GridPosition(const qint32 &row, const qint32 &column, QObject *parent = nullptr);
        /**
         * @brief Class constructor.
         * Initialize this class on row and column position of `gridPosition`.
         *
         * @param gridPosition The grid position where you want to retrieve row and column.
         * @param parent The object where this class is initialized.
         */
        explicit GridPosition(const GridPosition &gridPosition, QObject *parent = nullptr);

        //Functions
        /**
         * @brief Retrieve the row of the grid position.
         * @return An integer that is the row of the grid position.
         */
        qint32 getRow() const;
        /**
         * @brief Retrieve the column of the grid position.
         * @return An integer that is the column of the grid position.
         */
        qint32 getColumn() const;
        /**
         * @brief Set the row on this grid position.
         * If the value is different from the previous one, the signal `rowValueChangedSignal()` will be emitted.
         *
         * @param value The value of the row that you want to set.
         * @return Return `true` if the inserted value is different from the previous one, `false` otherwise.
         */
        bool setRow(const qint32 &value);
        /**
         * @brief Set the row on this grid position.
         * If the value is different from the previous one, the signal `columnValueChangedSignal()` will be emitted.
         *
         * @param value The value of the column that you want to set.
         * @return Return `true` if the inserted value is different from the previous one, `false` otherwise.
         */
        bool setColumn(const qint32 &value);
        /**
         * @brief Set a new position given the row in `row` and the column in `column`.
         *
         * If the row is different from the previous one, the signal `rowValueChangedSignal()` will be emitted.
         * If the column is different from the previous one, the signal `columnValueChangedSignal()` will be emitted.
         *
         * @param row The value of the row that you want to set.
         * @param column The value of the column that you want to set.
         * @return A bitwise status as following:
         * <ul>
         *  <li>`[0]` → The row is different from the previous one.</li>
         *  <li>`[1]` → The column is different from the previous one.</li>
         * </ul>
         */
        qint32 setPosition(const qint32 &row, const qint32 &column);
        /**
         * @brief Check if the position given in `item` is the same of this instance.
         * @param item The item which compare to.
         * @return Return `true` if the items are equal, `false` otherwise.
         */
        bool equals(const GridPosition &item) const override;
        /**
         * @brief Return a new instance of `GridPosition` with the same row and column position.
         * @return A copy of this instance.
         */
        GridPosition* clone() override;
        /**
         * @brief Function that return a string that represents this instance.
         * @return A string that represents this istance.
         */
        QString toString() override;

    private:
        //Variables
        /**
         * @brief The row position.
         */
        qint32 m_row;
        /**
         * @brief The column position.
         */
        qint32 m_column;

        //Functions
        /**
         * @brief Initialize all variables in this class.
         * @param row The row of the grid position.
         * @param column The column of the grid position.
         */
        void initialize(const qint32 &row, const qint32 &column);

    signals:
        /**
         * @brief Signal that is emitted when the value of the row change.
         * @param value The actual value of the row.
         */
        void rowValueChangedSignal(const qint32 &value);
        /**
         * @brief Signal that is emitted when the value of the column change.
         * @param value The actual value of the column.
         */
        void columnValueChangedSignal(const qint32 &value);
};

#endif // GRIDPOSITION_H
