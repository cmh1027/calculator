#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T13:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app
RESOURCES += qrc/resources.qrc
CONFIG += C++14
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    config/config.h \
    module/utility.h \
    module/calculator/calculation.h \
    module/calculator/constant.h \
    module/calculator/operation.h \
    module/calculator/operator.h \
    template/mainwindow.h \
    template/templates.h \
    template/content/content.h \
    template/content/mathcontent/calculator/calculator.h \
    template/content/mathcontent/calculator/general/general.h \
    template/content/mathcontent/calculator/scientific/scientific.h \
    template/content/mathcontent/mathcontent.h \
    template/content/config/configcontent.h \
    module/exception.h \
    module/ctl.h \
    module/calculator/dataobject.h \
    template/content/mathcontent/graph/graph.h \
    template/content/mathcontent/matrix/matrix.h \
    template/content/mathcontent/table/table.h \
    template/sidemenu/sidemenuitem.h \
    template/sidemenu/sidemenulayout.h \
    template/menuitem.h \
    template/menulayout.h \
    template/content/mathcontent/calculator/menu/constmenuitem.h \
    template/content/mathcontent/calculator/menu/constmenulayout.h \
    template/content/mathcontent/calculator/menu/funcmenuitem.h \
    template/content/mathcontent/calculator/menu/funcmenulayout.h \
    template/content/mathcontent/mathmenuitem.h \
    template/content/mathcontent/mathmenulayout.h

SOURCES += \
    config/config.cpp \
    module/utility.cpp \
    module/calculator/calculation.cpp \
    module/calculator/constant.cpp \
    module/calculator/operation.cpp \
    module/calculator/operator.cpp \
    template/mainwindow.cpp \
    template/content/content.cpp \
    template/content/mathcontent/calculator/calculator.cpp \
    template/content/mathcontent/calculator/general/general.cpp \
    template/content/mathcontent/calculator/scientific/scientific.cpp \
    template/content/mathcontent/mathcontent.cpp \
    template/content/config/configcontent.cpp \
    main.cpp \
    module/exception.cpp \
    module/calculator/dataobject.cpp \
    template/content/mathcontent/graph/graph.cpp \
    template/content/mathcontent/matrix/matrix.cpp \
    template/content/mathcontent/table/table.cpp \
    template/sidemenu/sidemenuitem.cpp \
    template/sidemenu/sidemenulayout.cpp \
    template/menuitem.cpp \
    template/menulayout.cpp \
    template/content/mathcontent/calculator/menu/constmenuitem.cpp \
    template/content/mathcontent/calculator/menu/constmenulayout.cpp \
    template/content/mathcontent/calculator/menu/funcmenuitem.cpp \
    template/content/mathcontent/calculator/menu/funcmenulayout.cpp \
    template/content/mathcontent/mathmenuitem.cpp \
    template/content/mathcontent/mathmenulayout.cpp

FORMS += \
    template/mainwindow.ui \
    template/content/mathcontent/calculator/calculator.ui \
    template/content/mathcontent/calculator/general/general.ui \
    template/content/mathcontent/calculator/scientific/scientific.ui \
    template/content/config/configcontent.ui \
    template/content/mathcontent/graph/graph.ui \
    template/content/mathcontent/table/table.ui \
    template/content/mathcontent/matrix/matrix.ui
