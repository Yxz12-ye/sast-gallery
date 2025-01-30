#include "MediaViewer.h"
#include <ElaMenu.h>
#include <ElaMenuBar.h>
#include <QDir>
#include <QScreen>
#include <delegate/MediaViewerDelegate.h>
#include <qobject.h>
#include <utils/Tools.h>

MediaViewer::MediaViewer(QAbstractItemModel* model, int index, QWidget* parent)
    : ElaCustomWidget(parent)
    , delegate(new MediaViewerDelegate(model, index, this, this)) {
    initWindow();
    initContent();
    delegate->initConnections();
}

MediaViewer::~MediaViewer() {}

void MediaViewer::initWindow() {
    resize(1080, 720);
    setMinimumSize(640, 480);
    QString fileName = QFileInfo(delegate->getFilePath()).fileName();
    setWindowTitle(fileName);
}

void MediaViewer::initContent() {
    auto* centralWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(centralWidget);

    // Create menu bar
    auto* menuBar = new ElaMenuBar(this);

    rotateAction = menuBar->addElaIconAction(ElaIconType::RotateRight, "rotate");
    deleteAction = menuBar->addElaIconAction(ElaIconType::TrashCan, "delete");
    printAction = menuBar->addElaIconAction(ElaIconType::Print, "print");
    editAction = menuBar->addElaIconAction(ElaIconType::Pen, "edit");
    prevAction = menuBar->addElaIconAction(ElaIconType::CircleChevronLeft, "previous");
    nextAction = menuBar->addElaIconAction(ElaIconType::CircleChevronRight, "next");

    ElaMenu* fileMenu = menuBar->addMenu(ElaIconType::Ellipsis, nullptr);
    openFileAction = fileMenu->addAction("Open");
    copyFileAction = fileMenu->addAction("Copy");
    saveasFileAction = fileMenu->addAction("Save As");
    openInFileExplorerAction = fileMenu->addAction("Open image in File Explorer");

    fileMenu->addSeparator();

    //Set menu bar layout policy
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    menuBar->setMinimumWidth(100);
    menuBar->setMaximumHeight(25);
    fileMenu->setMinimumWidth(50);

    // image view
    imageViewer = new ImageViewer(QPixmap::fromImage(delegate->getImage()), this);
    imageViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    imageViewer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create buttons
    QHBoxLayout* operationLayout = new QHBoxLayout(this);

    likeButton = new ElaIconButton(ElaIconType::Heart);
    likeButton->setMaximumWidth(25);

    fileInfoButton = new ElaIconButton(ElaIconType::CircleInfo);
    fileInfoButton->setMaximumWidth(25);

    ElaText* dividerText1 = new ElaText("|", this);
    dividerText1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dividerText1->setTextPixelSize(14);

    fileInfoBriefText
        = new ElaText(QString("%1 x %2 %3")
                          .arg(QString::number(QImage(delegate->getFilePath()).width()))
                          .arg(QString::number(QImage(delegate->getFilePath()).height()))
                          .arg(Tools::fileSizeString(delegate->getFilePath())),
                      this);
    fileInfoBriefText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    fileInfoBriefText->setTextPixelSize(14);

    zoomInButton = new ElaIconButton(ElaIconType::MagnifyingGlassPlus);
    zoomInButton->setMaximumWidth(25);

    zoomSlider = new ElaSlider(Qt::Orientation::Horizontal);
    // range from 1% to 300% scaleFactor: 0.01 to 3.00
    // scaleFactor = 1 + zoomSlider->value() / 100
    zoomSlider->setRange(1, 300); //percentage of zoom
    zoomSlider->setValue(100);
    zoomSlider->setMaximumWidth(300);

    zoomOutButton = new ElaIconButton(ElaIconType::MagnifyingGlassMinus);
    zoomOutButton->setMaximumWidth(25);

    ElaText* dividerText2 = new ElaText("|", this);
    dividerText2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dividerText2->setTextPixelSize(14);

    maximizeButton = new ElaIconButton(ElaIconType::ExpandWide);
    maximizeButton->setMaximumWidth(25);

    zoom2originalButton = new ElaIconButton(ElaIconType::Expand);
    zoom2originalButton->setMaximumWidth(25);

    operationLayout->addWidget(likeButton);
    operationLayout->addWidget(fileInfoButton);
    operationLayout->addWidget(dividerText1);
    operationLayout->addWidget(fileInfoBriefText);
    operationLayout->addStretch();
    operationLayout->addWidget(zoomOutButton);
    operationLayout->addWidget(zoomSlider);
    operationLayout->addWidget(zoomInButton);
    operationLayout->addWidget(dividerText2);
    operationLayout->addWidget(maximizeButton);
    operationLayout->addWidget(zoom2originalButton);

    // Add menu bar and buttons to layout
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(imageViewer);
    mainLayout->addLayout(operationLayout);
    mainLayout->setAlignment(Qt::AlignTop);

    setCentralWidget(centralWidget);

    // show actions status tips when pointing at them
    openFileAction->setStatusTip("Open a file");
    copyFileAction->setStatusTip("Copy a file");
    saveasFileAction->setStatusTip("Save a file as");
    openInFileExplorerAction->setStatusTip("Open the file in File Explorer");
    rotateAction->setStatusTip("Rotate the image");
    deleteAction->setStatusTip("Delete the image");
    printAction->setStatusTip("Print the image");
    editAction->setStatusTip("Edit the image");
    likeButton->setStatusTip("Like the image");
    fileInfoButton->setStatusTip("Show file info");
    zoomInButton->setStatusTip("Zoom in");
    zoomOutButton->setStatusTip("Zoom out");
    maximizeButton->setStatusTip("Fullscreen");
    zoom2originalButton->setStatusTip("Zoom to original size");
}

void MediaViewer::wheelEvent(QWheelEvent* event) {
    delegate->wheelEvent(event);
}