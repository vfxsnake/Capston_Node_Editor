#pragma once
#include <memory>
#include "glfw_app_base.hpp"

// forward declarations
class NodeEditor;

class App : public GLFWAppBase<App>
{
public:
    App();
    ~App();
    void Update();

private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    std::unique_ptr<NodeEditor> _node_editor;
};