#ifndef CONSOLE_H
#define CONSOLE_H

//@TODO: Backtrace magic for other platforms than GCC... (clang?, msvc)
//@TODO: Stack trace in an object to allow more manipulation?

#include <iostream>
#include <string>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>

#include <stdarg.h>

using namespace std;

//Defines for line numbers and filename...
//Sadly, can't be done by some other magic...
#define Console__Print(a)    Console::_Print(__FILE__, __LINE__, a);
#define Console__Printf(...) Console::_Printf(__FILE__, __LINE__, __VA_ARGS__);
#define Console__Log(a)      Console::_Log(__FILE__, __LINE__, #a, a);

namespace RedBox {
	class Console {
		private:
		// stacktrace.h (c) 2008, Timo Bingmann from http://idlebox.net/
		// published under the WTFPL v2.0
		// Previous credits applies only to private function print_stacktrace.
		/** Print a demangled stack backtrace of the caller function to FILE* out. */
		static inline void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63)
		{
			const int stackOffset = 2;

			// storage array for stack trace address data
			void* addrlist[max_frames+stackOffset];

			// retrieve current stack addresses
			int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

			if (addrlen == 0) {
				fprintf(out, "\t<empty, possibly corrupt>\n");
				return;
			}

			// resolve addresses into strings containing "filename(function+address)",
			// this array must be free()-ed
			char** symbollist = backtrace_symbols(addrlist, addrlen);

			// allocate string which will be filled with the demangled function name
			size_t funcnamesize = 256;
			char* funcname = (char*)malloc(funcnamesize);

			// iterate over the returned symbol lines. skip the first two
			// they are this function and the calling function (PrintTrace)
			for (int i = stackOffset; i < addrlen; i++)
			{
				char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

				// find parentheses and +address offset surrounding the mangled name:
				// ./module(function+0x15c) [0x8048a6d]
				for (char *p = symbollist[i]; *p; ++p)
				{
					if (*p == '(')
						begin_name = p;
					else if (*p == '+')
						begin_offset = p;
					else if (*p == ')' && begin_offset) {
						end_offset = p;
						break;
					}
				}

				if (begin_name && begin_offset && end_offset
					&& begin_name < begin_offset)
				{
					*begin_name++ = '\0';
					*begin_offset++ = '\0';
					*end_offset = '\0';

					// mangled name is now in [begin_name, begin_offset) and caller
					// offset in [begin_offset, end_offset). now apply
					// __cxa_demangle():

					int status;
					char* ret = abi::__cxa_demangle(begin_name,
													funcname, &funcnamesize, &status);
					if (status == 0) {
						funcname = ret; // use possibly realloc()-ed string
						fprintf(out, "\t#%03d %s : %s+%s\n",
								i-stackOffset, symbollist[i], funcname, begin_offset);
					}
					else {
						// demangling failed. Output function name as a C function with
						// no arguments.
						fprintf(out, "\t#%03d %s : %s()+%s\n",
								i-stackOffset, symbollist[i], begin_name, begin_offset);
					}
				}
				else
				{
					// couldn't parse the line? print the whole line.
					fprintf(out, "\t%s\n", symbollist[i]);
				}
			}

			free(funcname);
			free(symbollist);
		}

		public:
			/**
			 * Prints text on the console.
			 *
			 * @param text Text to print.
			 */
			static void Print(string text);
			/**
			 * Used by the macro to print text with file and line number information.
			 *
			 * @param file Filename of caller.
			 * @param line Line number of caller.
			 * @param text Text to print.
			 */
			static void _Print(string file, int line, string text);
			/**
			 * Used by the macro to print variable name and value with file and line number information.
			 *
			 * @param file Filename of caller.
			 * @param line Line number of caller.
			 * @param varname Name of the variable to print.
			 * @param value Value of the printed variableé
			 */
			static void _Log(string file, int line, string varname, string value);
			/**
			 * Prints the stack trace from caller's point of view.
			 */
			static void PrintTrace(int max = 63);
			/**
			 * Prints formatted as printf would.
			 *
			 * @param formatString Format string, as in printf.
			 * @param ... Things as parameters.
			 */
			static void Printf(string formatString, ...);
			/**
			 * Used by the macro to print formatted text with file and line number information.
			 *
			 * @param file Filename of caller.
			 * @param line Line number of caller.
			 * @param formatString Format string, as in printf.
			 * @param ... Things as parameters.
			 */
			static void _Printf(string file, int line, string formatString, ...);
			/**
			 * Prints warning information on the console.
			 *
			 * This usually only differ by style.
			 *
			 * @param text Text to print.
			 */
			static void Warn(string text);
			/**
			 * Prints information on the console.
			 *
			 * This usually only differ by style.
			 *
			 * @param text Text to print.
			 */
			static void Info(string text);
			/**
			 * Prints error information on the console.
			 *
			 * This usually only differ by style.
			 *
			 * @param text Text to print.
			 */
			static void Error(string text);
			/**
			 * Convert type to string.
			 */
			template<class T> static std::string ToString(T i);
			/**
			 * Convert integer to string.
			 */
			static std::string ToString(int i);
	};
}


#endif // CONSOLE_H
