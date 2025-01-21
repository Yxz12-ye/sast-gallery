#include "AboutPage.h"
#include <ElaText.h>

AboutPage::AboutPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("About");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("About");
    centralWidget->setSizePolicy(QSizePolicy::Policy::Ignored,
                                 centralWidget->sizePolicy().verticalPolicy());
    addCentralWidget(centralWidget);
}

AboutPage::~AboutPage() {}
