#include "cfbm/Increment.h"
#include "cfbm/Geometry.h"
#include "cfbm/State.h"

namespace cfbm {

Increment::Increment(const Geometry & geom, const eckit::Configuration & conf)
  : geom_(std::make_shared<const Geometry>(geom)) {
  // cfbm_inc_create_f90(keyF_, geom.keyF_);
}

//Constructor for specific variables at a specific time
Increment::Increment(const Geometry & geom,
                     const oops::Variables & vars,
                     const util::DateTime & time)
  : geom_(std::make_shared<const Geometry>(geom)),
    time_(time),
    vars_(vars) {

  // CURRENTLY: Do nothing or print

  // FUTURE: Call Fortran to allocate memory (initialized to zero usually)
  // cfbm_inc_create_vars_f90(keyF_, geom_->keyF_, vars_, time_);
  // cfbm_inc_zero_f90(keyF_);
}

Increment::~Increment() {
  // cfbm_inc_delete_f90(keyF_);
}

void Increment::diff(const State & x1, const State & x2) {
  // cfbm_inc_diff_f90(keyF_, x1.keyF_, x2.keyF_);
  time_ = x1.validTime();
}

void Increment::zero() {
  // cfbm_inc_zero_f90(keyF_);
}

void Increment::axpy(const double & zz, const Increment & dx, const bool check) {
  // cfbm_inc_axpy_f90(keyF_, zz, dx.keyF_);
}

Increment & Increment::operator+=(const Increment & dx) {
  this->axpy(1.0, dx);
  return *this;
}

Increment & Increment::operator-=(const Increment & dx) {
  this->axpy(-1.0, dx);
  return *this;
}

Increment & Increment::operator*=(const double & zz) {
  // cfbm_inc_mult_f90(keyF_, zz);
  return *this;
}

void Increment::read(const eckit::Configuration & conf) {}
void Increment::write(const eckit::Configuration & conf) const {}

void Increment::schur_product_with(const Increment & dx) {}
double Increment::dot_product_with(const Increment & other) const { return 0.0; }

void Increment::print(std::ostream & os) const {
  os << "CFBM Increment";
}

} // namespace cfbm