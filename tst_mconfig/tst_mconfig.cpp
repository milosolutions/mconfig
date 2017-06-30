#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "mconfig.h"
#include "submiloconfig.h"

class TestMiloConfig : public QObject
{
    Q_OBJECT

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

#include "tst_miloconfig.moc"
