#include "GalleryPage.h"
#include <ElaText.h>
#include <qboxlayout.h>
#include <qsizepolicy.h>

GalleryPage::GalleryPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Gallery");

    // root widget
    auto* rootWidget = new QWidget(this);
    rootWidget->setWindowTitle("Gallery");

    addCentralWidget(rootWidget);

}

GalleryPage::~GalleryPage() {}
