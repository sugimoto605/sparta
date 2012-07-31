/* ----------------------------------------------------------------------
   SPARTA - Stochastic PArallel Rarefied-gas Time-accurate Analyzer
   www.sandia.gov/sparta.html
   Steve Plimpton, sjplimp@sandia.gov, Michael Gallis, magalli@sandia.gov
   Sandia National Laboratories

   Copyright (2012) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level SPARTA directory.
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

FixStyle(grid/check,FixGridCheck)

#else

#ifndef SPARTA_FIX_GRID_CHECK_H
#define SPARTA_FIX_GRID_CHECK_H

#include "fix.h"

namespace SPARTA_NS {

class FixGridCheck : public Fix {
 public:
  FixGridCheck(class SPARTA *, int, char **);
  ~FixGridCheck() {}
  int setmask();
  void init();
  void end_of_step();
  double compute_scalar();

 private:
  int nevery,nflag;
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running SPARTA to see the offending line.

*/
