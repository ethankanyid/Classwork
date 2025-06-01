#pragma once
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

//adaptive huffman tree
class Tree
{
    //private class
    class Node
    {
    public:
        Node* parent;
        Node* left;
        Node* right;

        char ch;
        int count;

        Node(char item = '\0') 
        { 
            ch = item;
            parent = left = right = nullptr;
            count = 0;
        }
    };
    
    class CharArray
    {
        public:
        char ch;
        Node* node;

        CharArray()
        {
            ch = '\0';
            node = nullptr;
        }
    };
    
    //private methods
    void remidiate(Node* node);
    int valid_char(char ch);
    string toBinary(int ch);
    int toDecimal(string bin);
    int pathFinder(Node* node, int num = 0);
    Node* pathTaker(Node* node, string &message);

    //private members
    Node* root;
    Node* tail;
    int nodeCount;
    vector<CharArray> alphabet;
    vector<Node*> list;
    string newmessage;
    string path;

    public:
    // The constructor takes the alphabet as parameter
    Tree(const string alpha);
    ~Tree();

    void encode(string& message);
    void decode(string& message);

    void testTree();

};
