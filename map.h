//
// Created by Jiawen Liu on 1/24/20.
//

#ifndef MAP_H
#define MAP_H

#pragma once;
#include "../cs4500-assignment1-array/object.h"

#include "../cs4500-assignment1-array/array.h"

/**
 * An entry in a map
 */
class Entry: public Object {
public:

    /** The object used as the key */
    Object* key;

    /** The value of the entry */
    Object* value;

    /** The hash value of the key */
    size_t hash;

    /**
     * Creates a new entry
     * @param key The key of the entry
     * @param value The value of the entry
     */
    Entry(Object *key, Object *value) : key(key), value(value) {
        hash = key->hash();
    }
};

class Map : public Object {
public:

    /** The array that stores all of the buckets */
    ArrayObject _array;

    ArrayObject _entrySet;

    /**
     * Default constructor that constructs an empty Map with
    */
    Map() {
        for (int i = 0; i < 16; i++) {
            _array.push_back(new ArrayObject());
        }
    }

    /**
     * Destructor that delete Map object
     */
    ~Map() {
        for (int i = 0; i < _entrySet.size(); i++) {
            delete _entrySet.get(i);
        }
    }

public:
    /**
     * Returns the number of key-value pairs in this map.
     */
    int get_size() { return _entrySet.size(); }

    /**
     * Put the given key value pair into the map
     * If the key is already associated with a value, the new value should overwrite the previous one
     * @return  val
     */
    void put(Object* key, Object* val) {
        _resizeIfNeeded();

        Entry* entry = _getEntry(key);
        if (entry) {
            entry->value = val;
            return val;
        }

        Entry* newEntry = new Entry(key, val);
        _entrySet.push_back(entry);
        _put(newEntry);
        return val;
    }

    /**
     * Resizes the map's internal storage if needed. The array is resized if the load factor is less than or
     * equal to the number of entries in the map plus one.
     * The load factor is calculated by 0.75 * capacity
     */
    void _resizeIfNeeded() {
        size_t resizeThreshold = (float)_array.size() * 0.75;
        if (resizeThreshold <= (_entrySet.size() + 1)) {
            for (size_t i = 0; i < _array.size(); i++) {
                ArrayObject* bucketArr = dynamic_cast<ArrayObject*>(_array.get(i));
                bucketArr->clear();
            }

            size_t size = _array.size();
            for (size_t i = 0; i < size; i++) {
                _array.push_back(new ArrayObject());
            }

            for (size_t i = 0; i < _entrySet.size(); i++) {
                _put(dynamic_cast<Entry*>(_entrySet.get(i)));
            }
        }
    }

    void _put(Entry* entry) {
        size_t bucketIndex = entry->hash % _array.size();
        ArrayObject* bucketArr = dynamic_cast<ArrayObject*>(_array.get(bucketIndex));

        bucketArr->push_back(entry);
    }

    /**
     * Returns the value of which the specified key is mapped to, or nullptr if this map does not contain the given key
     * @param key   the key whose associated value is to be returned
     * @return  the value mapped to the given key, or nullptr if the key is not found
     */
    Object* get(Object* key) {
        Entry* entry = _getEntry(key);
        return entry ? entry->value : nullptr;
    }

    /**
     * Provides the entry for the object of the given key. If it is not found, nullptr is returned
     * @param key The key to get the entry of
     * @return The entry that represents the key
     */
    Entry* _getEntry(Object* key) {
        size_t hash = key->hash();
        size_t bucketIndex = hash % _array.size();

        ArrayObject* bucketArr = dynamic_cast<ArrayObject*>(_array.get(bucketIndex));
        if (bucketArr->size() == 1) {
            return dynamic_cast<Entry*>(bucketArr->get(0));
        } else {
            for (int i = 0; i < bucketArr->size(); i++) {
                Entry* entry = dynamic_cast<Entry*>(bucketArr->get(i));
                if (entry->value->equals(key)) {
                    return dynamic_cast<Entry*>(bucketArr->get(i));
                }
            }
        }

        return nullptr;
    }

    /**
     * Returns true if this map contains the given key
     * @param key   The key whose presence in this map is to be tested
     * @return  true if this map contains a mapping for the specified key, otherwise false
     */
    bool contains_key(Object* key) { return _getEntry(key) != nullptr; }


    /**
     * Removes the mapping for the specified key from this map if present.
     * @param key
     * @return   value associated with the key, or nullptr if the key is not found
     */
    Object* remove(Object* key) {
        size_t hash = key->hash();
        size_t bucketIndex = hash % _array.size();

        ArrayObject* bucketArr = dynamic_cast<ArrayObject*>(_array.get(bucketIndex));
        for (int i = 0; i < bucketArr->size(); i++) {
            Entry* entry = dynamic_cast<Entry*>(bucketArr->get(i));
            if (entry->key->equals(key)) {
                bucketArr->remove(i);
                return entry->value;
            }
        }

        return nullptr;
    }

    /**
     * @return  a list of values contained in this map
     */
    Object** values();

    size_t hash() {
        size_t hash = 0;
        for (size_t i = 0; i < _entrySet.size(); i++) {
            hash += dynamic_cast<Entry*>(_entrySet.get(i))->hash;
        }
        return hash;
    }

    bool equals(Object* object) {
        return false;
    }
};
#endif
