#include "cfbm/Geometry.h"

namespace cfbm {

Geometry::Geometry(const eckit::Configuration & conf,
                   const eckit::mpi::Comm & comm)
  : comm_(comm) {
    // HERE: You would typically call a Fortran routine to setup the
    // fire grid based on the config (e.g. setup_grid_f90(conf))
}

Geometry::~Geometry() {}

void Geometry::print(std::ostream & os) const {
  os << "CFBM Geometry";
}

} // namespace cfbm