#pragma once
#include "BasePage.h"

class AboutPage : public BasePage {
    Q_OBJECT
public:
    explicit AboutPage(QWidget* parent = nullptr);
    ~AboutPage();
private:
    ElaText* createText(const QString& text, int size);
};
