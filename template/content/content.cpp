#include "content.h"
#include <iostream>
#include "../mainwindow.h"
Content::Content(MainWindow *window, QWidget* widget):contentWidget(widget), mainWindow(window){}

Content::~Content(){}
