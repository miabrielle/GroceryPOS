#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T22:28:38
#
#-------------------------------------------------

QT       += core gui sql
CONFIG   += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BulkClub
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


SOURCES += \
        main.cpp \
        dbmanager.cpp \
    admincp.cpp \
    loginwindow.cpp \
    item.cpp \
    transaction.cpp \
    customer.cpp \
    edittransactiondialog.cpp \
    memberchangestatus.cpp \
    addcustomerdialog.cpp \
    addtransactiondialog.cpp

HEADERS += \
        dbmanager.h \
    admincp.h \
    loginwindow.h \
    item.h \
    transaction.h \
    edittransactiondialog.h \
    customer.h \
    memberchangestatus.h \
    addcustomerdialog.h \
    addtransactiondialog.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui \
    edittransactiondialog.ui \
    memberchangestatus.ui \
    addcustomerdialog.ui \
    addtransactiondialog.ui
