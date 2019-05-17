MConfig
===

[Online documentation](https://docs.milosolutions.com/milo-code-db/mconfig)

[Source code](https://github.com/milosolutions/mconfig)

# Getting started

MConfig is the reference config class for Milo projects.

Main features:
1. Very simple to use
2. Can work without saving any config files, with no overhead.
3. On demand can save or load configuration to/from file.
4. Does not require any special magic to work.
5. Class can be inherited multiple times.
6. Just check out the code, it speaks for itself :-)

For example usage, see main.cpp file. This project is fully docummented - please
check doxygen docs or see the comments directly in the source file(s).

### MMetaConfig

This is flavor of config class that is designed for easy generation of ui for editing values of config.
Basic editor is provided under the name MMetaConfigEditor. To use it in project add `CONFIG += mconfig-editors`
before including mconfig.pri file.

# License

This project is licensed under the MIT License - see the LICENSE-MiloCodeDB.txt file for details
