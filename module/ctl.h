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
class CMap : public QMap<K, V>{
public:
    using QMap<K, V>::QMap;
    virtual ~CMap() = default;
    const V value(const K &key) const;
    template <typename VV = V>
    const V clone(const K &key, typename std::enable_if<!std::is_pointer<VV>::value>::type* = nullptr) const;
    template <typename VV = V>
    const V clone(const K &key, typename std::enable_if<std::is_pointer<VV>::value>::type* = nullptr) const;
    template <typename VV = V>
    int remove(const K &key, typename std::enable_if<!std::is_pointer<VV>::value>::type* = nullptr);
    template <typename VV = V>
    int remove(const K &key, typename std::enable_if<std::is_pointer<VV>::value>::type* = nullptr);
    int simpleRemove(const K &key);
    V& operator[](const K &key);
    const V operator[](const K &key) const;
};

template <typename K, typename V>
const V CMap<K, V>::value(const K &key) const{
    if(QMap<K, V>::contains(key))
        return QMap<K, V>::value(key);
    else
        throw std::InvalidExprException();
}

template <typename K, typename V>
template <typename VV>
const V CMap<K, V>::clone(const K &key, typename std::enable_if<!std::is_pointer<VV>::value>::type*) const{
    if(QMap<K, V>::contains(key)){
        return V(QMap<K, V>::value(key));
    }
    else
        throw std::InvalidExprException();
}

template <typename K, typename V>
template <typename VV>
const V CMap<K, V>::clone(const K &key, typename std::enable_if<std::is_pointer<VV>::value>::type*) const{
    if(QMap<K, V>::contains(key)){
        using Type = typename std::remove_pointer<V>::type;
        Type* copied = new Type(*QMap<K, V>::value(key));
        return copied;
    }
    else
        throw std::InvalidExprException();
}

template <typename K, typename V>
template <typename VV>
int CMap<K, V>::remove(const K &key, typename std::enable_if<!std::is_pointer<VV>::value>::type*){
    return QMap<K, V>::remove(key);
}

template <typename K, typename V>
template <typename VV>
int CMap<K, V>::remove(const K &key, typename std::enable_if<std::is_pointer<VV>::value>::type*){
    delete QMap<K, V>::value(key);
    return QMap<K, V>::remove(key);
}

template <typename K, typename V>
int CMap<K, V>::simpleRemove(const K &key){
    return QMap<K, V>::remove(key);
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
