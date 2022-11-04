#pragma once

#include <iostream>
#include "abstract_node.h"

// function declaration
class AbstractPlug;
template<class>
class PlugIn;
template<class>
class PlugOut;

// classes Definitions
class AbstractPlug
{
public:
    // base class functions this functions will help in the node-plugs evaluation process
    // during the evaluation process the links between Plugs will require querying the status of the parent Node.
    
    // getters
    AbstractNode* GetParent() const
    {
        return _parent_node;
    }

    virtual void PrintValue() const =0;

    // setters
    void SetParent(AbstractNode* parent_node)
    {
        _parent_node = parent_node;
    }
    

private:
    // reference to the parent node, to query the status
    AbstractNode* _parent_node = nullptr;
};



template <typename T>
class PlugIn : public AbstractPlug
{
public:
    PlugIn()
    {
        // std::cout << "plug constructor" << std::endl;
    }
    ~PlugIn()
    {
        // std::cout << "plug destructor" << std::endl;
        _source_plug = nullptr;
        SetParent(nullptr);
    }

    // getters
    PlugOut<T>* GetSourcePlug() const
    {
        return _source_plug;
    }

    virtual void PrintValue() const override
    {
        _source_plug->PrintValue();
    }

    // setter    
    void SetSourcePlug(PlugOut<T>* source_plug)
    {
        _source_plug = source_plug;
        if(GetParent())
            GetParent()->SetDirty(true);
    } 

private:

    PlugOut<T>* _source_plug = nullptr;
};


template <typename T>
class PlugOut : public AbstractPlug
{
public:
    PlugOut()
    {
        // std::cout << "plug constructor" << std::endl;
    }
    ~PlugOut()
    {
        // std::cout << "plug destructor" << std::endl;
        SetParent(nullptr);
    }

    // getters
    T GetReferenceValue() const
    {
        return *_reference_to_value;
    }


    virtual void PrintValue() const override
    {
        std::cout << GetReferenceValue() << std::endl;
    }

    // setter
    void SetReferenceToValue(T* value)
    {
        _reference_to_value = value;
    }
    
private:
    T* _reference_to_value = nullptr;
};