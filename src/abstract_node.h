#pragma once

#include <iostream>
#include <vector>
// forward declarations:
class AbstractPlug;

class AbstractNode
{ 
public:
    // getter:
    const char* GetName();
    bool IsDirty() const;
  
    // setters
    void SetName(const char* name);
    void SetDirty(bool value);


    // this function is the must relevant 
    // here it will compute and set the plug
    // values
    virtual bool Compute() = 0;
    
    // function relevant for the evaluation manager 
    virtual std::vector<AbstractPlug*> GetPlugIns()const = 0;
    virtual std::vector<AbstractPlug*> GetPlugOuts() const = 0;

private:
    bool _dirty = true;
    const char* _name;
};
