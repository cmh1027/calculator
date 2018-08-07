#include <QWidget>
#include <QIntValidator>
#include "configcontent.h"
#include "ui_config_content.h"
#include "../content.h"
#include "../../../config/config.h"
#include "../../mainwindow.h"
extern Configuration* config;

namespace Template{
    Configuration::Configuration(MainWindow* window) : Content(window),
        contentUi(new Ui::Configuration), mainWindow(window), contentWidget(this)
    {
    }

    Configuration::~Configuration(){
        delete this->contentUi;
    }

    void Configuration::setup(){
        SETUP_UI(contentUi, contentWidget)
    }

    void Configuration::buttonConnect(){
        QCheckBox *defaultCheckBox = this->contentWidget->findChild<QCheckBox*>("decimalDefaultCheckBox");
        QLineEdit *decimalPoint = this->contentWidget->findChild<QLineEdit*>("decimalLineEdit");
        decimalPoint->setValidator(new QIntValidator(0, 99));
        connect(contentWidget->findChild<QRadioButton*>("degreeRadioButton"), &QRadioButton::clicked,
                this, [this]() mutable {config->setRadian(false); this->mainWindow->degreeUnitChanged();});
        connect(contentWidget->findChild<QRadioButton*>("radianRadioButton"), &QRadioButton::clicked,
                this, [this]() mutable {config->setRadian(true); this->mainWindow->degreeUnitChanged();});
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
                    this->mainWindow->precisionChanged();
                });
        connect(decimalPoint, &QLineEdit::textChanged, this,
                [this, decimalPoint]() mutable {
                    QString&& point = decimalPoint->text();
                    if(point.isEmpty())
                        config->setPrecision(-1);
                    else
                        config->setPrecision(point.toInt());
                    this->mainWindow->precisionChanged();
                });

    }
}
