/**
 * Pipeline.cpp - Solver Pipeline
 */
#include "sdk/Pipeline.hpp"

using namespace sdk;

/**
 * Initialize the pipeline with the puzzle to solve
 */
Pipeline::Pipeline(data::Grid* puzzle) : puzzle_(puzzle) {}

/**
 * Add trivial rule. These are rules so simple you wouldn't
 * usually call them out as even being a step.
 */
void Pipeline::AddTrivialRule(interfaces::IRule* rule) {
  trivial_rules_.push_back(std::unique_ptr<interfaces::IRule>(rule));
}

/**
 * Add complex rule. These are more complex rules that are still logical deduction.
 */
void Pipeline::AddComplexRule(interfaces::IRule* rule) {
  complex_rules_.push_back(std::unique_ptr<interfaces::IRule>(rule));
}

/**
 * Add hammer rule. These are extremly expensive operations to resolve complex grid states.
 */
void Pipeline::AddHammerRule(interfaces::IRule* rule) {
  hammer_rules_.push_back(std::unique_ptr<interfaces::IRule>(rule));
}

/**
 * Run rules until no progress is being made, then check if the puzzle is solved.
 */
data::Grid::SolveResult Pipeline::Run() {
  // Run each rule until no progress is made
  while (true) {
    bool progress = false;
    for (auto& rule : trivial_rules_) {
      progress |= rule->Apply();
    }

    if (progress) {
      continue;
    }

    for (auto& rule : complex_rules_) {
      progress |= rule->Apply();
    }

    if (progress) {
      continue;
    }

    for (auto& rule : hammer_rules_) {
      progress |= rule->Apply();
    }

    if (!progress) {
      break;
    }
  }

  return puzzle_->IsSolved();
}