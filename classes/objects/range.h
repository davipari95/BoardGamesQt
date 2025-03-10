#ifndef RANGE_H
#define RANGE_H

#include <QObject>

class Range : public QObject
{
        Q_OBJECT

    public:
        //Constructor
        explicit Range(const qint32 &min, const qint32 &max, QObject *parent = nullptr);

        //Functions
        qint32 getMin() const;
        qint32 getMax() const;
        bool isInRange(const qint32 &value) const;
        qint32 getGap() const;

        //Static functions
        static bool isInRange(const qint32 &min, const qint32 &max, const qint32 &value);

    private:
        //Variables
        qint32 m_min;
        qint32 m_max;

        //Functions
        void initialize(const qint32 &min, const qint32 &max);

    signals:
};

#endif // RANGE_H
