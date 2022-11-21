#include <memory>
#include <vector>
#include "abstract_node_container.h"

// forward declaration
class EvaluationNode;

template<typename>
class PlugIn;

template<typename>
class PlugOut;


class EvaluateNodeContainer : public AbstractNodeContainer
{
public:
    EvaluateNodeContainer(int &global_id);
    ~EvaluateNodeContainer();
    virtual void DrawNode() const override;
    std::vector<PlugIn<float>*> GetPlugIns() const;
    std::vector<PlugOut<float>*> GetPlugOuts() const;

private:
     std::unique_ptr<EvaluationNode> _logic;
};