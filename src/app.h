#pragma once

#include "glfw_app_base.hpp"

class App : public GLFWAppBase<App>
{
public:
    void Update();
private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

};