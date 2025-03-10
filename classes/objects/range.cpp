#include "range.h"
#include "qdebug.h"

Range::Range(const qint32 &min, const qint32 &max, QObject *parent) : QObject(parent)
{
    if (min > max)
    {
        qDebug() << "Min and max are swapped";
        initialize(max, min);
    }
    else
    {
        initialize(min, max);
    }
}

qint32 Range::getMin() const
{
    return m_min;
}

qint32 Range::getMax() const
{
    return m_max;
}

bool Range::isInRange(const qint32 &value) const
{
    return Range::isInRange(getMin(), getMax(), value);
}

qint32 Range::getGap() const
{
    return getMax() - getMin() + 1;
}

bool Range::isInRange(const qint32 &min, const qint32 &max, const qint32 &value)
{
    if (min > max)
    {
        qDebug() << "Min and max are swapped";
        return value >= max && value <= min;
    }
    else
    {
        return value >= min && value <= max;
    }
}

void Range::initialize(const qint32 &min, const qint32 &max)
{
    m_min = min;
    m_max = max;
}
