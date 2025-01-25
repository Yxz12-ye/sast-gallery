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
#include <QFileInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWheelEvent>

class ViewingWindow : public ElaCustomWidget {
    Q_OBJECT

public:
    explicit ViewingWindow(QString filepath, QWidget* parent = nullptr);
    ~ViewingWindow();

    void initWindow();
    void initContent();

private:
    QString filepath;

    ImageViewer* imageViewer;

    QString getBriefFileInfo(QString filepath);
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