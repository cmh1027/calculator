#ifndef CALSTACK_H
#define CALSTACK_H
#include <QStack>
#include <QMap>
#include "exception.h"
template <typename T>
class CStack : public QStack<T>{
public:
    using QStack<T>::QStack;
    virtual ~CStack() = default;
    T pop();
    T& top();
    const T& top() const;

};

template <typename K, typename V>
class CMap : public QMap<K, V>{
public:
    using QMap<K, V>::QMap;
    virtual ~CMap() = default;
    const V value(const K &key) const;
    V& operator[](const K &key);
    const V operator[](const K &key) const;

};


template <typename T>
T CStack<T>::pop(){
    if(QStack<T>::empty()){
        throw std::InvalidExprException();
    }
    else{
        return QStack<T>::pop();
    }
}

template <typename T>
T& CStack<T>::top(){
    if(QStack<T>::empty()){
        throw std::InvalidExprException();
    }
    else{
        return QStack<T>::top();
    }
}

template <typename T>
const T& CStack<T>::top() const{
    if(QStack<T>::empty()){
        throw std::InvalidExprException();
    }
    else{
        return QStack<T>::top();
    }
}



template <typename K, typename V>
const V CMap<K, V>::value(const K &key) const{
    if(QMap<K, V>::contains(key))
        return QMap<K, V>::value(key);
    else
        throw std::InvalidExprException();
}

template <typename K, typename V>
V& CMap<K, V>::operator[](const K &key){
    return QMap<K, V>::operator[](key);
}

template <typename K, typename V>
const V CMap<K, V>::operator[](const K &key) const{
    if(QMap<K, V>::contains(key))
        return QMap<K, V>::value(key);
    else
        throw std::InvalidExprException();
}


#endif // CALSTACK_H
