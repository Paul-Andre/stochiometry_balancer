
#include "readUtils.hpp"

#include "Molecule.hpp"

#define FOR_EVERY(iter, iterable) for(typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); ++iter)

#define FOR_EVERY_CONST(iter, iterable) for(typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); ++iter)

ostream& operator<< (ostream& cout, const map<string, int> m){

	FOR_EVERY_CONST(i,m){
	
		
	
	}


}

ostream& operator<< (ostream& cout, const Molecule& molecule){

	typedef Molecule::AtomList::const_iterator MolIterator;
	
	map<string, int> mol=molecule.atomList;
	
	if(mol.empty()){cout<<"[empty]";}
	
	cout<<molecule.coofficient<<" ";
	
	for(MolIterator i=mol.begin(); i!=mol.end(); i++){
	
		cout<<   i->first  <<"("<<  i->second  <<")"; 
	
	}
	
		cout << molecule.initialForm;

	return cout;
}


map<string, int> readPartOfFormula(istream& in){

	map<string, int> mol;
	
	
		while(true){
	
			string elem;
			int cooficient;
		
			ignoreWhitespace(in);
			if(readElem(in,elem)){
		
				if(!readNumber(in,cooficient))cooficient=1;
				//cout<<(int)in.tellg()<<endl;
				mol[elem]+=cooficient;
			}
			else if(confirmString(in,"(")){
			
				int parCooficient;
				map<string, int> tempMol;
				tempMol=readPartOfFormula(in);
				
				if (confirmString(in,")")){
				
					if(!readNumber(in,parCooficient)){
						
						parCooficient=1;
					
					}
					
					FOR_EVERY(i,tempMol){
					
						mol[i->first]+=i->second*parCooficient;
					
					}
				
				}
			
			}else if(checkString(in,")")){break;}
			else break;
		}
	
		return mol;
	

}



bool readMolecule(istream& in, Molecule& molecule){

	map<string, int> & mol= molecule.atomList;
	
	mol.clear();
	
	
	
	ignoreWhitespace(in);
	int temp;
	readNumber(in,temp);
	ignoreWhitespace(in);
	
	streampos begin=in.tellg();
	if (begin==-1) return false;
	streampos end;
	

	
	mol=readPartOfFormula(in);
	
	end=in.tellg();
	if(mol.empty()!=true){
	
	if(end==-1){
	in.clear();
	in.seekg(0, in.end);
	end=in.tellg();
	
	}
	
	in.clear();
	in.seekg(begin);
	string & form=molecule.initialForm;
	
	form.clear();
	
	
	
	
	while(in.tellg()<end){
		
		char ch=in.get();
		form+=ch;
	}
	
	return true;
	}
	return false;
}
