#include "PlatformFlagger.h"
#include "MainWindow.h"
#include "Engine.h"
#include RB_MAINWINDOW_INCLUDE

using namespace RedBox;

MainWindow& MainWindow::getInstance() {
	return RB_MAINWINDOW_IMPL;
}

MainWindow::MainWindow() : sigly::HasSlots<>() {
	Engine::onInitialize.connect(this, &MainWindow::onRedBoxInit);
}
