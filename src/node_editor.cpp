#include "node_editor.h"
#include "imgui.h"
#include <math.h>

// change this to basic math functions
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

NodeEditor::NodeEditor(int canvas_id, const char* canvas_name) : _id(canvas_id), _name(canvas_name)
{
    _scrolling = ImVec2(0.0f, 0.0f);
}


NodeEditor::~NodeEditor()
{
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
    ImGuiIO& io = ImGui::GetIO();
    ImGui::BeginGroup();
    ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", _scrolling.x, _scrolling.y);
    
    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
    ImGui::Checkbox("Show grid", &_show_grid);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
    ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    ImGui::PopStyleVar(); // WindowPadding
    ImGui::PushItemWidth(120.0f);

    const ImVec2 offset = ImGui::GetCursorScreenPos() + _scrolling;
    _draw_list = ImGui::GetWindowDrawList();
    
    // Display grid
    if (_show_grid)
    {
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = 64.0f;
        ImVec2 win_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_sz = ImGui::GetWindowSize();
        for (float x = fmodf(_scrolling.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
            _draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, GRID_COLOR);
        for (float y = fmodf(_scrolling.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
            _draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, GRID_COLOR);
    }

    // Scrolling
    if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
        _scrolling = _scrolling + io.MouseDelta;

    _draw_list->ChannelsMerge();
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::EndGroup();
}
