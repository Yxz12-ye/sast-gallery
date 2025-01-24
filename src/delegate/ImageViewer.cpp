#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget* parent)
    : WindowOverlayWidget(parent)
    , layout(new QVBoxLayout(this))
    , scaleFactor(1.0) {
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    
}

bool ImageViewer::loadImage(const QString& path) {
    try {
        image.load(path);
        if (image.isNull()) {
            return false;
        }
        imageLabel = new QLabel(this);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        layout->addWidget(imageLabel);
        return true;

    } catch (std::exception& err) {
        return false;
    }
}
