#pragma once
#include <iostream>
// forward declaration:
class AbstractNode;


template <typename T>
class Plug
{
public:
    Plug()
    {
        std::cout << "plug constructor" << std::endl;
    }
    ~Plug()
    {
        std::cout << "plug destructor" << std::endl;
        _value = nullptr;
        _parent_node = nullptr;
        _source_plug = nullptr;
    }

    // getters
    T* GetValue() const
    {
        return _value;
    }

    AbstractNode* GetParent() const
    {
        return _parent_node;
    }
    Plug<T>* GetSourcePlug() const
    {
        return _source_plug;
    }

    int GetId() const
    {
        return _id;
    }

    void PrintValue() const
    {
        std::cout << *_value << std::endl;
    }

    // setter
    void SetValue(T* value)
    {
        _value = value;
    }

    void SetParent(AbstractNode* parent_node)
    {
        _parent_node = parent_node;
    }
    
    void SetSourcePlug(Plug<T>* source_plug)
    {
        _source_plug = source_plug;
    } 

    void SetId(int id)
    {
        _id = id;
    }


private:
    T* _value = nullptr;
    AbstractNode* _parent_node = nullptr;
    Plug* _source_plug = nullptr;
    int _id;
};