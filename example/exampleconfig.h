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

#ifndef EXAMPLECONFIG_H
#define EXAMPLECONFIG_H

#include "../mconfig.h"

#include <QByteArray>

class ExampleConfig : public MConfig
{
public:
    ExampleConfig();
    ~ExampleConfig();

    int exampleValue = 42;
    QByteArray exampleString = "Milo";
};

#endif // EXAMPLECONFIG_H
