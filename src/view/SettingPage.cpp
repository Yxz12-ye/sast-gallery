#include "SettingPage.h"
#include <ElaText.h>

SettingPage::SettingPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Setting");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Setting");
    addCentralWidget(centralWidget);
}

SettingPage::~SettingPage() {}
