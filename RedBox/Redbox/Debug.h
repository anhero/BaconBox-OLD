/* ***************************************************************************\
 *                     _____          _ ____            
 *                    |  __ \        | |  _ \           
 *                    | |__) |___  __| | |_) | _____  __
 *                    |  _  // _ \/ _` |  _ < / _ \ \/ /
 *                    | | \ \  __/ (_| | |_) | (_) >  < 
 *                    |_|  \_\___|\__,_|____/ \___/_/\_\
 *
 *                     (c) 2009-2010  Illogical Studios
 *
 * TODO:ADD LICENSE BLOCK
 *
 *//**************************************************************************/
/**
 * @file
 * This file defines the debugging macro-framework that is available accross 
 * all the RedBox framework.
 *
 * @author Samuel Dionne-Riel
 *//**************************************************************************/

/*****************************************************************************\
 * Rules about the framework
 * *************************
 * 
 *  - A debug command must start with a dollar-sign ($).
 *  - A debug command should be chainable
 *    An exception to this rule is the debug beginning commands (e.g.: $PRINT)
 *    and the debug shortcut $DBG()
 *  - A debug command will not end with a semi-colon nor a bitshift
 *  - All the defined macros should expand to nothing when not in DEBUG
 *
 *//**************************************************************************/

#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef NDEBUG
#define DEBUG
#endif
#ifdef _DEBUG
#define DEBUG
#endif

#ifdef DEBUG
#include <iostream>
//Starts the debug as a print command
#define $PRINT std::cout << std::fixed
//TODO: A function to log to a file (usable as $FILE(name)
#define $FILE(f) $PRINT << "TODO: FILE"
//Pretty prints a variable following this rule:
// VAR_NAME: VAR_VALUE
#define $VAR(a) << #a << ": " << (a) << " "
//Appends the text prints the text
#define $TXT(a) << (a)
//Appends a newline character
#define $ENDLN << std::endl
//Appends the file name and line number of the statement
#define $FLLN << __FILE__ << "@" << __LINE__ << ": "
//Shortcut to print text
#define $ECHO(a) $PRINT $FLLN << a $ENDLN
//Shortcut to print variables
#define $DBG(a) $PRINT $FLLN $VAR(a) $ENDLN
#else
#define $PRINT
#define $VAR(a)
#define $TXT(a)
#define $ENDLN
#define $FLLN
#define $ECHO(a)
#define $DBG(a)
#endif

#endif
