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
    MenuLayout(MainWindow*, QScrollArea*, QWidget* standard = nullptr);
    virtual ~MenuLayout();
    void addItem(MenuItem*);
    QScrollArea* scrollArea;
    void show();
    void hide();

private:
    bool isOpen;

protected:
    MainWindow *mainWindow;
    QWidget* parent;
    QWidget* standard;
    QVector<MenuItem*> items;
    void setWidth(int width);
    void setHeight(int height);
    void moveToStandard();
    void resizeToStandard(int length);
    bool toggleOpen();

};
#endif // MENULAYOUT_H
