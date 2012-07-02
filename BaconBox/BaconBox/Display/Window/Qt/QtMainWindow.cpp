#include "BaconBox/Display/Window/Qt/QtMainWindow.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Display/Driver/OpenGL/RBOpenGL.h"
#include "BaconBox/Engine.h"

#include "BaconBox/Input/Keyboard/Qt/QtKeyboard.h"
#include "BaconBox/Input/Pointer/Qt/QtPointer.h"

#include "BaconBox/Input/InputManager.h"

#include "BaconBox/Console.h"

#include <QtGui>
#include <QtOpenGL>
#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>

using namespace BaconBox;

QtMainWindow& QtMainWindow::getInstance() {
	static QtMainWindow instance;
	return instance;
}

void QtMainWindow::onBaconBoxInit(unsigned int width, unsigned int height) {
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
	QCoreApplication::setApplicationName("BaconBoxApp");
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
	//this->setFixedSize(QtBaconBoxWidget::SCREEN_WIDTH, QtBaconBoxWidget::SCREEN_HEIGHT);

	engine = new QtBaconBoxWidget(this);

	setCentralWidget(engine);

	setEnabled(true);
	BaconBox::Engine::onInitialize.connect(this, &MyMainWindow::onBaconBoxInit);
}

MyMainWindow::~MyMainWindow() {
    delete ui;
}

void MyMainWindow::onBaconBoxInit(unsigned int width, unsigned int height) {
	setMaximumSize(width, height);
	QtBaconBoxWidget::screenWidth = width;
	QtBaconBoxWidget::screenHeight = height;

	BaconBox::InputManager::getInstance().setNbKeyboards(1);
	BaconBox::InputManager::getInstance().setNbPointers(1);

	BaconBox::QtPointer::setParentWidget(this);
	BaconBox::QtKeyboard::setParentWidget(this);

	if(engine) {
		engine->setMaximumSize(width, height);
	}
}


// ----------------------------- QtBaconBoxWidget --------------------------------

int QtBaconBoxWidget::screenWidth = 0;
int QtBaconBoxWidget::screenHeight = 0;

QtBaconBoxWidget::QtBaconBoxWidget(QWidget* parent): QGLWidget(parent) {

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(1);

	this->setAutoFillBackground(false);
	this->grabMouse();
	this->setMouseTracking(true);
	this->setEnabled(true);
	this->makeCurrent();
}

QtBaconBoxWidget::~QtBaconBoxWidget() {
}

QSize QtBaconBoxWidget::sizeHint() const {
	return QSize(screenWidth, screenHeight);
}

QSize QtBaconBoxWidget::minimumSizeHint() const {
	return QSize(screenWidth, screenHeight);
}

void QtBaconBoxWidget::initializeGL() {
}

void QtBaconBoxWidget::paintGL() {
	BaconBox::Engine::pulse();
}

void QtBaconBoxWidget::resizeGL(unsigned int width, unsigned int height) {
}

void QtBaconBoxWidget::animate() {
	BaconBox::Engine::pulse();
	if(!BaconBox::Engine::isBufferSwapped()) {
		this->updateGL();
		this->swapBuffers();
		BaconBox::Engine::setBufferSwapped();
	}
}


