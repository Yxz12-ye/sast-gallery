#include "SettingPage.h"
#include "utils/Settings.hpp"
#include <ElaApplication.h>
#include <ElaComboBox.h>
#include <ElaLog.h>
#include <ElaRadioButton.h>
#include <ElaScrollPageArea.h>
#include <ElaText.h>
#include <ElaTheme.h>
#include <ElaToggleSwitch.h>
#include <ElaWindow.h>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

SettingPage::SettingPage(QWidget* parent)
    : BasePage(parent) {
    auto* window = dynamic_cast<ElaWindow*>(parent);
    setWindowTitle("Setting");

    auto appearanceText = new ElaText("Appearance", this);
    appearanceText->setWordWrap(false);
    appearanceText->setTextPixelSize(18);

    _themeComboBox = new ElaComboBox(this);
    _themeComboBox->addItem("Light");
    _themeComboBox->addItem("Dark");
    auto* themeSwitchArea = new ElaScrollPageArea(this);
    auto* themeSwitchLayout = new QHBoxLayout(themeSwitchArea);
    auto* themeSwitchText = new ElaText("Themes", this);
    themeSwitchText->setWordWrap(false);
    themeSwitchText->setTextPixelSize(15);
    themeSwitchLayout->addWidget(themeSwitchText);
    themeSwitchLayout->addStretch();
    themeSwitchLayout->addWidget(_themeComboBox);
    _themeComboBox->setCurrentIndex(settings.value("theme").toString() == "light" ? 0 : 1);
    connect(_themeComboBox,
            QOverload<int>::of(&ElaComboBox::currentIndexChanged),
            this,
            [=](int index) {
                if (index == 0) {
                    eTheme->setThemeMode(ElaThemeType::Light);
                    settings.setValue("theme", "light");
                } else {
                    eTheme->setThemeMode(ElaThemeType::Dark);
                    settings.setValue("theme", "dark");
                }
            });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=, this](ElaThemeType::ThemeMode themeMode) {
        _themeComboBox->blockSignals(true);
        if (themeMode == ElaThemeType::Light) {
            _themeComboBox->setCurrentIndex(0);
        } else {
            _themeComboBox->setCurrentIndex(1);
        }
        _themeComboBox->blockSignals(false);
    });

    _micaSwitchButton = new ElaToggleSwitch(this);
    auto* micaSwitchArea = new ElaScrollPageArea(this);
    auto* micaSwitchLayout = new QHBoxLayout(micaSwitchArea);
    auto* micaSwitchText = new ElaText("Mica Effect", this);
    micaSwitchText->setWordWrap(false);
    micaSwitchText->setTextPixelSize(15);
    micaSwitchLayout->addWidget(micaSwitchText);
    micaSwitchLayout->addStretch();
    micaSwitchLayout->addWidget(_micaSwitchButton);
    _micaSwitchButton->setIsToggled(settings.value("micaEffect").toBool());
    connect(_micaSwitchButton, &ElaToggleSwitch::toggled, this, [=](bool checked) {
        eApp->setIsEnableMica(checked);
        settings.setValue("micaEffect", checked);
    });

    _minimumButton = new ElaRadioButton("Minimum", this);
    _compactButton = new ElaRadioButton("Compact", this);
    _maximumButton = new ElaRadioButton("Maximum", this);
    _autoButton = new ElaRadioButton("Auto", this);
    auto* displayModeArea = new ElaScrollPageArea(this);
    auto* displayModeLayout = new QHBoxLayout(displayModeArea);
    auto* displayModeText = new ElaText("Navigation Bar Display Mode", this);
    displayModeText->setWordWrap(false);
    displayModeText->setTextPixelSize(15);
    displayModeLayout->addWidget(displayModeText);
    displayModeLayout->addStretch();
    displayModeLayout->addWidget(_minimumButton);
    displayModeLayout->addWidget(_compactButton);
    displayModeLayout->addWidget(_maximumButton);
    displayModeLayout->addWidget(_autoButton);
    if (settings.value("navigationBarDisplayMode").toInt() == 1) {
        _minimumButton->setChecked(true);
    } else if (settings.value("navigationBarDisplayMode").toInt() == 2) {
        _compactButton->setChecked(true);
    } else if (settings.value("navigationBarDisplayMode").toInt() == 3) {
        _maximumButton->setChecked(true);
    } else {
        _autoButton->setChecked(true);
    }
    connect(_minimumButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            window->setNavigationBarDisplayMode(ElaNavigationType::Minimal);
            settings.setValue("navigationBarDisplayMode", 1);
        }
    });
    connect(_compactButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            window->setNavigationBarDisplayMode(ElaNavigationType::Compact);
            settings.setValue("navigationBarDisplayMode", 2);
        }
    });
    connect(_maximumButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            window->setNavigationBarDisplayMode(ElaNavigationType::Maximal);
            settings.setValue("navigationBarDisplayMode", 3);
        }
    });
    connect(_autoButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            window->setNavigationBarDisplayMode(ElaNavigationType::Auto);
            settings.setValue("navigationBarDisplayMode", 0);
        }
    });

    auto* functionsText = new ElaText("Functions", this);
    functionsText->setWordWrap(false);
    functionsText->setTextPixelSize(18);

    _wheelBehaviorComboBox = new ElaComboBox(this);
    _wheelBehaviorComboBox->addItem("Zoom");
    _wheelBehaviorComboBox->addItem("Switch");
    auto* wheelBehaviorSwitchArea = new ElaScrollPageArea(this);
    auto* wheelBehaviorSwitchLayout = new QHBoxLayout(wheelBehaviorSwitchArea);
    auto* wheelBehaviorSwitchText = new ElaText("Wheel Behaviors", this);
    wheelBehaviorSwitchText->setWordWrap(false);
    wheelBehaviorSwitchText->setTextPixelSize(15);
    wheelBehaviorSwitchLayout->addWidget(wheelBehaviorSwitchText);
    wheelBehaviorSwitchLayout->addStretch();
    wheelBehaviorSwitchLayout->addWidget(_wheelBehaviorComboBox);
    // TODO: implement the rest

    _deletionSwitchButton = new ElaToggleSwitch(this);
    auto* deletionSwitchArea = new ElaScrollPageArea(this);
    auto* deletionSwitchLayout = new QHBoxLayout(deletionSwitchArea);
    auto* deletionSwitchText = new ElaText("Ask for deletion permission", this);
    deletionSwitchText->setWordWrap(false);
    deletionSwitchText->setTextPixelSize(15);
    deletionSwitchLayout->addWidget(deletionSwitchText);
    deletionSwitchLayout->addStretch();
    deletionSwitchLayout->addWidget(_deletionSwitchButton);
    // TODO: implement the rest

    auto centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Setting");
    auto centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addSpacing(30);
    centerLayout->addWidget(appearanceText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeSwitchArea);
    centerLayout->addWidget(micaSwitchArea);
    centerLayout->addWidget(displayModeArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(functionsText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(wheelBehaviorSwitchArea);
    centerLayout->addWidget(deletionSwitchArea);
    centerLayout->addStretch();
    centerLayout->setContentsMargins(0, 0, 0, 0);
    addCentralWidget(centralWidget, true, true, 0);
}

SettingPage::~SettingPage() {}
