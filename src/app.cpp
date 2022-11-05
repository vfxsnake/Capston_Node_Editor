#include <iostream>
#include <memory>
#include "app.h"
#include "node_editor.h"


App::App()
{
    std::cout << "app constructor"<< std::endl;
    _node_editor = new NodeEditor(1, "Node Editor");
}

App::~App()
{
    std::cout << "app destructor."<< std::endl;
    
}

void App::Update()
{
    // std::cout << "update derived" << std::endl;
    // if(show_demo_window)
    //     ImGui::ShowDemoWindow(&show_demo_window);
    if(_node_editor)
        _node_editor->Draw();
}

