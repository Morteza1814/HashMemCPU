#include <iostream>
#include <fstream>
// #include <nlohmann/json.hpp>
#include "include/nlohmann/json.hpp"
#include <chrono>
#include "ContainerInterface.h"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

void measureMap(json inputJson, json queryJson)
{
    // using ContainerType = MapContainer<int, int>;
    // ContainerType map;
    using ContainerType = HopscotchMapContainer<int, int>;
    ContainerType map;
    // Insert items
    auto start = high_resolution_clock::now();
    for(size_t key=1; key < inputJson.size(); key++){
        // Read from JSON structure
        string str = to_string(key); 
        // Insert into the plain map
        map.insert(key, inputJson[str]);
    }
    auto stop = high_resolution_clock::now();
    seconds timeTakenToLoadTheMap = duration_cast<seconds>(stop - start);
    cout << "Time taken to load the map = " << timeTakenToLoadTheMap.count() << " seconds \n";
    // Measure lookup time
    auto lookupStart = high_resolution_clock::now();
    for(size_t i=1; i < queryJson.size(); i++){
        string str = to_string(i);
        int val;
        map.measureLookupTime(queryJson[str], val);
    }
    auto lookupStop = high_resolution_clock::now();
    seconds timeTakenToLookupTheMap = duration_cast<seconds>(lookupStop - lookupStart);
    cout << "Time taken to lookup the map = " << timeTakenToLookupTheMap.count() << " seconds \n";
}

int main(int argc, char** argv) {
    //read the json from the input
    string inputFileAddress = argv[1];
    string queryFileAddress = argv[2];
    ifstream inFile(inputFileAddress), queryFile(queryFileAddress);
    if (!inFile || !queryFile) {
        throw std::runtime_error("Failed to open the query file.");
    }
    json inputJson, queryJson;
    auto start = high_resolution_clock::now();
    inFile >> inputJson;
    auto stop = high_resolution_clock::now();
    inFile.close();
    seconds timeTaken= duration_cast<seconds>(stop - start);
    cout << "Time taken to read JSON file = " << timeTaken.count() << " seconds \n";
    //read query file
    queryFile >> queryJson;
    queryFile.close();
    // ContainerWrapper<int, string, ContainerType> wrapper;
    
    measureMap(inputJson, queryJson);
    return 0;
}
