#-------------------------------------------------
#
# Project created by QtCreator 2011-12-04T22:40:37
# Author: Onzalo
# https://github.com/onzalo
#
#-------------------------------------------------

QT       += core gui

TARGET = DeterministicTuringMachine
TEMPLATE = app

OTHER_FILES += \
    README.md \
    LICENSE

HEADERS += \
    turingmachine.h \
    state.h \
    mainwindow.h \
    dialogtransition.h \
    dialogstate.h \
    dialogsimulator.h \
    dialoginitialstate.h \
    dialogblank.h \
    dialogalphabet.h \
    dialogabout.h \
    alphabet.h

SOURCES += \
    turingmachine.cpp \
    state.cpp \
    mainwindow.cpp \
    main.cpp \
    dialogtransition.cpp \
    dialogstate.cpp \
    dialogsimulator.cpp \
    dialoginitialstate.cpp \
    dialogblank.cpp \
    dialogalphabet.cpp \
    dialogabout.cpp \
    alphabet.cpp

FORMS += \
    mainwindow.ui \
    dialogtransition.ui \
    dialogstate.ui \
    dialogsimulator.ui \
    dialoginitialstate.ui \
    dialogblank.ui \
    dialogalphabet.ui \
    dialogabout.ui

RESOURCES += \
    Resource.qrc
