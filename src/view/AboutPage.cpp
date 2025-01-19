#include "AboutPage.h"
#include <ElaText.h>

AboutPage::AboutPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("About");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("About");
    addCentralWidget(centralWidget);
}

AboutPage::~AboutPage() {}
