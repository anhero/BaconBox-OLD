#include "MainWindow.h"
#include "PlatformFlagger.h"
#include "Engine.h"
#include RB_MAINWINDOW_INCLUDE

using namespace RedBox;

const std::string MainWindow::DEFAULT_NAME = std::string("An unnamed RedBox application");

MainWindow& MainWindow::getInstance() {
	return RB_MAINWINDOW_IMPL;
}

MainWindow::MainWindow() : sigly::HasSlots<>() {
	Engine::onInitialize.connect(this, &MainWindow::onRedBoxInit);
}
