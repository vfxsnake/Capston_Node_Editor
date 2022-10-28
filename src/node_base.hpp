#pragma once
#include <iostream>
#include <vector>
#include "imgui.h"

// forward definition
// class Plug;

template<typename Derived>
class NodeBase
{
public:
    NodeBase()
    {
        std::cout << "Node template constructor"<< std::endl;
    }

    ~NodeBase()
    {
        std::cout << "Node template destructor"<< std::endl;
        _draw_list = nullptr;
    }

    void Draw()
    {
        _draw_list->ChannelsSplit(3);
        _draw_list->ChannelsSetCurrent(2);
        ImGui::BeginGroup(); // Lock horizontal position
        ImGui::Text("%s", _name);
        

        // Display node box
        _draw_list->ChannelsSetCurrent(1); // Background
        ImGui::SetCursorScreenPos(_position);
        ImGui::Button("node", ImVec2(10,10));
        ImVec2 min_size{10,5};
        ImU32 node_bg_color = IM_COL32(60, 60, 60, 255);
        _draw_list->AddRectFilled(min_size, _size, node_bg_color);
        _draw_list->AddRect(min_size, _size, IM_COL32(100, 100, 100, 255), 4.0f);  
        ImGui::EndGroup(); 
    }

    void Compute()
    {
        if(_dirty)
            static_cast<Derived*>(this)->Compute();
        _dirty = false; 
    }

    ImVec2 GetPosition()
    {
        return _position;
    }

    void SetPosition(int pos_x, int pos_y)
    {
        _position = ImVec2(pos_x, pos_y);
    }


    ImVec2 GetSize()
    {
        return _size;
    }

    void SetSize(int size_x, int size_y)
    {
        _size = ImVec2(size_x, size_y);
    }

    void SetDirty()
    {
        _dirty = false;
    }

    int GetId()
    {
        return _id;
    }

    void SetId(int id)
    {
        _id = id;
    }

    void SetName(const char* name)
    {
        strcpy(_name, name);
    }

    void SetDrawList(ImDrawList* draw_list)
    {
        _draw_list = draw_list;
    }

protected:
    // accessible to derived classes.
    // std::vector<Plug> plugs_in;
    // std::vector<Plug> plugs_out;

private:
    bool _dirty = true;
    int  _id;
    char _name[32];
    ImVec2 _position{50, 50};
    ImVec2 _size{50,100};
    ImDrawList* _draw_list;
    
}; 



class SimpleNode : public NodeBase<SimpleNode>
{
public:
    SimpleNode()
    {
        SetId(0);
        SetPosition(0,0);
        SetSize(50, 25);
        SetName("---test_node--");
        
    }
 
};