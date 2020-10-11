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
  void AddTrivialRule(interfaces::IRule* rule);
  void AddComplexRule(interfaces::IRule* rule);
  void AddHammerRule(interfaces::IRule* rule);
  data::Grid::SolveResult Run();

 private:
  data::Grid* puzzle_;
  std::vector<std::unique_ptr<interfaces::IRule>> trivial_rules_;
  std::vector<std::unique_ptr<interfaces::IRule>> complex_rules_;
  std::vector<std::unique_ptr<interfaces::IRule>> hammer_rules_;
};
}  // namespace sdk

#endif /* _SDK_PIPELINE */