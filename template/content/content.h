#ifndef CONTENT_H
#define CONTENT_H
#include <QWidget>

class MainWindow;

namespace Template{
    class Content : public QWidget{
        Q_OBJECT

    public:
        Content(MainWindow*);
        virtual ~Content() = default;
        virtual void setup() = 0;

    protected:
        virtual void buttonConnect() = 0; // must be in setup() function
        MainWindow* mainWindow;
        template <typename Ui, typename Widget>
        void setupUi(Content* ptr, Ui ui, Widget widget){
            ui->setupUi(widget);
            ptr->buttonConnect();
        }

    private:
        QWidget* contentWidget;

    };
}

#endif // CONTENT_H
