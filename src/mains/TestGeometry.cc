#include "cfbm/Traits.h"
#include "cfbm/Geometry.h"
#include "oops/runs/Run.h"
#include "test/interface/Geometry.h"

int main(int argc,  char ** argv) {
  // 1. Initialize MPI and Logging (OOPS does this for you)
  oops::Run run(argc, argv);

  // 2. Define the Test Suite we want to run
  // test::Geometry is a pre-written JEDI test that checks if a Geometry
  // can be constructed and printed correctly.
  test::Geometry<cfbm::Traits> tests;

  // 3. Execute
  return run.execute(tests);
}