#pragma once
#include <iostream>
#include <memory>
#include <any>
#include "abstract_node.h"

// forward declaration
template<class>
class PlugIn;

template<class>
class PlugOut;

template<class>
struct NodeAttribute;


// CONSTANTS
#define FLOAT_DEFAULT_VALUE 0.0f

class FloatNode : public AbstractNode
{
public:
    FloatNode(int& unique_id_reference);
    ~FloatNode();

    // override virtual functions
    virtual std::vector<AbstractPlug*> GetPlugIns() const override;
    virtual std::vector<AbstractPlug*> GetPlugOuts() const override;
    virtual bool Compute() override; 

    // edits the node default value, this node has no plugins,
    // this is the accessor to change the default value.
    void SetDefaultValue(float value);
    float GetDefaultValue() const;
    int GetDefaultValueId();

    PlugOut<float>* GetOutPlug()const;
    float* GetResultReference();
    
private:
    std::unique_ptr<PlugOut<float>> _out_0;
    std::unique_ptr<float> _result;
    std::unique_ptr<NodeAttribute<float>> _default_attr;
};


class FloatAdditionNode : public AbstractNode
{
public:
    FloatAdditionNode(int& unique_id_reference);
    ~FloatAdditionNode();

    // override virtual functions
    virtual std::vector<AbstractPlug*> GetPlugIns() const override;
    virtual std::vector<AbstractPlug*> GetPlugOuts() const override;
    virtual bool Compute() override; 

    // accessors to default values
    void SetDefaultValue_0(float value);
    float GetDefaultValue_0() const;
    int GetDefaultValue_0_Id() const;
    
    void SetDefaultValue_1(float value);
    float GetDefaultValue_1() const;
    int GetDefaultValue_1_Id() const;

   PlugOut<float>* GetOutPlug()const;

    PlugIn<float>* GetPlugIn_0()const; 
    PlugIn<float>* GetPlugIn_1()const; 

private:
    // unique pointers to plugs.
    // the ownership of the plugs belongs to the node.
    std::unique_ptr<PlugOut<float>> _out_0;
    std::unique_ptr<PlugIn<float>> _in_0;
    std::unique_ptr<PlugIn<float>> _in_1;
    
    // the result of the computation is saved in _result
    // and the ownership of this resource belongs to the node. 
    std::unique_ptr<float> _result;
    std::unique_ptr<NodeAttribute<float>> _default_attr_0;
    std::unique_ptr<NodeAttribute<float>> _default_attr_1;
};


class EvaluationNode : public AbstractNode
{
public:
    EvaluationNode(int& unique_id_reference);
    ~EvaluationNode();

    // override virtual functions
    virtual std::vector<AbstractPlug*> GetPlugIns() const override;
    virtual std::vector<AbstractPlug*> GetPlugOuts() const override;
    virtual bool Compute() override;
    bool IterateGraph(AbstractNode* node);

    PlugIn<float>* GetPlugIn_0()const;
    bool GetResultValue(float& out_float) const;

private:
    // reference to the last node in the network
    std::unique_ptr<PlugIn<float>> _in_0;

};