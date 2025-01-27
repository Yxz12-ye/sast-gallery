#pragma once

#include <ElaGraphicsView.h>
#include <QWheelEvent>

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