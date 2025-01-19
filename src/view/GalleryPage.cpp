#include "GalleryPage.h"
#include <ElaText.h>

GalleryPage::GalleryPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Gallery");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Gallery");
    addCentralWidget(centralWidget);
}

GalleryPage::~GalleryPage() {}
