#include <QtWidgets/QScrollArea>
#include "mathmenulayout.h"
#include "mathmenuitem.h"
#include "../../mainwindow.h"
MathMenuLayout::MathMenuLayout(MainWindow* window, QScrollArea *scrollArea, QWidget* standard) :
    MenuLayout(window, scrollArea, standard){
}
