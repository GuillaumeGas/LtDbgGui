#-------------------------------------------------
#
# Project created by QtCreator 2019-11-01T12:02:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LtDbgGui
TEMPLATE = app
# LIBS += "C:\Users\Guillaume\Documents\Visual Studio 2017\Projects\LtDbg\udis\BuildVS2010\Build\Bin\x64\libudis86.lib"
INCLUDEPATH += $$PWD\LtDbg\LtDbg
INCLUDEPATH += $$PWD\LtDbg\elfio

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    LtDbg/LtDbg/Utils/Disassembler.cpp \
    LtDbg/LtDbg/Utils/Registers.cpp \
    LtDbg/LtDbg/Utils/StringUtils.cpp \
    LtDbg/LtDbg/Utils/SymbolsHelper.cpp \
    LtDbg/LtDbg/CmdManager.cpp \
    LtDbg/LtDbg/Com.cpp \
    LtDbg/LtDbg/Commands.cpp \
    LtDbg/LtDbg/Dbg.cpp \
    asmwidget.cpp \
    cmdwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp \
    stacktracewidget.cpp \
    debuggerstate.cpp

HEADERS += \
        mainwindow.h \
    asmwidget.h \
    cmdwidget.hpp \
    parameters.h \
    stacktracewidget.h \
    LtDbg/elfio/elfio/elf_types.hpp \
    LtDbg/elfio/elfio/elfio.hpp \
    LtDbg/elfio/elfio/elfio_dump.hpp \
    LtDbg/elfio/elfio/elfio_dynamic.hpp \
    LtDbg/elfio/elfio/elfio_header.hpp \
    LtDbg/elfio/elfio/elfio_note.hpp \
    LtDbg/elfio/elfio/elfio_relocation.hpp \
    LtDbg/elfio/elfio/elfio_section.hpp \
    LtDbg/elfio/elfio/elfio_segment.hpp \
    LtDbg/elfio/elfio/elfio_strings.hpp \
    LtDbg/elfio/elfio/elfio_symbols.hpp \
    LtDbg/elfio/elfio/elfio_utils.hpp \
    LtDbg/LtDbg/LtKinc/ltkinc.h \
    LtDbg/LtDbg/Utils/Disassembler.hpp \
    LtDbg/LtDbg/Utils/Registers.hpp \
    LtDbg/LtDbg/Utils/StringUtils.hpp \
    LtDbg/LtDbg/Utils/SymbolsHelper.hpp \
    LtDbg/LtDbg/CmdManager.hpp \
    LtDbg/LtDbg/Com.hpp \
    LtDbg/LtDbg/Commands.hpp \
    LtDbg/LtDbg/Dbg.hpp \
    LtDbg/LtDbg/Exceptions.hpp \
    LtDbg/LtDbg/Response.hpp \
    LtDbg/udis/libudis86/extern.h \
    LtDbg/udis/libudis86/itab.h \
    LtDbg/udis/libudis86/syn.h \
    LtDbg/udis/libudis86/types.h \
    LtDbg/udis/libudis86/udint.h \
    LtDbg/udis/udis86.h \
    asmwidget.h \
    cmdwidget.hpp \
    mainwindow.h \
    parameters.h \
    stacktracewidget.h \
    debuggerstate.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx|win32: LIBS += -L$$PWD/'../../../Visual Studio 2017/Projects/LtDbg/udis/BuildVS2010/Build/Bin/x86/' -llibudis86

INCLUDEPATH += $$PWD/'../../../Visual Studio 2017/Projects/LtDbg/udis/BuildVS2010/Build/Bin/x86'
DEPENDPATH += $$PWD/'../../../Visual Studio 2017/Projects/LtDbg/udis/BuildVS2010/Build/Bin/x86'

win32-g++: PRE_TARGETDEPS += $$PWD/'../../../Visual Studio 2017/Projects/LtDbg/udis/BuildVS2010/Build/Bin/x86/libudis86.lib'
#else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/'../../../Visual Studio 2017/Projects/LtDbg/udis/BuildVS2010/Build/Bin/x64/liblibudis86.a'
