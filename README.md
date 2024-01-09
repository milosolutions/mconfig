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

QObject-based version of config that can be easily used in QML code. This class is designed for automatic  generation of ui for editing values of config. 
For apps using qt widgets basic editors are provided under the name MMetaConfigEditor. 

Usage:
* cmake: set mconfig-editors option to ON
* qmake: `CONFIG += mconfig-editors` (before including mconfig.pri file)

### Encryption

It is possible to encrypt your config file using MCrypto library.

Usage:
1. add mcrypto
	* qmake `include(mcrypto.pri)` 
	* cmake `add_subdirectory(/your-path-to-mcdb/mcrypto mcrypto))`
1. enable build option called **mconfig-mcrypto**.

# License

This project is licensed under the MIT License - see the LICENSE-MiloCodeDB.txt file for details
