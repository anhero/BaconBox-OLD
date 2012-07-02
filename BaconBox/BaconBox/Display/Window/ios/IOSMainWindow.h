/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_IOS_MAIN_WINDOW_H
#define RB_IOS_MAIN_WINDOW_H

#include "BaconBox/Display/Window/MainWindow.h"

namespace BaconBox {
	/**
	 * This is an implementation of MainWindow for IOS.
	 * @ingroup WindowDisplay
	 */
	class IOSMainWindow : public MainWindow {
		friend class Engine;
	public:
		void onBaconBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight);
		void show();
		void setCaption(const std::string &caption);
		bool isFullScreen() const;
		void setFullScreen(bool);
		/**
		 * Checks if the main window grabs the input. When the input is
		 * grabbed, the cursor is invisible.
		 * @return True if the main window grabbed the input, false if not.
		 */
		bool isInputGrabbed() const;

		/**
		 * Sets if the main window grabbed the input or not.
		 * @param newInputGrabbed
		 */
		void setInputGrabbed(bool newInputGrabbed);
		/**
		 * Set the resolution of the window.
		 */
		void setResolution(unsigned int resolutionWidth, unsigned int resolutionHeight);
        
	private:
		IOSMainWindow();

		~IOSMainWindow();
	};
}

#endif
