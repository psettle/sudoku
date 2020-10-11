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
#include "sdk/interfaces/ISolveObserver.hpp"

namespace sdk {
namespace rules {

class BisectRule : public interfaces::IRule {
 public:
  virtual ~BisectRule() {}

  BisectRule(data::Grid* puzzle, uint8_t order, uint32_t depth);
  void SetObserver(interfaces::ISolveObserver* observer);
  bool Apply() override;

 private:
  bool BisectCell(data::Cell* cell);
  void SendBisectStart(data::Cell const& target) const;
  void SendBisectBreak(data::Cell const& target, data::Digit const& impossible_value) const;
  void SendBisectComplete(data::Grid const& impossible_values) const;

  data::Grid* puzzle_;
  uint8_t order_;
  uint32_t depth_;
  interfaces::ISolveObserver* observer_;
};

}  // namespace rules
}  // namespace sdk