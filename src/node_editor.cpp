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
NodeEditor::NodeEditor(int canvas_id, const char* canvas_name, int node_ui_id_start, int editor_width, int editor_height, int creator_width) : 
                                                                                _id(canvas_id), // canvas window id to be recognized by imgui
                                                                                _name(canvas_name), 
                                                                                _global_id_count(node_ui_id_start), // offset when reloading an existing graph
                                                                                _editor_width(editor_height),
                                                                                _editor_height(editor_height),
                                                                                _creator_width(creator_width)
{
    // Start the Graph node system provided by ImNodes.
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
    ImGui::Text("\t\t\t\t\tNavigate by clicking and sustain the Middle mouse button. move nodes by click dragging the Nodes.");

    // Draw creator
    DrawCreator();
    ImGui::SameLine();
    // canvas
    DrawCanvas();

    
    ImGui::End();
}


template<typename T>
void NodeEditor::AppendNodeToNodeMap(int &global_id)
{
    std::unique_ptr<T> new_node =  std::make_unique<T>(global_id);
    for (auto plug_in : new_node->GetPlugIns())
        _plug_in_map.emplace(plug_in->GetId(), plug_in);
    
    for (auto plug_out : new_node->GetPlugOuts())
        _plug_out_map.emplace(plug_out->GetId(), plug_out);

    _node_map.emplace(new_node->GetId(), move(new_node));
}


void NodeEditor::DrawCreator()
{
    ImGui::BeginChild("node_list", ImVec2(_creator_width, 0));
    ImGui::Text("Create Nodes.");
    
    ImGui::Separator();
    ImGui::Text("Create nodes by clicking in \nthe create buttons to add \nfloat values nodes or \naddition nodes.");
    ImGui::Text("Attributes can be updated by \n");
    ImGui::Text("left click and drag from \n left to right. \n");
    
    if(ImGui::Button("Create float Node",ImVec2(250, 20)))
    {
        AppendNodeToNodeMap<FloatNodeContainer>(_global_id_count);
    }
    
    if(ImGui::Button("Create Addition Node",ImVec2(250, 20)))
    {
        AppendNodeToNodeMap<FloatAdditionNodeContainer>(_global_id_count);
    }
    
    ImGui::Separator();
    ImGui::Text("connect the nodes by \n left click and drag from \n an out plug to an in plug.");
    ImGui::Separator();
    ImGui::Text("Links can only be created \n at not connected plugs, \n if a plug exists select \nand press delete.");
     ImGui::Separator();
    ImGui::Text("for deleting nodes select \nand press delete.");
     ImGui::Separator();
    ImGui::Text("for editing the nodes values \nleft click and drag left \n or right to slide the value.");
     ImGui::Separator();
    ImGui::Text("For evaluate the node graph \nconnect the out plug of the \n network to the evaluate node.");
    

    ImGui::EndChild();
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
        // call node editors create link and add it to the link list
        std::unique_ptr<Link> current_link = std::make_unique<Link>(++_global_id_count, start_attr, end_attr);
        if(_plug_in_map.at(end_attr)->GetSourcePlug() == nullptr)
        {
            _plug_in_map.at(end_attr)->SetSourcePlug(_plug_out_map.at(start_attr));
            _link_map.emplace(current_link->id, std::move(current_link));
        }
    }

    if(ImGui::IsKeyReleased(ImGui::GetKeyIndex(ImGuiKey_Delete)))
    {
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
            DeleteLink(id);
        }
        ImNodes::ClearLinkSelection();
    }
}


void NodeEditor::DeleteLink(int link_id)
{
    _plug_in_map.at(_link_map.at(link_id)->target_plug_id)->SetSourcePlug(nullptr);
    _link_map.erase(link_id);
    std::cout << "link id: " << link_id << " deleted." << std::endl;
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
            if (_node_map.at(id)->IsPersistent())
                continue;
            std::vector<int> links_connected = FindLinksConnectedToNode(id);
            for (int link_id : links_connected)
            {
                std::cout << "link connected : " << link_id << std::endl;
                DeleteLink(link_id);
            }

            _node_map.erase(id);
            std::cout << "node id: " << id << " deleted." << std::endl;
        }
        ImNodes::ClearNodeSelection();
    }

}

 std::vector<int> NodeEditor::FindLinksConnectedToNode(int node_id)const
 {
    std::vector<int> connected_links_ids = {};
    std::vector<int> inputs =  _node_map.at(node_id)->GetInputsId();
    
    for(auto& x : _link_map)
    {   
        for(auto y : inputs)
        {
            if(x.second->target_plug_id == y)
                connected_links_ids.emplace_back(x.first);
        }
    }
    
    std::vector<int> outputs = _node_map.at(node_id)->GetOutputsId();
    for(auto& x : _link_map)
    {   
        for(auto y : outputs)
        {
            if(x.second->source_plug_id == y)
                connected_links_ids.emplace_back(x.first);
        }
    }

    return connected_links_ids;
 }