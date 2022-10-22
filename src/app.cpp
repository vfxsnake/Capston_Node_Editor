#include "app.h"
#include <iostream>


void App::Update()
{
    std::cout << "update derived" << std::endl;
    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
}