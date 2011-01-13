#ifndef __TYPECONVERTER_H
#define __TYPECONVERTER_H

#include <sstream>
#include <iostream>


namespace RedBox {
	
	class Convert {
	public:
		static int stringToInt(const std::string& str);
		static int wstringToInt(const std::wstring& wstr);
		static std::string intToString(const int anInt);
		static std::wstring intToWstring(const int anInt);
		static std::string wstringToString(const std::wstring& aString);
		static std::wstring stringToWstring(const std::string& aString);
	};
}

#endif
