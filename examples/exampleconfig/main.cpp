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


#include "exampleconfig.h"

#include <QCoreApplication>
#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(coreMain, "core.main")

//! Example use of MConfig class
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("Example config app");
    a.setOrganizationName("Milo");

    ExampleConfig example;
    qCDebug(coreMain) << "Application name is:" << a.applicationName();
    qCDebug(coreMain) << "Example value is:" << example.exampleValue;
    qCDebug(coreMain) << "Example string is:" << example.exampleString;
    qCDebug(coreMain) << "Config file would be saved to:" << example.filePath();
    qCDebug(coreMain) << "Uncomment load and save in ExampleConfig class if you actually want to create and use config file. ";
    qCDebug(coreMain) << "If you want to encrypt your config add mcrypto to the project and enable build option: mconfig-crypto";

    return 0;
}
