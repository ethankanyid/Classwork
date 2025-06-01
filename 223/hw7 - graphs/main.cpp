#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "graph_matrix.h"

using namespace std;

string readMatrix(string filename, GraphMatrix<char>* graph);
/* returns a string containing the identifiers for the nodes of the matrix */

string djikstra(const string nodes, GraphMatrix<char>* graph);
/* performs djikstras algorithim on a graph matrix with weighted directional connections*/

class Node
{
    public:
    
    char ch;
    char from;
    int pathWeight;
    bool visited;

    Node()
    {
        ch = from = 0;
        pathWeight = 0;
        visited = false;
    }
};

int main(const int argc, const char* argv[])
{
    if (argc != 2)
    {
        cout << "Call function with matrix file." << endl;
        return 1;
    }

    GraphMatrix<char>* graph = new GraphMatrix<char>;

    string temp = readMatrix(argv[1], graph);

    if(temp == "")
        return 1;


    temp = djikstra(temp, graph);

    if(temp == "")
        return 1;

    cout << temp;

    return 0;
}

string readMatrix(string filename, GraphMatrix<char>* graph)
{
    string temp = "";
    string nodes = "";
    int nodecount = 0;
    stringstream parser;

    fstream file(filename);

    if (!file.is_open())
    {
        cout << "Improper file name." << endl;
        return "";
    }

    //get nodes
    getline(file, nodes);
    for (int i = 0; i < nodes.size(); i++)
    {
        char ch = nodes[i];
        graph->addNode(ch);
        nodecount = i + 1;
    }

    int row = 0;
    int column = 0;

    while(getline(file,temp))
    {
        column = 0;
        parser.clear();
        parser.str(temp);

        //get connections
        while(getline(parser, temp, ' '))
        {
            if (column > nodecount - 1)
            {
                cout << "Improper Columns for Matrix at row " << row << " and column " << column << "." << endl;
                return "";
            }

            graph->addLink(row, column, stoi(temp));
            
            column++;
        }

        if (row > nodecount - 1)
        {
            cout << "Improper Rows for Matrix at row " << row << " and column " << column << "." << endl;
            return "";
        }
        row++;
    }
    file.close();
    
    cout << "Adjacency Matrix: " << endl; 
    for (int i = 0; i < nodecount; i ++)
    {
        cout << nodes[i] << " ";
    }
    cout << endl;
    graph->printAdjacencyMatrix();

    return nodes;
}

string djikstra(const string nodes, GraphMatrix<char>* graph)
{
    int nodecount = nodes.size();
    char node = 0;

    cout << "Enter a node to start Djikstras algorithim (";
    for (int i = 0; i < nodecount - 1; i ++)
    {
        cout << nodes[i] << ",";
    }
    cout << nodes[nodecount - 1] << "): ";
    cin >> node;

    if (nodes[0] == tolower(nodes[0]))
        node = tolower(node);
    else
        node = toupper(node);

    bool validNode = false;
    for (int i = 0; i < nodecount; i ++)
    {
        if(node == nodes[i])
            validNode = true;
    }

    if(!validNode)
    {
        cout << "Invalid Node." << endl;
        return "";
    }
    

    vector<Node> unvisited(nodecount);
    for (int i = 0; i < nodecount; i++)
    {
        unvisited[i].ch = nodes[i];
    }

    int start = graph->getNodeIndex(node);
    int current = start; 
    int weight = 0;
    int minIndex = 0;
    bool Unvisited = true;

    unvisited[current].visited = true;
    unvisited[current].from = unvisited[current].ch;
    unvisited[current].pathWeight = 0;

    while(Unvisited)
    {
        for (int index = 0; index < nodecount; index++)
        {
            if (!unvisited[index].visited)
            {
                if (graph->getLink(current, index))
                    weight = graph->getLink(current, index) + unvisited[current].pathWeight;

                if (weight)
                {
                    if (weight < unvisited[index].pathWeight || !unvisited[index].pathWeight)
                    {
                        unvisited[index].pathWeight = weight;
                        unvisited[index].from = unvisited[current].ch;
                    }
                }
                weight = 0;
            }
        }
        minIndex = -1;
        for(int i = 0; i < nodecount; i++)
        {
            if (!unvisited[i].visited && unvisited[i].pathWeight)
            {
                minIndex = ((minIndex == -1) || (unvisited[i].pathWeight < unvisited[minIndex].pathWeight)) ? i : minIndex;
            }
        }

        if (minIndex != -1)
        {
            unvisited[minIndex].visited = true;
            current = minIndex;
        }
        else
            Unvisited = false;
    }

    stringstream toreturn;

    toreturn << "Starting from '" << node << "' the shortest paths are: " << endl;

    for(int i = 0; i < nodecount - 1; i++)
    {
        if (unvisited[i].pathWeight == 0 && i != start)
            toreturn << unvisited[i].ch << ": INF(" << unvisited[i].from << "), ";
        else
            toreturn << unvisited[i].ch << ": " << unvisited[i].pathWeight << "(" << unvisited[i].from << "), ";
    }
    if (unvisited[nodecount - 1].pathWeight == 0 && nodecount - 1 != start)
        toreturn << unvisited[nodecount - 1].ch << ": INF(" << unvisited[nodecount - 1].from << ") " << endl;
    else
        toreturn << unvisited[nodecount - 1].ch << ": " << unvisited[nodecount - 1].pathWeight << "(" << unvisited[nodecount - 1].from << ") " << endl;

    return toreturn.str();
}
