#ifndef QGRIDLABEL_H
#define QGRIDLABEL_H

#include <QLabel>
#include <QObject>
#include <classes/objects/gridposition.h>

class QGridLabel : public QLabel
{
    Q_OBJECT

    public:
        //Constructors
        explicit QGridLabel(QWidget *parent = nullptr);
        explicit QGridLabel(const GridPosition &position, QWidget *parent = nullptr);
        explicit QGridLabel(const qint32 row, const qint32 column, QWidget *parent = nullptr);

        //Destructor
        ~QGridLabel();

        //Functions
        GridPosition *getGridPosition();

    private:
        //Variables
        std::unique_ptr<GridPosition> m_gridPosition;

        //Functions
        void init(const qint32 &row, const qint32 &column);
        void mouseReleaseEvent(QMouseEvent *ev) override;

    signals:
        void clicked(QGridLabel* sender);

};

#endif // QGRIDLABEL_H
