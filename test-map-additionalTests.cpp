#pragma once;
#include "map.h"
#include "string.h"
#include <iostream>

static const int _stressTestVal = 10000;

void mapStressTest() {
    Map* h1 = new Map();

    for (int i = 0; i < _stressTestVal; i++) {
        char *charKey = new char(6);
        strcpy(charKey, "key");
        charKey[4] = i;
        charKey[5] = '\0';
        String *keyStr = new String(charKey);

        char *charVal = new char(6);
        strcpy(charVal, "key");
        charVal[4] = i;
        charVal[5] = '\0';
        String *valStr = new String(charVal);

        // Test put
        h1->put(keyStr, valStr);

        delete charKey;
        delete charVal;
    }

    t_true(h1->get_size() == _stressTestVal);

    for (int i = 0; i < _stressTestVal; i++) {
        char *charKey = new char(6);
        strcpy(charKey, "key");
        charKey[4] = i;
        charKey[5] = '\0';
        String *keyStr = new String(charKey);

        char *charVal = new char(6);
        strcpy(charVal, "key");
        charVal[4] = i;
        charVal[5] = '\0';
        String *valStr = new String(charVal);

        // Test contain
        t_true(h1->contains_key(keyStr));

        // Test get
        String* getString = dynamic_cast<String*>(h1->get(keyStr));
        t_true(getString != nullptr);
        t_true(getString->equals(valStr));

        // Test removeString
        String* removedString = dynamic_cast<String*>(h1->get(keyStr));
        t_false(h1->contains_key(keyStr));
        
        delete charKey;
        delete charVal;
        delete removedString;
    }

    OK("Stress test complete");
}

