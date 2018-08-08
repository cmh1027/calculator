#ifndef FUNCMENUITEM_H
#define FUNCMENUITEM_H
#include "../../../../menuitem.h"

namespace Template{
    class Calculator;
}

class FuncMenuItem : public MenuItem{
    Q_OBJECT

public:
    FuncMenuItem(Template::Calculator*, QWidget*, const QString&, const int&);
    virtual ~FuncMenuItem() = default;
};

#endif
