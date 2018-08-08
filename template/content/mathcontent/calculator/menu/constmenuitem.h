#ifndef CONSTMENUITEM_H
#define CONSTMENUITEM_H
#include "../../mathmenuitem.h"

namespace Template{
    class Calculator;
}


class ConstMenuItem : public MathMenuItem{
    Q_OBJECT

public:
    ConstMenuItem(Template::Calculator*, QWidget*, const QString&, const int&);
    virtual ~ConstMenuItem() = default;
};

#endif // CONSTMENUITEM_H
