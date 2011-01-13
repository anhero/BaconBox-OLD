#include "Convert.h"

using namespace RedBox;

int Convert::stringToInt(const std::string& str){
	std::stringstream ss(str);
	int i;
	if((ss >> i).fail())
	{ 
		std::cout << "Impossible to parse " << str << " to integer." << std::endl;
	}
	return i;
}

int Convert::wstringToInt(const std::wstring& wstr) {
	std::wstringstream ss(wstr);
	int i;
	if((ss >> i).fail()) {
		std::wcout << L"Impossible to parse " << wstr << L" to integer." << std::endl;
	}
	return i;
}


std::string Convert::intToString(const int anInt){
	std::stringstream ss;
	ss << anInt;
	return ss.str();
}

std::wstring Convert::intToWstring(const int anInt){
	std::wstringstream ss;
	ss << anInt;
	return ss.str();
}

std::string Convert::wstringToString(const std::wstring& aString){
	std::string temp(aString.length(), ' ');
	copy(aString.begin(), aString.end(), temp.begin());
	return temp; 
}

std::wstring Convert::stringToWstring(const std::string& aString){
	std::wstring temp(aString.length(),L' ');
	std::copy(aString.begin(), aString.end(), temp.begin());
	return temp; 
}