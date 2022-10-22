#include <iostream>
#include <memory>
#include "app.h"
#include "node_canvas.h"

App::App()
{
    std::cout << "app constructor"<< std::endl;
    _node_canvas = new NodeCanvas(0, "Node Canvas");
}

App::~App()
{
    if(_node_canvas)
    {
        delete _node_canvas;
    }
    std::cout << "app destructor."<< std::endl;
    
}

void App::Update()
{
    std::cout << "update derived" << std::endl;
    if(show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    if(_node_canvas)
        _node_canvas->Show();
}

