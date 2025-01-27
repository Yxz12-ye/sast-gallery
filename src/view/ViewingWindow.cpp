#include "ViewingWindow.h"
#include <ElaGraphicsItem.h>
#include <ElaGraphicsScene.h>
#include <ElaGraphicsView.h>
#include <ElaIcon.h>
#include <ElaIconButton.h>
#include <ElaSlider.h>
#include <ElaText.h>
#include <QGraphicsProxyWidget>
#include <model/MediaListModel.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <utils/Tools.h>

ViewingWindow::ViewingWindow(QAbstractItemModel* model, int index, QWidget* parent)
    : ElaCustomWidget(parent)
    , mediaListModel(model)
    , rowIndex(index) {
    filepath = mediaListModel->data(mediaListModel->index(rowIndex, MediaListModel::Path))
                   .value<QString>();
    initWindow();
    initContent();
}

ViewingWindow::~ViewingWindow() {}

void ViewingWindow::initWindow() {
    resize(800, 600);
    setWindowTitle("Media Viewer Window");
}

void ViewingWindow::initContent() {
    // TODO: implement this to display images mimicking Windows Photo Viewer's UI
    imageViewer = new ImageViewer(this);

    QWidget* centralWidget = new QWidget(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    // mainLayout->addWidget(imageViewer);

    // Create menu bar
    ElaMenuBar* menuBar = new ElaMenuBar(this);

    QAction* rotateAction = menuBar->addElaIconAction(ElaIconType::RotateRight, "rotate");

    QAction* deleteAction = menuBar->addElaIconAction(ElaIconType::TrashCan, "delete");

    QAction* printAction = menuBar->addElaIconAction(ElaIconType::Print, "print");

    QAction* editAction = menuBar->addElaIconAction(ElaIconType::Pen, "edit");

    ElaMenu* fileMenu = menuBar->addMenu(ElaIconType::Ellipsis, nullptr);

    QAction* openFileAction = fileMenu->addAction("Open");

    QAction* copyFileAction = fileMenu->addAction("Copy");

    QAction* saveasFileAction = fileMenu->addAction("Save As");

    QAction* openInFileExplorerAction = fileMenu->addAction("Open image in File Explorer");

    fileMenu->addSeparator();

    //Set menu bar layout policy
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    menuBar->setMinimumWidth(100);
    menuBar->setMaximumHeight(25);
    fileMenu->setMinimumWidth(50);

    // put image relevant parts here and add them to mainLayout between menuBar and operationLayout

    // placeholder for image, remove this when actual image is displayed

    // Create buttons
    QHBoxLayout* operationLayout = new QHBoxLayout(this);

    ElaIconButton* likeButton = new ElaIconButton(ElaIconType::Heart);
    likeButton->setMaximumWidth(25);

    ElaIconButton* fileInfoButton = new ElaIconButton(ElaIconType::CircleInfo);
    fileInfoButton->setMaximumWidth(25);

    ElaText* dividerText1 = new ElaText("|", this);
    dividerText1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dividerText1->setTextPixelSize(14);

    ElaText* fileInfoBriefText = new ElaText(QString("%1 x %2 %3")
                                                 .arg(QString::number(QImage(filepath).width()))
                                                 .arg(QString::number(QImage(filepath).height()))
                                                 .arg(Tools::fileSizeString(filepath)),
                                             this);
    fileInfoBriefText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    fileInfoBriefText->setTextPixelSize(14);

    ElaIconButton* zoomInButton = new ElaIconButton(ElaIconType::MagnifyingGlassPlus);
    zoomInButton->setMaximumWidth(25);

    ElaSlider* zoomSlider = new ElaSlider(Qt::Orientation::Horizontal);
    // range from 1% to 300% scaleFactor: 0.01 to 3.00
    // scaleFactor = 1 + zoomSlider->value() / 100
    zoomSlider->setRange(1, 300); //percentage of zoom
    zoomSlider->setMaximumWidth(200);

    ElaIconButton* zoomOutButton = new ElaIconButton(ElaIconType::MagnifyingGlassMinus);
    zoomOutButton->setMaximumWidth(25);

    ElaText* dividerText2 = new ElaText("|", this);
    dividerText2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dividerText2->setTextPixelSize(14);

    ElaIconButton* maximizeButton = new ElaIconButton(ElaIconType::ExpandWide);
    maximizeButton->setMaximumWidth(25);

    ElaIconButton* zoom2originalButton = new ElaIconButton(ElaIconType::Expand);
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
    mainLayout->insertWidget(0, menuBar);

    mainLayout->addWidget(imageViewer, 1);

    mainLayout->addLayout(operationLayout);

    mainLayout->addStretch();

    mainLayout->setAlignment(Qt::AlignTop);
    // Set custom widget to the title bar

    setCentralWidget(centralWidget);

    // show actions info when pointing at them
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

    // connect to actions
    connect(openFileAction, &QAction::triggered, this, [=]() {
        imageViewer->openImageFileDialog();

        if (imageViewer->imageLabel) {
            imageViewer->imageLabel->setPixmap(QPixmap::fromImage(imageViewer->image));
            imageViewer->imageLabel->setScaledContents(true);
        }
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();

        int windowWidth = screenWidth / 2;
        int windowHeight = screenHeight / 2;
        this->resize(windowWidth, windowHeight);
        imageViewer->resize(windowWidth, windowHeight);

        // if you wanna adapt to your monitor resolution, use this
        // imageViewer->adaptiveResize();
    });
    connect(copyFileAction, &QAction::triggered, this, [=]() {
        imageViewer->copyImageToClipboard();
    });
    connect(saveasFileAction, &QAction::triggered, this, [=]() {
        imageViewer->saveImageFileDialog();
    });

    //TODO(must):implement the openInFileExplorer functionality
    //connect(openInFileExplorerAction,......)

    connect(rotateAction, &QAction::triggered, this, [=]() { qDebug() << "Rotate action clicked"; });

    connect(deleteAction, &QAction::triggered, this, [=]() { qDebug() << "Delete action clicked"; });

    connect(printAction, &QAction::triggered, this, [=]() { qDebug() << "Print action clicked"; });

    connect(editAction, &QAction::triggered, this, [=]() {
        //TODO(optional):implement the edit functionality
    });

    connect(likeButton, &ElaIconButton::clicked, this, [=]() {
        //TODO(must):implement the like functionality
        // add the image to Favorite Page
    });

    connect(fileInfoButton, &ElaIconButton::clicked, this, [=]() {
        imageViewer->readFullInfo(imageViewer->getImagePath());
    });

    connect(zoomInButton, &ElaIconButton::clicked, this, [=]() {
        // scaleFactor *= 1.2;
        // if (scaleFactor > 3) scaleFactor = 3;
        // zoomSlider->setToolTip(QString::number(scaleFacor * 100));
        // zoomSlider->setValue(scaleFactor * 100);
    });

    connect(zoomOutButton, &ElaIconButton::clicked, this, [=]() {
        // scaleFactor /= 0.2;
        // if (scaleFactor < 0.2) scaleFactor = 0.1;
        // zoomSlider->setToolTip(QString::number(scaleFactor * 100));
        // zoomSlider->setValue(scaleFactor * 100);
    });

    connect(maximizeButton, &ElaIconButton::clicked, this, [=]() { this->showMaximized(); });

    connect(zoom2originalButton, &ElaIconButton::clicked, this, [=]() {
        // scaleFactor = 1;
        // zoomSlider->setToolTip(QString::number(scaleFactor * 100));
        // zoomSlider->setValue(scaleFactor * 100);
    });

    connect(zoomSlider, &ElaSlider::valueChanged, this, [=](int value) {
        // range from 1% to 300%
        if (value >= 1 && value <= 300) {
            zoomSlider->setToolTip(QString::number(value));
            zoomSlider->setValue(value);
        }
    });
}