#include "abstract_node.h"

bool AbstractNode::IsDirty()const
{
    return _dirty;
}

void AbstractNode::SetDirty(bool value)
{
    _dirty = value;
}
