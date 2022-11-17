#include <math.h>
#include "node_editor.h"
#include "imgui.h"
#include "imnodes.h"
#include "abstract_node_container.h"
#include "float_node_container.h"
#include "float_addition_node_container.h"


/*
    NodeEditor class manages the Node system
    creates nodes and register the nodes, plugs y links
    It contains a map structure so we can relate node plugs to node container plug.
*/
NodeEditor::NodeEditor(int canvas_id, const char* canvas_name, int node_ui_id_start) : 
                                                                                _id(canvas_id), // canvas window id to be recognized by imgui
                                                                                _name(canvas_name), 
                                                                                _global_id_count(node_ui_id_start) // offset when reloading an existing graph
{
    // Start the Graph node system provided by ImNodes.
    _global_id_count = 0;
    _node_list.emplace_back(std::unique_ptr<AbstractNodeContainer>(new FloatNodeContainer(_global_id_count)));
    _node_list.emplace_back(std::unique_ptr<AbstractNodeContainer>(new FloatNodeContainer(_global_id_count)));
    _node_list.emplace_back(std::unique_ptr<AbstractNodeContainer>(new FloatAdditionNodeContainer(_global_id_count)));

    ImNodes::CreateContext();
}


NodeEditor::~NodeEditor()
{
    // Cleans all resources used by ImNodes.
    ImNodes::DestroyContext();
}

/*
    Main draw function for the node editor.
    Draws the Node out-liner creator, the Node canvas.
*/
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
    
    // draw Nodes
    for (std::unique_ptr<AbstractNodeContainer>& node : _node_list)
    {
        node->DrawNode();
    }
    // draw links
    

    ImNodes::EndNodeEditor();
    
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        std::cout << "link created from : " << start_attr << " " << end_attr << std::endl;
        // call node editors create link and add it to the link list
    }

    int link_id;
    if(ImNodes::IsLinkDestroyed(&link_id))
    {
        std::cout << "link destroyed" << std::endl;
        // call destroy link and releases the connection
    }
}

void NodeEditor::DrawNodes()
{
    // implement draw containers
}

void NodeEditor::DrawLinks()
{
    // implements draw links
}