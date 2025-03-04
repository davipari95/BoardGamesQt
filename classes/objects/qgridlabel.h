#ifndef QGRIDLABEL_H
#define QGRIDLABEL_H

#include <QLabel>
#include <QObject>
#include <classes/objects/gridposition.h>

class QGridLabel : public QLabel
{
    Q_OBJECT

    public:
        explicit QGridLabel(QWidget *parent = nullptr);
        explicit QGridLabel(const GridPosition &gridPosition, QWidget *parent = nullptr);
        explicit QGridLabel(const qint32 &row, const qint32 &column, QWidget *parent = nullptr);

    private:
        //Variables
        std::unique_ptr<GridPosition> m_gridPosition;

        //Functions
        void initialize(qint32 row, qint32 column);
        GridPosition* getGridPosition();
};

#endif // QGRIDLABEL_H
