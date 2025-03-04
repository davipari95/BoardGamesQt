#include "qgridlabel.h"

QGridLabel::QGridLabel(QWidget* parent)
    : QLabel(parent)
{
    initialize(0, 0);
}

QGridLabel::QGridLabel(const GridPosition &gridPosition, QWidget *parent)
    : QLabel(parent)
{
    initialize(gridPosition.getRow(), gridPosition.getColumn());
}

QGridLabel::QGridLabel(const qint32 &row, const qint32 &column, QWidget *parent)
    : QLabel(parent)
{
    initialize(row, column);
}

void QGridLabel::initialize(qint32 row, qint32 column)
{
    m_gridPosition = std::make_unique<GridPosition>(row, column);
}

GridPosition *QGridLabel::getGridPosition()
{
    return m_gridPosition.get();
}
