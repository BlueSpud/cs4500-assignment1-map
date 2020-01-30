Map should support the following operation:
1) put(Object* key, Object* val);  // put a key-value pair into the map, if the key already exist, override its associated value
2) get(Object* key); // get the value mapped to the given key if key exists, otherwise, return nullptr
3) contains_key(Object* key);  //check if the given key exist in the map
4) remove(Object* key); // remove a key-value pair from the map


Note:
detailed description of methods can be found in map.h.
map should support all kinds of object->object mapping, or at least, String->Object mapping
all key-value pair in a map should follow the map's contract (ex: a Map of String->String can not store a key-value pair of type String -> Int)

