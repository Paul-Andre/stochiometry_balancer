#include "solve.hpp"

#include <boost/rational.hpp>
#include "invertMatrix.hpp"

#include <iostream>
//#include <boost/numeric/ublas/io.hpp>


boost::numeric::ublas::matrix<int> wholize(const boost::numeric::ublas::matrix<boost::rational<int> > &);





boost::numeric::ublas::matrix<int> wholize(const boost::numeric::ublas::matrix<boost::rational<int> > & in){

using namespace boost;
	using namespace boost::numeric::ublas;

	matrix<rational<int> > m(in);

	
		bool clear=true;
		
	
		int p=2;

	while(true){
	
		clear=true;
		
		restart_loop:
		
		clear=true;
		
		for(unsigned i=0; i<m.size1(); i++){
			for(unsigned j=0; j<m.size2();j++){
			
				int denom=m(i,j).denominator();
				
				if(denom!=1){
					clear=false;
				
					if(denom%p==0){
				
						m*=p;
						goto restart_loop;
					}
				}
			
		}}
		
		
		
		if(clear)
			break;
		else
			p++;
	}
	
	matrix<int> ret(m.size1(),m.size2());
	
	for(unsigned i=0; i<m.size1(); i++)
		for(unsigned j=0; j<m.size2();j++){
			ret(i,j)=m(i,j).numerator()/m(i,j).denominator();
		}
	
	
	return ret;

}





bool solve(const boost::numeric::ublas::matrix<int> & input,std::vector<int>& output){


using namespace boost::numeric::ublas;
using namespace boost;
using namespace std;

//cout<<input<<endl;

matrix<rational<int> > mat=input;

matrix<rational<int> > mult(mat.size2(),1);
mult(0,0)=1;

bool singular=true;

mat=gjinverse(mat,singular);

//cout<<mat<<endl;

if(singular){return false;}

mat=prod(mat,mult);

//cout<<mat<<endl;

matrix<int> preResult=wholize(mat);

//cout<<preResult<<endl;

output.clear();



for(unsigned i=0;i<preResult.size1();i++){

	output.push_back(preResult(i,0));

}

return true;

}
