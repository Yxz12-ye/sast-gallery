#include "SettingPage.h"
#include <ElaText.h>

SettingPage::SettingPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Setting");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Setting");
    centralWidget->setSizePolicy(QSizePolicy::Policy::Ignored,
                                 centralWidget->sizePolicy().verticalPolicy());
    addCentralWidget(centralWidget);
}

SettingPage::~SettingPage() {}
