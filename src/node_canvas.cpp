#include "node_canvas.h"
#include "imgui.h"

NodeCanvas::NodeCanvas(int canvas_id, const char* canvas_name) : _id(canvas_id), _name(canvas_name)
{
}


NodeCanvas::~NodeCanvas()
{
}

void NodeCanvas::Show()
{
    ImGui::Begin("Node Graph");                          // Create a window called "Hello, world!" and append into it.
    ImGui::SameLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}