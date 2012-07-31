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

#include "string.h"
#include "compute_ke_molecule.h"
#include "particle.h"
#include "update.h"
#include "modify.h"
#include "comm.h"
#include "memory.h"
#include "error.h"

using namespace SPARTA_NS;

/* ---------------------------------------------------------------------- */

ComputeKEMolecule::ComputeKEMolecule(SPARTA *sparta, int narg, char **arg) :
  Compute(sparta, narg, arg)
{
  if (narg != 2) error->all(FLERR,"Illegal compute ke/molecule command");

  per_molecule_flag = 1;
  size_per_molecule_cols = 0;

  nmax = 0;
  ke = NULL;
}

/* ---------------------------------------------------------------------- */

ComputeKEMolecule::~ComputeKEMolecule()
{
  memory->destroy(ke);
}

/* ---------------------------------------------------------------------- */

void ComputeKEMolecule::init()
{
  int count = 0;
  for (int i = 0; i < modify->ncompute; i++)
    if (strcmp(modify->compute[i]->style,"ke/molecule") == 0) count++;
  if (count > 1 && comm->me == 0)
    error->warning(FLERR,"More than one compute ke/molecule");
}

/* ---------------------------------------------------------------------- */

void ComputeKEMolecule::compute_per_molecule()
{
  invoked_per_molecule = update->ntimestep;

  // grow ke array if necessary

  if (particle->nlocal > nmax) {
    memory->destroy(ke);
    nmax = particle->maxlocal;
    memory->create(ke,nmax,"ke/molecule:ke");
    vector_molecule = ke;
  }

  // compute kinetic energy for each atom in group

  Particle::Species *species = particle->species;
  Particle::OnePart *particles = particle->particles;
  int nlocal = particle->nlocal;

  double mass;
  double *v;
  double mvv2e = update->mvv2e;

  for (int i = 0; i < nlocal; i++) {
    mass = species[particles[i].ispecies].mass;
    v = particles[i].v;
    ke[i] = 0.5 * mvv2e * mass * (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  }
}

/* ----------------------------------------------------------------------
   memory usage of local atom-based array
------------------------------------------------------------------------- */

bigint ComputeKEMolecule::memory_usage()
{
  bigint bytes = nmax * sizeof(double);
  return bytes;
}
