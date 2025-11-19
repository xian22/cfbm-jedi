#include "cfbm/Geometry.h"
#include "eckit/config/Configuration.h"

// -----------------------------------------------------------------------------
// 1. Define the Interface to Fortran
// -----------------------------------------------------------------------------
extern "C" {
  // Setup: Fortran writes to this variable, so we pass by Reference (&)
  void cfbm_geo_setup_f90(const eckit::Configuration &, std::uintptr_t &);

  // Delete: Fortran needs the value of the address, so we pass by Value (no &)
  void cfbm_geo_delete_f90(std::uintptr_t);
}

namespace cfbm {

// -----------------------------------------------------------------------------

Geometry::Geometry(const eckit::Configuration & conf,
                   const eckit::mpi::Comm & comm)
  : comm_(comm) {

    // 2. Call Fortran
    // We pass 'conf' (the yaml) and receive 'keyF_' (the address of the fortran object)
    // Note: 'keyF_' must be defined in your Geometry.h as 'int keyF_;'
    // or we can cast it here if you used a pointer.

    // NOTE: If you haven't added 'int keyF_;' to Geometry.h yet,
    // add it as a private member now!
    cfbm_geo_setup_f90(conf, keyF_);
}

Geometry::~Geometry() {
    cfbm_geo_delete_f90(keyF_);
}

void Geometry::print(std::ostream & os) const {
  os << "CFBM Geometry";
  // Eventually you can call a Fortran routine here to print dimensions
}


} // namespace cfbm