#include <iostream>
#include <memory>
#include <imnodes.h>
#include "float_addition_node_container.h"
#include "nodes.h"
#include "plug.hpp"

FloatAdditionNodeContainer::FloatAdditionNodeContainer(int &global_id)
{
    _logic = std::unique_ptr<FloatAdditionNode>(new FloatAdditionNode(global_id));
    SetId(_logic->GetId()); 
    std::cout << "constructor floatNodeContainer id: " << std::endl;
}

FloatAdditionNodeContainer::~FloatAdditionNodeContainer()
{
    std::cout << "destructor floatNodeContainer id: "<< GetId() << std::endl;
}

void FloatAdditionNodeContainer::DrawNode() const
{
    // node begin
    ImNodes::BeginNode(GetId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("Float Addition Node");
    ImNodes::EndNodeTitleBar();

    // input 0
    ImNodes::BeginInputAttribute(_logic->GetPlugIn_0()->GetId());
    float text_width = ImGui::CalcTextSize("in_0").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("in_0").x - text_width);
    ImGui::TextUnformatted("in_0");
    ImNodes::EndInputAttribute();

    // attribute 0 definition.
    if(_logic->GetPlugIn_0()->GetSourcePlug() == nullptr)
    {
        ImNodes::BeginStaticAttribute(_logic->GetDefaultValue_0_Id());
        ImGui::PushItemWidth(120.0f);
        float dynamic_value_0 = _logic->GetDefaultValue_0();
        ImGui::DragFloat("value_0",&dynamic_value_0, 0.01f);
        if (dynamic_value_0 != _logic->GetDefaultValue_0())
        {
            _logic->SetDefaultValue_0(dynamic_value_0);
        }
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    // input 1
    ImNodes::BeginInputAttribute(_logic->GetPlugIn_1()->GetId());
    text_width = ImGui::CalcTextSize("in_1").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("in_1").x - text_width);
    ImGui::TextUnformatted("in_1");
    ImNodes::EndInputAttribute();

    // attribute 1 definition.
    if(_logic->GetPlugIn_1()->GetSourcePlug() == nullptr)
    {
        ImNodes::BeginStaticAttribute(_logic->GetDefaultValue_1_Id());
        ImGui::PushItemWidth(120.0f);
        float dynamic_value_1 = _logic->GetDefaultValue_1();
        ImGui::DragFloat("value_1",&dynamic_value_1, 0.01f);
        if (dynamic_value_1 != _logic->GetDefaultValue_1())
        {
            _logic->SetDefaultValue_1(dynamic_value_1);
        }
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    // Output attribute
    ImNodes::BeginOutputAttribute(_logic->GetOutPlug()->GetId());
    text_width = ImGui::CalcTextSize("output").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}


std::vector<PlugIn<float>*> FloatAdditionNodeContainer::GetPlugIns() const
{
    return {_logic->GetPlugIn_0(), _logic->GetPlugIn_1()};
}


std::vector<PlugOut<float>*> FloatAdditionNodeContainer::GetPlugOuts() const
{
    return {_logic->GetOutPlug()};
}