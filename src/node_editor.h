#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "imgui.h"
#include "plug.hpp"

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
class AbstractPlug;

struct Link;

class NodeEditor
{
public:
    // this class must apply the rule of five as it will be a unique pointer in the app.
    NodeEditor(int canvas_id, const char* canvas_name, int node_ui_id_start=100, int editor_width=700, int editor_height=600, int creator_width=250);
    
    // destructor
    ~NodeEditor();

    // draws nodes, and links
    void Draw();

    // create node
    template<typename T>
    void AppendNodeToNodeMap(int &global_id);


private:
    void DrawCreator();
    void DrawCanvas();
    void DrawNodes();
    void DrawLinks();

    void DeleteLinks(int number_of_links_selected);
    void DeleteNodes(int number_of_nodes_selected);

    int _id; // window id for imgui
    const char* _name;
    int _editor_width;
    int _editor_height;

    int _creator_width;

    int _global_id_count = 0;
    std::map<int ,std::unique_ptr<AbstractNodeContainer>> _node_map;
    std::map<int , std::unique_ptr<Link>> _link_map;
    std::map<int, PlugIn<float>*> _plug_in_map;
    std::map<int, PlugOut<float>*> _plug_out_map;
};
