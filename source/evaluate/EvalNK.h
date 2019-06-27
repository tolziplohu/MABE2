/**
 *  @note This file is part of MABE, https://github.com/mercere99/MABE2
 *  @copyright Copyright (C) Michigan State University, MIT Software license; see doc/LICENSE.md
 *  @date 2019
 *
 *  @file  EvalNK.h
 *  @brief MABE Evaluation module for NK Landscapes
 */

#ifndef MABE_EVAL_NK_H
#define MABE_EVAL_NK_H

#include "../core/MABE.h"
#include "../core/ModuleEvaluate.h"
#include "../tools/NK.h"

#include "tools/reference_vector.h"

namespace mabe {

  class EvalNK : public ModuleEvaluate {
  private:
    size_t N;
    size_t K;
    NKLandscape landscape;

  public:
    EvalNK(size_t _N, size_t _K) : N(_N), K(_K) { }
    ~EvalNK() { }

    void Setup(mabe::World & world) {
      landscape.Config(N, K, world.GetRandom());  // Setup the fitness landscape.
    }

    void Update() {
      // Loop through the populations and evaluate each organism.
      for (auto & pop : pops) {
        for (auto & org : pop) {
          org.GenerateOutput("NK");
          double fitness = landscape.GetFitness( org.GetVar<emp::BitVector>("NK") );
          org.SetVar<double>("fitness", fitness);
        }
      }
    }
  };

}

#endif
