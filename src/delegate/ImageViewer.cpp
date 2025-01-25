#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget* parent)
    : WindowOverlayWidget(parent)
    , layout(new QVBoxLayout(this))
    , scaleFactor(1.0) {
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    imageLabel = new QLabel(this);
    layout->addWidget(imageLabel);
}

bool ImageViewer::loadImagefrompath(const QString& path) {
    try {
        if (path.isEmpty()) {
            return false;
        }
        QImage loaded(path);
        if (loaded.isNull()) {
            return false;
        }
        image = loaded;
        if (imageLabel) {
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->setScaledContents(true);
        }
        return true;
    }
    catch (...) {
        return false;
    }
}
bool ImageViewer::loadImage(const QImage& image) {
    try {
        if (image.isNull()) {
            return false;
        }
        this->image = image;
        if (imageLabel) {
            imageLabel->setPixmap(QPixmap::fromImage(this->image));
            imageLabel->setScaledContents(true);
        }
        return true;

    } catch (...) {
        return false;
    }
}
    const QString& ImageViewer::getImagePath() {
        static QString imagePath;
        imagePath = QFileDialog::getOpenFileName(nullptr,
                                                 "Choose Image File",
                                                 "",
                                                 "Image Files (*.png *.jpg *.bmp *.jpeg *.gif)");
        return imagePath;
    }

    void ImageViewer::openImageFileDialog() {
        QString imagePath = getImagePath();
        if (!imagePath.isEmpty()) {
            loadImagefrompath(imagePath);
        }
    }

    void ImageViewer::updateDisplaydImage() {
        if (imageLabel) {
            imageLabel->setPixmap(QPixmap::fromImage(this->image));
            imageLabel->setScaledContents(true);
        }
    }
