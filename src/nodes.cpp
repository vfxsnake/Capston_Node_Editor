#include <iostream>
#include "nodes.h"
#include "plug.hpp"


FloatNode::FloatNode()
{
    std::cout << "FloatNode constructor"<< std::endl; 
    _default_value = 0.0f;
    _result = new float{};
    _out_0 = new PlugOut<float>{};
    _out_0->SetReferenceToValue(_result);

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
    outputs.emplace_back(_out_0);
    return outputs; 
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

