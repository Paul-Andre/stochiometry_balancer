#ifndef READ_EQUATION_HPP
#define READ_EQUATION_HPP


#include <string>
#include <iostream>






using namespace std;






void ignoreWhitespace(istream& in);

bool readElem(istream& in, string& out);


bool readNumber(istream& in, int& num);



bool confirmString(istream& in, const string& str);
bool checkString(istream& in, const string& str);

#endif 
