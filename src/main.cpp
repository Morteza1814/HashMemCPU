#include <iostream>
#include <fstream>
// #include <nlohmann/json.hpp>
#include "include/nlohmann/json.hpp"
#include <chrono>
#include "ContainerInterface.h"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

typedef std::chrono::high_resolution_clock Clock;

void measureMap(json inputJson, json queryJson, ContainerInterface<int, int>& container)
{
    cout << "container <<<<<" << container.getString() << ">>>>>>>>>>>>\n";
    // Measure Insert Time
    auto totalInsertTime = std::chrono::nanoseconds::zero();
    auto start = Clock::now();
    // Read from JSON structure and load the container
    for(size_t key=1; key < inputJson.size(); key++){
        string str = to_string(key); 
        int value = inputJson[str];
        // Insert into the plain container
        totalInsertTime += container.insert(key, value);
    }
    auto stop = Clock::now();
    auto timeTakenToLoadTheMap = duration_cast<seconds>(stop - start);
    cout << "Time taken to load the container: " << timeTakenToLoadTheMap.count() << " seconds \n";
    cout << "Total insert time: " << totalInsertTime.count() << " nanoseconds, " << std::chrono::duration<double>(totalInsertTime).count() << " seconds" << endl;

    // Measure Probing Time
    auto totalLookupTime = std::chrono::nanoseconds::zero();
    auto lookupStart = Clock::now();
    for(size_t i=1; i < queryJson.size(); i++){
        string str = to_string(i);
        int val;
        int key = queryJson[str];
        totalLookupTime += container.probeKey(key, val);
        //verify value
        string str1 = to_string(key);
        int value = inputJson[str1];
        if (val != value)
        {
            cout << "the value is incorrect: " << val << " != " << value << endl;
        }   
    }
    auto lookupStop = Clock::now();
    auto timeTakenToLookupTheMap = duration_cast<seconds>(lookupStop - lookupStart);
    cout << "Time taken to lookup the container = " << timeTakenToLookupTheMap.count() << " seconds \n";
    cout << "Total lookup time: " << totalLookupTime.count() << " nanoseconds, " << std::chrono::duration<double>(totalLookupTime).count() << " seconds" << endl;
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
    //compare insert and probing timing of different containers
    HopscotchMapContainer<int, int> hopSchotchMap;
    measureMap(inputJson, queryJson, hopSchotchMap);
    MapContainer<int, int> map;
    measureMap(inputJson, queryJson, map);
    UnorderedMapContainer<int, int> unorderedMap;
    measureMap(inputJson, queryJson, unorderedMap);
    return 0;
}
