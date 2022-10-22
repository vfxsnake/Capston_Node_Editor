#pragma once
#include <iostream>


/*
    This class defines the window with a canvas to create, arrange and
    connect the nodes. 
    It contains a file menu to save and load previous node graphs
*/
class NodeCanvas
{
public:
    // this class must apply the rule of five as it will be a unique pointer in the app.
    NodeCanvas(int canvas_id, const char* canvas_name);
    ~NodeCanvas();

    // copy constructor
    NodeCanvas(NodeCanvas &source);
    // copy operator
    NodeCanvas& operator=(NodeCanvas &source);

    // move constructor
    NodeCanvas(NodeCanvas &&source);

    // move operator
    NodeCanvas& operator=(NodeCanvas &&source); 

    void Show();

    // getters
    int GetID();
    const char* GetName();

private:
    int _id;
    const char* _name;
};