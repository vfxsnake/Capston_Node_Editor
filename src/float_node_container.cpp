#include <iostream>
#include <memory>
#include <imnodes.h>
#include "float_node_container.h"
#include "nodes.h"
#include "plug.hpp"

FloatNodeContainer::FloatNodeContainer(int &global_id)
{
    _logic = std::unique_ptr<FloatNode>(new FloatNode(global_id));
    SetId(_logic->GetId()); 
    std::cout << "constructor floatNodeContainer id: " << std::endl;
}

FloatNodeContainer::~FloatNodeContainer()
{
    std::cout << "destructor floatNodeContainer id: "<< GetId() << std::endl;
}

void FloatNodeContainer::DrawNode() const
{
    // node begin
    ImNodes::BeginNode(GetId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("Float Node");
    ImNodes::EndNodeTitleBar();
    // attribute definition.
    ImNodes::BeginStaticAttribute(_logic->GetDefaultValueId());
    ImGui::PushItemWidth(120.0f);
    float dynamic_value = _logic->GetDefaultValue();
    ImGui::DragFloat("value",&dynamic_value, 0.01f);
    if (dynamic_value != _logic->GetDefaultValue())
        _logic->SetDefaultValue(dynamic_value);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    // Output attribute
    ImNodes::BeginOutputAttribute(_logic->GetOutPlug()->GetId());
    const float text_width = ImGui::CalcTextSize("output").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();  
}


std::vector<PlugIn<float>*> FloatNodeContainer::GetPlugIns() const
{
    return {};
}


std::vector<PlugOut<float>*> FloatNodeContainer::GetPlugOuts() const
{
    return {_logic->GetOutPlug()};
}


std::vector<int> FloatNodeContainer::GetInputsId() const
{
    return {};
}   


std::vector<int> FloatNodeContainer::GetOutputsId() const
{
    std::vector<int> plug_outs = {};
    for(PlugOut<float>* plug : GetPlugOuts())
        plug_outs.emplace_back(plug->GetId());
    return plug_outs;
}