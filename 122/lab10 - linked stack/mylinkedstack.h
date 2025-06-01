//
//  mylinkedstack.h
//  lab10
//
//  Created by Ethan Kanyid on 4/15/24.
//

#ifndef mylinkedstack_h
#define mylinkedstack_h

#pragma once

#include <stdexcept>
#include "ADTStack.h"
#include "linkedlist.h"

using std::runtime_error;
using std::endl;

class StackEmptyException : public runtime_error
{
public:
    StackEmptyException() : runtime_error("Invalid Operation: Stack Empty!") { }

};


template <typename T>
class LinkedStack : public ADTStack<T>
{
    
private:
    LinkedList<T> data;
    
    
public:
    
    LinkedStack();
    ~LinkedStack();

    void push(T item);
    void pop();
    T peek();
    int size();
    void printStack(ostream& stream);

    
    
};

template <typename T>
LinkedStack<T>::LinkedStack()
{

}

template <typename T>
LinkedStack<T>::~LinkedStack()
{

}

template <typename T>
void LinkedStack<T>::push(T item)
{
    data.insert(item,-1);
}

template <typename T>
void LinkedStack<T>::pop()
{
    data.remove(-1);
}


template <typename T>
T LinkedStack<T>::peek()
{
    return data.at(-1);
}

template <typename T>
int LinkedStack<T>::size()
{
    return data.getSize();
}

template <typename T>
void LinkedStack<T>::printStack(ostream& stream)
{
    stream << "|";
    
    for(int i = 0; i < data.getSize(); i++)
    {
        stream << data.at(i) << " ";
    }
    stream << endl;
    
    return;
}



#endif /* mylinkedstack_h */
