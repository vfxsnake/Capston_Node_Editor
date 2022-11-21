#include "abstract_node.h"

void AbstractNode::SetName(const char* name)
{
    _name  = name;
}

void AbstractNode::SetId(int id)
{
    _id = id;
}

bool AbstractNode::IsDirty()const
{
    return _dirty;
}

void AbstractNode::SetDirty(bool value)
{
    _dirty = value;
    if (_dirty)
        std::cout << "node dirty" << std::endl;
}

int AbstractNode::GetId()
{
    return _id;
}
