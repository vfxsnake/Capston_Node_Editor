#include <iostream>
#include <memory>
#include "nodes.h"
#include "plug.hpp"
#include "node_attribute.hpp"

/*
    float Node Constructor:
        int& unique_id_reference: Reference to the system id count.
                                  this will be post-incremented when used.
    Is responsibility of the nodes to manages the usages of all the memory
    allocation, for that reason all its compositional elements must be 
    unique pointers
*/
FloatNode::FloatNode(int& unique_id_reference)
{ 
    // the unique must be passed by reference so it can be incremented
    // each time it is used inside the node. Float node uses 2 time, one for
    // itself id and the other for the out0 OutPlug id.
    SetId(++unique_id_reference);
    std::cout << "FloatNode constructor id: "<< GetId() << std::endl;
    _default_attr = std::make_unique<NodeAttribute<float>>(NodeAttribute<float>(++unique_id_reference));
    _default_attr->_value = FLOAT_DEFAULT_VALUE;
    _result = std::make_unique<float>(float());
    *_result = FLOAT_DEFAULT_VALUE;
    _out_0 =  std::make_unique<PlugOut<float>>(PlugOut<float>(++unique_id_reference));
    _out_0->SetReferenceToValue(_result.get());
    _out_0->SetParent(this);

    SetDirty(true);
}


FloatNode::~FloatNode()
{
    std::cout << "FloatNode destructor id: "<<  GetId() <<std::endl;
}


std::vector<AbstractPlug*> FloatNode::GetPlugIns() const 
{
    return {};
}


std::vector<AbstractPlug*> FloatNode::GetPlugOuts() const
{
    std::vector<AbstractPlug*> outputs;
    return {_out_0.get()};
}


PlugOut<float>* FloatNode::GetOutPlug() const
{
    return _out_0.get();
}


/*
    Compute returns true if the result value
    was updated, so it triggers the Dirty propagation
    in the node graph.
*/
bool FloatNode::Compute()
{
    // TODO Convert to multi thread
    if(IsDirty())
    {
        *_result = _default_attr->_value;
        // remove when the evaluation system is implemented it will change the state of the nodes.
        SetDirty(false);
        return true;
    }
    return false;
}


void FloatNode::SetDefaultValue(float value)
{
    if(_default_attr->_value != value)
        _default_attr->_value = value;
        SetDirty(true);
}


float FloatNode::GetDefaultValue() const
{
    return _default_attr->_value;
}


float* FloatNode::GetResultReference()
{
    return _result.get();
}

int FloatNode::GetDefaultValueId()
{
    return _default_attr->_id;
}


// --------------------------------------------------- Float Addition Node -----------------------------------------------------------------
FloatAdditionNode::FloatAdditionNode(int& unique_id_reference)
{
    SetId(++unique_id_reference);
    std::cout << "FloatAdditionNode constructor id: "<< GetId() << std::endl; 
    _default_attr_0 = std::make_unique<NodeAttribute<float>>(NodeAttribute<float>(++unique_id_reference));
    _default_attr_0->_value = FLOAT_DEFAULT_VALUE;

    _default_attr_1 = std::make_unique<NodeAttribute<float>>(NodeAttribute<float>(++unique_id_reference));
    _default_attr_1->_value = FLOAT_DEFAULT_VALUE;
    
    _result = std::make_unique<float>(float());
    *_result = FLOAT_DEFAULT_VALUE;
    
    _out_0 = std::make_unique<PlugOut<float>>(PlugOut<float>(++unique_id_reference));
    _out_0->SetParent(this);
    _out_0->SetReferenceToValue(_result.get());

    _in_0 = std::make_unique<PlugIn<float>>(PlugIn<float>(++unique_id_reference));
    _in_0->SetParent(this);
    
    _in_1 =std::make_unique<PlugIn<float>>(++unique_id_reference);
    _in_1->SetParent(this);
    
    SetDirty(true);
}


FloatAdditionNode::~FloatAdditionNode()
{
    std::cout << "FloatAdditionNode destructor id: "<< GetId() <<std::endl;
}


std::vector<AbstractPlug*> FloatAdditionNode::GetPlugIns() const 
{   
    std::vector<AbstractPlug*> connected_plugins = {};
    if (GetPlugIn_0()->GetSourcePlug())
        connected_plugins.emplace_back(GetPlugIn_0()->GetSourcePlug());
    if (GetPlugIn_1()->GetSourcePlug())
        connected_plugins.emplace_back(GetPlugIn_1()->GetSourcePlug());
    return connected_plugins;
}


std::vector<AbstractPlug*> FloatAdditionNode::GetPlugOuts() const
{    
    return {GetOutPlug()}; 
}

 
bool FloatAdditionNode::Compute()
{
    // look first if theres a input connection from it's PlugIns.
    // if not uses default value.
    // connecting result to default value address.
    if(IsDirty())
    {
        float value_0, value_1;

        if(_in_0->GetSourcePlug() == nullptr)
            value_0 = _default_attr_0->_value;
        else
            value_0 = _in_0->GetSourcePlug()->DeReferenceValue();
        
        if(_in_1->GetSourcePlug() == nullptr)
            value_1 = _default_attr_1->_value;
        else
            value_1 = _in_1->GetSourcePlug()->DeReferenceValue();

        //  perform addition
        std::cout << " val 0: " << value_0 << " val 1: " << value_1 << std::endl;
        *_result = value_0 + value_1;
        return true;
    }

    return false;
}


int FloatAdditionNode::GetDefaultValue_0_Id() const
{
    return _default_attr_0->_id;
}


float FloatAdditionNode::GetDefaultValue_0() const
{
    return _default_attr_0->_value;
}


void FloatAdditionNode::SetDefaultValue_0(float value)
{
    _default_attr_0->_value = value;
    if (!IsDirty())
        SetDirty(true);
}


int FloatAdditionNode::GetDefaultValue_1_Id() const
{
    return _default_attr_1->_id;
}


float FloatAdditionNode::GetDefaultValue_1() const
{
    return _default_attr_1->_value;
}


void FloatAdditionNode::SetDefaultValue_1(float value)
{
    _default_attr_1->_value = value;
    if (!IsDirty())
        SetDirty(true);
}


PlugIn<float>* FloatAdditionNode::GetPlugIn_0() const
{
    return _in_0.get();
}


PlugIn<float>* FloatAdditionNode::GetPlugIn_1()const
{
    return _in_1.get();
}


PlugOut<float>* FloatAdditionNode::GetOutPlug() const
{
    return _out_0.get();
}


// --------------------------------------- evaluation node --------------------------------------
EvaluationNode::EvaluationNode(int& unique_id_reference)
{
    SetId(++unique_id_reference);
    std::cout << "EvaluationNode constructor id: "<<  GetId() <<std::endl;
    _in_0 = std::make_unique<PlugIn<float>>(++unique_id_reference);
    _in_0->SetParent(this);
}


EvaluationNode::~EvaluationNode()
{
    std::cout << "EvaluationNode destructor id: "<< GetId() <<std::endl;
}


std::vector<AbstractPlug*> EvaluationNode::GetPlugIns() const 
{
    if(_in_0->GetSourcePlug())
        return {_in_0->GetSourcePlug()};
    return {};
}


std::vector<AbstractPlug*> EvaluationNode::GetPlugOuts() const
{
    return {};
}


bool EvaluationNode::IterateGraph(AbstractNode* node)
{    
    for(auto x : node->GetPlugIns())
    {
        std::cout << "plugIn id: " << x->GetId() <<std::endl;
        if(x->GetParent())
        {
            std::cout <<"has parent id:" << x->GetParent()->GetId() << std::endl;
            if(IterateGraph(x->GetParent()))
                node->SetDirty(true);
        }
    }

    if (node->Compute())
    {
        std::cout << "graph evaluated" << std::endl;
        node->SetDirty(false);
        return true;
    }
    return false;
}


bool EvaluationNode::Compute()
{
    if(_in_0->GetSourcePlug())
    {

        if (_in_0->GetSourcePlug()->GetParent())
        {
            std::cout << "has parent id:" << _in_0->GetSourcePlug()->GetParent()->GetId() << std::endl;
            IterateGraph(_in_0->GetSourcePlug()->GetParent());
        }
    // just for debugging 
        GetPlugIn_0()->PrintValue();
        return true;
    }
    return false;
} 


PlugIn<float>* EvaluationNode::GetPlugIn_0() const
{
    return _in_0.get();
}


bool EvaluationNode::GetResultValue(float& out_float) const
{
    if (GetPlugIn_0()->GetSourcePlug())
        out_float = GetPlugIn_0()->GetSourcePlug()->DeReferenceValue();
        return true;
    return false;
}