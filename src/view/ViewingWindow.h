#pragma once

#include "delegate/ImageViewer.h"
#include <ElaCustomWidget.h>
#include <ElaGraphicsItem.h>
#include <ElaGraphicsScene.h>
#include <ElaGraphicsView.h>
#include <ElaIcon.h>
#include <ElaIconButton.h>
#include <ElaMenu.h>
#include <ElaMenuBar.h>
#include <ElaPushButton.h>
#include <ElaSlider.h>
#include <ElaText.h>
#include <ElaWidget.h>
#include <QAbstractItemModel>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWheelEvent>

class ViewingWindow : public ElaCustomWidget {
    Q_OBJECT

public:
    explicit ViewingWindow(QAbstractItemModel* model, int index, QWidget* parent = nullptr);
    ~ViewingWindow();

    void initWindow();
    void initContent();

private:
    QAbstractItemModel* mediaListModel;
    int rowIndex;
    QString filepath;
    ImageViewer* imageViewer;

    QString briefFileInfo();
};

class ZoomableGraphicsView : public ElaGraphicsView {
    Q_OBJECT
public:
    using ElaGraphicsView::ElaGraphicsView;

protected:
    void wheelEvent(QWheelEvent* event) override {
        double factor = 1.15;
        if (event->angleDelta().y() > 0) {
            scale(factor, factor);
        } else {
            scale(1 / factor, 1 / factor);
        }
    }
};