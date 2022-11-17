#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "imgui.h"

// #include "node_base.hpp"

// forward declaration not working for structs imgui.h needed
// struct ImVec2;
// struct ImDrawList;

/*
    This class defines the window with a canvas to create, arrange and
    connect the nodes. 
    It contains a file menu to save and load previous node graphs
*/

// forward declarations
class NodeContainers;
class AbstractNodeContainer;
struct Link;

class NodeEditor
{
public:
    // this class must apply the rule of five as it will be a unique pointer in the app.
    NodeEditor(int canvas_id, const char* canvas_name, int node_ui_id_start=0);
    
    // destructor
    ~NodeEditor();

    // draws nodes, and links
    void Draw();

    // getters
    int GetNodeEditorId();
    const char* GetName();

    // create node
    void AddNode(const char* node_name);

private:

    void DrawCanvas();
    void DrawOutLiner();
    void DrawNodes();
    void DrawLinks();

    int _id; // window id for imgui
    const char* _name;

    int _out_liner_width = 150;
    int _global_id_count = 0;
    std::vector<std::unique_ptr<AbstractNodeContainer>> _node_list;
    std::vector<std::unique_ptr<Link>> _link_list;
};