#-------------------------------------------------
#
# Project created by QtCreator 2019-04-13T18:42:45
#
#-------------------------------------------------

QT       += core gui
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessQtGUI
TEMPLATE = app

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
    main.cpp \
    mainwindow.cpp \
    accountmanagement.cpp \
    logindialog.cpp \
    registrationdialog.cpp \
    player.cpp \
    bishop.cpp \
    handler.cpp \
    knight.cpp \
    move.cpp \
    pawn.cpp \
    piece.cpp \
    queen.cpp \
    rook.cpp \
    take.cpp

HEADERS += \
    mainwindow.h \
    accountmanagement.h \
    logindialog.h \
    registrationdialog.h \
    player.h \
    bishop.h \
    handler.h \
    knight.h \
    move.h \
    pawn.h \
    piece.h \
    queen.h \
    rook.h \
    take.h

FORMS += \
    mainwindow.ui \
    registrationdialog.ui \
    logindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
