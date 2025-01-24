#pragma once
#include "BasePage.h"
#include "utils/MediaFlexLayout.h"
#include <QAbstractItemModel>

class GalleryPage : public BasePage {
    Q_OBJECT
public:
    explicit GalleryPage(QAbstractItemModel* model, QWidget* parent = nullptr);
    ~GalleryPage();
};
