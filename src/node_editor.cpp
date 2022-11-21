#include <math.h>
#include <algorithm>
#include "node_editor.h"
#include "imgui.h"
#include "imnodes.h"
#include "abstract_node_container.h"
#include "float_node_container.h"
#include "float_addition_node_container.h"
#include "evaluate_node_container.h"
#include "link.hpp"


/*
    NodeEditor class manages the Node system
    creates nodes and register the nodes, plugs y links
    It contains a map structure so we can relate node plugs to node container plug.
*/
NodeEditor::NodeEditor(int canvas_id, const char* canvas_name, int node_ui_id_start, int editor_width, int editor_height) : 
                                                                                _id(canvas_id), // canvas window id to be recognized by imgui
                                                                                _name(canvas_name), 
                                                                                _global_id_count(node_ui_id_start), // offset when reloading an existing graph
                                                                                _editor_width(editor_height),
                                                                                _editor_height(editor_height)
{
    // Start the Graph node system provided by ImNodes.
    AppendNodeToNodeMap<FloatNodeContainer>(_global_id_count);
    AppendNodeToNodeMap<FloatNodeContainer>(_global_id_count);
    AppendNodeToNodeMap<FloatAdditionNodeContainer>(_global_id_count);

    AppendNodeToNodeMap<EvaluateNodeContainer>(_global_id_count);
    
    ImNodes::CreateContext();
}


NodeEditor::~NodeEditor()
{
    // Cleans all resources used by ImNodes.
    ImNodes::DestroyContext();
}


/*
    Main draw function for the node editor.
    Draws the canvas, nodes and links.
*/
void NodeEditor::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin("Node Editor");
    ImGui::SameLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGuiIO& io = ImGui::GetIO();
    // ImGui::SameLine();
    DrawCanvas();

    ImGui::End();
}


template<typename T>
void NodeEditor::AppendNodeToNodeMap(int &global_id)
{
    std::unique_ptr<T> new_node =  std::make_unique<T>(global_id);
    _node_map.emplace(new_node->GetId(), move(new_node));
}

void NodeEditor::DrawCanvas()
{
    ImNodes::BeginNodeEditor();
    
    // draw Nodes
    DrawNodes();

    // draw links
    DrawLinks();

    ImNodes::EndNodeEditor();
    
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        std::cout << "link created from : " << start_attr << " " << end_attr << std::endl;
        // call node editors create link and add it to the link list
        std::unique_ptr<Link> current_link = std::make_unique<Link>(++_global_id_count, start_attr, end_attr);
        _link_map.emplace(current_link->id, std::move(current_link));
    }

    if(ImGui::IsKeyReleased(ImGui::GetKeyIndex(ImGuiKey_Delete)))
    {
        std::cout << "delete key released" <<std::endl;
        int links_selected = ImNodes::NumSelectedLinks();
        DeleteLinks(links_selected);

        
        int nodes_selected = ImNodes::NumSelectedNodes();
        if(nodes_selected > 0)
        {
            DeleteNodes(nodes_selected);
        }
    }

}


void NodeEditor::DrawNodes()
{
    for (std::pair<const int, std::unique_ptr<AbstractNodeContainer>>& node_pair : _node_map)
    {
        node_pair.second->DrawNode();
    }
}


void NodeEditor::DrawLinks()
{
    for (std::pair<const int, std::unique_ptr<Link>>& link_pair : _link_map)
    {
        link_pair.second->DrawLink();
    }
}


void NodeEditor::DeleteLinks(int number_of_links_selected)
{
    if(number_of_links_selected > 0)
    {
        std::vector<int> links_id_vector;
        links_id_vector.resize(static_cast<size_t>(number_of_links_selected));
        ImNodes::GetSelectedLinks(links_id_vector.data()); 
        for(int id : links_id_vector)
        {
            _link_map.erase(id);
            std::cout << "link id: " << id << " deleted." << std::endl;
        
        }
    }
}


void NodeEditor::DeleteNodes(int number_of_nodes_selected)
{
    if(number_of_nodes_selected > 0)
    {
        std::vector<int> nodes_id_vector;
        nodes_id_vector.resize(static_cast<size_t>(number_of_nodes_selected));
        ImNodes::GetSelectedNodes(nodes_id_vector.data()); 
        for(int id : nodes_id_vector)
        {
            // look for connections ins and out connections to delete links before deleting
            _node_map.erase(id);
            std::cout << "node id: " << id << " deleted." << std::endl;
        }
    }

}