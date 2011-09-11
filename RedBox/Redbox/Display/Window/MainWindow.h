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
		 * @param resolutionWidth The resolution width of the window.
		 * @param resolutionHeight The resolution height of the window
         * @param contextWidth The width of the context (set it to 0 if you want to work 
         * with pixels, it will match the resolution width).
         * @param contextHeight The height of the context (set it to 0 if you want to work 
         * with pixels, it will match the resolution height).
		 */
		virtual void onRedBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, unsigned int contextWidth, unsigned int contextHeight) = 0;
        
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
        
		/**
		 * Checks if the main window grabs the input. When the input is
		 * grabbed, the cursor is invisible.
		 * @return True if the main window grabbed the input, false if not.
		 */
		virtual bool isInputGrabbed() const = 0;
        
		/**
		 * Sets if the main window grabbed the input or not.
		 * @param newInputGrabbed
		 */
		virtual void setInputGrabbed(bool newInputGrabbed) = 0;
        
		/**
		 * Grabs the input.
		 */
		void grabInput();
        
		/**
		 * Releases the input grabbing.
		 */
		void releaseInput();
        
        /** 
         * Set the resolution of the window.
         */
        virtual void setResolution(unsigned int resolutionWidth, unsigned int resolutionHeight) = 0;
        /**
         * Set the size. If you want to work in pixels, set them to 0 and they 
         * will automagically match the current resolution width and height
         */
        virtual void setContextSize(unsigned int contextWidth, unsigned int contextHeight) = 0;

        ///Return the current window resolution width
        unsigned int getResolutionWidth();
        ///Return the current window resolution height
        unsigned int getResolutionHeight();
        ///Return the current context width
        unsigned int getContextWidth();
        ///Return the current context height
        unsigned int getContextHeight();

    protected:
        ///True if the current window is fullscreen.
        bool fullscreen;
        
        /// Screen's width resolution (or width of the window in window mode).
		unsigned int resolutionWidth;
        
		/// Screen's height resolution (or height of the window in window mode).
		unsigned int resolutionHeight;
        
        ///Render context width (if you want to work with pixel set it to the same value as resolutionWidth.
        unsigned int contextWidth;
        ///Render context width (if you want to work with pixel set it to the same value as resolutionHeight.
        unsigned int contextHeight;
        
		/**
		 * The constructor. When implementing a MainWindow, do any
		 * initialization in here.
		 */
		MainWindow();
        
		/**
		 * Destructor.
		 */
		virtual ~MainWindow();
	};
}

#endif
