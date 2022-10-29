#pragma once
#include <iostream>
#include "abstract_node.h"

class AbstractPlug
{
public:
    // base class functions this functions will help in the node-plugs evaluation process
    // during the evaluation process the links between Plugs will require querying the status of the parent Node.
    
    // getters
    int GetId() const
    {
        return _id;
    }

    AbstractNode* GetParent() const
    {
        return _parent_node;
    }

    virtual void PrintValue() const =0;

    // setters
    void SetId(int id)
    {
        _id = id;
    }

    void SetParent(AbstractNode* parent_node)
    {
        _parent_node = parent_node;
    }
    

private:
    // reference to the parent node, to query the status
    AbstractNode* _parent_node;
    int _id;
};

template <typename T>
class Plug : public AbstractPlug
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
        _source_plug = nullptr;
        SetParent(nullptr);
    }

    // getters
    T* GetValue() const
    {
        return _value;
    }

    Plug<T>* GetSourcePlug() const
    {
        return _source_plug;
    }

    virtual void PrintValue() const override
    {
        std::cout << *_value << std::endl;
    }

    // setter
    void SetValue(T* value)
    {
        _value = value;
    }
    
    void SetSourcePlug(Plug<T>* source_plug)
    {
        _source_plug = source_plug;
    } 

private:
    T* _value = nullptr;
    Plug* _source_plug = nullptr;
};