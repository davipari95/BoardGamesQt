#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include <QObject>
#include <classes/virtuals/equatable.h>
#include <classes/virtuals/cloneable.h>
#include <classes/virtuals/to_stringable.h>

class GridPosition : public QObject, Equatable<GridPosition>, Cloneable<GridPosition*>, ToStringable
{
    Q_OBJECT

    public:
        explicit GridPosition();
        explicit GridPosition(const qint32 &row, const qint32 &column);
        explicit GridPosition(const GridPosition &gridPosition);

        //Functions
        qint32 getRow() const;
        qint32 getColumn() const;
        bool setRow(const qint32 &value);
        bool setColumn(const qint32 &value);
        qint32 setPosition(const qint32 &row, const qint32 &column);
        bool equals(const GridPosition &item) const override;
        GridPosition* clone() override;
        QString toString() override;

    private:
        //Variables
        qint32 m_row;
        qint32 m_column;

        //Functions
        void initialize(const qint32 &row, const qint32 &column);

    signals:
        void rowValueChangedSignal(GridPosition *sender, const qint32 &value);
        void columnValueChangedSignal(GridPosition *sender, const qint32 &value);
};

#endif // GRIDPOSITION_H
