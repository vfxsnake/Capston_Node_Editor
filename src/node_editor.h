#pragma once
#include <iostream>
#include <math.h> // fmodf
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
class NodeEditor
{
public:
    // this class must apply the rule of five as it will be a unique pointer in the app.
    NodeEditor(int canvas_id, const char* canvas_name);
    // destructor
    ~NodeEditor();

    // copy constructor
    NodeEditor(NodeEditor &source);
    // copy operator
    NodeEditor& operator=(NodeEditor &source);

    // move constructor
    NodeEditor(NodeEditor &&source);

    // move operator
    NodeEditor& operator=(NodeEditor &&source); 

    void Draw();

    // getters
    int GetID();
    const char* GetName();

    // create node
    void AddNode(const char* node_name);

private:

    void DrawCanvas();
    void DrawGrid();
    void DrawOutLiner();

    int _id;
    const char* _name;

    bool _show_grid = true;
    ImVec2 _scrolling;
    ImDrawList* _draw_list;
    int _out_liner_width = 150;
    // std::vector<Node> nodes; // implement the array of nodes
    // std::vector<Link> links; // implement the array of links should be a class to call draw function of each node and link

};