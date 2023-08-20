#include "Galaxy.h"

void Galaxy::addNode(Node* node)//Adds a node to the Galaxy
{
    nodes.push_back(node);
}


Galaxy::Galaxy(int id)//Constructor
{
    id_galaxy = id;
}

int Galaxy::get_idgalaxy()//Returns the ID of the galaxy.
{
    return id_galaxy;

}

void Galaxy::is_node(string name , int id )//Checks if a node with the given name and id exists in this galaxy.
{
    for(Node* n : nodes)
    {
        if( n->get_name() == name && n->get_id() == id)
        {
            throw "There is a node with this name and id in this galaxy";
        }
        if(n->get_name() == name)
        {
            throw "There is a node with this name in this galaxy";
        }

        if(n->get_id() == id)
        {
            throw "There is a node with this id in this galaxy";
        }
    }


}


void Galaxy::addEdge(string nameNode, int id_galaxy, Edge* edge)
{
    for(auto n: nodes)
    {
        if(n->get_name() == nameNode && this->id_galaxy == id_galaxy)   // destination node is in this galaxy
        {
            adjacencyList[n->get_id()].push_back(edge);
        }
        else if(n->get_name() == nameNode && this->id_galaxy != id_galaxy)  // destination node is not in this galaxy
        {
            adj_list[n->get_id()][id_galaxy].push_back(edge);
        }
    }
    
}

void Galaxy::create_pathTable()   //Create a routing table
{    
    int numNodes = nodes.size();
    for(int n=0 ; n < numNodes ; n++)           //Perform the routing algorithm for all nodes of the galaxy
    {
        for(int i=0 ; i < numNodes ; i++)
        {   
            dijkstra( nodes[n]->get_id() , nodes[i]->get_id());
        }

    }
    
    
}

Node* Galaxy::get_node(string name)//Returns a node with the given name
{
    for(Node* n : nodes)
    {
        if(n->get_name() == name)
        {
            return n;
        }
    }
}

int Galaxy::get_idnode(string name)  //Returning the node ID by getting the node name
{
    for(auto n:nodes)
    {
        if(n->get_name() == name)
        {
            return n->get_id();
        }
    }
}

void Galaxy::dijkstra( int source, int destination)
{
    unordered_map<int, int> distance;  // To store the destination of each node
    unordered_map<int, bool> visited; // To store the visiting status of each node
    unordered_map<int, int> parent;

    // Initial value of distance equal to infinity and visit status equal to false
    for (auto& pair : adjacencyList) {
        distance[pair.first] = INT_MAX;
        visited[pair.first] = false;
        parent[pair.first] = -1;
    }
    
    stack<int> nodespath;
    // The initial distance value for the starting node is zero
    distance[source] = 0;
    nodespath.push(source);
    // Finding the shortest path using Dijkstra's algorithm
    for (int i = 0; i < adjacencyList.size(); i++) {
        int minDistance = INT_MAX;
        int minNode;
 
        // Finding the node that has the closest path to it in the current phase
        for (auto& pair : adjacencyList) {
            int node = pair.first;
            int dist = distance[node];
 
            if (!visited[node] && dist <= minDistance) {
                minDistance = dist;
                minNode = node;
            }
        }
 
        // Visiting a node to remove it from the list of open nodes
        visited[minNode] = true;
 
        // Updating the distances of neighboring nodes
        for (auto& edge : adjacencyList[minNode]) {
            int dest = get_idnode(edge->get_dest());
            int weight = edge->getCost();
 
            if (!visited[dest] && distance[minNode] != INT_MAX && distance[minNode] + weight < distance[dest])
            {
                distance[dest] = distance[minNode] + weight;
                parent[dest] = minNode;
            }
        }
    }
    //Cost storage in the path table
    path_table[source][destination] = distance[destination];

    stack<int> path;   //Save nodes in the path
    int current = destination;
    while (current != -1) {
        path.push(current);      //Save nodes in stack
        current = parent[current];
    }
    nodepath = path;
 
}

void Galaxy::find_path(int source , int dest)
{
    create_pathTable();        //Create a path table
    dijkstra(source, dest);   //Performing Dijkstra's algorithm for two nodes

    while (!nodepath.empty()) {
        int topElement = nodepath.top();  // Get the top element of the stack
        cout << get_name(topElement) ;  // Print the top element of the stack
        nodepath.pop();  // Remove the top element from the stack
        if( !nodepath.empty())
        {
            cout << " -> ";
        }
        else
        {
            cout << " : ";
        }
    }
    cout << path_table[source][dest] << endl;   //Print path cost

}

string Galaxy::get_name(int id)    //Returning the node name by getting the node id
{
    for(auto n:nodes)
    {
        if(n->get_id() == id)
        {
            return n->get_name();
        }
    }
}

bool Galaxy::isNode(string name)   //Check the exist of node in the galaxy
{
    for(auto n:nodes)
    {
        if(n->get_name() == name)
        {
            return true;
        }
    }
    return false;
}

