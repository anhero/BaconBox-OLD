
#include "Console.h"

using namespace RedBox;

void Console::Print(string text) {
	std::cout << text << std::endl;
}

void Console::PrintTrace(int max) {
	Console::print_stacktrace(stdout, max);
}

void Console::_Log(string file, int line, string varname, string value) {
	std::cout << file << "@" << line << ": " << varname << " == " << value << std::endl;
}

void Console::_Print(string file, int line, string text) {
	std::cout << file << "@" << line << ": " << text << std::endl;
}

void Console::Error(string text) {
	Console::Print("Error: " + text);
}

void Console::Info(string text) {
	Console::Print("Info: " + text);
}

void Console::Warn(string text) {
	Console::Print("Warn: " + text);
}

void Console::_Printf(string file, int line, string formatString, ...) {
	va_list args;
	va_start (args, formatString);
	std::cout << file << "@" << line << ": ";
	vfprintf (stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end (args);
}
void Console::Printf(string formatString, ...) {
	va_list args;
	va_start (args, formatString);
	vfprintf (stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end (args);
}


template<class T> std::string Console::ToString(T i) {
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

std::string Console::ToString(int i) {
	return Console::ToString<int>(i);
}
