
#include "Console.h"
#ifndef RB_ANDROID
using namespace RedBox;

void Console::printTrace(int max) {
	Console::print_stacktrace(stdout, max);
}

void Console::_log(std::string file, int line,std::string varname, std::string value) {
	std::cout << file << "@" << line << ": " << varname << " == " << value << std::endl;
}

void Console::_print(std::string file, int line, std::string text) {
	std::cout << file << "@" << line << ": " << text << std::endl;
}

void Console::_printf(std::string file, int line, std::string formatString, ...) {
	va_list args;
	va_start(args, formatString);
	std::cout << file << "@" << line << ": ";
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
}

void Console::printf(std::string formatString, ...) {
	va_list args;
	va_start(args, formatString);
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
}




#endif
