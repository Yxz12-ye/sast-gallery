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
        this->image = loaded;
        if (imageLabel) {
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->setScaledContents(true);
        }
        return true;
    } catch (...) {
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

bool ImageViewer::copyImageToClipboard() {
    if (this->image.isNull()) {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText("Image failed to copy to clipboard,plz load image first");
        return false;
    } else {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setImage(this->image);
        return true;
    }
}
void ImageViewer::openImageFileDialog() {
    QString imagePath = getImagePath();
    if (!imagePath.isEmpty()) {
        loadImagefrompath(imagePath);
    }
}

void ImageViewer::saveImageFileDialog() {
    QString imagePath
        = QFileDialog::getSaveFileName(nullptr,
                                       "Save Image File",
                                       "",
                                       "Image Files (*.png *.jpg *.bmp *.jpeg *.gif)");
    if (!imagePath.isEmpty()) {
        this->image.save(imagePath);
    }
}
void ImageViewer::updateDisplaydImage() {
    if (imageLabel) {
        imageLabel->setPixmap(QPixmap::fromImage(this->image));
        imageLabel->setScaledContents(true);
    }
}
