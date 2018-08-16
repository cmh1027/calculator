#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T13:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app
RESOURCES += qrc/resources.qrc \
    qrc/resources.qrc
CONFIG += C++14
CONFIG += object_parallel_to_source
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
    module/ctl.h \
    module/exception.h \
    module/table.h \
    module/utility.h \
    module/mathcontent/calculation.h \
    module/mathcontent/constant.h \
    module/mathcontent/dataobject.h \
    module/mathcontent/operation.h \
    module/mathcontent/operator.h \
    template/mainwindow.h \
    template/menuItem.h \
    template/menuLayout.h \
    template/templates.h \
    template/sidemenu/sidemenuitem.h \
    template/sidemenu/sidemenulayout.h \
    template/dialog/config/constant.h \
    template/dialog/mathcontent/advanced.h \
    template/content/content.h \
    template/content/mathcontent/mathcontent.h \
    template/content/mathcontent/mathmenuitem.h \
    template/content/mathcontent/mathmenulayout.h \
    template/content/mathcontent/calculator/calculator.h \
    template/content/mathcontent/calculator/general/general.h \
    template/content/mathcontent/calculator/menu/constmenuitem.h \
    template/content/mathcontent/calculator/menu/constmenulayout.h \
    template/content/mathcontent/calculator/menu/funcmenuitem.h \
    template/content/mathcontent/calculator/menu/funcmenulayout.h \
    template/content/mathcontent/calculator/scientific/scientific.h \
    template/content/mathcontent/graph/graph.h \
    template/content/mathcontent/matrix/matrix.h \
    template/content/mathcontent/table/table.h \
    template/content/config/config.h

SOURCES += \
    config/config.cpp \
    module/exception.cpp \
    module/utility.cpp \
    module/mathcontent/calculation.cpp \
    module/mathcontent/constant.cpp \
    module/mathcontent/dataobject.cpp \
    module/mathcontent/operation.cpp \
    module/mathcontent/operator.cpp \
    template/mainwindow.cpp \
    template/menuItem.cpp \
    template/menuLayout.cpp \
    template/sidemenu/sidemenuitem.cpp \
    template/sidemenu/sidemenulayout.cpp \
    template/dialog/config/constant.cpp \
    template/dialog/mathcontent/advanced.cpp \
    template/content/content.cpp \
    template/content/mathcontent/mathcontent.cpp \
    template/content/mathcontent/mathmenuitem.cpp \
    template/content/mathcontent/mathmenulayout.cpp \
    template/content/mathcontent/calculator/calculator.cpp \
    template/content/mathcontent/calculator/general/general.cpp \
    template/content/mathcontent/calculator/menu/constmenuitem.cpp \
    template/content/mathcontent/calculator/menu/constmenulayout.cpp \
    template/content/mathcontent/calculator/menu/funcmenuitem.cpp \
    template/content/mathcontent/calculator/menu/funcmenulayout.cpp \
    template/content/mathcontent/calculator/scientific/scientific.cpp \
    template/content/mathcontent/graph/graph.cpp \
    template/content/mathcontent/matrix/matrix.cpp \
    template/content/mathcontent/table/table.cpp \
    main.cpp \
    template/content/config/config.cpp

DISTFILES += \
    resource/icon.ico

FORMS += \
    template/mainwindow.ui \
    template/dialog/config/constant.ui \
    template/dialog/mathcontent/advanced.ui \
    template/content/mathcontent/calculator/calculator.ui \
    template/content/mathcontent/calculator/general/general.ui \
    template/content/mathcontent/calculator/scientific/scientific.ui \
    template/content/mathcontent/graph/graph.ui \
    template/content/mathcontent/matrix/matrix.ui \
    template/content/mathcontent/table/table.ui \
    template/content/config/config.ui
