#include "MainWindow.h"
#include "utils/Settings.hpp"
#include "view/ViewingWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent) {
    initWindow();
    initContent();
    moveToCenter();
}

MainWindow::~MainWindow() {
    settings.setValue("windowSize", size());
}

void MainWindow::initWindow() {
    resize(settings.value("windowSize").toSize());
    setUserInfoCardVisible(false);
    setWindowTitle("SAST Gallery");

    setWindowButtonFlag(ElaAppBarType::ButtonType::StayTopButtonHint, false);
}

void MainWindow::initContent() {
    // pages
    galleryPage = new GalleryPage(this);
    addPageNode("Gallery", galleryPage, ElaIconType::Images);

    favoritePage = new FavoritePage(this);
    addPageNode("Favourites", favoritePage, ElaIconType::Heart);

    aboutPage = new AboutPage(this);
    QString aboutPageKey;
    addFooterNode("About", aboutPage, aboutPageKey, 0, ElaIconType::CircleInfo);

    settingPage = new SettingPage(this);
    QString settingPageKey;
    addFooterNode("Setting", settingPage, settingPageKey, 0, ElaIconType::GearComplex);

    
    // ViewingWindow for media
    auto* viewingWindow = new ViewingWindow();
    connect(this, &MainWindow::destroyed, viewingWindow, &ViewingWindow::close);
    viewingWindow->hide();
    
    // Add PageNode for showing ViewingWindow 
    QWidget* viewingWindowWidget = viewingWindow;
    addPageNode("ViewingMedia", viewingWindowWidget, ElaIconType::Window);
    connect(viewingWindowWidget, &QWidget::customContextMenuRequested, viewingWindow, &ViewingWindow::show);
}
