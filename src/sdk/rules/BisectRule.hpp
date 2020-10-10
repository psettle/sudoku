/**
 * BisectRule.hpp - Bisect Rule
 *
 * Educated guess and check. Find cells with highly restricted options
 * and try the options to see if they break the grid or lead to shared outcomes.
 */
#include <stdint.h>
#include "sdk/data/Cell.hpp"
#include "sdk/data/Grid.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
namespace rules {

class BisectRule : public interfaces::IRule {
 public:
  virtual ~BisectRule() {}

  BisectRule(data::Grid* puzzle, uint8_t order, uint32_t depth)
      : puzzle_(puzzle), order_(order), depth_(depth) {}

  /**
   * Implements IRule::Apply
   */
  bool Apply() override;

 private:
  bool BisectCell(data::Cell* cell);

  data::Grid* puzzle_;
  uint8_t order_;
  uint32_t depth_;
};

}  // namespace rules
}  // namespace sdk