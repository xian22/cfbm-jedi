#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <memory> // Required for shared_ptr

#include "oops/util/Printable.h"
#include "oops/util/ObjectCounter.h"
#include "eckit/config/Configuration.h"
#include "eckit/mpi/Comm.h"

// ADD THESE ATLAS HEADERS
#include "atlas/functionspace/FunctionSpace.h"
#include "atlas/field/FieldSet.h"

namespace cfbm {

class Geometry : public util::Printable,
                 private util::ObjectCounter<Geometry> {
 public:
  static const std::string classname() { return "cfbm::Geometry"; }

  explicit Geometry(const eckit::Configuration &,
                    const eckit::mpi::Comm & comm = eckit::mpi::comm());
  ~Geometry();

  const eckit::mpi::Comm & getComm() const { return comm_; }

  bool levelsAreTopDown() const {return true;}

  // -------------------------------------------------------------------
  // REQUIRED BY JEDI/OOPS
  // -------------------------------------------------------------------
  const atlas::FunctionSpace & functionSpace() const { return functionSpace_; }
  const atlas::FieldSet      & fields()        const { return fields_; }

 private:
  void print(std::ostream &) const override;
  const eckit::mpi::Comm & comm_;

  // Fortran Handle
  std::uintptr_t keyF_;;

  // Atlas Objects (Placeholders)
  atlas::FunctionSpace functionSpace_;
  atlas::FieldSet fields_;
};

} // namespace cfbm