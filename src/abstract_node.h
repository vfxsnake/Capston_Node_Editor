#pragma once


class AbstractNode
{ 
public:
    virtual bool is_dirty() const = 0;
    
    virtual void set_dirty(bool value)
    {
        _dirty = value;
    }

private:
    bool _dirty = true;
};