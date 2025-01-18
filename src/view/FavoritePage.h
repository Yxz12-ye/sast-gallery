#pragma once
#include "BasePage.h"

class FavoritePage : public BasePage {
    Q_OBJECT
public:
    explicit FavoritePage(QWidget* parent = nullptr);
    ~FavoritePage();
};
