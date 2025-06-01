#include "tree.h"

Tree::Tree(const string alpha)
{
    root = tail = nullptr;
    nodeCount = 0;
    newmessage = "";
    path = "";

    alphabet.resize(alpha.size());

    int x = 0;
    for (int i = 0; i < alphabet.size(); i++)
    {   
        if (alpha[x] == 92 && alpha[x + 1] != 92)
        {
            if(alpha[x+1] == 't')
                alphabet[i].ch = 9;
            else if(alpha[x+1] == 'n')
                alphabet[i].ch = 10;
            else if(alpha[x+1] == 's')
                alphabet[i].ch = 32;
            
            x++;
            alphabet.resize(alphabet.size() - 1);
        }
        else
            alphabet[i].ch = alpha[x];
        
        x++;
    }
}

Tree::~Tree()
{
    for (int i = 0; i < list.size(); i++)
    {
        delete list[i];
    }
}

int Tree::valid_char(char ch)
{
    for(int i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i].ch == ch)
            return i;
    }
    return -1;
}

void Tree::encode(string& message)
{
    path = "";

    int i = valid_char(message.at(0));
    if (i == -1) 
    {
        stringstream error;
        error << "Invalid message. " << message.at(0) <<  " is not in the alphabet.";
        throw error.str();
    }
    if (root == nullptr) //empty tree
    {
        // write 1s and 0s to newmessage
        newmessage.append(toBinary(message.at(0)));

        Node* newnode = new Node(message.at(0));
        Node* newroot = new Node();
        Node* newtail = new Node();

        root = newroot;
        tail = newtail;
        alphabet[i].node = newnode;

        newnode->parent = root;
        tail->parent = root;

        root->left = tail;
        root->right = newnode;

        nodeCount = 3;
        newnode->count++;
        root->count++;

        // manage list
        list.push_back(root);
        list.push_back(newnode);
        list.push_back(tail);
    }
    else if (alphabet[i].node == nullptr) // first time seeing char
    {
        // write 1s and 0s to newmessage
        pathFinder(root, 0);
        newmessage.append(path);
        path = "";
        newmessage.append(toBinary(message.at(0)));

        Node* newnode = new Node(message.at(0));
        Node* newtail = new Node();

        alphabet[i].node = newnode;
        
        newnode->parent = tail;
        newtail->parent = tail;

        tail->left = newtail;
        tail->right = newnode;

        tail = newtail;

        nodeCount += 2;
        newnode->count++;
        newnode->parent->count++;

        // manage list
        list.push_back(newnode);
        list.push_back(newtail);

        remidiate(newnode->parent);
    }
    else // seen the node, increment
    {
        // write 1s and 0s to newmessage   
        pathFinder(root, message.at(0));
        newmessage.append(path);
        path = "";

        alphabet[i].node->count++;
        remidiate(alphabet[i].node);
    }

    message.erase(0,1);
    if (!message.empty())
        encode(message);
    else
    {
        message = newmessage;
        testTree();
    }

}

void Tree::decode(string& message)
{
    if (root == nullptr) //empty tree
    {
        // read 1s and 0s
        char ch = toDecimal(message.substr(0,8));
        message.erase(0,8);

        int i = valid_char(ch);
        if (i == -1) 
        {
            stringstream error;
            error << "Invalid message. " << message.at(0) <<  " is not in the alphabet.";
            throw error.str();
        }

        newmessage += ch;

        Node* newnode = new Node(ch);
        Node* newroot = new Node();
        Node* newtail = new Node();

        root = newroot;
        tail = newtail;
        alphabet[i].node = newnode;

        newnode->parent = root;
        tail->parent = root;

        root->left = tail;
        root->right = newnode;

        nodeCount = 3;
        newnode->count++;
        root->count++;

        // manage list
        list.push_back(root);
        list.push_back(newnode);
        list.push_back(tail);
    }
    else
    {
        Node* node = pathTaker(root, message);
        
        if (node == tail) // first time seeing char
        {
            // read 1s and 0s
            char ch = toDecimal(message.substr(0,8));
            message.erase(0,8);

            int i = valid_char(ch);
            if (i == -1) 
            {
                stringstream error;
                error << "Invalid message. " << message.at(0) <<  " is not in the alphabet.";
                throw error.str();
            }

            newmessage += ch;

            Node* newnode = new Node(ch);
            Node* newtail = new Node();

            alphabet[i].node = newnode;
            
            newnode->parent = tail;
            newtail->parent = tail;

            tail->left = newtail;
            tail->right = newnode;

            tail = newtail;

            nodeCount += 2;
            newnode->count++;
            newnode->parent->count++;

            // manage list
            list.push_back(newnode);
            list.push_back(newtail);

            remidiate(newnode->parent);
        }
        else // seen the node, increment
        {   
            newmessage += node->ch;

            node->count++;
            remidiate(node);
        }
    }


    if (!message.empty())
        decode(message);
    else
    {
        message = newmessage;
        message.push_back('\n');
        testTree();
    }

}

void Tree::remidiate(Node* node)
{
    if (node == root)
        return;

    int i = 0;
    for (i = 0; i < list.size() ; i++) //find pos in list
    {
        if (list[i] == node)
            break;
    }

    if (node->count <= list[i - 1]->count)
    {
        node->parent->count++;
        remidiate(node->parent);
    }
    else // find leader and swap
    {
        int x = i - 1;

        while ((list[x]->count) < (list[i]->count))
            x--;

        x++;

        Node* X = list[x];
        Node* I = list[i];
        Node* IP = list[i]->parent;
        Node* XP = list[x]->parent;


        if (XP == IP)
        {
            IP->right = I;
            XP->left = X;
        }
        else
        {
            I->parent = XP;
            X->parent = IP;

            IP->left = (IP->left == I) ? X : IP->left;
            XP->left = (XP->left == X) ? I : XP->left;

            IP->right = (IP->right == I) ? X : IP->right;
            XP->right = (XP->right == X) ? I : XP->right;
        }

        list[x] = I;
        list[i] = X;

        node->parent->count++;
        remidiate(node->parent);
    }
}

string Tree::toBinary(int ch)
{
    string value = "";
    stringstream yikes;
    int val = 0;

    for (int i = 7; i >= 0; i--)
    {
        val = ch/(pow(2,i));
        if (val)
            ch = ch - (pow(2,i));
        yikes << val;
    }
    value.append(yikes.str());

    return value;
}

int Tree::toDecimal(string bin)
{
    int val = 0;

    for (int i = 0; i < 8; i++)
    {
        val += (bin.back() - '0')*(pow(2,i));
        bin.pop_back();
    }

    return val;
}

int Tree::pathFinder(Node* node, int num)
//default case finds 0 node. otherwise finds path to char.
{
    if (!node)
        return 0;
    else if((node->ch == num && node->ch) || (node == tail && node->ch == num ))
        return 1;

    path.append("0");
    if (pathFinder(node->left, num))
        return 1;

    path.pop_back();
    path.append("1");

    if (pathFinder(node->right, num))
        return 1;

    path.pop_back();
    return 0;
}

Tree::Node* Tree::pathTaker(Node* node, string& message)
{
    if(!node->right && !node->left)
    {
        return node;
    }

    if (message.empty()) 
    {
        stringstream error;
        error << "Message is too short to decode further.";
        throw error.str();
    }

    int way = message.at(0) - '0';
    message.erase(0,1);

    if (way)
    {
        return pathTaker(node->right, message);
    }
    else
    {
        return pathTaker(node->left, message);
    }
}

void Tree::testTree()
{
    vector<char> seen('\0');
    //test tree and list.
    for (int i = 0; i < list.size() - 1; i++)
    {
        //check queue
        if (list[i]->count < list[i+1]->count)
            cout << "1. error in list at " << i << endl;

        //check alphabet pointing to correct node
        if (list[i]->ch != 0)
        {
            int x = valid_char(list[i]->ch);
            if (list[i] != alphabet[x].node)
                cout << "2. error in list at " << i << endl;

            for (int y = 0; y < seen.size(); y++)
            {
                if (seen[y] == list[i]->ch)
                    cout << "2.5 error in tree with" << list[i]->ch << endl;
            }
            seen.push_back(list[i]->ch);

        }
        if (list[i] != root)
        {
            //check tree pointers
            if (list[i]->parent->left != list[i] && list[i]->parent->right != list[i])
                cout << "3. error in tree at " << i << endl;
            
        }
    }

    if (root != list[0])
        cout << "root error" << endl;
    if (tail != list[list.size() - 1])
        cout << "tail error" << endl;

    cout << "characters seen: " << seen.size() << endl;
    cout << "tree size " << nodeCount << endl;
    cout << "list size " << list.size() << endl;
    cout << "alphabet size " << alphabet.size() << endl;

}
