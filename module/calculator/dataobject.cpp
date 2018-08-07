#include <QString>
#include "dataobject.h"
DataObject::DataObject(const QString& des, const bool& flag) : description(des), defaultFlag(flag)
{}

void DataObject::setDescription(const QString& str){
    this->description = std::move(str);
}

QString DataObject::getDescription() const{
    return this->description;
}

void DataObject::setDefault(const bool& flag){
    this->defaultFlag = flag;
}

bool DataObject::isDefault() const{
    return this->defaultFlag;
}
