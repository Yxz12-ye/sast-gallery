#include "FavoritePage.h"
#include <ElaText.h>

FavoritePage::FavoritePage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Favorite");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Favorite");
    centralWidget->setSizePolicy(QSizePolicy::Policy::Ignored,
                                 centralWidget->sizePolicy().verticalPolicy());
    addCentralWidget(centralWidget);
}

FavoritePage::~FavoritePage() {}
