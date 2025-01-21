#include "ViewingWindow.h"

ViewingWindow::ViewingWindow(QWidget* parent)
    : ElaCustomWidget(parent) {
    initWindow();
    initContent();
}

ViewingWindow::~ViewingWindow() {}

void ViewingWindow::initWindow() {
    resize(800, 600);
    setWindowTitle("Media Viewer Window");
}

void ViewingWindow::initContent() {
    // TODO: implement this to display images and videos mimicking Windows Photo Viewer's UI
}
