#pragma once
#include "Nodo.h"

template<class T>
class Pila
{
public:
    Pila();
    ~Pila();
    void Push(T);
    T Pop();
    T Peek();
    bool isEmpty();
    int size();

private:
    Nodo<T>* ultimo;
};
