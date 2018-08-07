#ifndef MENUITEM_H
#define MENUITEM_H
#include <QPushButton>

class QString;
class QWidget;
class QFont;
class MenuItem : public QPushButton{
    Q_OBJECT

protected:
    void font(int, bool);

public:
    MenuItem(QWidget* parent, const QString &text);
    virtual ~MenuItem() = default;
};
#endif // MENUITEM_H
