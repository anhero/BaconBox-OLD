/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_QT_MAIN_WINDOW_H
#define RB_QT_MAIN_WINDOW_H

#include <sigly.h>
#include "BaconBox/Display/Window/MainWindow.h"

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QGLWidget>

namespace Ui {
    class MainWindow;
}

namespace BaconBox {
	class QtBaconBoxWidget : public QGLWidget {
		Q_OBJECT
	public:
		static int screenWidth;
		static int screenHeight;
		QtBaconBoxWidget(QWidget *parent = 0);
		~QtBaconBoxWidget();

		QSize sizeHint() const;
		QSize minimumSizeHint() const;

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(unsigned int width, unsigned int height);

	private slots:
		void animate();
	private:
		QTimer * timer;
	};

	class MyMainWindow : public QMainWindow, public sigly::HasSlots<> {
		Q_OBJECT
		public:
			explicit MyMainWindow(QWidget *parent = 0);
			~MyMainWindow();
			void onBaconBoxInit(unsigned int width, unsigned int height);
		private:
			Ui::MainWindow *ui;
			QtBaconBoxWidget* engine;
	};


	/**
	 * This is an implementation of MainWindow using Qt.
	 */
	class QtMainWindow : public MainWindow {
	public:
		/// Gets the singleton instance of QtMainWindow.
		static QtMainWindow& getInstance();
		void onBaconBoxInit(unsigned int width, unsigned int height);
		void show();
		void setCaption(const std::string& caption);
		bool isFullScreen() const;
		void setFullScreen(bool newFullScreen);
	private:
		/// Instance of the Qt Window.
		MyMainWindow* window;

		/// Instance of QApplication
		QApplication* application;

		/**
		 * Initializes.
		 */
		QtMainWindow();

		/**
		 * Properly quits.
		 */
		~QtMainWindow();

	};

}

#endif
