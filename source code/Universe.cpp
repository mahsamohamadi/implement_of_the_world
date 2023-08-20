#include "Universe.h"

Universe::Universe()
{
}


void Universe::addGalaxy(Galaxy* galaxy)//Adds a Galaxy object to the Universe.
{
    galaxies.push_back(galaxy);
}

bool Universe::isGalaxy(int id)//Check if a given ID corresponds to a galaxy in the universe.
{
    for(Galaxy* g : galaxies)
    {
        if(g->get_idgalaxy() == id)
        {
            return true;//if the ID corresponds to a galaxy
        }
    }
    return false;//otherwise
}

Galaxy* Universe::get_galaxy(int id) //Retrieves the Galaxy object with the specified ID.
{
    for(Galaxy* g : galaxies)
    {
        if(g->get_idgalaxy() == id)
        {
            return g;//return a pointer to the Galaxy object with the specified ID.
        }

    }

}


void Universe::FindShortestPathBetweenGalaxies(Galaxy* galaxy1, Galaxy* galaxy2, const int node1, const int node2)
{
    galaxy1->create_pathTable();  //Create a path table for galaxy1
    galaxy2->create_pathTable();  //Create a path table for galaxy2

    int gateway_id = INT_MAX;   //id the gateway between galaxies
    int gateway_cost = INT_MAX;  //cost the gateway between galaxies
    int dest;  //BG node in the destination galaxy

    for (const auto& outer_pair : galaxy1->adj_list) {
        int gateway = outer_pair.first;
        
        for (const auto& inner_pair : outer_pair.second) {
            
            if (inner_pair.first == galaxy2->get_idgalaxy()) {
                //Access and scroll through the Edge* list
                for (const auto& edge : inner_pair.second) {
                    
                    int cost = edge->getCost();  //Link cost between galaxies
                    
                    if (cost < gateway_cost) {   //If the cost is less than the current gate cost
                        gateway_cost = cost;     //Gateway cost change 
                        gateway_id = gateway;    //Gateway id change
                        dest = galaxy2->get_idnode(edge->get_dest());
                    }
                
                    
                }
            }
        }
    }

    if (gateway_id == INT_MAX) { // If no way is found between the galaxies
        cout << "No path found between " << galaxy1->get_name(node1) << " and " << galaxy2->get_name(node2) << endl;
        return;
    }

    int cost= galaxy1->path_table[node1][ gateway_id];  //path cost in galaxy1
    galaxy1->dijkstra(node1, gateway_id);          //The shortest path in galaxy1
    cost += gateway_cost;                          //The cost of the path between two galaxies
    cost += galaxy2->path_table[dest][node2];      //path cost in galaxy2
    galaxy2->dijkstra(dest, node2);               //The shortest path in galaxy2

    while (!galaxy1->nodepath.empty()) {         //Print the path in the origin galaxy
        int topElement = galaxy1->nodepath.top();  // Get the top element of the stack
        cout << galaxy1->get_name(topElement) ;  // Print the top element of the stack
        galaxy1->nodepath.pop();  // Remove the top element from the stack
        if( !galaxy1->nodepath.empty())
        {
            cout << " -> ";
        }

    }
    cout << " --> ";
    while (!galaxy2->nodepath.empty()) {         //Print the path in the destination galaxy
        int topElement = galaxy2->nodepath.top();  // Get the top element of the stack
        cout << galaxy2->get_name(topElement) ;  // Print the top element of the stack
        galaxy2->nodepath.pop();  // Remove the top element from the stack
        if( !galaxy2->nodepath.empty())
        {
            cout << " -> ";
        }

    }

    cout << " : " << cost <<endl;  // print path cost

}
