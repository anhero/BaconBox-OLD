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
	 * Represents the main window of the application. This
	 * class is used to control the basic properties of the
	 * window and control it.
	 */
	class MainWindow : public sigly::HasSlots<> {
	public:
		/**
		 * Gets the singleton instance of the currently implemented
		 * MainWindow.
		 */
		static MainWindow& getInstance();
		/**
		 * Method called when the engine is initialized.
		 * It is used to setup the geometry of the window.
		 *
		 * @param width The width of the window.
		 * @param height The height of the window
		 */
		virtual void onRedBoxInit(int width, int height)=0;
		/**
		 * Activates and opens the window.
		 */
		virtual void show()=0;
		/**
		 * Changes the caption of the window. This is usually
		 * the title in the titlebar.
		 *
		 * @param caption The text used to replace the title.
		 */
		virtual void setCaption(const std::string& caption)=0;
	protected:
		/**
		 * The constructor. When implementing a MainWindow, do any
		 * initialization in here.
		 */
		MainWindow();
	};
}

#endif
