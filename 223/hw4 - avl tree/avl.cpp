#pragma once
#include "exception.cpp"
#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

template <typename DATA_TYPE>
class avlTree
{
    // By placing this class definition inside the private section of the tree class,
    // it is only accessible to the tree class
    class TreeNode
    {
    public:
        DATA_TYPE data;
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;

        // avl data
        int factor; // -1,0,1
        int height;  //always positive

        TreeNode() { parent = left = right = nullptr; factor = height = 0; }
    };

    // This is the member variable that will be used to hold the comparison function
    int (*compare)(const DATA_TYPE& item1, const DATA_TYPE& item2);

    // This function searches the tree for the node
    // that either contains a duplicate of the item, or the node that would be the parent of the item.
    TreeNode* findParentOrDuplicate(const DATA_TYPE& item);

    //
    void privateRotateRight(TreeNode* node);

    //
    void privateRotateLeft(TreeNode* node);

    //
    void postOrderDelete(TreeNode* node);

    //
    void privatePrintInOrder(TreeNode* node, int level = 0);

    void adjustHeight(TreeNode* node,
                    char casetype = 'b',
                    bool toRoot = false,
                    TreeNode* child = nullptr,
                    TreeNode* grandchild = nullptr);

    void insertCase(TreeNode* node, TreeNode* child, TreeNode* grandchild);
    void removeCase(TreeNode* node, TreeNode* child);

    // Private members
    TreeNode* root;
    int nodeCount;

public:
    // The constructor takes as a parameter the comparison function
    // that will be used to determine the structure of the tree
    avlTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2));
    ~avlTree();

    //
    int count();

    //
    void insert(DATA_TYPE item);

    //
    void remove(const DATA_TYPE& item);

    //
    DATA_TYPE search(const DATA_TYPE& item);

    //
    void printTree();

    //
    void rotateRight(DATA_TYPE item);

    //
    void rotateLeft(DATA_TYPE item);
};

// Private methods
template <typename DATA_TYPE>
typename avlTree<DATA_TYPE>::TreeNode* avlTree<DATA_TYPE>::findParentOrDuplicate(const DATA_TYPE& item)
//find parent or duplicate or node
{
    TreeNode* current = root;
    TreeNode* parent = current;

    while (current) // exits when current is null meaning item was not found
    {
        // -1 right (greater)
        // 1 left (less)
        // 0 item found
        parent = current;
        if (!compare(current->data, item)) // duplicate detected, returns item node
            break;
        // Next, decide if we need to go left or right.
        if (compare(current->data, item) == 1) // Go left
            current = current->left;
        else // Go right.
            current = current->right;
    }

    return parent;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::privateRotateRight(TreeNode* node)
{
    //rotating node passed in around its parent
    //left child stays the same
    //right child becomes new left child of original parent
    //nodes grandparent becomes nodes parent

    TreeNode* P = node->parent;
    TreeNode* GP = node->parent->parent;
    TreeNode* RC = node->right;
    TreeNode* LC = node->left;

    if(node == root || P->left != node)
    //node is the root or node isnt rotatable left (there is nothing to rotate)
    {
        DuplicateItemException exception(__LINE__, "Invalid node to rotate");
        throw exception;
    }

    P->left = RC;
    if(RC) //node had a right child
        RC->parent = P;

    node->right = P;
    P->parent = node;

    if(!GP && P == root)
    //node does not have a grandparent (nodes parent is root)
    {
        node->parent = nullptr;
        root = node;
    }
    else // node had a grandparent
    {
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
    // adjust height
    adjustHeight(P);
    adjustHeight(node);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::privateRotateLeft(TreeNode* node)
{
    //rotating node passed in around its parent
    //right child stays the same
    //left child becomes new right child of original parent
    //nodes grandparent becomes nodes parent

    TreeNode* P = node->parent;
    TreeNode* GP = node->parent->parent;
    TreeNode* RC = node->right;
    TreeNode* LC = node->left;

    if(node == root || P->right != node)
    //node is the root or node isnt rotatable right (there is nothing to rotate)
    {
        DuplicateItemException exception(__LINE__, "Invalid node to rotate");
        throw exception;
    }

    P->right = LC;
    if(LC) // node has a left child
        LC->parent = P;

    node->left = P;
    P->parent = node;

    if (!GP && P == root)
    // node does not have a grandparent (nodes parent is root)
    {
        node->parent = nullptr;
        root = node;
    }
    else // node had a grandparent
    {
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

    // adjust height
    adjustHeight(P);
    adjustHeight(node);

}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::postOrderDelete(TreeNode* node)
{
    if (!node)
        return;

    postOrderDelete(node->left);
    postOrderDelete(node->right);
    delete node;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::privatePrintInOrder(TreeNode* node, int level)
{
    if (!node)
    {
        level--;
        return;
    }

    level++;
    cout << "Level: " << level << " Data: " << node->data << " \n\tHeight: " << node->height << " \n\tFactor: " << node->factor << endl;  // visit
    privatePrintInOrder(node->left,level);
    privatePrintInOrder(node->right,level);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::adjustHeight(TreeNode* node,
                                        char casetype,
                                        bool toRoot,
                                        TreeNode* child,
                                        TreeNode* grandchild)
// three functions call this. privateRotate, insert, and remove
// must pass in node, case = b, child and grandchild = nullptr
//char decides case i - insert, r - remove, b - basic
{
    if(!node)
    //node is last node in tree
    {
        return;
    }

    // establish base case
    if (node == root)
    {
        toRoot = false;
    }

    // node has both children and evaluates greater height
    if (node->right && node->left)
    {
        node->height = (node->left->height >= node->right->height) ? node->left->height + 1 : node->right->height + 1;
        node->factor = node->right->height - node->left->height;
    }
    // node has just the right
    else if (node->right)
    {
        node->height = node->right->height + 1;
        node->factor = node->right->height + 1;
    }
    // node has just the left
    else if (node->left)
    {
        node->height = node->left->height + 1;
        node->factor =  -(node->left->height + 1);
    }
    // node is a leaf node
    else
    {
        node->height = 0;
        node->factor = 0;
    }

    //insert cases (insert cannot go out of sort until at least two levels, hence grandchild cannot equal nullptr)
    if ((node->factor < -1 || node->factor > 1) && casetype == 'i')
        insertCase(node, child, grandchild);
    // delete case
    else if ((node->factor < -1 || node->factor > 1) && casetype == 'r')
        removeCase(node, child);
    if (toRoot)
        adjustHeight(node->parent, casetype, toRoot, node, child);
    return;

}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::insertCase(TreeNode* node, TreeNode* child, TreeNode* grandchild)
{
    cout << "Remidiating insert case" << endl;

    if (child == node->left)
    {
        if(grandchild == child->left) // left left
        {
            cout << "Left Left case" << endl;
            privateRotateRight(child);
        }
        else if (grandchild == child->right)// left right??
        {
            cout << "Left Right case" << endl;
            privateRotateLeft(grandchild);
            privateRotateRight(grandchild);
        }
    }
    else if (child == node->right)
    {
        if(grandchild == child->right) // right right
        {
            cout << "Right Right case" << endl;
            privateRotateLeft(child);
        }
        else if (grandchild == child->left)// right left??
        {
            cout << "Right Left case" << endl;
            privateRotateRight(grandchild);
            privateRotateLeft(grandchild);
        }
    }
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::removeCase(TreeNode* node, TreeNode* child)
{
    cout << "Remidiating remove case" << endl;

    if (child == node->left)
    {
        if(node->right->factor == -1) // check for double rotation
        {
            cout << "Double rotation on left child of right uncle"<< endl;
            privateRotateRight(node->right->left);
            privateRotateLeft(node->right);
        }
        else // single rotation
        {
            cout << "Single rotation on right uncle"<< endl;
            privateRotateLeft(node->right);
        }
    }
    else if (child == node->right)
    {
        if(node->left->factor == 1) // check for double rotation
        {
            cout << "Double rotation on right child of left uncle"<< endl;
            privateRotateLeft(node->left->right);
            privateRotateRight(node->left);
        }
        else // single rotation
        {
            cout << "Single rotation on left uncle"<< endl;
            privateRotateRight(node->left);
        }
    }
}

// Public methods
template <typename DATA_TYPE>
int avlTree<DATA_TYPE>::count()
{
    return nodeCount;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::printTree()
{
    privatePrintInOrder(root);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::rotateRight(DATA_TYPE item)
{
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    privateRotateRight(findParentOrDuplicate(item));
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::rotateLeft(DATA_TYPE item)
{
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    privateRotateLeft(findParentOrDuplicate(item));
}

template <typename DATA_TYPE>
avlTree<DATA_TYPE>::avlTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2))
{
    compare = cmp;
    nodeCount = 0;
    root = nullptr;
}

template <typename DATA_TYPE>
avlTree<DATA_TYPE>::~avlTree()
{
    postOrderDelete(root);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::insert(DATA_TYPE item)
{
    if(!root) // Insert into an empty tree
    {
        root = new TreeNode();
        root->data = item;
        nodeCount++;
        return;
    }

    // Find the parent node, or identify a duplicate entry
    TreeNode* searchNode = findParentOrDuplicate(item);
    if (!compare(searchNode->data, item)) // Check to see if the item already exists
    {
        // Duplicate item detected, throw an exception
        DuplicateItemException exception(__LINE__, "Duplicate item detected. Unable to insert");
        throw exception;
    }

    // Item didn't exist, we can proceed as normal. searchNode now points to the parent node

    // Create new node
    TreeNode* node = new TreeNode();
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

    //fix heights
    adjustHeight(searchNode, 'i', true, node);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::remove(const DATA_TYPE& item)
{
    // Find the item to remove
    TreeNode* searchResult = findParentOrDuplicate(item);
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
        TreeNode* current = searchResult->left;
        while (current->right)
            current = current->right;
        // Swap the data item
        DATA_TYPE tmp = searchResult->data;
        searchResult->data = current->data;
        current->data = tmp;

        // Set searchResult to the immediate predecessor
        searchResult = current;
    }

    TreeNode* child = searchResult->right ? searchResult->right : searchResult->left;
    TreeNode* parent = searchResult->parent;

    if(parent)
    {
        // I'm using a double pointer here rather than having a separate if/else for this.
        TreeNode** side = (parent->right == searchResult) ? &(parent->right) : &(parent->left);
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

    adjustHeight(parent, 'r', true);
    /* predecessor up to root changes*/
}

template <typename DATA_TYPE>
DATA_TYPE avlTree<DATA_TYPE>::search(const DATA_TYPE& item)
{
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    return searchResult->data;
}
