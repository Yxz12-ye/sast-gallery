#pragma once
#include "BasePage.h"

class SettingPage : public BasePage {
    Q_OBJECT
public:
    explicit SettingPage(QWidget* parent = nullptr);
    ~SettingPage();
};
