#include "utils/WindowOverlayWidget.h"
#include <qnamespace.h>

class ImageViewer : public WindowOverlayWidget {
public:
    ImageViewer(QWidget* parent = {})
        : WindowOverlayWidget{parent} {
        // setAttribute(Qt::WA_TranslucentBackground);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p{this};
        p.fillRect(rect(), {100, 100, 100, 128});
        p.setPen({200, 200, 255});
        p.setFont({"arial,helvetica", 48});
        p.drawText(rect(), "IMAGE HERE", Qt::AlignBottom | Qt::AlignRight);
        p.drawText(rect(), "IMAGE HERE", Qt::AlignTop | Qt::AlignLeft);
    }
};