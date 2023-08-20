#ifndef UNIVESE_H
#define UNIVESE_H

#include <vector>
#include "Galaxy.h"

using namespace std;

class Universe
{
private:
    vector<Galaxy*> galaxies;   //Vector to save galaxies 
public:

    bool isGalaxy(int );//Check if a given ID corresponds to a galaxy in the universe.
    Galaxy* get_galaxy(int); //Retrieves the Galaxy object with the specified ID.
    Universe();//Constructor
    void addGalaxy(Galaxy*);//Adds a Galaxy object to the Universe.
    void FindShortestPathBetweenGalaxies(Galaxy*, Galaxy*, const int, const int);  //Find the shortest path between two galaxy

};

#endif // UNIVESE_H


