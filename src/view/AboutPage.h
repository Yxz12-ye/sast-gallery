#pragma once
#include "BasePage.h"
#include <ElaScrollPageArea.h>

class AboutPage : public BasePage {
    Q_OBJECT
public:
    explicit AboutPage(QWidget* parent = nullptr);
    ~AboutPage();

private:
    ElaScrollPageArea* createTextContent(QString label, QString content);
    ElaScrollPageArea* createLinkContent(QString label, QString link);
};