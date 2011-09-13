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
float MainWindow::getContextWidth(){
    return contextWidth;
}
float MainWindow::getContextHeight(){
    return contextHeight;
}

void MainWindow::setContextSize(float contextWidth, float contextHeight){
    if (this->contextWidth == 0) {
        this->contextWidth =resolutionWidth;
    }
    else{
        this->contextWidth = contextWidth;
    }
    
    if (this->contextHeight == 0) {
        this->contextHeight = resolutionHeight;
    }
    else{
        this->contextHeight = contextHeight;
    }
}
