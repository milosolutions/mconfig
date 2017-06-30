#ifndef SUBMILOCONFIG_H
#define SUBMILOCONFIG_H

#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QString>
#include <QDateTime>

#include "mconfig.h"

class SubMiloConfig : public MConfig
{
public:
    SubMiloConfig(QByteArray groupName);
    ~SubMiloConfig();
    void zeroData();

    bool testBool = true;
    int testInt = 1;
    float testFloat = 1.0f;
    QByteArray testByteArray = "Test ByteArray";
    QString testString = "Test String";
    QPoint testPoint = QPoint(1, 1);
    QPointF testPointF = QPointF(1.0f, 1.0f);
    QRect testRect = QRect(4, 1, 2, 3);
    QRectF testRectF = QRectF(4.0f, 1.0f, 2.0f, 3.0f);
    QDateTime testDateTime = QDateTime::fromMSecsSinceEpoch(666);

    bool operator==(const SubMiloConfig &rhs) const {
        return (this->testBool == rhs.testBool &&
                this->testInt == rhs.testInt &&
                this->testString == rhs.testString &&
                this->testByteArray == rhs.testByteArray &&
                this->testPoint == rhs.testPoint &&
                this->testPointF == rhs.testPointF &&
                this->testRect == rhs.testRect &&
                this->testRectF == rhs.testRectF &&
                this->testDateTime.toString() == rhs.testDateTime.toString() &&
                this->testFloat - rhs.testFloat == 0);
    }

};

#endif // SUBMILOCONFIG_H
