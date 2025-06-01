#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "linkedlist.h"
#include "task.h"

using namespace std;


/* two print functions: one for main, and one for functions. i couldnt figure out why one would work in main but not in function and vice versa.*/
void printListfunction(LinkedList<Task*>* list);
template <typename TYPE>
void printList(List<TYPE> &list);

/*compare function. mildly overwritten to compare task classes instead of ints.*/
int compare(const Task& item1,const Task& item2);

/*createtask function is used to create a list from input or a file*/
void CreateTask(LinkedList<Task>* todolist, int priority = 0, string task = "");

/*removetask function removes a task at an index*/
void RemoveTask(LinkedList<Task>* todolist, int index = 0);

/*edittasklist is called to create a list, remove from the list, and save the list to a file*/
void EditTaskList(LinkedList<Task>* todolist, string filename = "");

int main(int argc, const char * argv[])
{
    LinkedList<Task> todolist;
    
    try
    {
        bool readFromFile = false;
        
        cout << "Would you like to read from a file? (0 = false; 1 = true): ";
        cin >> readFromFile;
        
        if(!readFromFile)// reads from input
        {
            EditTaskList(&todolist);
        }
        else if(readFromFile)//reads from file
        {
            ifstream file;
            string filename;
            string task = "", trash;
            int priority = 0;
            
            cout << "Enter a file name to read and write from (.txt): ";
            cin.ignore();
            getline(cin, filename);
            file.open (filename);
            if(file.is_open())
            {
                getline(file,trash); // clears header
                while(getline(file,task))
                {
                    stringstream ss(task);
                    ss >> priority;
                    getline(ss,task);
                    CreateTask(&todolist,priority,task);
                }
                printList(todolist);
            }
            else
            {
                cout << "Could not open file.";
            }
            file.close();
            
            bool editList = false;
            cout << "Would you like to edit this list? (0 = false; 1 = true): ";
            cin >> editList;
            
            if(editList)// allows the user to edit the list read from file
            {
                EditTaskList(&todolist,filename);
            }
        }
    }
    catch(IndexOutOfBounds msg)
    {
        cout << msg.getMessage() << endl;
    }
    
    return 0;
}


void printListfunction(LinkedList<Task>* list)
{
    cout << "Index \t Priority \t Task" << endl;
    for (int index = 0; index < list->getSize(); index++)
    {
        cout << index+1 << " \t\t "<< list->at(index).getPriority() << " \t\t\t " << list->at(index).getTask() << endl;
    }
    cout << endl;
}
template <typename TYPE>
void printList(List<TYPE> &list)
{
    cout << "Index \t Priority \t Task" << endl;
    for (int index = 0; index < list.getSize(); index++)
    {
        cout << index+1 << " \t\t "<< list.at(index).getPriority() << " \t\t\t " << list.at(index).getTask() << endl;
    }
    cout << endl;
}

int compare(const Task& item1,const Task& item2)
{
    if (item1.getPriority() < item2.getPriority())
        return -1;
    if (item1.getPriority() == item2.getPriority())
        return 0;

    return 1;
}

void CreateTask(LinkedList<Task>* todolist, int priority, string task)
{
    if(task.empty())// checks to see if the function is being called to create a new list or input a task into a list
    {
        int count = 0;
        
        cout << "Enter a number of tasks to input: ";
        cin >> count;
        
        for(int i = 0; i < count; i++)
        {
            cout << "Enter a task to be inputted: ";
            cin.ignore();
            getline(cin, task);
            cout << "Enter the priority of the task: ";
            cin >> priority;
            Task temp;
            temp.setTask(task);
            temp.setPriority(priority);
            todolist->insert(temp,0);
        }
    }
    else
    {
        Task temp; //how do i need to delete this data or is it cleared when linkedlist remove is called?
        temp.setTask(task);
        temp.setPriority(priority);
        todolist->insert(temp,0);
    }
}
void RemoveTask(LinkedList<Task>* todolist, int index)
{
    int count;
    cout << "Enter a number of tasks to remove: ";
    cin >> count;

    for(int i = 0; i < count; i++)
    {
        cout << "Enter the index of the task to be removed: ";
        cin >> index;
        todolist->remove(index -1);
    }
}
void EditTaskList(LinkedList<Task>* todolist, string filename)
{
    CreateTask(todolist);
    printListfunction(todolist);

    RemoveTask(todolist);
    printListfunction(todolist);
    
    cout << "Sorted List: " << endl;
    todolist->sort(compare, false);
    printListfunction(todolist);
    
    bool saveToFile = false;
    cout << "Would you like to save this list to a file? (0 = false; 1 = true): ";
    cin >> saveToFile;
    
    if(saveToFile) // allows the user to save the list to a file
    {
        if(filename.empty()) // checks to see if the list was read from a previous file, if not it prompts the user to enter a file name
        {
            cout << "Enter a file name to write to (.txt): ";
            cin.ignore();
            getline(cin, filename);
        }
        
        ofstream file;
        file.open (filename);
        if(file.is_open())
        {
            file << "Priority \t Task" << endl;
            for(int i = 0; i < todolist->getSize(); i++)
            {
                file << todolist->at(i).getPriority() << " \t " << todolist->at(i).getTask() << endl;
            }
        }
        else
        {
            cout << "Could not open file.";
        }
        file.close();
    }
    
}
