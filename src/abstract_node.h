#pragma once

#include <iostream>
#include <vector>
#include <memory>
// forward declarations:
class AbstractPlug;

class AbstractNode
{ 
public:
    // getter:
    const char* GetName();
    bool IsDirty() const;
    int GetId();
    AbstractNode* GetPointer();
  
    // setters
    void SetName(const char* name);
    void SetDirty(bool value);
    void SetId(int id);

    // this function is the must relevant 
    // here it will compute and set the plug
    // values
    virtual bool Compute() = 0;
    
    // function relevant for the evaluation and drawing process
    // on draw this will be use to get the number of inputs and 
    // outputs and the corresponding ids to be mapped in the ui.
    // plugs ins is the key component for the evaluation system 
    virtual std::vector<AbstractPlug*> GetPlugIns() const = 0;
    virtual std::vector<AbstractPlug*> GetPlugOuts() const = 0;

private:
    bool _dirty = true;
    const char* _name;
    int _id = 0;
};
