#pragma once
#include "utils/WindowOverlayWidget.h"

// ref: https://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
// TODO: implement me

class ImageViewer : public WindowOverlayWidget {
public:
    ImageViewer(QWidget* parent = {})
        : WindowOverlayWidget{parent} {
        // setAttribute(Qt::WA_TranslucentBackground);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        // placeholder
        QPainter p{this};
        p.fillRect(rect(), {100, 100, 100, 128});
        p.setPen({200, 200, 255});
        p.setFont({"arial,helvetica", 48});
        p.drawText(rect(), "IMAGE HERE", Qt::AlignBottom | Qt::AlignRight);
        p.drawText(rect(), "IMAGE HERE", Qt::AlignTop | Qt::AlignLeft);
    }
};