#ifndef DATAOBJECT_H
#define DATAOBJECT_H
#include <QString>
class DataObject{
public:
    DataObject() = default;
    DataObject(const QString&, const bool& = true);
    void setDescription(const QString&);
    QString getDescription() const;
    void setDefault(const bool&);
    bool isDefault() const;

private:
    QString description;
    bool defaultFlag;
};
#endif // DATAOBJECT_H
