#include "BTree.h"

using namespace std;

template <typename DATA_TYPE>
int compare(const DATA_TYPE& item1, const DATA_TYPE& item2)
{
	if (item1 < item2)
		return -1;
	if (item1 == item2)
		return 0;

	return 1;
}

int main(int const argc, char const *argv[])
{
    try
    {
        BTree<int> tree(compare);
        
        tree.insert(1);
        tree.insert(2);
        tree.insert(18);
        tree.insert(19);
        tree.insert(10);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);
        tree.insert(17);
        tree.insert(16);
        tree.insert(15);
        tree.insert(20);
        tree.insert(21);
        tree.insert(22);
        tree.insert(14);
        tree.insert(13);
        tree.insert(12);

        tree.remove(14);
        tree.remove(2);
        tree.remove(18);
        tree.remove(19);
        tree.remove(10);
        tree.remove(3);
        tree.remove(4);
        tree.remove(5);
        tree.remove(17);
        tree.remove(16);
        tree.remove(15);
        tree.remove(20);
        tree.remove(21);
        tree.remove(22);
        tree.remove(13);
        tree.remove(12);

        tree.printTree();

    }
    catch(DuplicateItemException x)
    {
        cout << x.toString() << '\n';
    }
    catch(TreeEmptyException x)
    {
        cout << x.toString() << '\n';
    }
    catch(ItemNotFoundException x)
    {
        cout << x.toString() << '\n';
    }
    catch(InvalidSize x)
    {
        cout << x.toString() << '\n';
    }


    return 0;
}
