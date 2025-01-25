#include "ViewingWindow.h"
#include <ElaGraphicsItem.h>
#include <ElaGraphicsScene.h>
#include <ElaGraphicsView.h>
#include <ElaIcon.h>
#include <ElaIconButton.h>
#include <ElaSlider.h>
#include <ElaText.h>

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
    menuBar->addElaIconAction(ElaIconType::RotateRight, "rotate");
    menuBar->addElaIconAction(ElaIconType::TrashCan, "delete");
    menuBar->addElaIconAction(ElaIconType::Print, "print");
    menuBar->addElaIconAction(ElaIconType::Pen, "edit");
    ElaMenu* fileMenu = menuBar->addMenu(ElaIconType::Ellipsis, nullptr);
    fileMenu->addAction("Open");
    fileMenu->addAction("Copy");
    fileMenu->addAction("Save As");
    fileMenu->addAction("Open image in File Explorer");
    fileMenu->addSeparator();

    //Set menu bar layout policy
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    menuBar->setMinimumWidth(100);
    menuBar->setMaximumHeight(25);
    fileMenu->setMinimumWidth(50);

    // put image relevant parts here and add them to viewLayout between menuBar and operationLayout

    // placeholder for image, remove this when actual image is displayed
    ElaGraphicsScene* scene = new ElaGraphicsScene(this);
    scene->setSceneRect(0, 0, 500, 500);
    ElaGraphicsItem* item1 = new ElaGraphicsItem();
    item1->setItemImage(QImage(":/res/icon/app_icon.svg"));
    item1->setWidth(100);
    item1->setHeight(100);
    scene->addItem(item1);
    ElaGraphicsView* view = new ElaGraphicsView(scene);
    view->setScene(scene);
    view->setFixedHeight(600);
    QVBoxLayout* graphicsLayout = new QVBoxLayout();
    graphicsLayout->addWidget(view);

    // Create buttons
    QHBoxLayout* operationLayout = new QHBoxLayout(this);
    ElaIconButton* likeButton = new ElaIconButton(ElaIconType::Heart);
    likeButton->setMaximumWidth(25);
    ElaIconButton* fileInfoButton = new ElaIconButton(ElaIconType::CircleInfo);
    fileInfoButton->setMaximumWidth(25);
    ElaText* dividerText1 = new ElaText("|", this);
    dividerText1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dividerText1->setTextPixelSize(14);
    ElaText* fileInfoBriefText = new ElaText("1920 x 1080 1.2MB", this);
    fileInfoBriefText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    fileInfoBriefText->setTextPixelSize(14);
    ElaIconButton* zoomInButton = new ElaIconButton(ElaIconType::MagnifyingGlassPlus);
    zoomInButton->setMaximumWidth(25);
    ElaSlider* zoomSlider = new ElaSlider(Qt::Orientation::Horizontal);
    zoomSlider->setMaximumWidth(200);
    ElaIconButton* zoomOutButton = new ElaIconButton(ElaIconType::MagnifyingGlassMinus);
    zoomOutButton->setMaximumWidth(25);
    ElaText* dividerText2 = new ElaText("|", this);
    dividerText2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dividerText2->setTextPixelSize(14);
    ElaIconButton* fullscreenButton = new ElaIconButton(ElaIconType::ExpandWide);
    fullscreenButton->setMaximumWidth(25);
    ElaIconButton* zoom2originalButton = new ElaIconButton(ElaIconType::Expand);
    zoom2originalButton->setMaximumWidth(25);

    operationLayout->addWidget(likeButton);
    operationLayout->addWidget(fileInfoButton);
    operationLayout->addWidget(dividerText1);
    operationLayout->addWidget(fileInfoBriefText);
    operationLayout->addStretch();
    operationLayout->addWidget(zoomInButton);
    operationLayout->addWidget(zoomSlider);
    operationLayout->addWidget(zoomOutButton);
    operationLayout->addWidget(dividerText2);
    operationLayout->addWidget(fullscreenButton);
    operationLayout->addWidget(zoom2originalButton);

    // Add menu bar and buttons to layout

    viewLayout->addWidget(menuBar);
    viewLayout->addStretch();
    viewLayout->addLayout(graphicsLayout);
    viewLayout->addStretch();
    viewLayout->addLayout(operationLayout);
    viewLayout->setAlignment(Qt::AlignTop);
    // Set custom widget to the title bar

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(viewLayout);
    setCentralWidget(centralWidget);
}