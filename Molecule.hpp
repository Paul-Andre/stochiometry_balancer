#ifndef MOLECULE_CLASS_H
#define MOLECULE_CLASS_H

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Molecule{

	public:
	
	typedef map<string, int > AtomList;
	
	AtomList atomList;
	string initialForm;
	int coofficient;

};

ostream& operator<< (ostream& cout, const Molecule& mol);


bool readMolecule(istream& in, Molecule& mol);

#endif
