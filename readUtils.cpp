
#include "readUtils.hpp"

#include <stack>


using namespace std;






void ignoreWhitespace(istream& in){
	in>>ws;
}

bool readElem(istream& in, string& out){
	
	char ch;
	out.clear();

	if(in.get(ch)){

		if(ch>='A'&&ch<='Z'){
			out+=ch;
			while(true){
				if(!in.get(ch))break;
				if(ch>='a'&&ch<='z'){
					out+=ch;
				}else break;
			
			} in.unget();
			return true;
		}else{in.unget();return false;}

	}else{in.unget();return false;}


}


bool readNumber(istream& in, int& num){
	
	stack<int> st;
	
	streampos begin=in.tellg();
	
	char ch;
	
	int mult=1;
	
	while(true){
	
		ch=in.get();
		
		if(ch>='0'&& ch<='9'){
		
			st.push(ch-'0');
		
		}else break;
		
	}	in.unget();
	
	if (st.size()==0){
		in.clear();
		in.seekg(begin);
		return false;
	
	}
	
	num=0;
	while(st.size()!=0){
	
		num+=st.top()*mult;
		st.pop();
		mult*=10;
	
	}
	
	return true;
	
}





bool confirmString(istream & in, const string & str){

	streampos begin=in.tellg();
	
	bool result=true;
	
	for (string::const_iterator i=str.begin(); i!=str.end(); i++){
	
		if(in.get()!=(*i)){result=false;in.clear();in.seekg(begin);break;}
	
	}
	
	return result;
}

bool checkString(istream & in, const string & str){

	streampos begin=in.tellg();
	
	bool result=true;
	
	for (string::const_iterator i=str.begin(); i!=str.end(); i++){
	
		if(in.get()!=(*i)){result=false;break;}
	
	}
	
	in.clear();in.seekg(begin);
	return result;
}

