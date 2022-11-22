#include <iostream>
#include <memory>
#include <imnodes.h>
#include "evaluate_node_container.h"
#include "nodes.h"
#include "plug.hpp"

EvaluateNodeContainer::EvaluateNodeContainer(int &global_id)
{
    _logic = std::unique_ptr<EvaluationNode>(new EvaluationNode(global_id));
    SetId(_logic->GetId()); 
    SetPersistent(true);
    std::cout << "constructor EvaluationNodeContainer id: " << std::endl;
}

EvaluateNodeContainer::~EvaluateNodeContainer()
{
    std::cout << "destructor EvaluationNodeContainer id: "<< GetId() << std::endl;
}

void EvaluateNodeContainer::DrawNode() const
{
    // node begin
    _logic->Compute();
    ImNodes::BeginNode(GetId());
    
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("Evaluate Node");
    ImNodes::EndNodeTitleBar();
    
    // attribute definition.
    ImNodes::BeginStaticAttribute(_logic->GetResultId());
    ImGui::PushItemWidth(120.0f);
    float dynamic_value = _logic->GetResultValue();
    ImGui::DragFloat("value",&dynamic_value, 0.00);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    // Output attribute
    ImNodes::BeginInputAttribute(_logic->GetPlugIn_0()->GetId());
    const float text_width = ImGui::CalcTextSize("result").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("result");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}


std::vector<PlugIn<float>*> EvaluateNodeContainer::GetPlugIns() const
{
    return {_logic->GetPlugIn_0()};
}


std::vector<PlugOut<float>*> EvaluateNodeContainer::GetPlugOuts() const
{
    return {};
}