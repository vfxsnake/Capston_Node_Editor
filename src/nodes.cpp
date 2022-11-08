#include <iostream>
#include <memory>
#include "nodes.h"
#include "plug.hpp"


FloatNode::FloatNode(int& unique_id_reference)
{ 
    SetId(++unique_id_reference);
    std::cout << "FloatNode constructor id: "<< GetId() << std::endl;
    _default_value = FLOAT_DEFAULT_VALUE;
    _result = std::make_shared<float>(float());
    *_result = FLOAT_DEFAULT_VALUE;
    _out_0 =  std::make_shared<PlugOut<float>>(PlugOut<float>(++unique_id_reference));
    _out_0->SetReferenceToValue(_result);
    _out_0->SetParent(this->GetPointer());

    SetDirty(true);
}


FloatNode::~FloatNode()
{
    std::cout << "FloatNode destructor id: "<<  GetId() <<std::endl;

}


std::vector<std::shared_ptr<AbstractPlug>> FloatNode::GetPlugIns() const 
{
    return {};
}


std::vector<std::shared_ptr<AbstractPlug>> FloatNode::GetPlugOuts() const
{
    std::vector<std::shared_ptr<AbstractPlug>> outputs;
    return {_out_0};
}


std::shared_ptr<PlugOut<float>> FloatNode::GetOutPlug() const
{
    return _out_0;
}


bool FloatNode::Compute()
{
    // TODO Convert to multi thread
    // connecting result to default value address.
    if(IsDirty())
    {
        *_result = _default_value;
        // remove when the evaluation system is implemented it will change the state of the nodes.
        SetDirty(false);
        return true;
    }
    return false;
}


void FloatNode::SetDefaultValue(float value)
{
    _default_value = value;
    SetDirty(true);
}


// --------------------------------------------------- Float Addition Node -----------------------------------------------------------------
FloatAdditionNode::FloatAdditionNode(int& unique_id_reference)
{
    SetId(++unique_id_reference);
    std::cout << "FloatAdditionNode constructor id: "<< GetId() << std::endl; 
    _default_value_0 = FLOAT_DEFAULT_VALUE;
    _default_value_0 = FLOAT_DEFAULT_VALUE;
    _result = std::make_shared<float>(float());
    *_result = FLOAT_DEFAULT_VALUE;
    
    _out_0 = std::make_shared<PlugOut<float>>(PlugOut<float>(++unique_id_reference));
    _out_0->SetParent(this->GetPointer());
    _out_0->SetReferenceToValue(_result);

    _in_0 = std::make_shared<PlugIn<float>>(++unique_id_reference);
    _in_0->SetParent(this->GetPointer());
    
    _in_1 =std::make_shared<PlugIn<float>>(++unique_id_reference);
    _in_1->SetParent(this->GetPointer());
    
    SetDirty(true);
}


FloatAdditionNode::~FloatAdditionNode()
{
    std::cout << "FloatAdditionNode destructor id: "<< GetId() <<std::endl;
}


std::vector< std::shared_ptr<AbstractPlug>> FloatAdditionNode::GetPlugIns() const 
{   
    std::vector<std::shared_ptr<AbstractPlug>> source_connections;
    if(_in_0->GetSourcePlug())
        source_connections.emplace_back(_in_0->GetSourcePlug());
    if(_in_1->GetSourcePlug())
        source_connections.emplace_back(_in_1->GetSourcePlug());
    return source_connections;
}


std::vector< std::shared_ptr<AbstractPlug>> FloatAdditionNode::GetPlugOuts() const
{    
    return {_out_0}; 
}

 
std::shared_ptr<PlugOut<float>> FloatAdditionNode::GetOutPlug() const
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
        std::cout << " val 0: " << value_0 << " val 1: " << value_1 << std::endl;
        *_result = value_0 + value_1;
        return true;
    }
            
    return false;
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

std::shared_ptr<PlugIn<float>> FloatAdditionNode::GetPlugIn_0() const
{
    return _in_0;
}
std::shared_ptr<PlugIn<float>> FloatAdditionNode::GetPlugIn_1()const
{
    return _in_1;
}


// --------------------------------------- evaluation node --------------------------------------
EvaluationNode::EvaluationNode(int& unique_id_reference)
{
    SetId(++unique_id_reference);
    std::cout << "EvaluationNode constructor id: "<<  GetId() <<std::endl;
    _in_0 = std::make_shared<PlugIn<float>>(++unique_id_reference);
    _in_0->SetParent(this->GetPointer());
}


EvaluationNode::~EvaluationNode()
{
    std::cout << "EvaluationNode destructor id: "<< GetId() <<std::endl;
}


std::vector<std::shared_ptr<AbstractPlug>> EvaluationNode::GetPlugIns() const 
{
    if(_in_0->GetSourcePlug())
        return {_in_0->GetSourcePlug()};
    return {};
}


std::vector<std::shared_ptr<AbstractPlug>> EvaluationNode::GetPlugOuts() const
{
    return {};
}


bool EvaluationNode::IterateGraph(std::shared_ptr<AbstractNode> node)
{    
    for(auto x : node->GetPlugIns())
    {
        if(x->GetParent())
        {
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
        IterateGraph(_in_0->GetSourcePlug()->GetParent());
    // just for debugging 
        GetPlugIn_0()->PrintValue();
        return true;
    }
    return false;
} 


std::shared_ptr<PlugIn<float>> EvaluationNode::GetPlugIn_0() const
{
    return _in_0;
}


bool EvaluationNode::GetResult(float& out_float) const
{
    if (GetPlugIn_0()->GetSourcePlug())
        out_float = GetPlugIn_0()->GetSourcePlug()->GetReferenceValue();
        return true;
    return false;
}