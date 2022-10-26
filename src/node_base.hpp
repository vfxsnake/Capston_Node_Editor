#pragma once
#include <vector>
#include "imgui.h"

template<typename Derived>
class NodeBase
{
public:
    NodeBase();
    ~NodeBase();
    void Compute()
    {
        if(_dirty)
            static_cast<Derived*>(this)->Compute();
        _dirty = false; 
    }

    ImVec2 GetPosition()
    {
        return _position()
    }

    void SetPosition(ImVec2 new_position)
    {
        _position = new_position;
    }
    
private:
    bool _dirty = true;
    ImVec2 _position;
    ImVec2 _size;
    int _id;
    
};