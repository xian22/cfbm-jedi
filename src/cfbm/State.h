#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "oops/util/Printable.h"
#include "oops/util/DateTime.h"
#include "oops/util/ObjectCounter.h"
#include "eckit/config/Configuration.h"
#include "oops/base/Variables.h"

namespace cfbm {
  class Geometry;
  class Increment;

class State : public util::Printable,
              private util::ObjectCounter<State> {
 public:
  static const std::string classname() { return "cfbm::State"; }

  // Constructor 1: Create from Geometry and Config (e.g. Read from file)
  State(const Geometry &, const eckit::Configuration &);

  // Constructor 1b: Create from Geometry, Variables, and DateTime
  State(const Geometry &, const oops::Variables &, const util::DateTime &);

  // Constructor 2: Copy constructor
  State(const Geometry &, const State &);

  // Constructor 3: Create by adding Increment to State
  State(const Geometry &, const State &, const Increment &);

  ~State();

  // Required for JEDI
  void zero();
  void accumul(const double &);
  double norm() const;
  const util::DateTime & validTime() const { return time_; }
  void updateTime(const util::Duration & dt) { time_ += dt; }
  const oops::Variables & variables() const { return vars_; }

  // Read/Write (Crucial for PseudoModel)
  void read(const eckit::Configuration &);
  void write(const eckit::Configuration &) const;

 private:
  void print(std::ostream &) const override;

  // Pointer to geometry
  std::shared_ptr<const Geometry> geom_;

  // Valid time of the state
  util::DateTime time_;

// variables
  oops::Variables vars_;

  // HERE: You will eventually hold a pointer to Fortran data structures
  // int keyF_;
};

} // namespace cfbm