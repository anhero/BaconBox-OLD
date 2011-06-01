
#include "Console.h"
#ifndef RB_ANDROID
using namespace RedBox;
using namespace std;

void Console::print(const string& text) {
	std::cout << text << std::endl;
}

void Console::printTrace(int max) {
	Console::print_stacktrace(stdout, max);
}

void Console::_log(string file, int line, string varname, string value) {
	std::cout << file << "@" << line << ": " << varname << " == " << value << std::endl;
}

void Console::_print(string file, int line, string text) {
	std::cout << file << "@" << line << ": " << text << std::endl;
}

void Console::error(string text) {
	Console::print("Error: " + text);
}

void Console::info(string text) {
	Console::print("Info: " + text);
}

void Console::warn(string text) {
	Console::print("Warn: " + text);
}

void Console::_printf(string file, int line, string formatString, ...) {
	va_list args;
	va_start(args, formatString);
	std::cout << file << "@" << line << ": ";
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
}
void Console::printf(string formatString, ...) {
	va_list args;
	va_start(args, formatString);
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
}




#endif