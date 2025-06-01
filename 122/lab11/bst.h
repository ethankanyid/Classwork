#pragma once
#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

class Exception
{
protected:
    string message;
    int errorNumber;

public:
    Exception(int eNo, string msg) : errorNumber(eNo), message(msg) {}
    virtual string toString()
    {
        stringstream sstream;
        sstream << "Exception: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};

class DuplicateItemException : public Exception
{
public:
    DuplicateItemException(int eNo, string msg) : Exception(eNo, msg) {}
    string toString()
    {
        stringstream sstream;
        sstream << "DuplicatItemException: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};


class TreeEmptyException: public Exception
{
public:
    TreeEmptyException(int eNo, string msg) : Exception(eNo, msg) {}
    string toString()
    {
        stringstream sstream;
        sstream << "TreeEmptyException: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};

class ItemNotFoundException: public Exception
{
public:
    ItemNotFoundException(int eNo, string msg) : Exception(eNo, msg) {}
    string toString()
    {
        stringstream sstream;

        sstream << "ItemNotFoundException: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};

template <typename DATA_TYPE>
class BinarySearchTree
{
    // By placing this class definition inside the private section of the tree class,
    // it is only accessible to the tree class
    class BinaryTreeNode
    {
    public:
        DATA_TYPE data;
        BinaryTreeNode* parent;
        BinaryTreeNode* left;
        BinaryTreeNode* right;

        BinaryTreeNode() { parent = left = right = nullptr; }
    };

    BinaryTreeNode* root;
    int nodeCount;
    // This is the member variable that will be used to hold the comparison function
    int (*compare)(const DATA_TYPE& item1, const DATA_TYPE& item2);
    BinaryTreeNode* findParentOrDuplicate(const DATA_TYPE& item);
    void privateInOrder(BinaryTreeNode* node, void (*visit)(const DATA_TYPE& item))
    {
        if (!node)
            return;

        privateInOrder(node->left, visit);
        visit(node->data);
        privateInOrder(node->right, visit);
    }

    void postOrderDelete(BinaryTreeNode* node)
    {
        if (!node)
            return;

        postOrderDelete(node->left);
        postOrderDelete(node->right);
        delete node;
    }

    void rotateRight(BinaryTreeNode* node);
    void rotateLeft(BinaryTreeNode* node);

    void PrintInOrder(BinaryTreeNode* node, int level = 0)
    {
        if (!node)
        {
            level--;
            return;
        }

        level++;
        cout << "Level: " << level << " Data: " << node->data << " " << endl;  // visit
        PrintInOrder(node->left,level);
        PrintInOrder(node->right,level);
    }

public:
    /**
     * The constructor takes as a parameter the comparison function that will be 
     * used to determine the structure of the tree
     */
    BinarySearchTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2));
    ~BinarySearchTree();
    void insert(DATA_TYPE item);
    void remove(const DATA_TYPE& item);
    DATA_TYPE search(const DATA_TYPE& item);
    int size()
    {
        return nodeCount;
    }

    void inOrder(void (*visit)(const DATA_TYPE& item))
    {
        privateInOrder(root, visit);
    }
    void PrintTree()
    {
        PrintInOrder(root);
    }
    void PublicRotateRight(DATA_TYPE item)
    {
        rotateRight(findParentOrDuplicate(item));

        BinaryTreeNode* searchResult = findParentOrDuplicate(item);
        if (!searchResult || compare(searchResult->data, item))
        {
            // Throw ItemNotFoundException
            throw ItemNotFoundException(__LINE__, "Item was not found");
        }

    }
    void PublicRotateLeft(DATA_TYPE item)
    {
        rotateLeft(findParentOrDuplicate(item));

        BinaryTreeNode* searchResult = findParentOrDuplicate(item);
        if (!searchResult || compare(searchResult->data, item))
        {
            // Throw ItemNotFoundException
            throw ItemNotFoundException(__LINE__, "Item was not found");
        }
    }


};

// Public methods
template <typename DATA_TYPE>
BinarySearchTree<DATA_TYPE>::BinarySearchTree(
    int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2)
)
{
    compare = cmp;
    nodeCount = 0;
    root = nullptr;
}

template <typename DATA_TYPE>
BinarySearchTree<DATA_TYPE>::~BinarySearchTree()
{
    postOrderDelete(root);
}

template <typename DATA_TYPE>
void BinarySearchTree<DATA_TYPE>::insert(DATA_TYPE item)
{
    if(!root) // Insert into an empty tree
    {
        root = new BinaryTreeNode();
        root->data = item;
        nodeCount++;
        return;
    }

    // Find the parent node, or identify a duplicate entry
    BinaryTreeNode* searchNode = findParentOrDuplicate(item);
    if (!compare(searchNode->data, item)) // Check to see if the item already exists
    {
        // Duplicate item detected, throw an exception
        DuplicateItemException exception(__LINE__, "Duplicate item detected. Unable to insert");
        throw exception;
    }

    // Item didn't exist, we can proceed as normal. searchNode now points to the parent node
    
    // Create new node
    BinaryTreeNode* node = new BinaryTreeNode();
    node->data = item;

    // Link the parent
    node->parent = searchNode;

    // Determine if the node will be a left or right child
    // Attach the node to the appropriate side
    if (compare(searchNode->data, item) == 1) // left child
        searchNode->left = node;
    else
        searchNode->right = node;

    // Increment the node counter
    nodeCount++;
}

template <typename DATA_TYPE>
void BinarySearchTree<DATA_TYPE>::remove(const DATA_TYPE& item)
{
    // Find the item to remove
    BinaryTreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw item not found exception
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    // Check to see if it is a simple or hard case
    if (searchResult->left && searchResult->right)
    {
        //If hard
        // reduce to a simple case, then reset the pointer
        // Find the immediate predecessor
        BinaryTreeNode* current = searchResult->left;
        while (current->right)
            current = current->right;
        // Swap the data item
        DATA_TYPE tmp = searchResult->data;
        searchResult->data = current->data;
        current->data = tmp;

        // Set searchResult to the immediate predecessor
        searchResult = current;
    }

    BinaryTreeNode* child = searchResult->right ? searchResult->right : searchResult->left;
    BinaryTreeNode* parent = searchResult->parent;
    
    if(parent)
    {
        // I'm using a double pointer here rather than having a separate if/else for this.
        BinaryTreeNode** side = parent->right== searchResult ? &(parent->right) : &(parent->left);
        *side = child;
        if(child) 
            child->parent = parent;
    }
    else
    {
        // Node was the root
        root = child;
    }

    delete searchResult;
    
    nodeCount--;
}

template <typename DATA_TYPE>
DATA_TYPE BinarySearchTree<DATA_TYPE>::search(const DATA_TYPE& item)
{
    BinaryTreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    return searchResult->data; 
}

// Private functions
/**
 * This function searches the tree for the node that either contains a duplicate of the item,
 * or the node that would be the parent of the item.
 */
template <typename DATA_TYPE>
typename BinarySearchTree<DATA_TYPE>::BinaryTreeNode* BinarySearchTree<DATA_TYPE>::findParentOrDuplicate(const DATA_TYPE& item)
{
    BinaryTreeNode* current = root;
    BinaryTreeNode* parent = current;

    while (current)
    {
        parent = current;
        if (!compare(current->data, item))
            break;
        // Next, decide if we need to go left or right.
        if (compare(current->data, item) == 1) // Go left
            current = current->left;
        else // Go right. Duplicate is detected in the test of the while
            current = current->right;
    }

    return parent;
}

template <typename TYPE>
void BinarySearchTree<TYPE>::rotateRight(BinaryTreeNode* node)
{
    //rotating node passed in around its parent
    //left child stays the same
    //right child becomes new left child of original parent
    //nodes grandparent becomes nodes parent

    BinaryTreeNode* P = node->parent;
    BinaryTreeNode* GP = node->parent->parent;
    BinaryTreeNode* RC = node->right;
    BinaryTreeNode* LC = node->left;

    if(node == root || P->left != node)//node is the root or node isnt rotatable left (there is nothing to rotate)
    {
        return;
    }
    else if(GP)// node has a grandparent
    {
        if(RC)//node has a right child
        {            
            P->left = RC;
            RC->parent = P;

            node->right = P;
            P->parent = node;

            node->parent = GP;
            if(GP->right == P)
            {
                GP->right = node;
            }
            else if(GP->left == P)
            {
                GP->left = node;
            }
        }
        else if(!RC)//node does not have a right child
        {
            P->left = nullptr;

            node->right = P;
            P->parent = node;

            node->parent = GP;
            if(GP->right == P)
            {
                GP->right = node;
            }
            else if(GP->left == P)
            {
                GP->left = node;
            }

        }
    }
    else if(!GP && P == root)//node does not have a grandparent (nodes parent is root)
    {
        if(RC)//node has a right child
        {
            P->left = RC;
            RC->parent = P;

            node->right = P;
            P->parent = node;

            node->parent = nullptr;
            root = node;
        }
        else if(!node->right)// node does not have a right child
        {
            P->left = nullptr;

            node->right = P;
            P->parent = node;
            
            node->parent = nullptr;
            root = node;
        }

    }



}

template <typename TYPE>
void BinarySearchTree<TYPE>::rotateLeft(BinaryTreeNode* node)
{
    //rotating node passed in around its parent
    //right child stays the same
    //left child becomes new right child of original parent
    //nodes grandparent becomes nodes parent

    BinaryTreeNode* P = node->parent;
    BinaryTreeNode* GP = node->parent->parent;
    BinaryTreeNode* RC = node->right;
    BinaryTreeNode* LC = node->left;

    if(node == root || P->right != node)//node is the root or node isnt rotatable right (there is nothing to rotate)
    {
        return;
    }
    else if(GP)// node has a grandparent
    {
        if(LC)//node has a left child
        {            
            P->right = LC;
            LC->parent = P;

            node->left = P;
            P->parent = node;

            node->parent = GP;
            if(GP->left == P)
            {
                GP->left = node;
            }
            else if(GP->right == P)
            {
                GP->right = node;
            }
        }
        else if(!LC)//node does not have a left child
        {
            P->right = nullptr;

            node->left = P;
            P->parent = node;

            node->parent = GP;
            if(GP->left == P)
            {
                GP->left = node;
            }
            else if(GP->right == P)
            {
                GP->right = node;
            }

        }
    }
    else if(!GP && P == root)//node does not have a grandparent (nodes parent is root)
    {
        if(LC)//node has a left child
        {
            P->right = LC;
            LC->parent = P;

            node->left = P;
            P->parent = node;

            node->parent = nullptr;
            root = node;
        }
        else if(!node->left)// node does not have a left child
        {
            P->right = nullptr;
            
            node->left = P;
            P->parent = node;
            
            node->parent = nullptr;
            root = node;
        }

    }


}