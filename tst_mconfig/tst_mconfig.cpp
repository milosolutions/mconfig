/*******************************************************************************
Copyright (C) 2017 Milo Solutions
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
#include <QRandomGenerator>

// Template of simple MConfig of type T
template <typename T>
class SimpleConfig : public MConfig
{
public:
    T value;
    SimpleConfig()
        : MConfig(QByteArray(QMetaType(qMetaTypeId<T>()).name()) + "Config") {
        CONFIG_VALUE(value, qMetaTypeId<T>())
    }
  #ifdef ENCRYPTED_CONFIG
    SimpleConfig(const QByteArray& password)
        : MConfig(QByteArray(QMetaType(qMetaTypeId<T>()).name()) + "Config",
                  password) {
        CONFIG_VALUE(value, qMetaTypeId<T>())
    }
  #endif
};

class TestMConfig : public QObject
{
   Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testDefaultStorage();
    void testIniFileStorage();

#ifdef ENCRYPTED_CONFIG
    void testEncryptedStorage();
#endif

private:
    const QString m_IniPath = QStringLiteral("test_config_file.ini");
};

void TestMConfig::initTestCase()
{
    QCoreApplication::setApplicationName("MConfig Unit Test");
    QCoreApplication::setOrganizationName("Milo");
}

void TestMConfig::cleanupTestCase()
{
    // Clear generated files
    QFile::remove(m_IniPath);
    MConfig config("");
    QFile::remove(config.filePath());
}


template <typename T>
void test_save_and_load(T userValue)
{
    SimpleConfig<T> config1;
    config1.value = userValue;
    config1.save();
    SimpleConfig<T> config2;
    config2.load();
    QCOMPARE(config1.value, config2.value);
}
void TestMConfig::testDefaultStorage()
{
    int randomInt = static_cast<int>(QRandomGenerator::global()->generate());
    test_save_and_load(randomInt);
    test_save_and_load(QDateTime(QDate(2022, 5, 27), QTime(20, 2)));
    test_save_and_load(QUrl("https://milosolutions.com"));

    // TODO make similar calls for all supported data types
}

template <typename T>
void test_save_and_load_with_inifile(T userValue, const QString& filepath)
{
    SimpleConfig<T> config1;
    config1.value = userValue;
    config1.save(filepath);
    SimpleConfig<T> config2;
    config2.load(filepath);
    QCOMPARE(config1.value, config2.value);
}
void TestMConfig::testIniFileStorage()
{
    test_save_and_load_with_inifile(12, m_IniPath);
    test_save_and_load_with_inifile(QString("text to be remembered"), m_IniPath);

    // TODO make similar calls for all supported data types
}

#ifdef ENCRYPTED_CONFIG
template <typename T>
void test_save_and_load_encrypted(T userValue)
{
    QByteArray password = "Password must be known before config is created!"
    SimpleConfig<T> config1(password);
    config1.value = userValue;
    config1.save();
    SimpleConfig<T> config2(password);
    config2.load();
    QCOMPARE(config1.value, config2.value);
}
void TestMConfig::testEncryptedStorage()
{
    test_save_and_load_encrypted(int(300732));

    // TODO make similar calls for all supported data types
}
#endif

QTEST_MAIN(TestMConfig)

#include "tst_mconfig.moc"
