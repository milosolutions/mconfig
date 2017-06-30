/*******************************************************************************
  Copyright (C) 2016 Milo Solutions
  Contact: https://www.milosolutions.com

  This file is part of Milo Code Database, which is a collection of useful code
  snippets often reused within Milo Solutions. As such, this code is present in
  many projects done by Milo Solutions and does not constitute a copyright
  infridgement.

  You are entitled to do anything you please with this code, just as with the
  rest of code you bought. Files not containing this notice were written
  specifically for this project and have not been shared with any other party
  within or without Milo.
*******************************************************************************/

#include "exampleconfig.h"

#include <QCoreApplication>
#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(coreMain, "core.main")

//! Example use of MiloConfig class
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("Example config app");
    a.setOrganizationName("Milo");

    ExampleConfig example;
    qCDebug(coreMain) << "Application name is:" << a.applicationName();
    qCDebug(coreMain) << "Example value is:" << example.exampleValue;
    qCDebug(coreMain) << "Example string is:" << example.exampleString;
    qCDebug(coreMain) << "Config file will be saved to:" << example.filePath();

    return a.exec();
}
