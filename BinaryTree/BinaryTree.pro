#-------------------------------------------------
#
# Project created by QtCreator 2022-02-10T21:08:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryTree
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainscene.cpp \
    mypushbutton.cpp \
    ergodicsequenceinput.cpp \
    usualpushbutton.cpp \
    showscene.cpp \
    traversescene.cpp \
    signalamplifier.cpp \
    BTtree.cpp \
    amplifiers.cpp \
    BSTnode.cpp \
    BSTsence.cpp

HEADERS += \
        mainscene.h \
    mypushbutton.h \
    ergodicsequenceinput.h \
    usualpushbutton.h \
    showscene.h \
    arrayqueue.h \
    arraystack.h \
    binarytreenode.h \
    errorinfo.h \
    linkedbinarytree.h \
    traversescene.h \
    signalamplifier.h \
    BTtree.h \
    amplifiers.h \
    BSTnode.h \
    BSTsence.h

FORMS += \
        mainscene.ui \
    ergodicsequenceinput.ui \
    amplifiers.ui \
    signalamplifier.ui \
    BSTsence.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    res/input.jpg \
    res/input.jpg
