#include "GalleryPage.h"
#include "utils/MediaThumbnail.h"

GalleryPage::GalleryPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Gallery");

    // page root
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Gallery");
    centralWidget->setSizePolicy(QSizePolicy::Policy::Ignored,
                                 centralWidget->sizePolicy().verticalPolicy());
    addCentralWidget(centralWidget);

    centralLayout = new MediaFlexLayout(centralWidget);

    // centralLayout->addWidget(new MediaThumbnail())
}

GalleryPage::~GalleryPage() {}
