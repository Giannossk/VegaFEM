#include <string.h>
#include "integratorSolverSelection.h"

namespace vega 
{

// returns the string corresponding to the selected integrator solver
void GetIntegratorSolver(char * solver)
{
  strcpy(solver, "UNKNOWN");

  #ifdef PCG 
    strcpy(solver, "PCG");
  #endif

  #ifdef SPOOLES 
    strcpy(solver, "SPOOLES");
  #endif

  #ifdef PARDISO 
    strcpy(solver, "PARDISO");
  #endif
}


} // namespace vega
