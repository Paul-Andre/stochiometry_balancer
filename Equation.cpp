

#include "Equation.hpp"
#include "readUtils.hpp"
#include <set>
#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>
#include "solve.hpp"
using namespace boost::numeric::ublas;

bool readEquation (istream& in, Equation& eq){
	
	while(true){
		
		Molecule mol;
		
		ignoreWhitespace(in);
		
		if(readMolecule(in,mol)){
			eq.reactants.insert(eq.reactants.end(),mol);
			typedef Molecule::AtomList::const_iterator atomIt;
			for(atomIt i=mol.atomList.begin();i!=mol.atomList.end();i++){
				eq.atoms.insert(i->first);
			}
		}
		else if(confirmString(in,"+")){
		}
		else if(confirmString(in,"->")||
				confirmString(in,"=>")||
				confirmString(in,"-->")||
				confirmString(in,"==>")||
				confirmString(in,"=")||
				confirmString(in,"→")||
				confirmString(in,"==")){
			goto products_loop;
		}
		else return false;
		
		
	
	}
	
	products_loop:

	while(true){
	
		Molecule mol;
		
		ignoreWhitespace(in);
		
		if(readMolecule(in,mol)){
		
			eq.products.insert(eq.products.end(),mol);
				typedef Molecule::AtomList::const_iterator atomIt;
			for(atomIt i=mol.atomList.begin();i!=mol.atomList.end();i++){
				eq.atoms.insert(i->first);
			}
			
		}
		else if(confirmString(in,"+")){
		
		}else {
		
			break;
		}

	}


	
	if (eq.reactants.empty()||eq.products.empty()) return false;
	else return true;

}

ostream& operator<< (ostream& out, const Equation& eq){

	
	

	
	for(unsigned i=0;i<eq.reactants.size();i++){
		
		cout<<eq.reactants[i]<<" ";
		if(i<eq.reactants.size()-1)cout<<"+ ";
		
	
	}
	
	cout<<"-> ";
	
	for(unsigned i=0;i<eq.products.size();i++){
	
		cout<<eq.products[i]<<" ";
		if(i<eq.products.size()-1)cout<<"+ ";
	
	}	
	
	
	return out;


}


bool Equation::balance(){

using namespace std;
using namespace boost::numeric;

	int matrixWidth=reactants.size()+products.size();
	int matrixHeight=atoms.size();
	
	map<string, int> elementIndex;
	
	//std::cout<<*this;
	
	{
		typedef set<string>::const_iterator setIt;
	setIt i;
	unsigned ii;
	for(i=atoms.begin(),ii=1;i!=atoms.end();i++,ii++){
	
		elementIndex[*i]=ii;
	
	}
	}
	
	
	
	if(matrixWidth!=(matrixHeight+1)){
	
		return false;
		
	}
	
	
	ublas::matrix<int > prematrix(matrixWidth,matrixHeight+1);
	unsigned ii=0;
	
	{for (unsigned i = 0; i < prematrix.size1 (); ++ i)
		for (unsigned j = 0; j < prematrix.size2 (); ++ j)
			prematrix(i, j) = 0;
	}
	
	
	typedef std::vector<Molecule>::iterator molIt;
	
	for(molIt i=reactants.begin();i!=reactants.end();i++,ii++){
	
		typedef Molecule::AtomList::const_iterator atIt;
		for(atIt j=i->atomList.begin();j!= i->atomList.end();j++){
			
			
			prematrix(elementIndex[j->first],ii)=j->second;
		}
	
	}
	
	
	for(molIt i=products.begin();i!=products.end();i++,ii++){
	
		typedef Molecule::AtomList::const_iterator atIt;
		for(atIt j=i->atomList.begin();j!= i->atomList.end();j++){
			
			
			prematrix(elementIndex[j->first],ii)=-j->second;
		}
	
	}
	
	prematrix(0,0)=1;
	
	//cout<<prematrix<<endl;
	
	
	std::vector<int > solution;
	
	bool solved=solve(prematrix,solution);
	
	//cout<<solved<<endl;
	if(!solved){
		return false;
	}
		
	//cout<<solution;
	
	for(unsigned i=0; i<solution.size();i++){
	
		if(i<reactants.size()){
			reactants.at(i).coofficient=solution[i];
		
		
		}else{
		
			products.at(i-reactants.size()).coofficient=solution[i];
		
		}
	
	}
	
	return true;
}
