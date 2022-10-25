#include "node_editor.h"
#include "imgui.h"
#include <math.h>

NodeEditor::NodeEditor(int canvas_id, const char* canvas_name) : _id(canvas_id), _name(canvas_name)
{
}


NodeEditor::~NodeEditor()
{
}

void NodeEditor::Draw()
{
    ImGui::Begin("Node Graph");
    
    ImGui::SameLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    
    
    ImGui::End();
}


