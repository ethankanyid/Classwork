#include "list.h"
#include "exceptions.h"
#include <sstream>

// class node is where data will actually be stored.
template <typename TYPE>
class Node
{
public:
    Node<TYPE>* next;
    Node<TYPE>* prev;

    TYPE data;

    Node();
};

template <typename TYPE>
Node<TYPE>::Node()
// constructor
{
    prev = nullptr;
    next = nullptr;

}

template <typename TYPE>
class LinkedList : public List<TYPE>
{
public: 
	LinkedList();
	~LinkedList();
	void insert(TYPE item, int index);
	void remove(int index);
	TYPE at(int index);
	void sort(int(*cmp)(const TYPE& item1, const TYPE& item2), bool doQuicksort);
	int search(TYPE item, int(*cmp)(const TYPE& item1, const TYPE& item2));
	int getSize();


private:

    Node<TYPE>* head;
    Node<TYPE>* tail;
    int count;

};

template <typename TYPE>
LinkedList<TYPE>::LinkedList() // consturctor
{
    head = nullptr;
    tail = head;
    count = 0;
}


template <typename TYPE>
LinkedList<TYPE>::~LinkedList()// deconstructor

{
    while (count > 0)
    {
        remove(0);
    }
}

template <typename TYPE>
void LinkedList<TYPE>::insert(TYPE item, int index)
{
    if (index < -1 || index > count+1)//catches exceptions
    {
        stringstream sstream;
        sstream << "Index " << index << " is out of bounds (function: insert)";
        string msg;
        getline(sstream, msg);
        throw IndexOutOfBounds(msg);
    }
    
    Node<TYPE>* node = new Node<TYPE>;
    node->data = item;
    count++;

    if (index == 0) //Head Case
    {
        if (count != 1)//inserting into a list greater than 1
        {
            head->prev = node;
            node->next = head;
            head = node;
            node->prev = nullptr;
        }
        else if (count == 1)//inserting into an empty list (assigns head and tail)
        {
            head = node;
            tail = head;
            node->prev = nullptr;
            node->next = nullptr;
        }
    }
    else if(index == -1)//Tail Case
    {
        if (count != 1)//inserting into a list greater than 1
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
            node->next = nullptr;
        }
        else if(count == 1)//inserting into an empty list (assigns head and tail)
        {
            tail = node;
            head = tail;
            node->next = nullptr;
            node->prev = nullptr;
        }
    }
    else //Everything in the middle
    {
        Node<TYPE>* temp = head;
        for(int i = 0; i < index -1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        node->prev = temp;
        temp->next = node;
        node->next->prev = node;
    }
    return;
}

template <typename TYPE>
void LinkedList<TYPE>::remove(int index)
{
    if (index < -1 || index >= count)//catches exceptions
    {
        stringstream sstream;
        sstream << "Index " << index << " is out of bounds (function: remove)";
        string msg;
        getline(sstream, msg);
        throw IndexOutOfBounds(msg);
    }

    if (index == -1 || (count == 2 && index == 1)) // tail case
    {
        if (index == -1 && count > 2)//leaves two or more items in list
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        else if (index == -1 && count > 1)//leaves one item in list
        {
            tail = tail->prev;
            delete tail->next;
            head = tail;
            tail->next = nullptr;
            tail->prev = nullptr;
        }
        else//leaves empty list
        {
            delete tail;
            tail = nullptr;
            head = tail;
        }
        count--;
    }
    else if(index == 0) //Head case
    {
        if (index == 0 && count > 2)//leaves two or more items in list
        {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        else if (index == 0 && count > 1)//leaves one item in list
        {
            head = head->next;
            delete head->prev;
            tail = head;
            head->next = nullptr;
            head->prev = nullptr;
        }
        else//leaves empty list
        {
            delete head;
            head = nullptr;
            tail = head;
        }
        count--;
    }
    else if(index < count)// Middle Item
    {
        Node<TYPE>* temp = head;
        for(int i = 0; i < index; i++)//iterates to the position to be removed
        {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        count--;
    }
    return;
}

template <typename TYPE>
TYPE LinkedList<TYPE>::at(int index)
{
    if (index < -1 || index >= count)//catches exceptions
	{
		// Throw an index out of bounds exception
		stringstream sstream;
		sstream << "Index " << index << " is out of bounds (function: at)";
		string msg;
		getline(sstream, msg);
		throw IndexOutOfBounds(msg);
	}

    Node<TYPE>* temp = head;
    
    if(index == -1)//tail item
    {
        return tail->data;
    }
    else// everything else
    {
        for(int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
    }
    
    return temp->data;
}



/**
* Method to sort the data in the List. Takes a pointer to a comparison function
* 
* The comparison function takes 2 TYPEs as parameters. It returns a -1 if the first item is "less than" the second, a 0 if they are 
* "equal", and a 1 if the second item is "less than" the first.
*/
template <typename TYPE>
void LinkedList<TYPE>::sort(int(*cmp)(const TYPE& item1, const TYPE& item2), bool doQuicksort)
{
    Node<TYPE>* temp = nullptr;
    int tempcount = count;

    bool swapped = true;
    while(swapped)
    {
        swapped = false;
        
        temp = head;
        
        for (int i = 0; i < tempcount - 1; i++)
        {
            if(cmp(at(i), at(i+1)) > 0)
            //This is a method to sort only by swapping values and not pointers
            {
                TYPE data = temp -> data;
                temp->data = temp -> next ->data;
                temp -> next -> data = data;
                
                swapped = true;
            }
            temp = temp->next;
            
        }
        tempcount--;
    }

}

/**
* Method to search for a given item. Takes an ITEM as a parameter and a comparison function. Returns the index of the item if found
*
* Utilizes a compare function similar to the sort method.
*/
template <typename TYPE>
int LinkedList<TYPE>::search(TYPE item, int(*cmp)(const TYPE& item1, const TYPE& item2))
{
    Node<TYPE>* temp = head;

    for (int i = 0; i < count -1; i++)
	{
		if (!cmp(item,temp->data))
		{
			return i;
		}
        temp = temp->next;
	}
	return -1;

}

/**
* Method to get the size of the List
*/
template <typename TYPE>
int LinkedList<TYPE>::getSize()
{
    return count;
}
