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
  class State;

class Increment : public util::Printable,
                  private util::ObjectCounter<Increment> {
 public:
  static const std::string classname() { return "cfbm::Increment"; }

  Increment(const Geometry &, const eckit::Configuration &);
  Increment(const Geometry &, const Increment &);
  Increment(const Geometry &, const oops::Variables &, const util::DateTime &);
  Increment(const Geometry &, const State &); // Diff between two states
  ~Increment();

  // Linear Algebra
  void diff(const State &, const State &);
  void zero();
  void axpy(const double &, const Increment &, const bool check = true);
  Increment & operator+=(const Increment &);
  Increment & operator-=(const Increment &);
  Increment & operator*=(const double &);
  void schur_product_with(const Increment &);
  double dot_product_with(const Increment &) const;

  // I/O
  void read(const eckit::Configuration &);
  void write(const eckit::Configuration &) const;

  // Time
  void updateTime(const util::Duration & dt) { time_ += dt; }
  const util::DateTime & validTime() const { return time_; }
  const oops::Variables & variables() const { return vars_; }

 private:
  void print(std::ostream &) const override;
  std::shared_ptr<const Geometry> geom_;
  util::DateTime time_;
  oops::Variables vars_;

  // int keyF_; // Handle to Fortran object
};

} // namespace cfbm