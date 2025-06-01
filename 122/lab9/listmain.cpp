#include <iostream>
#include <iomanip>
#include "arraylist.h"
#include "linkedlist.h"

using std::cout;
using std::endl;
using std::boolalpha;

/**
* This function is used to compare 2 items. The assumption is that the < and == operators have meaining for TYPE
* Returns a -1 if the first item is less than the second, 0 if they are equivalent, and a 1 if the firs item is 
* greater than the second.
* 
* The reason for this type of function is that often the "basis for comparison" might be a compound comparison.
* The library author for the List implementation could not be expected to know all the myriad of ways that two
* items might be compared. Using this sort of a comparison function allows the library consumer to define how
* the items get compared for sort and search methods.
*/
template <typename TYPE>
int compare(const TYPE& item1, const TYPE& item2)
{
	if (item1 < item2)
		return -1;
	if (item1 == item2)
		return 0;

	return 1;
}

/*
* Print the list, assuming that the list contains integers.
*/
void printList(List<int>& list)
{
	for (int index = 0; index < list.getSize(); index++)
	{
		cout << (index > 0 ? ", " : "") << list.at(index);
	}
	cout << endl << endl;
}

/**
* Function to test the list. This should work with either ArrayList or LinkedList, as long as it is based on the List parent class.
*/
bool testList(List<int> &list)
{
	// Add items to the list
	list.insert(5, 0);
	list.insert(12, 0);
	list.insert(4, -1);
	list.insert(18, 0);
	list.insert(1, 0);
	list.insert(35, 0);
	list.insert(46, 0);
	list.insert(11, 0);
	list.insert(0, 0);
	list.insert(64, 0);
	list.insert(75, 0);
    
    printList(list);
    
	// Sort the list
	list.sort(compare, false);
	printList(list);
    
	// Test the list by checking specific indexes
	int indexValue = list.at(4);
	if (indexValue != 11)
	{
		cout << "Failed index retrieval test. retrieved index 4 and got value " << indexValue << endl;
		return false;
	}

	// Test search
	int searchIndex = list.search(35, compare);
	if (searchIndex != 7)
	{
		cout << "Failed search index test. Searched for 35 and found it at " << searchIndex << endl;
		return false;
	}

	return true; // Default is test succeeded.
}

int main(int argc, char* argv[])
{
	//ArrayList<int> arrayList;

	//testList(arrayList);

    // The following is a sample of how you should be able to use the testList function to test
    // your linked list implementation.
	
    LinkedList<int> linkedList;
    
    cout << "Testing LinkedList" << endl;
    
    bool testResult = false;
    
    int value = 0, index = 0, count = 0;
    
    try
    {
        testResult = testList(linkedList);

        cout << "Enter a number of values to input: ";
		std::cin >> count;
		for(int i = 0; i < count; i++)
		{
			cout << "Enter a value to be inputted: ";
			std::cin >> value;
			cout << "Enter a index to input it at: ";
			std::cin >> index;
			
			linkedList.insert(value,index);
			printList(linkedList);
		}
		
        cout << "Enter a number of values to remove: ";
		std::cin >> count;
		for(int i = 0; i < count; i++)
		{
			cout << "Enter a index to be removed: ";
			std::cin >> index;
			
			linkedList.remove(index);           
			printList(linkedList);
		}
        cout << "Enter an index to see its data: ";
        std::cin >> index;
        linkedList.at(index);
        cout << "The value at " << index << " is " << linkedList.at(index) << endl;
        
        cout << boolalpha << "Test result is " << testResult << endl;
        
    }
    catch(IndexOutOfBounds msg)
    {
        cout << msg.getMessage() << endl;
    }

	return 0;
}
