/*******************************************************************************
Copyright (C) 2016 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "mconfig.h"
#include "submconfig.h"

class TestMiloConfig : public QObject
{
   // Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testLoad1_data();
    void testLoad1();
    void testSave1_data();
    void testSave1();

    void testLoad2_data();
    void testLoad2();
    void testSave2_data();
    void testSave2();
private:
    QString m_testConfigPath = QCoreApplication::applicationDirPath() + "/miloConfTest.ini";
};

void TestMiloConfig::initTestCase()
{
    QCoreApplication::setApplicationName("MiloConfig Test");
    QCoreApplication::setOrganizationName("Milo");
}

void TestMiloConfig::cleanupTestCase()
{
    MiloConfig config("Test");
    QFile::remove(config.filePath());
    QFile::remove(m_testConfigPath);
}

void TestMiloConfig::testLoad1_data()
{
    QTest::addColumn<QByteArray>("groupName");
    QTest::newRow("SimpleGroupName") << QByteArray("TestGroup");
    QTest::newRow("NumberGroupName") << QByteArray("123");
    QTest::newRow("Spaced GroupName") << QByteArray("Test Group");
}

void TestMiloConfig::testLoad1()
{
    QFETCH(QByteArray, groupName);
    SubMiloConfig config1(groupName);
    config1.zeroData();
    config1.load(":/data/miloConfTest.ini");
    SubMiloConfig config2(groupName);

    QCOMPARE(config1, config2);
}

void TestMiloConfig::testSave1_data()
{
    QTest::addColumn<QByteArray>("groupName");
    QTest::newRow("SimpleGroupName") << QByteArray("TestGroup");
    QTest::newRow("NumberGroupName") << QByteArray("123");
    QTest::newRow("Spaced GroupName") << QByteArray("Test Group");
}

void TestMiloConfig::testSave1()
{
    QFETCH(QByteArray, groupName);
    SubMiloConfig config(groupName);
    config.save();
    QVERIFY(QFile::exists(config.filePath()));
}

void TestMiloConfig::testLoad2_data()
{
    QTest::addColumn<QByteArray>("groupName");
    QTest::newRow("SimpleGroupName") << QByteArray("TestGroup");
    QTest::newRow("NumberGroupName") << QByteArray("123");
    QTest::newRow("Spaced GroupName") << QByteArray("Test Group");
}

void TestMiloConfig::testLoad2()
{
    QFETCH(QByteArray, groupName);
    SubMiloConfig config1(groupName);
    SubMiloConfig config2(groupName);

    config1.zeroData();
    QVERIFY(!(config1 == config2));
    config1.load();
    QCOMPARE(config1, config2);
}

void TestMiloConfig::testSave2_data()
{
    QTest::addColumn<QByteArray>("groupName");
    QTest::newRow("SimpleGroupName") << QByteArray("TestGroup");
    QTest::newRow("NumberGroupName") << QByteArray("123");
    QTest::newRow("Spaced GroupName") << QByteArray("Test Group");
}

void TestMiloConfig::testSave2()
{
    QFETCH(QByteArray, groupName);
    SubMiloConfig config(groupName);
    config.save(m_testConfigPath);
    QVERIFY(QFile::exists(m_testConfigPath));
}

QTEST_MAIN(TestMiloConfig)

//#include "tst_miloconfig.moc"
