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
    QWidget* standard;

public:
    MenuItem(QWidget* parent, const QString &text, QWidget* standard = nullptr, const int &num = -1);
    virtual ~MenuItem() = default;
};
#endif // MENUITEM_H
