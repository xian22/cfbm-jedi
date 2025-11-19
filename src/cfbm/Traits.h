#pragma once

#include <string>
#include "oops/base/Variables.h"

namespace cfbm {

class Geometry;
class State;
class Increment;

struct Traits {
  static std::string name() { return "CFBM"; }

  using Geometry = cfbm::Geometry;
  using State    = cfbm::State;
  using Increment= cfbm::Increment;

  using Variables = oops::Variables;

  // For simple PseudoModel/LETKF, we can often alias these to generic/empty classes
  // or implement minimal versions later.
  using GetValues = void; // Placeholder for now
  using LinearModel = void; // Placeholder
  using ModelAuxControl = void; // Placeholder
};

} // namespace cfbm