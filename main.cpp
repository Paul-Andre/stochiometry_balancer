#include <string>
#include <iostream>
#include <sstream>


#include "Equation.hpp"

using namespace std;



int main(){

	cout<<"Welcome to the chemical equation balancer.\nIt works, but paranthesises aren't yet accepted.\n"
	<<"Rememeber, element symbols must start with a capital letter.\n"
	<<"Submit your equations in the form of:\n\n"<<"H2O -> H2 + O2\n\n"<<flush;
	
while(true){

	Equation equation;

	string eq;

	getline(cin,eq);

	

	stringstream eqStr(eq);

	
	bool read=readEquation(eqStr,equation);
	
	//cout<<endl<<read<<endl;
	//cout<<equation;
	
	if(read){
	
		if(equation.balance()){
	
	
		cout<<equation<<"\n\n"<<flush;
		}else{
	
			cout<<"There was a problem balancing the equation\n";
		
		cout<<"For the moment, we can only solve equations with a single solution.\n";
		cout<<"The first letter of each element's symbol should be a capital.\n\n"<<flush;
	
	
		}
	
	}else{
	
		cout<<"There was a problem reading your equation.\n";
		cout<<"Remember, the first letter of each element's symbol should be a capital\n\n"<<flush;
	
	
	}

	//if(readEquation(eqStr,equation)){cout<<"read";}else{cout<<"unread";}
//cout<<endl<<readEquation(eqStr,equation)<<endl<<"I've ";

//cout<<"been here ";
//	cout<<equation<<" llol\n";

	//}else{return 0;}								
}

return 0;
}
