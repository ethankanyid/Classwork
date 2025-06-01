#include "bst.h"
#include <iostream>

using namespace std;

template <typename TYPE>
int compare(const TYPE& item1, const TYPE& item2)
{
	if (item1 < item2)
		return -1;
	if (item1 == item2)
		return 0;

	return 1;
}


int main()
{
    BinarySearchTree<int> tree(compare);
    int count = 0;

    try
    {
        /*cout << " How many elements would you like the tree to be?: ";
        cin >> count;
        for(int i = 0; i < count; i++)
        {
            tree.insert(i+1);
        }*/

        tree.insert(8);
        tree.insert(9);
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);
        tree.insert(3);
        tree.insert(4);
        tree.insert(1);
        tree.insert(2);
        
        cout << "Unbalanced: " << endl;
        tree.PrintTree();

        tree.DSW();
        cout << "Balanced: " << endl;
        tree.PrintTree();


        /*bool x = false;

        cout << " Would you like to rotate an element right: (false = 0; true = 1): ";
        cin >> x;
        while(x)
        {
            cout << " Enter an element to rotate right: ";
            cin >> count; //reused
            tree.PublicRotateRight(count);
            tree.PrintTree();

            cout << " Would you like to rotate an element right: (false = 0; true = 1): ";
            cin >> x;
        }
        

        cout << " Would you like to rotate an element left: (false = 0; true = 1): ";
        cin >> x;
        while(x)
        {
            cout << " Enter an element to rotate left: ";
            cin >> count; //reused
            tree.PublicRotateLeft(count);
            tree.PrintTree();
            
            cout << " Would you like to rotate an element left: (false = 0; true = 1): ";
            cin >> x;
        }*/



    }
    catch(Exception x)
    {
        cout << x.toString() << endl;
    }

    return 0;
}