Map should support the following operation:
1) get_size() // return the number of  key-value pair in the map
2) get_capacity();
3) resize();   // map should be able to dynamically allocate new space if necessary (or shrink)
4) put(Object* key, Object* val);  // put a key-value pair into the map, if the key already exist, override its associated value
5) get(Object* key); // get the value mapped to the given key if key exists, otherwise, return nullptr
6) contains_key(Object* key);  //check if the given key exist in the map
7) remove(Object* key); // remove a key-value pair from the map
8) Object** key_set(); // List out all of the keys in this map
9) Object** values(); // Listout all of the values in this map


Note:
detailed description of methods can be found in map.h.
map should support all kinds of object->object mapping, or at least, String->Object mapping
all key-value pair in a map should follow the map's contract (ex: a Map of String->String can not store a key-value pair of type String -> Int)

