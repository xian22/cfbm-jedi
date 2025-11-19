#include "cfbm/State.h"
#include "cfbm/Geometry.h"
#include "cfbm/Increment.h"

#include "eckit/exception/Exceptions.h"

namespace cfbm {

// Constructor: Read from file
State::State(const Geometry & geom, const eckit::Configuration & conf)
  : geom_(std::make_shared<const Geometry>(geom)) {

  if (conf.has("date")) {
    time_ = util::DateTime(conf.getString("date"));
  }

  // HERE: Call Fortran to allocate fields and read NetCDF file
  // cfbm_state_create_f90(keyF_, geom.keyF_, conf);
  // cfbm_state_read_f90(keyF_, conf);
}

//Constructor for specific variables at a specific time
State::State(const Geometry & geom,
             const oops::Variables & vars,
             const util::DateTime & time)
  : geom_(std::make_shared<const Geometry>(geom)),
    time_(time),
    vars_(vars) {

  // CURRENTLY: Just printing for debugging
  // std::cout << "CFBM: Allocating State for variables: " << vars_ << std::endl;

  // FUTURE: Call Fortran to allocate memory for these specific variables
  // cfbm_state_create_vars_f90(keyF_, geom_->keyF_, vars_, time_);
}

// Copy Constructor
State::State(const Geometry & geom, const State & other)
  : geom_(std::make_shared<const Geometry>(geom)), time_(other.time_) {
  // cfbm_state_clone_f90(keyF_, other.keyF_);
}

// State + Increment
State::State(const Geometry & geom, const State & state, const Increment & inc)
  : geom_(std::make_shared<const Geometry>(geom)), time_(state.time_) {
  // cfbm_state_add_inc_f90(keyF_, state.keyF_, inc.keyF_);
}

State::~State() {
  // cfbm_state_delete_f90(keyF_);
}

void State::read(const eckit::Configuration & conf) {
   // cfbm_state_read_f90(keyF_, conf);
}

void State::write(const eckit::Configuration & conf) const {
   // cfbm_state_write_f90(keyF_, conf);
}

void State::zero() {
   // cfbm_state_zero_f90(keyF_);
}

void State::accumul(const double & zz) {
   // cfbm_state_axpy_f90(keyF_, zz);
}

double State::norm() const {
   // return cfbm_state_rms_f90(keyF_);
   return 0.0;
}

void State::print(std::ostream & os) const {
  os << "CFBM State valid at " << time_;
}

} // namespace cfbm