/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_MAIN_WINDOW_H
#define RB_MAIN_WINDOW_H

#include <sigly.h>

#include <string>

namespace RedBox {
	/**
	 * Represents the application's main window. This class is used to control
	 * the basic properties of the main window.
	 * @ingroup WindowDisplay
	 */
	class MainWindow : public sigly::HasSlots<> {
	public:
		/// Default name given to all new main windows.
		static const std::string DEFAULT_NAME;

		/**
		 * Gets the singleton instance of the currently implemented
		 * MainWindow.
		 */
		static MainWindow& getInstance();

		/**
		 * Method called when the engine is initialized.
		 * It is used to setup the geometry of the window.
		 * @param width The width of the window.
		 * @param height The height of the window
		 */
		virtual void onRedBoxInit(unsigned int width, unsigned int height) = 0;

		/**
		 * Activates and opens the window.
		 */
		virtual void show() = 0;

		/**
		 * Changes the caption of the window. This is usually
		 * the title in the titlebar.
		 * @param caption The text used to replace the title.
		 */
		virtual void setCaption(const std::string& caption) = 0;
        
		/**
		 * Checks if the main window is full screen.
		 * @param True if the main window is in full screen, false if not.
		 */
		virtual bool isFullScreen() const = 0;

		/**
		 * Makes the main window full screen or not.
		 * @param newFullScreen If true, sets the main window to full screen.
		 * If false, makes sure it's not full screen.
		 */
		virtual void setFullScreen(bool newFullScreen) = 0;
    protected:
		/**
		 * The constructor. When implementing a MainWindow, do any
		 * initialization in here.
		 */
		MainWindow();
	};
}

#endif
