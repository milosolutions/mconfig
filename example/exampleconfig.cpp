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

ExampleConfig::ExampleConfig() : MConfig("ExampleConfig")
{
    CONFIG_VALUE(exampleValue, QMetaType::Int);
    CONFIG_VALUE(exampleString, QMetaType::QByteArray);
    // load(); // uncomment if you want to load settings from file
}

ExampleConfig::~ExampleConfig()
{
    //save(); // uncomment if you want to save settings to file
}
