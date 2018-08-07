#ifndef MENULAYOUT_H
#define MENULAYOUT_H
#include <QObject>
#include <QVector>

class MainWindow;
class MenuItem;
class QWidget;
class QString;
class QScrollArea;

class MenuLayout : public QObject{
    Q_OBJECT

public:
    MenuLayout(MainWindow*, QScrollArea*);
    virtual ~MenuLayout() = default;
    virtual void applyLayout() = 0;
    void addItem(MenuItem*);
    QScrollArea* scrollArea;
    void show();
    void hide();


protected:
    MainWindow *mainWindow;
    QWidget *parent;
    QVector<MenuItem*> items;
    void setWidth(int width);
    void setHeight(int height);
    void moveTo(QWidget*);

};
#endif // MENULAYOUT_H
