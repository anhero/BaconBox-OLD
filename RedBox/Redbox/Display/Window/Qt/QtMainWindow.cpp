#include "QtMainWindow.h"

#include "PlatformFlagger.h"

#include "RBOpenGL.h"
#include "Engine.h"

#include "QtKeyboard.h"
#include "QtPointer.h"

#include "InputManager.h"

#include "Console.h"

#include <QtGui>
#include <QtOpenGL>
#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>

using namespace RedBox;

QtMainWindow& QtMainWindow::getInstance() {
	static QtMainWindow instance;
	return instance;
}

void QtMainWindow::onRedBoxInit(unsigned int width, unsigned int height) {
	//Do nothing... It's all done in the MyMainWindow's function.
}

void QtMainWindow::show() {
	window->show();
	application->exec();
}

void QtMainWindow::setCaption(const std::string& caption) {
	window->setWindowTitle(QString::fromStdString(caption));
}

bool QtMainWindow::isFullScreen() const {
	return window->isFullScreen();
}

void QtMainWindow::setFullScreen(bool newFullScreen) {
	if(newFullScreen) {
		window->showFullScreen();
	} else {
		window->showNormal();
	}
}

QtMainWindow::QtMainWindow() : MainWindow() {
	//I build it with new to control its lifespan.
	application = new QApplication(Engine::getApplicationArgc(), Engine::getApplicationArgv());
	//Then the window
	window = new MyMainWindow();
	//@TODO: Check what to do with this... I want to make this configurable... It is shown in the menu bar on OS X.
	QCoreApplication::setApplicationName("RedBoxApp");
}

QtMainWindow::~QtMainWindow() {
	delete window;
	delete application;
}

// ----------------------------- MyMainWindow ----------------------------------

#include "ui_mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) :
	QMainWindow(parent), sigly::HasSlots<>(),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//this->setFixedSize(QtRedBoxWidget::SCREEN_WIDTH, QtRedBoxWidget::SCREEN_HEIGHT);

	engine = new QtRedBoxWidget(this);

	setCentralWidget(engine);

	setEnabled(true);
	RedBox::Engine::onInitialize.connect(this, &MyMainWindow::onRedBoxInit);
}

MyMainWindow::~MyMainWindow() {
    delete ui;
}

void MyMainWindow::onRedBoxInit(unsigned int width, unsigned int height) {
	setMaximumSize(width, height);
	QtRedBoxWidget::screenWidth = width;
	QtRedBoxWidget::screenHeight = height;

	RedBox::InputManager::getInstance().setNbKeyboards(1);
	RedBox::InputManager::getInstance().setNbPointers(1);

	RedBox::QtPointer::setParentWidget(this);
	RedBox::QtKeyboard::setParentWidget(this);

	if(engine) {
		engine->setMaximumSize(width, height);
	}
}


// ----------------------------- QtRedBoxWidget --------------------------------

int QtRedBoxWidget::screenWidth = 0;
int QtRedBoxWidget::screenHeight = 0;

QtRedBoxWidget::QtRedBoxWidget(QWidget* parent): QGLWidget(parent) {

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(1);

	this->setAutoFillBackground(false);
	this->grabMouse();
	this->setMouseTracking(true);
	this->setEnabled(true);
	this->makeCurrent();
}

QtRedBoxWidget::~QtRedBoxWidget() {
}

QSize QtRedBoxWidget::sizeHint() const {
	return QSize(screenWidth, screenHeight);
}

QSize QtRedBoxWidget::minimumSizeHint() const {
	return QSize(screenWidth, screenHeight);
}

void QtRedBoxWidget::initializeGL() {
}

void QtRedBoxWidget::paintGL() {
	RedBox::Engine::pulse();
}

void QtRedBoxWidget::resizeGL(unsigned int width, unsigned int height) {
}

void QtRedBoxWidget::animate() {
	RedBox::Engine::pulse();
	if(!RedBox::Engine::isBufferSwapped()) {
		this->updateGL();
		this->swapBuffers();
		RedBox::Engine::setBufferSwapped();
	}
}


