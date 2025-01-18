#include "SettingPage.h"
#include <ElaText.h>

SettingPage::SettingPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("Setting");
    addCentralWidget(new ElaText("Empty", this));
}

SettingPage::~SettingPage() {}
