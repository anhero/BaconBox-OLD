#include "MainWindow.h"
#include "PlatformFlagger.h"
#include "Engine.h"
#include RB_MAINWINDOW_INCLUDE

using namespace RedBox;

const std::string MainWindow::DEFAULT_NAME = std::string("An unnamed RedBox application");

MainWindow& MainWindow::getInstance() {
	return RB_MAINWINDOW_IMPL;
}

void MainWindow::grabInput() {
	setInputGrabbed(true);
}

void MainWindow::releaseInput() {
	setInputGrabbed(false);
}

MainWindow::MainWindow() : sigly::HasSlots<>() {
	Engine::onInitialize.connect(this, &MainWindow::onRedBoxInit);
}

MainWindow::~MainWindow() {
}

unsigned int MainWindow::getResolutionWidth(){
    return resolutionWidth;
}
unsigned int MainWindow::getResolutionHeight(){
    return resolutionHeight;
}
unsigned int MainWindow::getContextWidth(){
    return contextWidth;
}
unsigned int MainWindow::getContextHeight(){
    return contextHeight;
}