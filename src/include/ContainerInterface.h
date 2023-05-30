#include <iostream>
#include <chrono>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> // for find
#include <type_traits>
#include "tsl/hopscotch_map.h"

using namespace std;
// Base Container interface
template <typename Key, typename Value>
class ContainerInterface {
public:
    ContainerInterface(){}
    virtual chrono::nanoseconds insert(const Key& key, const Value& value) = 0;
    virtual const Value& get(const Key& key) const = 0;
    virtual chrono::nanoseconds probeKey(const Key& key, Value &value) const = 0;
    virtual ~ContainerInterface() {}
    virtual const std::string& getString() const = 0;
};


// Container class for hopscotchmap
template <typename Key, typename Value>
class HopscotchMapContainer : public ContainerInterface<Key, Value> {
    tsl::hopscotch_map <Key, Value> container_;
    string containerName;
public:
    HopscotchMapContainer(){containerName = "HopscotchMap";}
    chrono::nanoseconds insert(const Key& key, const Value& value) override {
        auto start = chrono::high_resolution_clock::now();
        container_[key] = value;
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration;
    }

    const Value& get(const Key& key) const override {
        return container_.at(key);
    }

    chrono::nanoseconds probeKey(const Key& key, Value& value) const override {
        auto start = chrono::high_resolution_clock::now();
        value = container_.at(key);
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration;
    }

    const std::string& getString() const override {
        return containerName;
    }
};

// Container class for map
template <typename Key, typename Value>
class MapContainer : public ContainerInterface<Key, Value> {
    map<Key, Value> container_;
    string containerName;
public:
    MapContainer(){containerName = "Map";}
    chrono::nanoseconds insert(const Key& key, const Value& value) override {
        auto start = chrono::high_resolution_clock::now();
        container_[key] = value;
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration;
    }

    const Value& get(const Key& key) const override {
        return container_.at(key);
    }

    chrono::nanoseconds probeKey(const Key& key, Value& value) const override {
        auto start = chrono::high_resolution_clock::now();
        value = container_.at(key);
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration;
    }

    const std::string& getString() const override {
        return containerName;
    }
};

// Container class for unordered_map
template <typename Key, typename Value>
class UnorderedMapContainer : public ContainerInterface<Key, Value> {
    unordered_map<Key, Value> container_;
    string containerName;
public:
    UnorderedMapContainer(){containerName = "UnorderedMap";}
    chrono::nanoseconds insert(const Key& key, const Value& value) override {
        auto start = chrono::high_resolution_clock::now();
        container_[key] = value;
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration;
    }

    const Value& get(const Key& key) const override {
        return container_.at(key);
    }

    chrono::nanoseconds probeKey(const Key& key, Value& value) const override {
        auto start = chrono::high_resolution_clock::now();
        value = container_.at(key);
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration;
    }

    const std::string& getString() const override {
        return containerName;
    }
};

// Container class for multimap
template <typename Key, typename Value>
class MultiMapContainer : public ContainerInterface<Key, Value> {
    multimap<Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_.emplace(key, value);
    }

    const Value& get(const Key& key) const override {
        auto range = container_.equal_range(key);
        auto it = find_if(range.first, range.second,
                               [&](const pair<Key, Value>& pair) {
                                   return pair.first == key;
                               });

        if (it != range.second)
            return it->second;

        throw out_of_range("Key not found in CustomMultiMapContainer");
    }

    chrono::microseconds probeKey(const Key& key) const override {
        auto start = chrono::high_resolution_clock::now();
        get(key);
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start);
    }
};

// Container class for unordered_multimap
template <typename Key, typename Value>
class UnorderedMultiMapContainer : public ContainerInterface<Key, Value> {
    unordered_multimap<Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_.emplace(key, value);
    }

    const Value& get(const Key& key) const override {
        auto range = container_.equal_range(key);
        auto it = find_if(range.first, range.second,
                               [&](const pair<Key, Value>& pair) {
                                   return pair.first == key;
                               });

        if (it != range.second)
            return it->second;

        throw out_of_range("Key not found in CustomUnorderedMultiMapContainer");
    }

    chrono::microseconds probeKey(const Key& key) const override {
        auto start = chrono::high_resolution_clock::now();
        get(key);
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start);
    }
};

// Container class for queue
template <typename Value>
class QueueContainer : public ContainerInterface<int, Value> {
    queue<Value> container_;

public:
    void insert(const int& /* key */, const Value& value) override {
        container_.push(value);
    }

    const Value& get(const int& /* key */) const override {
        if (!container_.empty())
            return container_.front();

        throw out_of_range("Queue is empty in CustomQueueContainer");
    }

    chrono::microseconds probeKey(const int& /* key */) const override {
        auto start = chrono::high_resolution_clock::now();
        get(0);
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start);
    }
};

// Container class for list
template <typename Value>
class ListContainer : public ContainerInterface<int, Value> {
    list<Value> container_;

public:
    void insert(const int& /* key */, const Value& value) override {
        container_.push_back(value);
    }

    const Value& get(const int& /* key */) const override {
        if (!container_.empty())
            return container_.front();

        throw out_of_range("List is empty in CustomListContainer");
    }

    chrono::microseconds probeKey(const int& /* key */) const override {
        auto start = chrono::high_resolution_clock::now();
        get(0);
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start);
    }
};


// Container class for vector
template <typename Value>
class VectorContainer : public ContainerInterface<int, Value> {
    vector<Value> container_;

public:
    void insert(const int& /* key */, const Value& value) override {
        container_.push_back(value);
    }

    const Value& get(const int& /* key */) const override {
        if (!container_.empty())
            return container_.front();

        throw out_of_range("Vector is empty in CustomVectorContainer");
    }

    chrono::microseconds probeKey(const int& /* key */) const override {
        auto start = chrono::high_resolution_clock::now();
        get(0);
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start);
    }
};