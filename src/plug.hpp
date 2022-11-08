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
    std::shared_ptr<AbstractNode> GetParent() const
    {
        return _parent_node;
    }

    int GetId()
    {
        return _id;
    }

    virtual void PrintValue() const =0;

    // setters
    void SetParent(std::shared_ptr<AbstractNode> parent_node)
    {
        _parent_node = parent_node;
    }

    void SetId(int id)
    {
        _id = id;
    }
    

private:
    // reference to the parent node, to query the status
    std::shared_ptr<AbstractNode> _parent_node;
    int _id = 0;
};



template <typename T>
class PlugIn : public AbstractPlug
{
public:
    PlugIn(float id) 
    {
        // std::cout << "plug constructor" << std::endl;
        SetId(id);
    }
    ~PlugIn()
    {
        // std::cout << "plug destructor" << std::endl;
        _source_plug = nullptr;
        SetParent(nullptr);
    }

    // deep copy
    PlugIn(PlugIn<T>& source_plug_in)
    {
        SetId(source_plug_in.GetId());
        _source_plug = source_plug_in.GetSourcePlug();
        SetParent(source_plug_in.GetParent());
    }

    // copy assign operator
    PlugIn& operator =(PlugIn& source_plug_in)
    {
        if(source_plug_in == this)
            return this;
        
        this->SetId(source_plug_in.GetId());
        this->SetSourcePlug(source_plug_in.GetSourcePlug());
        this->SetParent(source_plug_in.GetParent());
    }

    // move constructor
    PlugIn(PlugIn &&source_plug_in)
    {
        this->SetId(source_plug_in.GetId());
        this->SetSourcePlug(source_plug_in.GetSourcePlug);
        this->SetParent(source_plug_in.GetParent());
    }

    // move assign operator
    PlugIn& operator =(PlugIn &&source_plug_in)
    {
        if(source_plug_in == this)
            return this;
        
        this->SetId(source_plug_in.GetId());
        this->SetSourcePlug(source_plug_in.GetSourcePlug());
        this->SetParent(source_plug_in.GetParent());
    }

    // getters
    std::shared_ptr<PlugOut<T>> GetSourcePlug() const
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

    std::shared_ptr<PlugOut<T>> _source_plug;
};


template <typename T>
class PlugOut : public AbstractPlug
{
public:
    PlugOut(float id)
    {
        // std::cout << "plug constructor" << std::endl;
        SetId(id);
    }
    ~PlugOut()
    {
        // std::cout << "plug destructor" << std::endl;
        SetParent(nullptr);
    }

    // deep copy constructor
    PlugOut(PlugOut& source_out_plug)
    {
        // std::cout << "plug constructor" << std::endl;
        SetId(source_out_plug.GetID());
        SetParent(source_out_plug.GetParent());
        _reference_to_value = source_out_plug.GetReferenceToValue();
    }

    // copy assign operator
    PlugOut operator =(PlugOut& source_out_plug)
    {
        if(&source_out_plug == this)
            return this;
        
        SetId(source_out_plug.GetId());
        SetParent(source_out_plug.GetParent());
        _reference_to_value = source_out_plug.GetReferenceToValue();
    }
    // move constructor
    PlugOut(PlugOut &&source_out_plug)
    {
        SetId(source_out_plug.GetId());
        SetParent(source_out_plug.GetParent());
        _reference_to_value = source_out_plug.GetReferenceToValue();
    }

    // move assign operator


    // getters
    std::shared_ptr<T> GetReferenceToValue()
    {
        return _reference_to_value;
    }    

    T GetReferenceValue() const
    {
        return *_reference_to_value;
    }


    virtual void PrintValue() const override
    {
        std::cout << GetReferenceValue() << std::endl;
    }

    // setter
    void SetReferenceToValue(std::shared_ptr<T> value)
    {
        _reference_to_value = value;
    }
    
private:
    // variable pointing to the value stored in the node 
    std::shared_ptr<T> _reference_to_value = nullptr;
};