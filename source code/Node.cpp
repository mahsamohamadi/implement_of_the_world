#include "Node.h"

Node::Node( string name, int id, string type , int galaxy) : name(name) ,id(id), type(type), galaxy(galaxy)
{

}


string Node::get_name()//Returns the name of the node
{
    return name;
}
int Node::get_id()//Returns the ID of the node
{
    return id;
}



