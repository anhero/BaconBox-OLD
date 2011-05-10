/* ***************************************************************************\
 *                     _____          _ ____            
 *                    |  __ \        | |  _ \           
 *                    | |__) |___  __| | |_) | _____  __
 *                    |  _  // _ \/ _` |  _ < / _ \ \/ /
 *                    | | \ \  __/ (_| | |_) | (_) >  < 
 *                    |_|  \_\___|\__,_|____/ \___/_/\_\
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

#error Debug.h is now deprecated.

#ifndef __DEBUG_H
#define __DEBUG_H

/*
#ifdef NDEBUG
#define DEBUG
#endif
#ifdef _DEBUG
#define DEBUG
#endif

#ifdef DEBUG
*/
#include <iostream>

//Starts the debug as a print command
#define RB_PRINT std::cout << std::fixed
//Pretty prints a variable following this rule:
// VAR_NAME: VAR_VALUE
#define RB_VAR(a) << #a << ": " << (a) << " "
//Appends the text prints the text
#define RB_TXT(a) << (a)
//Appends a newline character
#define RB_ENDLN << std::endl
//Appends the file name and line number of the statement
#define RB_FLLN << __FILE__ << "@" << __LINE__ << ": "
//Shortcut to print text
#define RB_ECHO(a) RB_PRINT RB_FLLN << a RB_ENDLN
//Shortcut to print variables
#define RB_DBG(a) RB_PRINT RB_FLLN RB_VAR(a) RB_ENDLN

/*
#else
#define RB_PRINT
#define RB_VAR(a)
#define RB_TXT(a)
#define RB_ENDLN
#define RB_FLLN
#define RB_ECHO(a)
#define RB_DBG(a)
#endif
*/
#endif
