#pragma once
#include "BasePage.h"
#include "utils/MediaFlexLayout.h"

class GalleryPage : public BasePage {
    Q_OBJECT
public:
    Q_INVOKABLE explicit GalleryPage(QWidget* parent = nullptr);
    ~GalleryPage();
    QWidget* centralWidget;
    MediaFlexLayout* centralLayout;
};
