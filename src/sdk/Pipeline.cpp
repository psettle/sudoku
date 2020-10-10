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
 * Run rules until no progress is being made, then check if the puzzle is solved.
 */
data::Grid::SolveResult Pipeline::Run() {
  // Run each rule until no progress is made
  while (true) {
    bool progress = false;
    for (auto& rule : rules_) {
      progress |= rule->Apply();
    }

    if (!progress) {
      break;
    }
  }

  return puzzle_->IsSolved();
}