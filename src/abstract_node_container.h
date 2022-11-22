#pragma once
#include <imgui.h>

class AbstractNodeContainer
{
public:
    // setters
    void SetId(int id);
    void SetPosition(ImVec2 position);
    
    // getters
    int GetId() const;
    ImVec2 GetPosition() const;

    // should be implemented in any future subclass.
    virtual void DrawNode() const = 0;
    
    void SetPersistent(bool value);
    bool IsPersistent() const;

private:
    float _id;
    ImVec2 _position;
    bool _persistent = false;
};