#include "Parser.h"

using namespace RedBox;

int Parser::stringToInt(const std::string& str){
	std::stringstream ss(str);
	int i;
	if((ss >> i).fail())
	{ 
		std::cout << "Impossible to parse " << str << " to integer." << std::endl;
	}
	return i;
}


std::string Parser::intToString(const int anInt){
	std::stringstream ss;
	ss << anInt;
	return ss.str();
}


std::string Parser::floatToString(const float aFloat){
	std::stringstream ss;
	ss << aFloat;
	return ss.str();
}