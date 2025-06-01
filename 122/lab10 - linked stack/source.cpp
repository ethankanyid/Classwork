#include <iostream>
#include <stdexcept>
//#include "LinkedStack.h"
#include "mylinkedstack.h"

using std::cout;
using std::endl;
using std::cin;

void SetDiskCount(LinkedStack<int>* stackA);
void MakeLegalMove(LinkedStack<int>* stackA, LinkedStack<int>* stackB);
void PrintStacks(LinkedStack<int>* stackA, LinkedStack<int>* stackB, LinkedStack<int>* stackC);

int main(int argc, char const *argv[])
{
    
try
{
    LinkedStack<int> stackA;
    LinkedStack<int> stackB;
    LinkedStack<int> stackC;
    
    SetDiskCount(&stackA);
    PrintStacks(&stackA, &stackB, &stackC);
    
    
    //Move one disk from peg A to peg B or vice versa, whichever move is legal.
    //Move one disk from peg A to peg C or vice versa, whichever move is legal.
    //Move one disk from peg B to peg C or vice versa, whichever move is legal.
    
    while(stackA.size() != 0 || stackB.size() != 0)
    {
        MakeLegalMove(&stackA, &stackB);
        PrintStacks(&stackA, &stackB, &stackC);
        
        MakeLegalMove(&stackA, &stackC);
        PrintStacks(&stackA, &stackB, &stackC);
        
        MakeLegalMove(&stackB, &stackC);
        PrintStacks(&stackA, &stackB, &stackC);
    }
}
catch(IndexOutOfBounds msg)
{
    cout << msg.getMessage() << endl;
}
    
    return 0;
}


void SetDiskCount(LinkedStack<int>* stackA)
{
    int count;
    
    cout << "How many disks would you like for the Towers of Hanoi? ";
    
    cin >> count;
    
    for(; count > 0; count --)
    {
        stackA->push(count);
    }
    return;
}

void MakeLegalMove(LinkedStack<int>* stackA, LinkedStack<int>* stackB)
{
    if(stackA->size() == 0 && stackB->size() == 0)
    {
        return;
    }
    else if(stackA->size() == 0)
    {
        stackA->push(stackB->peek());
        stackB->pop();
    }
    else if(stackB->size() == 0)
    {
        stackB->push(stackA->peek());
        stackA->pop();
    }
    else if(stackA->peek() < stackB->peek())
    {
        stackB->push(stackA->peek());
        stackA->pop();
    }
    else if(stackB->peek() < stackA->peek())
    {
        stackA->push(stackB->peek());
        stackB->pop();
    }
    return;
}

void PrintStacks(LinkedStack<int>* stackA, LinkedStack<int>* stackB, LinkedStack<int>* stackC)
{
    cout << "stack a: ";
    stackA->printStack(cout);
    cout << "stack b: ";
    stackB->printStack(cout);
    cout << "stack c: ";
    stackC->printStack(cout);
    cout << endl;
    return;
}
