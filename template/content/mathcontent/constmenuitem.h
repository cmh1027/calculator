#ifndef CONSTMENUITEM_H
#define CONSTMENUITEM_H
#include "../../menuitem.h"

namespace Template{
    class Calculator;
}

class ConstMenuItem : public MenuItem{
    Q_OBJECT

public:
    ConstMenuItem(Template::Calculator*, QWidget*, const QString&, const int&);
    virtual ~ConstMenuItem() = default;
};

#endif // CONSTMENUITEM_H
