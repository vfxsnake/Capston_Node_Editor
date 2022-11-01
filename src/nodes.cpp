#include <iostream>
#include "nodes.h"
#include "plug.hpp"


FloatNode::FloatNode()
{
    std::cout << "FloatNode constructor"<< std::endl; 
    _default_value = FLOAT_DEFAULT_VALUE;
    _result = new float{};
    *_result = FLOAT_DEFAULT_VALUE;
    _out_0 = new PlugOut<float>{};
    _out_0->SetReferenceToValue(_result);
    _out_0->SetParent(this);

    SetDirty(true);
}


FloatNode::~FloatNode()
{
    std::cout << "FloatNode destructor"<< std::endl;
    delete _out_0;
    delete _result;
}


std::vector<AbstractPlug*> FloatNode::GetPlugIns() const 
{
    return {};
}


std::vector<AbstractPlug*> FloatNode::GetPlugOuts() const
{
    std::vector<AbstractPlug*> outputs;
    return {_out_0};
}


PlugOut<float>* FloatNode::GetOutPlug() const
{
    return _out_0;
}


bool FloatNode::Compute()
{
    // TODO Convert to multi thread
    // connecting result to default value address.
    if(IsDirty())
        *_result = _default_value;
        // remove when the evaluation system is implemented it will change the state of the nodes.
        SetDirty(false);
    return true;
}


void FloatNode::SetDefaultValue(float value)
{
    _default_value = value;
    SetDirty(true);
}


// ----------------------------------------------------------------------------------------------------------------------
FloatAdditionNode::FloatAdditionNode()
{
    std::cout << "FloatAdditionNode constructor"<< std::endl; 
    _default_value_0 = FLOAT_DEFAULT_VALUE;
    _default_value_0 = FLOAT_DEFAULT_VALUE;
    _result = new float{};
    *_result = FLOAT_DEFAULT_VALUE;
    
    _out_0 = new PlugOut<float>{};
    _out_0->SetParent(this);
    _out_0->SetReferenceToValue(_result);

    _in_0 = new PlugIn<float>{};
    _in_0->SetParent(this);
    
    _in_1 = new PlugIn<float>{};
    _in_1->SetParent(this);
    
    SetDirty(true);
}


FloatAdditionNode::~FloatAdditionNode()
{
    std::cout << "FloatAdditionNode destructor"<< std::endl;
    delete _out_0;
    delete _in_0;
    delete _in_1;
    delete _result;
}


std::vector<AbstractPlug*> FloatAdditionNode::GetPlugIns() const 
{
    return {_in_0, _in_1};
}


std::vector<AbstractPlug*> FloatAdditionNode::GetPlugOuts() const
{
    std::vector<AbstractPlug*> outputs;
    
    return {_out_0}; 
}


PlugOut<float>* FloatAdditionNode::GetOutPlug() const
{
    return _out_0;
}


bool FloatAdditionNode::Compute()
{
    // TODO Convert to multi thread
    // connecting result to default value address.
    if(IsDirty())
    {
        float value_0, value_1;

        if(_in_0->GetSourcePlug() == nullptr)
            value_0 = _default_value_0;
        else
            value_0 = _in_0->GetSourcePlug()->GetReferenceValue();
        
        if(_in_1->GetSourcePlug() == nullptr)
            value_1 = _default_value_1;
        else
            value_1 = _in_1->GetSourcePlug()->GetReferenceValue();

        //  perform addition
        *_result = value_0 + value_1;
        // remove when the evaluation system is implemented it will change the state of the nodes.
        SetDirty(false);

    }
            
    return true;
}


void FloatAdditionNode::SetDefaultValue_0(float value)
{
    _default_value_0 = value;
    if (!IsDirty())
        SetDirty(true);
}

void FloatAdditionNode::SetDefaultValue_1(float value)
{
    _default_value_1 = value;
    if (!IsDirty())
        SetDirty(true);
}

PlugIn<float>* FloatAdditionNode::GetPlugIn_0() const
{
    return _in_0;
}
PlugIn<float>* FloatAdditionNode::GetPlugIn_1()const
{
    return _in_1;
}
