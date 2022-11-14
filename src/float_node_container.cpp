#include <iostream>
#include <memory>
#include <imnodes.h>
#include "float_node_container.h"
#include <nodes.h>
#include <plug.hpp>

FloatNodeContainer::FloatNodeContainer(int &global_id)
{
    _logic = std::make_unique<FloatNode>(FloatNode(global_id));
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
    ImGui::TextUnformatted(_logic->GetName());
    ImNodes::EndNodeTitleBar();
    
    // attribute definition.
    ImNodes::BeginStaticAttribute(_logic->GetDefaultValueId());
    ImGui::PushItemWidth(120.0f);
    float dynamic_value;
    ImGui::DragFloat("value", &dynamic_value, 0.01f);
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