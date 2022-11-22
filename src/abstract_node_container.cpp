#include "abstract_node_container.h"

void AbstractNodeContainer::SetId(int id)
{
    _id = id;
}


int AbstractNodeContainer::GetId() const
{
    return _id;
}


void AbstractNodeContainer::SetPosition(ImVec2 position)
{
    _position = position;
}


ImVec2 AbstractNodeContainer::GetPosition() const
{
    return _position;
}

void AbstractNodeContainer::SetPersistent(bool value)
{
    _persistent = value;
}

bool AbstractNodeContainer::IsPersistent() const
{
    return _persistent;
}
