#include "abstract_node.h"

void AbstractNode::SetName(const char* name)
{
    _name  = name;
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
