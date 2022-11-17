#include <memory>
#include "abstract_node_container.h"

// forward declaration
class EvaluationNode;

class EvaluateNodeContainer : public AbstractNodeContainer
{
public:
    EvaluateNodeContainer(int &global_id);
    ~EvaluateNodeContainer();
    virtual void DrawNode() const override;

private:
     std::unique_ptr<EvaluationNode> _logic;
};