#ifndef TABLE_H
#define TABLE_H
#include <QVector>
#include <iostream>
template <typename T>
class Table{
public:
    Table() = default;
    Table(const int&);
    ~Table();
    int rowCount() const;
    int columnCount() const;
    T* at(int, int) const;
    void insert(const T, int, int);
    void eraseRow(int);
    void eraseColumn(int);
    void removeRow(int);
    void removeColumn(int);
    void rowClear();

private:
    QVector<QVector<T*>> data;
    int rowLength;
    int columnLength;
};

template <typename T>
Table<T>::Table(const int& column) : rowLength(0), columnLength(0){
    for(int i = 0; i < column; i++){
        this->data.push_back(QVector<T*>());
        this->columnLength += 1;
    }
}

template <typename T>
Table<T>::~Table(){
    for(auto it = this->data.begin(); it != this->data.end(); ++it){
        for(auto it2 = it->begin(); it2 != it->end(); ++it2){
            if((*it2) != nullptr)
                delete (*it2);
        }
    }
}

template <typename T>
Table<T>::rowCount() const{
    return this->rowLength;
}

template <typename T>
Table<T>::columnCount() const{
    return this->columnLength;
}

template <typename T>
T* Table<T>::at(int row, int column) const{
    if(column >= this->columnLength){
        Q_ASSERT(column >= this->columnLength);
        column = this->columnLength - 1;
    }
    if(row >= this->rowLength){
        Q_ASSERT(row >= this->rowLength);
        row = this->rowLength - 1;
    }
    return this->data.at(column).at(row);
}

template <typename T>
void Table<T>::insert(const T element, int row, int column){
    if(column >= this->columnLength){
        Q_ASSERT(column >= this->columnLength);
        column = this->columnLength - 1;
    }
    if(row >= this->rowLength + 1){
        Q_ASSERT(row >= this->rowLength + 1);
        row = this->rowLength;
    }
    if(row == this->rowLength){
        for(auto it = this->data.begin(); it != this->data.end(); ++it){
            it->push_back(nullptr);
        }
        this->rowLength += 1;
    }
    if(this->at(row, column) != nullptr)
        delete this->at(row, column);
    const_cast<QVector<T*>&>(this->data.at(column)).replace(row, new T(element));
}

template <typename T>
void Table<T>::eraseRow(int row){
    if(row >= this->rowLength){
        Q_ASSERT(row >= this->rowLength);
        row = this->rowLength - 1;
    }
    for(auto it = this->data.begin(); it != this->data.end(); ++it){
        delete it->at(row);
    }
}

template <typename T>
void Table<T>::eraseColumn(int column){
    if(column >= this->columnLength){
        Q_ASSERT(column >= this->columnLength);
        column = this->columnLength - 1;
    }
    for(auto it = this->data.at(column).begin(); it != this->data.at(column).end(); ++it){
        delete (*it);
    }
}

template <typename T>
void Table<T>::removeRow(int row){
    if(row >= this->rowLength){
        Q_ASSERT(row >= this->rowLength);
        row = this->rowLength - 1;
    }
    for(auto it = this->data.begin(); it != this->data.end(); ++it){
        delete it->at(row);
        it->remove(row);
    }
    this->rowLength -= 1;
}

template <typename T>
void Table<T>::removeColumn(int column){
    if(column >= this->columnLength){
        Q_ASSERT(column >= this->columnLength);
        column = this->columnLength - 1;
    }
    for(auto it = this->data.at(column).begin(); it != this->data.at(column).end(); ++it){
        delete (*it);
    }
    this->data.remove(column);
    this->columnLength -= 1;
}

template <typename T>
void Table<T>::rowClear(){
    for(auto it = this->data.begin(); it != this->data.end(); ++it){
        for(auto it2 = it->begin(); it2 != it->end(); ++it2){
            delete (*it2);
        }
        it->clear();
    }
    this->rowLength = 0;
}
#endif // TABLE_H
