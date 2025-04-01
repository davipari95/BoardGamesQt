#ifndef QGRIDLABEL_H
#define QGRIDLABEL_H

#include <QLabel>
#include <QObject>
#include <classes/objects/gridposition.h>

/**
 * @brief A label that contains grid informations.
 */
class QGridLabel : public QLabel
{
    Q_OBJECT

    public:
        //Constructors
        /**
         * @brief Initialize this class with grid informations in `(0, 0)`.
         * @param[in] parent `QWidget` where this widget is initialized.
         */
        explicit QGridLabel(QWidget *parent = nullptr);
        /**
         * @brief Initialize this class with grid informations given in `position`.
         * @param[in] position Position of this grid label.
         * @param[in] parent `QWidget` where this widget is initialized.
         */
        explicit QGridLabel(const GridPosition &position, QWidget *parent = nullptr);
        /**
         * @brief Initialize this class with grid informations given in `row` and `column`.
         * @param[in] row Row position of the grid label.
         * @param[in] column Column position of the grid label.
         * @param[in] parent `QWidget` where this widget is initialized.
         */
        explicit QGridLabel(const qint32 row, const qint32 column, QWidget *parent = nullptr);

        //Destructor
        ~QGridLabel();

        //Functions
        /**
         * @brief Retrieve the grid position.
         * @return A pointer of `GridPosition` with position informations.
         */
        GridPosition *getGridPosition();

    private:
        //Variables
        /**
         * @brief Grid position of this label.
         */
        GridPosition *m_gridPosition;

        //Functions
        /**
         * @brief Initialize the variables of this class.
         *
         * This function will set the variable `m_gridPosition` with row given in `row` and column given in `column`.
         *
         * @param[in] row Row of the grid position.
         * @param[in] column Column of the grid position.
         */
        void init(const qint32 &row, const qint32 &column);
        /**
         * @brief This function is used when the click of the mouse is released on this label.
         * @param[in,out] ev Parameter that descrive the mouse event.
         */
        void mouseReleaseEvent(QMouseEvent *ev) override;

    signals:
        /**
         * @brief Signal that is emitted when this cell is clicked.
         */
        void clicked();

};

#endif // QGRIDLABEL_H
