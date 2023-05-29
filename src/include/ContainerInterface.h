#include <iostream>
#include <chrono>
#include <map>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <algorithm> // for std::find
#include <type_traits>
#include "tsl/hopscotch_map.h"

// Base Container interface
template <typename Key, typename Value>
class ContainerInterface {
public:
    virtual void insert(const Key& key, const Value& value) = 0;
    virtual const Value& get(const Key& key) const = 0;
    virtual std::chrono::microseconds measureLookupTime(const Key& key, Value &value) const = 0;
    virtual ~ContainerInterface() {}
};


// Container class for hopscotchmap
template <typename Key, typename Value>
class HopscotchMapContainer : public ContainerInterface<Key, Value> {
    tsl::hopscotch_map <Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_[key] = value;
    }

    const Value& get(const Key& key) const override {
        return container_.at(key);
    }

    std::chrono::microseconds measureLookupTime(const Key& key, Value& value) const override {
        auto start = std::chrono::high_resolution_clock::now();
        value = container_.at(key);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};

// Container class for std::map
template <typename Key, typename Value>
class MapContainer : public ContainerInterface<Key, Value> {
    std::map<Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_[key] = value;
    }

    const Value& get(const Key& key) const override {
        return container_.at(key);
    }

    std::chrono::microseconds measureLookupTime(const Key& key, Value& value) const override {
        auto start = std::chrono::high_resolution_clock::now();
        value = container_.at(key);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};

// Container class for std::unordered_map
template <typename Key, typename Value>
class UnorderedMapContainer : public ContainerInterface<Key, Value> {
    std::unordered_map<Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_[key] = value;
    }

    const Value& get(const Key& key) const override {
        return container_.at(key);
    }

    std::chrono::microseconds measureLookupTime(const Key& key, Value& value) const override {
        auto start = std::chrono::high_resolution_clock::now();
        value = container_.at(key);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};

// Container class for std::multimap
template <typename Key, typename Value>
class MultiMapContainer : public ContainerInterface<Key, Value> {
    std::multimap<Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_.emplace(key, value);
    }

    const Value& get(const Key& key) const override {
        auto range = container_.equal_range(key);
        auto it = std::find_if(range.first, range.second,
                               [&](const std::pair<Key, Value>& pair) {
                                   return pair.first == key;
                               });

        if (it != range.second)
            return it->second;

        throw std::out_of_range("Key not found in CustomMultiMapContainer");
    }

    std::chrono::microseconds measureLookupTime(const Key& key) const override {
        auto start = std::chrono::high_resolution_clock::now();
        get(key);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};

// Container class for std::unordered_multimap
template <typename Key, typename Value>
class UnorderedMultiMapContainer : public ContainerInterface<Key, Value> {
    std::unordered_multimap<Key, Value> container_;

public:
    void insert(const Key& key, const Value& value) override {
        container_.emplace(key, value);
    }

    const Value& get(const Key& key) const override {
        auto range = container_.equal_range(key);
        auto it = std::find_if(range.first, range.second,
                               [&](const std::pair<Key, Value>& pair) {
                                   return pair.first == key;
                               });

        if (it != range.second)
            return it->second;

        throw std::out_of_range("Key not found in CustomUnorderedMultiMapContainer");
    }

    std::chrono::microseconds measureLookupTime(const Key& key) const override {
        auto start = std::chrono::high_resolution_clock::now();
        get(key);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};

// Container class for std::queue
template <typename Value>
class QueueContainer : public ContainerInterface<int, Value> {
    std::queue<Value> container_;

public:
    void insert(const int& /* key */, const Value& value) override {
        container_.push(value);
    }

    const Value& get(const int& /* key */) const override {
        if (!container_.empty())
            return container_.front();

        throw std::out_of_range("Queue is empty in CustomQueueContainer");
    }

    std::chrono::microseconds measureLookupTime(const int& /* key */) const override {
        auto start = std::chrono::high_resolution_clock::now();
        get(0);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};

// Container class for std::list
template <typename Value>
class ListContainer : public ContainerInterface<int, Value> {
    std::list<Value> container_;

public:
    void insert(const int& /* key */, const Value& value) override {
        container_.push_back(value);
    }

    const Value& get(const int& /* key */) const override {
        if (!container_.empty())
            return container_.front();

        throw std::out_of_range("List is empty in CustomListContainer");
    }

    std::chrono::microseconds measureLookupTime(const int& /* key */) const override {
        auto start = std::chrono::high_resolution_clock::now();
        get(0);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};


// Container class for std::vector
template <typename Value>
class VectorContainer : public ContainerInterface<int, Value> {
    std::vector<Value> container_;

public:
    void insert(const int& /* key */, const Value& value) override {
        container_.push_back(value);
    }

    const Value& get(const int& /* key */) const override {
        if (!container_.empty())
            return container_.front();

        throw std::out_of_range("Vector is empty in CustomVectorContainer");
    }

    std::chrono::microseconds measureLookupTime(const int& /* key */) const override {
        auto start = std::chrono::high_resolution_clock::now();
        get(0);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }
};