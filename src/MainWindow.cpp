#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent) {
    initWindow();
    initContent();
    moveToCenter();
}

MainWindow::~MainWindow() {}

void MainWindow::initWindow() {
    resize(1200, 740);
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

    // media viewer
    mediaViewer = new MediaViewer(this);
    mediaViewer->hide();
}
