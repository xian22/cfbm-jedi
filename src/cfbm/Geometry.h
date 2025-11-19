#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "oops/util/Printable.h"
#include "oops/util/ObjectCounter.h"
#include "eckit/config/Configuration.h"
#include "eckit/mpi/Comm.h"

namespace cfbm {

class Geometry : public util::Printable,
                 private util::ObjectCounter<Geometry> {
 public:
  static const std::string classname() { return "cfbm::Geometry"; }

  // Constructor reads grid size from yaml (e.g., nx, ny)
  explicit Geometry(const eckit::Configuration &,
                    const eckit::mpi::Comm & comm = eckit::mpi::comm());

  ~Geometry();

  const eckit::mpi::Comm & getComm() const { return comm_; }

  // Helper to get grid dimensions (used by State)
  // You can add methods here like getNy(), getNx()

 private:
  void print(std::ostream &) const override;
  const eckit::mpi::Comm & comm_;
};

} // namespace cfbm