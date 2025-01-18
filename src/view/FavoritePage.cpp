#include "FavoritePage.h"
#include <ElaText.h>

FavoritePage::FavoritePage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Favorite");
    addCentralWidget(new ElaText("Empty", this));
}

FavoritePage::~FavoritePage() {}
