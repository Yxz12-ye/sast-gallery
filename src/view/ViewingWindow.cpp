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
    // TODO: implement this to display images mimicking Windows Photo Viewer's UI

    QVBoxLayout* viewLayout = new QVBoxLayout(this);

    // Create menu bar
    ElaMenuBar* menuBar = new ElaMenuBar(this);
    ElaMenu* fileMenu = menuBar->addMenu(ElaIconType::File, "File");
    fileMenu->addAction("Open");
    fileMenu->addAction("Copy");
    fileMenu->addAction("Save As");
    fileMenu->addAction("Open image in File Explorer");
    fileMenu->addSeparator();
    fileMenu->addAction("Close");

    //Set menu bar layout policy
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    menuBar->setMinimumWidth(100);
    fileMenu->setMinimumWidth(50);

    // Create buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    ElaIconButton* rotateButton = new ElaIconButton(ElaIconType::RotateRight);
    ElaIconButton* deleteButton = new ElaIconButton(ElaIconType::TrashCan);
    ElaIconButton* fileInfoButton = new ElaIconButton(ElaIconType::CircleInfo);
    ElaIconButton* zoomInButton = new ElaIconButton(ElaIconType::MagnifyingGlassPlus);
    ElaIconButton* zoomOutButton = new ElaIconButton(ElaIconType::MagnifyingGlassMinus);
    ElaIconButton* fullscreenButton = new ElaIconButton(ElaIconType::ExpandWide);
    ElaIconButton* zoom2originalButton = new ElaIconButton(ElaIconType::Expand);
    ElaIconButton* likeButton = new ElaIconButton(ElaIconType::Heart);

    buttonLayout->addWidget(rotateButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(fileInfoButton);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);
    buttonLayout->addWidget(fullscreenButton);
    buttonLayout->addWidget(zoom2originalButton);
    buttonLayout->addWidget(likeButton);

    // Add menu bar and buttons to layout

    viewLayout->addWidget(menuBar);
    viewLayout->addLayout(buttonLayout);
    viewLayout->setAlignment(Qt::AlignTop);
    // Set custom widget to the title bar

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(viewLayout);
    setCentralWidget(centralWidget);
}