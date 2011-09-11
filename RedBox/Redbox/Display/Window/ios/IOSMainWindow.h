/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_IOS_MAIN_WINDOW_H
#define RB_IOS_MAIN_WINDOW_H

#include <sigly.h>
#include "MainWindow.h"

namespace RedBox {
	/**
	 * This is an implementation of MainWindow for IOS.
	 */
	class IOSMainWindow : public MainWindow {
	public:
		/// Gets the singleton instance of IOSMainWindow.
		static IOSMainWindow& getInstance();
		void onRedBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, unsigned int contextWidth, unsigned int contextHeight);
		void show();
		void setCaption(const std::string& caption);
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
        /**
         * Set the size. If you want to work in pixels, set them to 0 and they 
         * will automagically match the current resolution width and height
         */
        void setContextSize(unsigned int contextWidth, unsigned int contextHeight);
	private:
		IOSMainWindow();
		~IOSMainWindow();
	};
}

#endif
