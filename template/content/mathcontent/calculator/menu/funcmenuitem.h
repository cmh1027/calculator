#ifndef FUNCMENUITEM_H
#define FUNCMENUITEM_H
#include "../../mathmenuitem.h"

namespace Template{
    class Calculator;
}

class FuncMenuItem : public MathMenuItem{
    Q_OBJECT

public:
    FuncMenuItem(Template::Calculator*, QWidget*, const QString&, const int&);
    virtual ~FuncMenuItem() = default;
};

#endif
