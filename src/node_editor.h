#pragma once
#include <iostream>


// forward declaration


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

private:

    void DrawCanvas();
    void DrawGrid();
    void DrawOutLiner();

    int _id;
    const char* _name;
};