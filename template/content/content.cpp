#include "content.h"
#include <iostream>

Content::Content(QMainWindow *window, QWidget* widget):contentWidget(widget), mainWindow(window){}

Content::~Content(){
}
