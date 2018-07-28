#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T13:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
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
        template/mainwindow.cpp \
    module/calculator/operation.cpp \
    module/calculator/operator.cpp \
    template/content/calculator/scientific/scientific.cpp \
    template/content/content.cpp \
    template/content/calculator/general/general.cpp \
    template/content/calculator/calculator.cpp \
    module/calculator/calculation.cpp \
    module/calculator/constant.cpp \
    module/utility.cpp \
    template/sidemenu/menuLayout.cpp \
    template/sidemenu/menuItem.cpp \
    template/configuration.cpp

HEADERS += \
        template/mainwindow.h \
    module/calculator/operation.h \
    module/calculator/operator.h \
    template/content/content.h \
    template/content/calculator/scientific/scientific.h \
    template/content/calculator/general/general.h \
    template/content/calculator/calculator.h \
    module/calculator/calculation.h \
    template/templates.h \
    module/calculator/constant.h \
    module/utility.h \
    template/sidemenu/menuItem.h \
    template/sidemenu/menulayout.h \
    template/configuration.h

FORMS += \
        template/mainwindow.ui \
    template/content/calculator/scientific/scientific.ui \
    template/content/calculator/general/general.ui \
    template/content/calculator/calculator.ui
