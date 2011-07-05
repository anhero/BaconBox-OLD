
#include "Console.h"
using namespace RedBox;
using namespace std;

void Console::print(const string& text) {
#ifndef RB_ANDROID
	std::cout << text << std::endl;
#endif
}

void Console::printTrace(int max) {
#ifndef RB_ANDROID
	Console::print_stacktrace(stdout, max);
#endif
}

void Console::_log(string file, int line, string varname, string value) {
#ifndef RB_ANDROID
	std::cout << file << "@" << line << ": " << varname << " == " << value << std::endl;
#endif
}

void Console::_print(string file, int line, string text) {
#ifndef RB_ANDROID
	std::cout << file << "@" << line << ": " << text << std::endl;
#endif
}

void Console::error(string text) {
#ifndef RB_ANDROID
	Console::print("Error: " + text);
#endif
}

void Console::info(string text) {
#ifndef RB_ANDROID
	Console::print("Info: " + text);
#endif
}

void Console::warn(string text) {
#ifndef RB_ANDROID
	Console::print("Warn: " + text);
#endif
}

void Console::_printf(string file, int line, string formatString, ...) {
#ifndef RB_ANDROID
	va_list args;
	va_start(args, formatString);
	std::cout << file << "@" << line << ": ";
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
#endif
}
void Console::printf(string formatString, ...) {
#ifndef RB_ANDROID
	va_list args;
	va_start(args, formatString);
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
#endif
}




