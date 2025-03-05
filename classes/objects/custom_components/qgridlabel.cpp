#include "qgridlabel.h"

QGridLabel::QGridLabel(QWidget *parent) : QLabel(parent)
{
    init(0, 0);
}

QGridLabel::QGridLabel(const GridPosition &position, QWidget *parent) : QLabel(parent)
{
    init(position.getRow(), position.getColumn());
}

QGridLabel::QGridLabel(const qint32 row, const qint32 column, QWidget *parent) : QLabel(parent)
{
    init(row, column);
}

QGridLabel::~QGridLabel()
{
    //Nothing to do ?
}

GridPosition *QGridLabel::getGridPosition()
{
    return m_gridPosition.get();
}

void QGridLabel::init(const qint32 &row, const qint32 &column)
{
    m_gridPosition = std::make_unique<GridPosition>(row, column);
}

void QGridLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    (void) ev;

    emit clicked(this);
}
