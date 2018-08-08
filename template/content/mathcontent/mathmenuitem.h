#ifndef MATHMENUITEM_H
#define MATHMENUITEM_H
#include "../../menuitem.h"

namespace Template{
    class Calculator;
}


class MathMenuItem : public MenuItem{
    Q_OBJECT

public:
    MathMenuItem(QWidget*, const QString&, QWidget*, const int&);
    virtual ~MathMenuItem() = default;
};

#endif // CONSTMENUITEM_H
