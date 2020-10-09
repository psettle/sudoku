/**
 * sdk_Pipeline.hpp - Solver pipeline
 */
#ifndef _SDK_PIPELINE
#define _SDK_PIPELINE
#include <memory>
#include <vector>

#include "sdk/data/Grid.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
class Pipeline {
 public:
  Pipeline(data::Grid* puzzle);

  void AddRule(interfaces::IRule* rule) {
    rules_.push_back(std::unique_ptr<interfaces::IRule>(rule));
  }

  bool Run();

 private:
  data::Grid* puzzle_;
  std::vector<std::unique_ptr<interfaces::IRule>> rules_;
};
}  // namespace sdk

#endif /* _SDK_PIPELINE */