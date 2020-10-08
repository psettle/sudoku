/**
 * sdk_Pipeline.hpp - Solver pipeline
 */
#ifndef _SDK_PIPELINE
#define _SDK_PIPELINE
#include <memory>
#include <vector>

#include "sdk_Grid.hpp"
#include "sdk_IRule.hpp"

namespace sdk {
class Pipeline {
 public:
  Pipeline(Grid* puzzle);

  void AddRule(IRule* rule) { rules_.push_back(std::unique_ptr<IRule>(rule)); }

  bool Run();

 private:
  Grid* puzzle_;
  std::vector<std::unique_ptr<IRule>> rules_;
};
}  // namespace sdk

#endif /* _SDK_PIPELINE */