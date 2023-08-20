#ifndef EDGE_H
#define EDGE_H

#include <iostream>
using namespace std;

class Edge
{
private:
    int cost;
    string dest;
public:
    Edge(int , string ); //Constructor
    int getCost() const; //return the cost of the Edge
    string get_dest(); //return the destination node
};

#endif // EDGE_H


