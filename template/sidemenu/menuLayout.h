#ifndef MENULAYOUT_H
#define MENULAYOUT_H
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "menuitem.h"

class MenuLayout : public QVBoxLayout{
    Q_OBJECT
public:
    MenuLayout(QMainWindow*);
};
#endif // MENULAYOUT_H
