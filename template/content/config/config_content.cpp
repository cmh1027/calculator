#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtGui/QIntValidator>
#include "config_content.h"
#include "ui_config_content.h"
#include "../content.h"
#include "../../../config/config.h"
#include "../../mainwindow.h"
#include "../../dialog/config/constant_dialog.h"
#include "../../dialog/config/function_dialog.h"
extern Configuration::Configuration* config;

namespace Template{
    Configuration::Configuration(MainWindow* window) : Content(window),
        contentUi(new Ui::Configuration), mainWindow(window), contentWidget(this)
    {
    }

    Configuration::~Configuration(){
        delete this->contentUi;
    }

    void Configuration::setup(){
        SETUP_UI(contentUi, contentWidget);
    }

    void Configuration::buttonConnect(){
        QCheckBox *defaultCheckBox = this->contentWidget->findChild<QCheckBox*>("decimalDefaultCheckBox");
        QLineEdit *decimalPoint = this->contentWidget->findChild<QLineEdit*>("decimalLineEdit");
        decimalPoint->setValidator(new QIntValidator(0, 99));
        connect(contentWidget->findChild<QRadioButton*>("degreeRadioButton"), &QRadioButton::clicked,
                this, [this]() mutable {config->setRadian(false);});
        connect(contentWidget->findChild<QRadioButton*>("radianRadioButton"), &QRadioButton::clicked,
                this, [this]() mutable {config->setRadian(true);});
        connect(defaultCheckBox, &QCheckBox::clicked, this,
                [this, defaultCheckBox, decimalPoint]() mutable {
                    if(defaultCheckBox->isChecked()){
                        decimalPoint->setEnabled(false);
                        config->setPrecision(-1);
                    }
                    else{
                        decimalPoint->setEnabled(true);
                        QString&& point = decimalPoint->text();
                        if(point.isEmpty())
                            config->setPrecision(-1);
                        else
                            config->setPrecision(point.toInt());
                    }
                });
        connect(decimalPoint, &QLineEdit::textChanged, this,
                [this, decimalPoint]() mutable {
                    QString&& point = decimalPoint->text();
                    if(point.isEmpty())
                        config->setPrecision(-1);
                    else
                        config->setPrecision(point.toInt());
                });
        connect(contentWidget->findChild<QPushButton*>("constButton"), &QPushButton::clicked, this, [](){
            Dialog::Constant* dialog = new Dialog::Constant();
            dialog->show();
        });
        connect(contentWidget->findChild<QPushButton*>("functionButton"), &QPushButton::clicked, this, [](){
            Dialog::Function* dialog = new Dialog::Function();
            dialog->show();
        });
    }
}
