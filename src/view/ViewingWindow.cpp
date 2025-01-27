#include "ViewingWindow.h"
#include <ElaGraphicsItem.h>
#include <ElaGraphicsScene.h>
#include <ElaGraphicsView.h>
#include <ElaIcon.h>
#include <ElaIconButton.h>
#include <ElaSlider.h>
#include <ElaText.h>
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
    QVBoxLayout* viewLayout = new QVBoxLayout(this);
    viewLayout->addWidget(imageViewer);
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

    // put image relevant parts here and add them to viewLayout between menuBar and operationLayout

    // placeholder for image, remove this when actual image is displayed
    ElaGraphicsScene* scene = new ElaGraphicsScene(this);
    scene->setSceneRect(0, 0, 500, 500);
    ElaGraphicsItem* item1 = new ElaGraphicsItem();
    item1->setItemImage(QImage(filepath));
    item1->setWidth(400);
    item1->setHeight(400);
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

    ElaIconButton* fullscreenButton = new ElaIconButton(ElaIconType::ExpandWide);
    fullscreenButton->setMaximumWidth(25);

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
    operationLayout->addWidget(fullscreenButton);
    operationLayout->addWidget(zoom2originalButton);

    // Add menu bar and buttons to layout
    viewLayout->insertWidget(0, menuBar);
    viewLayout->addStretch();
    viewLayout->addLayout(graphicsLayout);
    viewLayout->addStretch();
    viewLayout->addLayout(operationLayout);
    viewLayout->setAlignment(Qt::AlignTop);
    // Set custom widget to the title bar

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(viewLayout);
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
    fullscreenButton->setStatusTip("Fullscreen");
    zoom2originalButton->setStatusTip("Zoom to original size");

    ZoomableGraphicsView* zoomableGraphicsView = new ZoomableGraphicsView(scene);
    view->setFixedHeight(600);
    graphicsLayout->addWidget(view);

    // connect to actions
    connect(openFileAction, &QAction::triggered, this, [=]() {
        imageViewer->openImageFileDialog();

        // get the resolution of user's monitor
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();
        //get the size of the image

        QImage loadedImage = QImage(filepath);
        int imageWidth = loadedImage.width();
        int imageHeight = loadedImage.height();

        //calculate the size of the Window
        int windowWidth = imageWidth;
        int windowHeight = imageHeight;
        if (imageWidth > screenWidth || imageHeight > screenHeight) {
            qreal widthRatio = static_cast<qreal>(screenWidth) / windowWidth;
            qreal heightRatio = static_cast<qreal>(screenHeight) / windowHeight;
            qreal scaleFactor = qMin(widthRatio, heightRatio);
            windowWidth = static_cast<int>(windowWidth * scaleFactor);
            windowHeight = static_cast<int>(windowHeight * scaleFactor);
        }
        imageViewer->resize(windowWidth, windowHeight);
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
        // scaleFactor += 0.2;
        // if (scaleFactor > 3) scaleFactor = 3;
        // zoomSlider->setToolTip(QString::number(scaleFacor * 100));
        // zoomSlider->setValue(scaleFactor * 100);
    });
    connect(zoomOutButton, &ElaIconButton::clicked, this, [=]() {
        // scaleFactor -= 0.2;
        // if (scaleFactor < 0.2) scaleFactor = 0.1;
        // zoomSlider->setToolTip(QString::number(scaleFactor * 100));
        // zoomSlider->setValue(scaleFactor * 100);
    });
    connect(fullscreenButton, &ElaIconButton::clicked, this, [=]() { this->showFullScreen(); });
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
    connect(scene, &ElaGraphicsScene::mouseLeftClickedItem, this, [=](ElaGraphicsItem* item) {
        qDebug() << "Scene now displays image";
    });
}