#pragma once
#include "exception.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;

#define BLOCKSIZE 16 // fixed it fo ya


template <typename DATA_TYPE>
class BTree
{
    class BNode
    {
    public:

        vector<DATA_TYPE> key;
        vector<BNode*> kid;

        BNode* parent;
        int items;

        BNode(int size) 
        { 
            parent = nullptr;
            items = 0;
            key.assign(size + 1,0);
            kid.assign(size + 2,nullptr);
        }
    };

    // This is the member variable that will be used to hold the comparison function
    int (*compare)(const DATA_TYPE& item1, const DATA_TYPE& item2);

    // This function searches the tree for the node
    // that either contains a duplicate of the item, or the node that would be the parent of the item.
    BNode* findParentOrDuplicate(const DATA_TYPE& item);

    void postOrderDelete(BNode* node);

    void privatePrintInOrder(BNode* node);

    // Private members
    BNode* root;
    int nodeCount;
    int nodesize;
    int itemCount;



public:
    // The constructor takes as a parameter the comparison function
    // that will be used to determine the structure of the tree
    BTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2));
    ~BTree();

    int countNode();
    int countItem();

    void insert(DATA_TYPE item, BNode* searchNode = nullptr);

    void remove(const DATA_TYPE& item, BNode* searchNode = nullptr);

    int search(const DATA_TYPE& item);

    void printTree();

    DATA_TYPE find(DATA_TYPE item);

};

// Private methods
template <typename DATA_TYPE>
typename BTree<DATA_TYPE>::BNode* BTree<DATA_TYPE>::findParentOrDuplicate(const DATA_TYPE& item)
//find parent or duplicate or node
{
    BNode* node = root;
    BNode* old = node;
    int i = 0;

    while (node && i < node->items) // exits when current is null meaning item was not found
    {
        // -1 right (greater)
        // 1 left (less)
        // 0 item found

        old = node;

        if (!compare(node->key[i], item)) // item is found, returns null
            return node;
        
        // Next, decide if we need to go left or right.

        if ((compare(node->key[i], item) == 1)) // item is less, take immediate left
        {
            node = node->kid[i];
            i = 0;
        }
        else if (i == node->items - 1) // end of keys and item is larger
        {
            node = node->kid[i+1];
            i = 0;
        }
        else // item is larger than key[i].data check key [i+1]
        {
            i++;
        }


    }

    return old;
}

template <typename DATA_TYPE>
void BTree<DATA_TYPE>::postOrderDelete(BNode* node)
{
    if (!node)
        return;

    for (int i = 0; i < node->items; i++)
    {
        postOrderDelete(node->kid[i]);
    }
    postOrderDelete(node->kid[node->items]);
    delete node;
}

template <typename DATA_TYPE>
void BTree<DATA_TYPE>::privatePrintInOrder(BNode* node)
{
    if (!node)
        return;

    for (int i = 0; i < node->items; i++)
    {
        privatePrintInOrder(node->kid[i]);
        cout << " Data: " << node->key[i] << endl;  // visit
    }
    privatePrintInOrder(node->kid[node->items]);
}

// Public methods
template <typename DATA_TYPE>
int BTree<DATA_TYPE>::countNode()
{
    return nodeCount;
}

template <typename DATA_TYPE>
int BTree<DATA_TYPE>::countItem()
{
    return itemCount;
}

template <typename DATA_TYPE>
void BTree<DATA_TYPE>::printTree()
{
    privatePrintInOrder(root);
}

template <typename DATA_TYPE>
BTree<DATA_TYPE>::BTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2))
{
    compare = cmp;
    nodeCount = 0;
    itemCount = 0;
    root = nullptr;

    nodesize = BLOCKSIZE/sizeof(DATA_TYPE);

    if (nodesize <= 1 || BLOCKSIZE%sizeof(DATA_TYPE) != 0)
    {
        throw InvalidSize(__LINE__, "Invalid Size");
        return;
    }


}

template <typename DATA_TYPE>
BTree<DATA_TYPE>::~BTree()
{
    if (root)
        postOrderDelete(root);
}

template <typename DATA_TYPE>
void BTree<DATA_TYPE>::insert(DATA_TYPE item, BNode* searchNode)
{   
    if(!root) // Insert into an empty tree else always inserting in leaf
    {
        root = new BNode(nodesize);
        root->key[0] = item;
        root->items++;
        nodeCount++;
        itemCount++;

        root->parent = nullptr;
        root->kid[0] = nullptr;
        root->kid[1] = nullptr;

        return;
    }

    if (!searchNode)    // need to look for node
    {
        if (search(item)) // catches if item exists
        {
            // Duplicate item detected, throw an exception
            DuplicateItemException exception(__LINE__, "Duplicate item detected. Unable to insert");
            throw exception;
        }
        else
            searchNode = findParentOrDuplicate(item); // else finds node
    }
    
    int midpoint = ceil(nodesize / 2);

    for (int i = searchNode->items; i >= 0; i--) // insert (node has one extra spot to hold item)
    {   
        if (compare(item, searchNode->key[i-1]) == 1)
        {
            searchNode->key[i] = item;
            break;
        }
        else
        {
            searchNode->key[i] = searchNode->key[i-1];           
        }
    }

    searchNode->items++;
    itemCount++;

    if (searchNode->items > nodesize)  //leaf is over full
    {
        BNode* node = new BNode(nodesize);
        nodeCount++;
        node->parent = searchNode->parent; //pushes parent pointer early to handle in recursion

        if(searchNode->parent)
        {
            for (int i = nodesize + 1; i >= 0; i--) // adjust parent pointers
            {   
                if (searchNode->parent->kid[i - 1] == searchNode)
                {
                    searchNode->parent->kid[i] = node;
                    break;
                }
                else
                {
                    searchNode->parent->kid[i] = searchNode->parent->kid[i-1];           
                }
            }
        }
        for (int i = midpoint + 1; i <= nodesize; i++) //transfer keys to sibling
        {
            node->key[i - midpoint - 1] = searchNode->key[i];
            searchNode->key[i] = 0;
            node->items++;
            searchNode->items--;
        }
        for (int i = midpoint + 1; i <= nodesize + 1; i++) //transfer kids to sibling
        {
            node->kid[i - midpoint - 1] = searchNode->kid[i];

            if (searchNode->kid[i]) //update kids parent pointer to point to new node
                searchNode->kid[i]->parent = node;
            
            searchNode->kid[i] = nullptr;

        }


        if (searchNode == root) //searchnode is root
        {
            BNode* newroot = new BNode(nodesize);
            nodeCount++;
            root = newroot;

            // midpoint goes to root
            root->key[0] = searchNode->key[midpoint];
            searchNode->key[midpoint] = 0;
            searchNode->items--;
            root->items++;

            //update root
            root->kid[0] = searchNode;
            root->kid[1] = node;

            //update left child
            searchNode->parent = root;
            node->parent = root;
        }
        else
        {
            insert(searchNode->key[midpoint], searchNode->parent);
            searchNode->key[midpoint] = 0;
            searchNode->items--;
            itemCount--;
        }
    }
}

template <typename DATA_TYPE>
void BTree<DATA_TYPE>::remove(const DATA_TYPE& item, BNode* searchNode)
{
    int midpoint = ceil(nodesize / 2);
    int i = 0;

    if (!searchNode) //was node passed in?
    {
        if (!search(item)) // catches if item exists
        {
            ItemNotFoundException exception(__LINE__, "Item Not Found");
            throw exception;
        }

        searchNode = findParentOrDuplicate(item);

        while (i < searchNode->items && compare(item, searchNode->key[i])) // find item in node
            i++;
        
        BNode* tempnode = (searchNode->kid[0]) ? searchNode->kid[i] : nullptr;
        while (tempnode) // find predecessor
        {
            if (!tempnode->kid[0])
                break;
            tempnode = tempnode->kid[tempnode->items];
        }

        if (!tempnode) // no child predecessor, delete
        {
            searchNode->items--;
            for (; i <= searchNode->items; i++) // moving other items back.
            {
                searchNode->key[i] = searchNode->key[i + 1];
            }
        }
        else // replace by copy 
        {
            searchNode->key[i] = tempnode->key[tempnode->items - 1];
            tempnode->items--;
            tempnode->key[tempnode->items] = 0;
            searchNode = tempnode;
        }
        
        itemCount--;
    }
    i = 0;

    if (searchNode == root) // base case and case to handle empty tree
    {
        if (nodeCount == 1 && searchNode->items == 0)
        {   
            delete root;
            root = nullptr;
            nodeCount--;
        }
        else if (searchNode->items == 0)
        {
            root = root->kid[0] ? root->kid[0] : root->kid[1];
            delete root->parent;
            nodeCount--;
            root->parent = nullptr;
        }
        return;
    }

    if (searchNode->items < midpoint) // node doesnt have enough cells 
    {
        BNode* P = searchNode->parent; //guaranteed to have parent because of base case

        while (i <= nodesize && P->kid[i] != searchNode)  // find potential siblings (i points to search node (left child of key))
            i++;

        BNode* L = (i != 0) ? (P->kid[i - 1]) : nullptr;
        BNode* R = (i != nodesize) ? (P->kid[i + 1]) : nullptr;
        DATA_TYPE temp = 0;

        if (L && L->items > midpoint) //left sibling can handle underflow
        {
            temp = P->key[i - 1];
            P->key[i - 1] = L->key[L->items - 1];
            L->items--;
            L->key[L->items] = 0;

            insert(temp, searchNode);
            itemCount--;
            searchNode->kid[searchNode->items] = L->kid[L->items + 1];
            L->kid[L->items + 1] = nullptr;
        }
        else if (R && R->items > midpoint) //right sibling can handle underflow 
        {
            temp = P->key[i];
            P->key[i] = R->key[0];
            R->items--;
            for (i = 0; i <= R->items; i++) // moving other items back.
            {
                R->key[i] = R->key[i + 1];
            }

            insert(temp, searchNode);
            itemCount--;
            searchNode->kid[searchNode->items] = R->kid[0]; // bring over kid
            for (i = 0; i <= nodesize; i++) //adjust Rs kids
                R->kid[i] = R->kid[i + 1];   
        }
        else if (R) // cells will merge (right sibling into searchnode)
        {
            searchNode->key[searchNode->items] = P->key[i];
            searchNode->items++;

            for (int x = i; x < P->items; x++) // adjust parent keys
                P->key[x] = P->key[x + 1];

            P->items--;

            for (i++; i <= nodesize; i++) // adjust parent pointers
                P->kid[i] = P->kid[i + 1];           

            for (i = 0; i < R->items; i++) // transfer R keys and pointers
            {
                searchNode->key[searchNode->items] = R->key[i];
                searchNode->kid[searchNode->items] = R->kid[i];
                if (searchNode->kid[searchNode->items])
                    searchNode->kid[searchNode->items]->parent = searchNode;
                searchNode->items++;
            }
            // one more kid than key
            searchNode->kid[searchNode->items] = R->kid[i];
            if (searchNode->kid[searchNode->items])
                searchNode->kid[searchNode->items]->parent = searchNode;

            delete R;
            nodeCount--;
        }
        else if (L) // cells will merge (searchnode into left sibling)
        {
            L->key[L->items] = P->key[i - 1];
            L->items++;

            P->key[i - 1] = 0;// adjust parent key
            P->items--;

            P->kid[i] = nullptr; // adjust parent pointer

            for (i = 0; i < searchNode->items; i++) // transfer L keys and pointers
            {
                L->key[L->items] = searchNode->key[i];
                L->kid[L->items] = searchNode->kid[i]; 
                if(L->kid[L->items])
                    L->kid[L->items]->parent = L; 
                L->items++;
            }
            // one more kid than key
            L->kid[L->items] = searchNode->kid[i]; 
            if(L->kid[L->items])
                L->kid[L->items]->parent = L; 

            delete searchNode;
            nodeCount--;
        }

        if (P->items < midpoint && (P != root || P->items == 0)) // parent doesnt have enough items.
        {
            remove(0, P); // item doesnt matter, it wont be used.
        }
        
    }

}

template <typename DATA_TYPE>
int BTree<DATA_TYPE>::search(const DATA_TYPE& item)
{
    BNode* searchResult = findParentOrDuplicate(item);
    for (int i = 0; i < searchResult->items; i++)
    {   
        if (!compare(searchResult->key[i], item))
        {
            return 1;
        }
    }
    return 0;
}

template <typename DATA_TYPE>
DATA_TYPE BTree<DATA_TYPE>::find(DATA_TYPE item)
{
    BNode* searchResult = findParentOrDuplicate(item);
    for (int i = 0; i < searchResult->items; i++)
    {   
        if (!compare(searchResult->key[i], item))
        {
            return searchResult->key[i];
        }
    }

    ItemNotFoundException exception(__LINE__, "Item Not Found");
    throw exception;
}