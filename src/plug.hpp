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
    // base class functions this functions will help in the node-plugs evaluation.
    // during the evaluation process the links between Plugs will require querying the status of the parent Node.
    

    // getters
    AbstractNode* GetParent() const
    {   
        return _parent_node;
    }

    int GetId()
    {
        return _id;
    }

    virtual void PrintValue() const =0;

    // setters
    void SetParent(AbstractNode* parent_node)
    {
        _parent_node = parent_node;
    }

    void SetId(int id)
    {
        _id = id;
    }
    

private:
    // reference to the parent node, to query the status
    AbstractNode* _parent_node=nullptr;
    int _id = 0;
};



template <typename T>
class PlugIn : public AbstractPlug
{
public:
    PlugIn(float id) 
    {
        SetId(id);
        std::cout << "plugIn constructor id: "<< GetId() << std::endl;
    }

    ~PlugIn()
    {
        std::cout << "plugIn destructor << id: "<< GetId() << std::endl;
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
        if(_source_plug)
            _source_plug->PrintValue();
        else
            std::cout << "nothing connect to this plug" << std::endl;
    }

    // setter    
    void SetSourcePlug(PlugOut<T>* source_plug)
    {
        _source_plug = source_plug;
        if(GetParent())
            GetParent()->SetDirty(true);
    } 

private:
    // stores the reference to the pointer of OutPlug to make the connection.  
    PlugOut<T>* _source_plug=nullptr;
};


template <typename T>
class PlugOut : public AbstractPlug
{
public:
    PlugOut(float id)
    {
        SetId(id);
        std::cout << "plugOut constructor id: " << GetId() <<std::endl;
    }

    ~PlugOut()
    {
        std::cout << "plugOut destructor id: "<< GetId() << std::endl;
        SetParent(nullptr);
    }

    // getters
     T* GetPointerToValue()
    {
        return _pointer_to_value;
    }    

    T DeReferenceValue() const
    {
        return *_pointer_to_value;
    }


    virtual void PrintValue() const override
    {
        std::cout << DeReferenceValue() << std::endl;
    }

    // setter
    void SetReferenceToValue(T* value)
    {
        _pointer_to_value = value;
    }
    
private:
    // variable pointing to the value stored in the node 
    T* _pointer_to_value = nullptr;
};