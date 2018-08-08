#ifndef MATHMENU_H
#define MATHMENU_H
#include "../../menulayout.h"
class MainWindow;
class QString;
namespace Template{
    class MathContent;
}


class MathMenuLayout : public MenuLayout{
    Q_OBJECT


public:
    MathMenuLayout(MainWindow*, QScrollArea*, QWidget*);
    virtual ~MathMenuLayout() = default;
};

#endif // CONSTMENU_H
