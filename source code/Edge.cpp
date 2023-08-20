#include "Edge.h"

//Constructor
Edge:: Edge(int cost , string dest) : cost(cost), dest(dest) 
{
}  

int Edge::getCost() const //return the cost of the Edge
{
     return cost; 
}

string Edge::get_dest()
{
     return dest;
}