#include "gridposition.h"

GridPosition::GridPosition()
    : QObject{nullptr}
{
    initialize(0, 0);
}

GridPosition::GridPosition(const qint32 &row, const qint32 &column)
    : QObject {nullptr}
{
    initialize(row, column);
}

GridPosition::GridPosition(const GridPosition &gridPosition)
    : QObject {nullptr}
{
    initialize(gridPosition.getRow(), gridPosition.getColumn());
}

qint32 GridPosition::getRow() const
{
    return m_row;
}

qint32 GridPosition::getColumn() const
{
    return m_column;
}

bool GridPosition::setRow(const qint32 &value)
{
    if (m_row != value)
    {
        m_row = value;

        emit rowValueChangedSignal(this, value);

        return true;
    }

    return false;
}

bool GridPosition::setColumn(const qint32 &value)
{
    if (m_column != value)
    {
        m_column = value;

        emit columnValueChangedSignal(this, value);

        return true;
    }

    return false;
}

qint32 GridPosition::setPosition(const qint32 &row, const qint32 &column)
{
    qint32 result = 0;

    if (setRow(row))
    {
        result |= 1 << 0;
    }

    if (setColumn(column))
    {
        result |= 1 << 1;
    }

    return result;
}

bool GridPosition::equals(const GridPosition &item) const
{
    return
        item.getRow() == getRow() &&
        item.getColumn() == getColumn();
}

GridPosition* GridPosition::clone()
{
    return new GridPosition(*this);
}

QString GridPosition::toString()
{
    return QString("{row = %0 ::: column = %1}")
        .arg(getRow())
        .arg(getColumn());
}

void GridPosition::initialize(const qint32 &row, const qint32 &column)
{
    m_row = row;
    m_column = column;
}
