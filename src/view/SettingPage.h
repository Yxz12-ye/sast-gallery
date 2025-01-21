#pragma once

#include "BasePage.h"
class ElaRadioButton;
class ElaToggleSwitch;
class ElaComboBox;

class SettingPage : public BasePage {
    Q_OBJECT
public:
    explicit SettingPage(QWidget* parent = nullptr);
    ~SettingPage();

private:
    ElaComboBox* _themeComboBox{nullptr};
    ElaComboBox* _wheelBehaviorComboBox{nullptr};
    ElaToggleSwitch* _deletionSwitchButton{nullptr};
    ElaToggleSwitch* _micaSwitchButton{nullptr};
    ElaRadioButton* _minimumButton{nullptr};
    ElaRadioButton* _compactButton{nullptr};
    ElaRadioButton* _maximumButton{nullptr};
    ElaRadioButton* _autoButton{nullptr};
};
