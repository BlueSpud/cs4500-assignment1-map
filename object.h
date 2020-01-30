//
// Created by Jiawen Liu on 1/21/20.
//
#pragma once;
#include <stdio.h>
#ifndef OBJECT_H
#define OBJECT_H

class Object {

public:
    virtual size_t hash();
    virtual bool equals(Object* object);
};
#endif