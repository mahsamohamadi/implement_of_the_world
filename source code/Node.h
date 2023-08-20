#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Edge.h"

using namespace std;

class Node
{
private:

    string name;
    int id;
    string type;
    int galaxy;

public:

    Node(string n, int id, string type , int galaxy); //Constructor
    string get_name(); //Returns the name of the node
    int get_id(); //Returns the ID of the node

    
};

#endif // NODE_H

