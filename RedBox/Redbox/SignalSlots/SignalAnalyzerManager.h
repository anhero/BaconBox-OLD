/**
 * @file
 * @ingroup Events
 */
#ifndef RB_SIGNAL_ANALYZER_MANAGER_H
#define RB_SIGNAL_ANALYZER_MANAGER_H

#include <map>
#include <string>

#include "SignalAnalyzer.h"

namespace RedBox {
	/**
	 * Manages signal analyzers.
	 * @ingroup Events
	 */
	class SignalAnalyzerManager {
	public:

		static SignalAnalyzerManager* getInstance();

		/**
		 * Adds a signal analyzer to the manager. From the time the analyzer is
		 * passed to the manager, the manager takes care of freeing up the
		 * memory
		 * @param analyzerName Name to give to the analyzer.
		 */
		void addSignalAnalyzer(const std::string& analyzerName,
		                       SignalAnalyzer* analyzer,
		                       bool overwrite = false);

		/**
		 * Removes the signal analyzer from the manager.
		 * @param analyzerName Name of the analyzer to delete and remove from
		 * the manager.
		 */
		void removeSignalAnalyzer(const std::string& analyzerName);

		/**
		 * Gets a signal analyzer.
		 * @param analyzerName Name of the analyzer to get.
		 * @return Pointer to the signal analyzer. Can be used to deactivate
		 * its slots temporarily.
		 */
		SignalAnalyzer* getSignalAnalyzer(const std::string& analyzerName);

	private:
		/// Singleton's instance.
		static SignalAnalyzerManager* instance;

		/// Analyzers and their name.
		std::map<std::string, SignalAnalyzer*> analyzers;

		/**
		 * Private default constructor.
		 */
		SignalAnalyzerManager();

		/**
		 * Private destructor.
		 */
		~SignalAnalyzerManager();
	};
}

#endif