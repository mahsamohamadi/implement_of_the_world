
#include <iostream>
#include <regex>
#include <string>
#include "Node.h"
#include "Edge.h"
#include "Universe.h"
#include "Galaxy.h"

using namespace std;

int main() 
{
    Universe universe;      //create universe

    string command;

    while (command != "Exit")
    {
        getline(cin , command);       //Getting input

        // Pattern for create node command      exp:   CREATE (A: Node, {id: '1', Type: 'BG', Galaxy: 'AS1'})
        regex create_node_pattern(R"(CREATE\s*\(\s*(\w+)\s*:\s*Node,\s*\{\s*id\s*:\s*'(\d+)'\s*,\s*Type\s*:\s*'(\w+)'\s*,\s*Galaxy\s*:\s*'AS(\d+)'\s*\}\))");

        // Pattern for edge creation command     exp:  CREATE (A.AS1) – [:ROAD {cost:50}] –> (B.AS1)
        regex create_road_pattern(R"(CREATE\s*\(\s*(\w+).AS(\d+)\s*\)\s*-\s*\[\s*:\s*ROAD\s*\{\s*cost\s*:\s*(\d+)\s*\}\s*\]\s*->\s*\(\s*(\w+).AS(\d+)\s*\))");

        // Path finding patterns    exp:  FIND AS4.W->AS4.X
        regex path_find_pattern(R"(FIND\s*AS(\d+).(\w+)\s*->\s*AS(\d+).(\w+))");


        smatch matches;

        if (regex_search(command, matches, create_node_pattern))   // create node
        {
            string name_node = matches[1].str();    //save name node
            int id = stoi(matches[2]);               // save id node
            string type = matches[3].str();          // save type node
            int id_galaxy = stoi( matches[4] );      // save galaxy node

            if( universe.isGalaxy(id_galaxy))   //There is galaxy with this ID
            {
                Galaxy* galaxy = universe.get_galaxy(id_galaxy);
                try 
                {
                    galaxy->is_node(name_node , id );      //Checking name and ID node
                    Node* newnode = new Node(name_node , id , type , id_galaxy);    //Create a node with the given information
                    galaxy->addNode(newnode);                //Add the created node to the galaxy
                }
                catch(const char* message)
                {                                      //Display a message if this node exists in the galaxy
                    cout << message << endl;
                }
            }
            else                              //There is no galaxy with this ID
            {
                Galaxy* galaxy = new Galaxy(id_galaxy);   //Creation of the galaxy
                universe.addGalaxy(galaxy);               //Add galaxy to the universe
                Node* newnode = new Node(name_node , id , type , id_galaxy);     //Create a node with the given information
                galaxy->addNode(newnode);            //Add the created node to the galaxy
            }


        }
        else if (regex_search(command, matches, create_road_pattern))  // create edge
        {
            string node1 = matches[1].str();
            int galaxy_node1 = stoi( matches[2]);
            int cost = stoi(matches[3]);
            string node2 = matches[4].str();
            int galaxy_node2 = stoi( matches[5]);

            if(cost > 0)   //Checking the validity of the cost
            {
                Edge* edge1 =new Edge(cost, node2);     //Create a edge for the node1
                Edge* edge2 = new Edge(cost, node1);     //Create a edge for the node1

                if (galaxy_node1 == galaxy_node2)          //Both nodes are in the same galaxy
                {
                    Galaxy* galaxy1 = universe.get_galaxy(galaxy_node1);   //Creating a galaxy including both nodes
                    galaxy1->addEdge(node1, galaxy_node2, edge1);   //Add edge to node1 
                    galaxy1->addEdge(node2, galaxy_node1, edge2);    //Add edge to node2
                }
                else
                {
                    Galaxy* galaxy1 = universe.get_galaxy(galaxy_node1);   //Creating  galaxy1 including Node1
                    Galaxy* galaxy2 = universe.get_galaxy(galaxy_node2);    //Creating  galaxy2 including Node2

                    galaxy1->addEdge(node1, galaxy_node2, edge1);    //Add edge to node1 in galaxy1
                    galaxy2->addEdge(node2, galaxy_node1, edge2);    //Add edge to node2 in galaxy2

                }
            }
            else
            {
                cout << "Invalid Edge cost!" << endl; 
            }


        }
        else if (regex_search(command, matches, path_find_pattern))  // find path
        {
            int galaxy_node1 = stoi( matches[1]);
            string node1 = matches[2].str();
            int galaxy_node2 = stoi( matches[3]);
            string node2 = matches[4].str();

            if( universe.isGalaxy(galaxy_node1) && universe.isGalaxy(galaxy_node2))    //Validity check of both galaxies
            {
                Galaxy* galaxy1 = universe.get_galaxy(galaxy_node1);     //Creating  galaxy1 including Node1
                Galaxy* galaxy2 = universe.get_galaxy(galaxy_node2);     //Creating  galaxy2 including Node2

                if(galaxy1->isNode(node1) && galaxy2->isNode(node2))    //Checking the presence of nodes
                {
                    if( galaxy1 == galaxy2 )     //Check if the galaxy is one
                    {
                        galaxy1->find_path( galaxy1->get_idnode(node1) , galaxy1->get_idnode(node2) );   //Perform routing between two nodes
                    }
                    else           //If the nodes were not in the same galaxy
                    {        //Find the shortest path
                        universe.FindShortestPathBetweenGalaxies(galaxy1, galaxy2, galaxy1->get_idnode(node1), galaxy2->get_idnode(node2));
                    }
                }
                else
                {
                    cout << "Invalid node name." << endl;    
                }

            }
            else
            {
                cout << "Invalid galaxy ID." << endl;
            }
            
        }
    }
    

    return 0;
}



