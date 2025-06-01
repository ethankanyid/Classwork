#pragma once

#include <stdexcept>
#include "ADTStack.h"

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
    class Node
    {
    public:
        Node() { next = nullptr; }
        T data;
        Node* next;
    };
    int count;
    Node* top;

    void printStack(Node* node, ostream& stream);

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
    count = 0;
    top = nullptr;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    while (top)
        pop();
}

template <typename T>
void LinkedStack<T>::push(T item)
{
    Node* temp = new Node();
    temp->data = item;

    temp->next = top;
    top = temp;
    count++;
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (!top)
    {
        throw StackEmptyException();
    }
    Node* temp = top;
    top = temp->next;
    delete temp;
    count--;
}


template <typename T>
T LinkedStack<T>::peek()
{
    if (!top)
    {
        throw StackEmptyException();
    }
    return top->data;
}

template <typename T>
int LinkedStack<T>::size()
{
    return count;
}

template <typename T>
void LinkedStack<T>::printStack(ostream& stream)
{
    stream << "|";
    printStack(top, stream);
    stream << endl;
}

template <typename T>
void LinkedStack<T>::printStack(Node* node, ostream& stream)
{
    if (!node)
        return;

    printStack(node->next, stream);

    stream << node->data << " ";
}
