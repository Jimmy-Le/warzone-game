// Map.h
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

//Forward declarations
class Player;
class Continent;
class Map;

/**
 * Territory class represents a node in the map graph
 * Each territory has a name, owner(owned by which player), armies (how many), continent, and adjacent territories
 */
class Territory{
    private:
        string* name;
        Player* owner;
        int* armies;
        Continent* continent;
        vector<Territory*>* adjacentTerritories;

    public:
        //Constructors and destructor
        Territory();
        Territory(const string& name);
        Territory(const Territory& other);
        ~Territory(); //Destructor

        // Assignment operator
        Territory& operator=(const Territory& other);

        // Stream insertion operator
        friend ostream& operator<<(ostream& os, const Territory& territory);

        // Getters
        string getName() const;
        Player* getOwner() const;
        int getArmies() const;
        Continent* getContinent() const;
        vector<Territory*>* getAdjacentTerritories() const;

        // Setters
        void setName(const std::string& name);
        void setOwner(Player* owner);
        void setArmies(int armies);
        void setContinent(Continent* continent);

        // Territory operations
        void addAdjacentTerritory(Territory* territory);
        bool isAdjacent(Territory* territory) const;

};

/**
 * Continent class represents a connected subgraph of territories
 * Each continent has a name, bonus armies, and a collection of territories
 */
class Continent {
    private:
        string* name;
        int* bonusArmies;
        vector<Territory*>* territories;

    public:
        // Constructors and destructor
        Continent();
        Continent(const string& name, int bonus);
        Continent(const Continent& other);
        ~Continent();//Destructor

        // Assignment operator
        Continent& operator=(const Continent& other);

        // Stream insertion operator
        friend ostream& operator<<(std::ostream& os, const Continent& continent);

        // Getters
        string getName() const;
        int getBonusArmies() const;
        vector<Territory*>* getTerritories() const;

        // Setters
        void setName(const string& name);
        void setBonusArmies(int bonus);

        // Continent operations
        void addTerritory(Territory* territory);
        bool isConnected() const;
    
};

/**
 * Map class represents the complete game map as a connected graph
 * Contains territories, continents, and validation methods
 */
class Map{
    private:
        vector<Territory*>* territories;
        vector<Continent*>* continents;

    public:
        // Constructors and destructor
        Map();
        Map(const Map& other);
        ~Map();//Destructor

        // Assignment operator
        Map& operator=(const Map& other);

        // Stream insertion operator
        friend ostream& operator<<(ostream& os, const Map& map);

        // Getters
        vector<Territory*>* getTerritories() const;
        vector<Continent*>* getContinents() const;

        // Map operations
        void addTerritory(Territory* territory);
        void addContinent(Continent* continent);
        Territory* getTerritory(const string& name) const;
        Continent* getContinent(const string& name) const;

        // Validation methods
        bool validate() const;
        bool isConnectedGraph() const; 
        bool areContinentsConnected() const;
        bool isEachTerritoryInOneContinent() const;

};

/**
 * MapLoader class handles loading map files and creating Map objects as graph data structure. 
 * Can read Conquest format .map files and validate them
 * Should be able to read any text file (even invaild ones)
 */

class MapLoader{
    private:
        string* fileName;

        // Helper methods for parsing
        vector<string> split(const string& str, char delimiter) const;
        string trim(const string& str) const;
        bool isValidMapSection(const string& line) const;

    public:
        // Constructors and destructor
        MapLoader();
        MapLoader(const string& fileName);
        MapLoader(const MapLoader& other);
        ~MapLoader();

        // Assignment operator
        MapLoader& operator=(const MapLoader& other);

        // Stream insertion operator
        friend ostream& operator<<(ostream& os, const MapLoader& loader);

        // Getters
        string getFileName() const;

        // Setters
        void setFileName(const string& fileName);

        // Map loading operations
        Map* loadMap() const;
        Map* loadMap(const string& fileName) const;
        bool isValidMapFile(const string& fileName) const;
};

#endif