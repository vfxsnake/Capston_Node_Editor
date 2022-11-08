#pragma once

#include <iostream>
#include <vector>
#include <memory>
// forward declarations:
class AbstractPlug;

class AbstractNode : std::enable_shared_from_this<AbstractNode>
{ 
public:
    // getter:
    const char* GetName();
    bool IsDirty() const;
    int GetId();
    std::shared_ptr<AbstractNode> GetPointer();
  
    // setters
    void SetName(const char* name);
    void SetDirty(bool value);
    void SetId(int id);

    // this function is the must relevant 
    // here it will compute and set the plug
    // values
    virtual bool Compute() = 0;
    
    // function relevant for the evaluation and drawing systems
    // on draw this will be use to get the number of inputs and 
    // outputs and the corresponding ids to be mapped in the ui. 
    virtual std::vector<std::shared_ptr<AbstractPlug>> GetPlugIns()const = 0;
    virtual std::vector<std::shared_ptr<AbstractPlug>> GetPlugOuts() const = 0;

private:
    bool _dirty = true;
    const char* _name;
    int _id = 0;
};
