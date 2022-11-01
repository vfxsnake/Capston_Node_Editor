#pragma once
#include <iostream>
#include <memory>
#include "abstract_node.h"

// forward declaration
template<class>
class PlugIn;
template<class>
class PlugOut;

// CONSTANTS
#define FLOAT_DEFAULT_VALUE 0.0f

class FloatNode : public AbstractNode
{
public:
    FloatNode();
    ~FloatNode();

    // override virtual functions
    virtual std::vector<AbstractPlug*> GetPlugIns() const override;
    virtual std::vector<AbstractPlug*> GetPlugOuts() const override;
    virtual bool Compute() override; 

    // edits the node default value, this node has no plugins,
    // this is the accessor to change the default value.
    void SetDefaultValue(float value);

    PlugOut<float>* GetOutPlug()const;

private:

    PlugOut<float>* _out_0;
    float* _result;
    float _default_value;
};
