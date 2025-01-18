#pragma once
#include "view/AboutPage.h"
#include "view/FavoritePage.h"
#include "view/GalleryPage.h"
#include "view/SettingPage.h"
#include <ElaWindow.h>
#include <QMainWindow>

class MainWindow : public ElaWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initWindow();
    void initContent();

private:
    FavoritePage* favoritePage;
    GalleryPage* galleryPage;
    SettingPage* settingPage;
    AboutPage* aboutPage;
};