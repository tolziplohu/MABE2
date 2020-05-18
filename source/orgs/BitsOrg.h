/**
 *  @note This file is part of MABE, https://github.com/mercere99/MABE2
 *  @copyright Copyright (C) Michigan State University, MIT Software license; see doc/LICENSE.md
 *  @date 2019
 *
 *  @file  BitsOrg.h
 *  @brief An organism consisting of a series of bits.
 *  @note Status: ALPHA
 */

#ifndef MABE_BITS_ORGANISM_H
#define MABE_BITS_ORGANISM_H

#include "../core/MABE.h"
#include "../core/Organism.h"
#include "../core/OrganismManager.h"

#include "tools/BitVector.h"
#include "tools/random_utils.h"

namespace mabe {

  class BitsOrg : public Organism {
  protected:
    emp::BitVector bits;
    std::string output_name;  // @CAO: Should move this to org manager?

  public:
    BitsOrg(OrganismManager<BitsOrg> & _manager)
      : Organism(_manager), bits(100), output_name("bits") { }
    BitsOrg(const BitsOrg &) = default;
    BitsOrg(BitsOrg &&) = default;
    BitsOrg(const emp::BitVector & in, OrganismManager<BitsOrg> & _manager)
      : Organism(_manager), bits(in) { }
    BitsOrg(size_t N, OrganismManager<BitsOrg> & _manager)
      : Organism(_manager), bits(N), output_name("bits") { }
    ~BitsOrg() { ; }

    /// Use "to_string" to convert.
    std::string ToString() override { return emp::to_string(bits); }

    size_t Mutate(emp::Random & random) override {
      if (bits.size() == 0) return 0;
      for (size_t i = 0; i < 3; i++) {
        size_t pos = random.GetUInt(bits.size());
        bits[pos] = random.P(0.5);
      }
      return 3;
    }

    void Randomize(emp::Random & random) override {
      emp::RandomizeBitVector(bits, random, 0.5);
    }

    // Nothing to evaluate -- just put the bits in the correct output position.
    bool Evaluate() override {
      SetVar<emp::BitVector>(output_name, bits);
      return true;
    }

    /// Request output type (multiple types are possible); default to unknown.
    /// Argument is the output ID.
    emp::TypeID GetOutputType(size_t=0) override {
      return emp::GetTypeID<emp::BitVector>();
    }

    /// Setup this organism to load from config.
    void SetupConfig() override {
      LinkVar(output_name, "output_name",
              "Name of variable to contain bit sequence.",
              "bits");
      LinkFuns<size_t>([this](){ return bits.size(); },
                       [this](const size_t & N){ return bits.Resize(N); },
                       "N", "Number of bits in organism", 100);
    }
  };

  MABE_REGISTER_ORG_TYPE(BitsOrg, "Organism consisting of a series of N bits.");
}

#endif
