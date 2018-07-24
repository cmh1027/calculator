#ifndef GENERAL_H
#define GENERAL_H
#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QRegExp>
#include <QString>
#include <QMap>
#include <utility>
#include "../content.h"
#include "../../../module/calculator/operator.h"
class GeneralCalculator : public Content{
    GeneralCalculator(QMainWindow* MainWindow);

}

#endif // GENERAL_H
