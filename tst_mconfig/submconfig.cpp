#include "submiloconfig.h"

SubMiloConfig::SubMiloConfig(QByteArray groupName) : MConfig(groupName)
{
    CONFIG_VALUE(testBool, QMetaType::Bool);
    CONFIG_VALUE(testByteArray, QMetaType::QByteArray);
    CONFIG_VALUE(testDateTime, QMetaType::QDateTime);
    CONFIG_VALUE(testFloat, QMetaType::Float);
    CONFIG_VALUE(testInt, QMetaType::Int);
    CONFIG_VALUE(testPoint, QMetaType::QPoint);
    CONFIG_VALUE(testPointF, QMetaType::QPointF);
    CONFIG_VALUE(testRect, QMetaType::QRect);
    CONFIG_VALUE(testRectF, QMetaType::QRectF);
    CONFIG_VALUE(testString, QMetaType::QString);
}

SubMiloConfig::~SubMiloConfig()
{

}

void SubMiloConfig::zeroData()
{
    testBool = false;
    testByteArray = NULL;
    testDateTime = QDateTime();
    testFloat = 0.0f;
    testInt = 0;
    testPoint = QPoint();
    testPointF = QPointF();
    testRect = QRect();
    testRectF = QRectF();
    testString = "";
}
