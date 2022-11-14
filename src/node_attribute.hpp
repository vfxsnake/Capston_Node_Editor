#pragma once
#include <iostream>

template <typename T>
struct NodeAttribute
{
    NodeAttribute(int id) : _id(id)
    {
        std::cout << " attribute created"<< std::endl;
    }
    int _id;
    T _value;
};