// MapDriver.cpp
#include "Map.h"
#include "MapDriver.h" 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>  

using namespace std;

/**
 * Driver function to test loading and validation of various map files.
 */
void testLoadMaps() {
    cout << "\n========== Map File Loading and Validation ==========\n" << endl;

    // Create MapDriver instance
    MapLoader* loader = new MapLoader();

    // List of test files
    vector<string> testFiles = {
        "Earth.map",
        "Alberta.map"
    };

    // Loop through each file
    for (const string& filename : testFiles) {
        cout << "----------------------------------------" << endl;
        cout << "Testing file: " << filename << endl;

        // Load map using the loader
        Map* loadedMap = loader->loadMap(filename);

        if (loadedMap == nullptr) {
            cout << "Result: Failed to load map from \"" << filename << "\"." << endl;
            cout << "Reason: File missing, corrupt, or invalid format." << endl;
        } else {
            cout << "Result: Successfully loaded map from \"" << filename << "\"" << endl;

            // Run validation tests
            bool isConnected = loadedMap->isConnectedGraph();
            bool continentsConnected = loadedMap->areContinentsConnected();
            bool eachInOneContinent = loadedMap->isEachTerritoryInOneContinent();
            bool isValid = loadedMap->validate();

            cout << "\nValidation Results:" << endl;
            cout << "  1. Map is fully connected: " << (isConnected ? "PASS" : "FAIL") << endl;
            cout << "  2. Continents are connected subgraphs: " << (continentsConnected ? "PASS" : "FAIL") << endl;
            cout << "  3. Each territory is in one continent: " << (eachInOneContinent ? "PASS" : "FAIL") << endl;
            cout << "  => Overall Map Validation: " << (isValid ? "VALID MAP" : "INVALID MAP") << endl;

            if (isValid) {
                cout << "\nMap Details:" << endl;
                cout << "  - Territories: " << loadedMap->getTerritories()->size() << endl;
                cout << "  - Continents: " << loadedMap->getContinents()->size() << endl;
            }

            delete loadedMap;
        }

        cout << endl;
    }

    delete loader;

    cout << "========== Map Testing Complete ==========\n" << endl;
}


