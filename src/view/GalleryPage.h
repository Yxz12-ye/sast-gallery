#pragma once
#include "BasePage.h"
#include "utils/MediaFlexLayout.h"
#include "utils/MediaThumbnail.h"

class GalleryPage : public BasePage {
    Q_OBJECT
public:
    Q_INVOKABLE explicit GalleryPage(QWidget* parent = nullptr);
    ~GalleryPage();
    void test() {
        centralLayout->addWidget(
            new MediaThumbnail(centralWidget,
                               "C:/Users/cEvolve05/OneDrive/Desktop/Picture/87480762_p0.jpg"));
    }
    QWidget* centralWidget;
    MediaFlexLayout* centralLayout;
};
