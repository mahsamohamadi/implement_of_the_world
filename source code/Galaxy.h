#ifndef GALAXY_H
#define GALAXY_H

#include <list>
#include <vector>
#include <unordered_map>
#include <climits>
#include <stack>
#include "Node.h"
#include "Edge.h"

using namespace std;

class Galaxy
{
    friend class Universe;
private:
    vector<Node*> nodes;           //Vector to save galaxy nodes
    unordered_map< int ,list<Edge*> > adjacencyList;   //Saving edges within the galaxy
    unordered_map< int, unordered_map< int, list<Edge*>>> adj_list;    //Save edges between two galaxies
    unordered_map< int, unordered_map< int, int>> path_table;    //Routing table
    stack <int> nodepath;  //Save path nodes
    int id_galaxy; 

public:
    
    int get_idgalaxy();             //Returns the ID of the galaxy
    void addNode(Node*);            //Add a node to the galaxy
    void is_node(string , int );   //Checking name and ID node
    Galaxy(int);                    //Constructor
    Node* get_node(string name);    //Returns a node with the given name
    void addEdge(string, int, Edge*);    //Add node to the galaxy
    void create_pathTable();       //Create a routing table
    int get_idnode(string);        //Returning the node ID by getting the node name
    void dijkstra( int , int);   //Perform Dijkstra's algorithm
    void find_path(int, int);    //Finding the shortest path between two nodes in a galaxy
    string get_name(int);       //Returning the node name by getting the node id
    bool isNode(string);        //Check the exist of node in the galaxy
    

};
#endif // GALAXY_H

