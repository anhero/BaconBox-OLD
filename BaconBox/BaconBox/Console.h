#ifndef RB_CONSOLE_H
#define RB_CONSOLE_H

#include "BaconBox/PlatformFlagger.h"

// @TODO: Backtrace magic for other platforms than GCC... (clang?, msvc)
// @TODO: Stack trace in an object to allow more manipulation?

#include "BaconBox/PlatformFlagger.h"

#include <cstdio>
#include <cstdlib>

#ifdef RB_HAS_GCC_STACKTRACE
#include <execinfo.h>
#include <cxxabi.h>
#endif

#include <cstdarg>

#ifndef RB_ANDROID
#include <iostream>
#endif

#include <string>
#include <sstream>

// Defines for line numbers and filename...
// Sadly, can't be done by some other magic...
#define Console__print(a)    Console::_print(__FILE__, __LINE__, a);
#define Console__printf(...) Console::_printf(__FILE__, __LINE__, __VA_ARGS__);
#define Console__log(a)      Console::_log(__FILE__, __LINE__, #a, a);

#ifdef RB_ANDROID
#define PV(x) ;
#else
#define PV(x) std::cout << #x << ": " << x << std::endl
#endif

namespace BaconBox {
	class Console {
	public:
		/**
		 * Prints text in the console. Adds a new line at the end.
		 *
		 * @param input Value to print.
		 */
		template <typename T>
		static void println(const T& input) {
#ifndef RB_ANDROID
			std::cout << input << std::endl;
#endif
		}

		/**
		 * Prints text in the console.
		 *
		 * @param input Value to print.
		 */
		template <typename T>
		static void print(const T& input) {
#ifndef RB_ANDROID
			std::cout << input;
#endif
		}

		/**
		 * Prints warning information on the console.
		 *
		 * This usually only differ by style.
		 *
		 * @param input Text to print.
		 */
		template <typename T>
		static void warn(const T& input) {
#ifndef RB_ANDROID
			std::cout << "Warn: " << input << std::endl;
#endif
		}

		/**
		 * Prints information on the console.
		 *
		 * This usually only differ by style.
		 *
		 * @param input Text to print.
		 */
		template <typename T>
		static void info(const T& input) {
#ifndef RB_ANDROID
			std::cout << "Info: " << input << std::endl;
#endif
		}

		/**
		 * Prints error information on the console.
		 *
		 * This usually only differ by style.
		 *
		 * @param input Text to print.
		 */
		template <typename T>
		static void error(const T& input) {
#ifndef RB_ANDROID
			std::cerr << "Error: " << input << std::endl;
#endif
		}

		/**
		 * Used by the macro to print text with file and line number information.
		 *
		 * @param file Filename of caller.
		 * @param line Line number of caller.
		 * @param text Text to print.
		 */
		static void _print(std::string file, int line, std::string text);

		/**
		 * Used by the macro to print variable name and value with file and line number information.
		 *
		 * @param file Filename of caller.
		 * @param line Line number of caller.
		 * @param varname Name of the variable to print.
		 * @param value Value of the printed variable
		 */
		static void _log(std::string file, int line, std::string varname,
		                 std::string value);

		/**
		 * Prints the stack trace from caller's point of view.
		 */
		static void printTrace(int max = 63);

		/**
		 * Prints formatted as printf would.
		 *
		 * @param formatString Format string, as in printf.
		 * @param ... Things as parameters.
		 */
		static void printf(std::string formatString, ...);

		/**
		 * Used by the macro to print formatted text with file and line number information.
		 *
		 * @param file Filename of caller.
		 * @param line Line number of caller.
		 * @param formatString Format string, as in printf.
		 * @param ... Things as parameters.
		 */
		static void _printf(std::string file, int line, std::string formatString, ...);

		/**
		 * Convert type to string.
		 */
		template<class T> static std::string toString(T i) {
			std::stringstream ss;
			ss << i;
			return ss.str();
		}
	private:
#ifdef RB_HAS_GCC_STACKTRACE
		// stacktrace.h (c) 2008, Timo Bingmann from http://idlebox.net/
		// published under the WTFPL v2.0
		// Previous credits applies only to private function print_stacktrace.
		/** Print a demangled stack backtrace of the caller function to FILE* out. */
		static inline void print_stacktrace(FILE* out = stderr, unsigned int max_frames = 63) {
			const int stackOffset = 2;
			// storage array for stack trace address data
			void* addrlist[max_frames + stackOffset];
			// retrieve current stack addresses
			int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

			if(addrlen == 0) {
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
			for(int i = stackOffset; i < addrlen; i++) {
				char* begin_name = 0, *begin_offset = 0, *end_offset = 0;

				// find parentheses and +address offset surrounding the mangled name:
				// ./module(function+0x15c) [0x8048a6d]
				for(char* p = symbollist[i]; *p; ++p) {
					if(*p == '(') {
						begin_name = p;

					} else if(*p == '+') {
						begin_offset = p;

					} else if(*p == ')' && begin_offset) {
						end_offset = p;
						break;
					}
				}

				if(begin_name && begin_offset && end_offset
				   && begin_name < begin_offset) {
					*begin_name++ = '\0';
					*begin_offset++ = '\0';
					*end_offset = '\0';
					// mangled name is now in [begin_name, begin_offset) and caller
					// offset in [begin_offset, end_offset). now apply
					// __cxa_demangle():
					int status;
					char* ret = abi::__cxa_demangle(begin_name,
					                                funcname, &funcnamesize, &status);

					if(status == 0) {
						funcname = ret; // use possibly realloc()-ed string
						fprintf(out, "\t#%03d %s : %s+%s\n",
						        i - stackOffset, symbollist[i], funcname, begin_offset);

					} else {
						// demangling failed. Output function name as a C function with
						// no arguments.
						fprintf(out, "\t#%03d %s : %s()+%s\n",
						        i - stackOffset, symbollist[i], begin_name, begin_offset);
					}

				} else {
					// couldn't parse the line? print the whole line.
					fprintf(out, "\t%s\n", symbollist[i]);
				}
			}

			free(funcname);
			free(symbollist);
		}
#else
		static inline void print_stacktrace(FILE* out = stderr, unsigned int max_frames = 63) {
			fprintf(out, ">> No stacktrace method available\n");
		}
#endif
	};
}


#endif // CONSOLE_H
