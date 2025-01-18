#include "AboutPage.h"
#include <ElaText.h>

AboutPage::AboutPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("About");
    addCentralWidget(new ElaText("Empty", this));
}

AboutPage::~AboutPage() {}
