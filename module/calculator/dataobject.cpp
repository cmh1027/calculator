#include <QString>
#include "dataobject.h"
DataObject::DataObject(const QString& des, const bool& flag) : description(des), tempFlag(!flag), defaultFlag(flag)
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

void DataObject::setTemp(const bool& flag){
    this->tempFlag = flag;
}

bool DataObject::isTemp() const{
    return this->tempFlag;
}
