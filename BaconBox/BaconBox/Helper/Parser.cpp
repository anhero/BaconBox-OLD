#include "BaconBox/Helper/Parser.h"
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace BaconBox;

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


std::string Parser::doubleToString(const double aDouble, int precision){
	std::stringstream ss;
	//std::ostringstream oss;
	if(precision != RB_FULL_PRECISION){
		ss << std::fixed <<std::setprecision(precision) << aDouble;
	}
	else {
		ss << aDouble;

	}
	return ss.str();
}
