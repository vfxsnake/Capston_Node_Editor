#include <iostream>
#include <memory>
#include "app.h"
#include "node_editor.h"


App::App()
{
    std::cout << "app constructor"<< std::endl;
    _node_editor = new NodeEditor(0, "Node Editor");
}

App::~App()
{
    std::cout << "app destructor."<< std::endl;
    delete _node_editor;
    
}

void App::Update()
{
    if(_node_editor)
        _node_editor->Draw();
}

