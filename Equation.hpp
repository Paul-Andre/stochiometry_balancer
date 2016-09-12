#ifndef EQUATION_CLASS_H
#define EQUATION_CLASS_H


#include <vector>
#include <iostream>
#include <set>

#include "Molecule.hpp"


class Equation{

public:
vector<Molecule> reactants;
vector<Molecule> products;

set<string> atoms;

bool balance();
};

bool readEquation (istream& in, Equation& eq);
ostream& operator<< (ostream& out,const Equation& eq);

#endif
