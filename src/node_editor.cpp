#include <math.h>
#include "node_editor.h"
#include "imgui.h"
#include "imnodes.h"


// change this to basic math functions
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

NodeEditor::NodeEditor(int canvas_id, const char* canvas_name) : _id(canvas_id), _name(canvas_name)
{
    _scrolling = ImVec2(0.0f, 0.0f);
    ImNodes::CreateContext();
}


NodeEditor::~NodeEditor()
{
    ImNodes::DestroyContext();
}

void NodeEditor::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin("Node Editor");
    ImGui::SameLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGuiIO& io = ImGui::GetIO();
    DrawOutLiner();
    ImGui::SameLine();
    DrawCanvas();

    ImGui::End();
}


void NodeEditor::DrawOutLiner()
{
    ImGui::BeginChild("node_list", ImVec2(_out_liner_width, 0));
    ImGui::Text("Outliner");
    ImGui::Separator();
    // TODO: initialize the content for element in node list
    // for (int node_idx = 0; node_idx < nodes.Size; node_idx++)
    // {
    //     Node* node = &nodes[node_idx];
    //     ImGui::PushID(node->ID);
    //     if (ImGui::Selectable(node->Name, node->ID == node_selected))
    //         node_selected = node->ID;
    //     if (ImGui::IsItemHovered())
    //     {
    //         node_hovered_in_list = node->ID;
    //         open_context_menu |= ImGui::IsMouseClicked(1);
    //     }
    //     ImGui::PopID();
    // }
    ImGui::EndChild();
}

void NodeEditor::DrawCanvas()
{
    ImNodes::BeginNodeEditor();

    
    ImNodes::EndNodeEditor();
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        std::cout << "link created from : " << start_attr << " " << end_attr << std::endl;
    }
}