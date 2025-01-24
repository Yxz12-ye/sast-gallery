#include "ViewingWindow.h"

ViewingWindow::ViewingWindow(QWidget* parent)
    : ElaCustomWidget(parent) {
    initWindow();
    initContent();
}

ViewingWindow::~ViewingWindow() {}

void ViewingWindow::initWindow() {
    resize(800, 600);
    setWindowTitle("Media Viewer Menu Window");
}

void ViewingWindow::initContent() {
    // TODO: implement this to display images and videos mimicking Windows Photo Viewer's UI

    // MenuBar
    auto* menuBar = new ElaMenuBar(this);
    menuBar->setObjectName("ViewingWindowMenuBar");
    menuBar->setFixedHeight(90);
    ElaMenu* fileMenu = menuBar->addMenu(ElaIconType::File, "File");
    fileMenu->setMinimumSize(50, 25);
}
