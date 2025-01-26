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
    imagePath = getImagePath();
    if (!imagePath.isEmpty()) {
        loadImagefrompath(imagePath);
    }
}

void ImageViewer::saveImageFileDialog() {
    imagePath = QFileDialog::getSaveFileName(nullptr,
                                             "Save Image File",
                                             "",
                                             "Image Files (*.png *.jpg *.bmp *.jpeg *.gif)");
    if (!imagePath.isEmpty()) {
        this->image.save(imagePath);
    }
}

void ImageViewer::readFullInfo(const QString& path) {
    QFileInfo info(path);
    QString fileInfo = "File Name: " + info.fileName() + "\n";
    fileInfo += "File Resolution: " + QString::number(QImage(path).width()) + "x"
                + QString::number(QImage(path).height()) + "\n";
    fileInfo += "File Path: " + info.absoluteFilePath() + "\n";
    auto size = static_cast<double>(info.size());
    QString sizeUnit[] = {"B", "KB", "MB", "GB"};
    int unitIndex = 0;
    for (; unitIndex < 3; unitIndex++) {
        if (size < 1024) {
            break;
        }
        size /= 1024;
        size = static_cast<int>(size * 10) / 10.0;
    }
    fileInfo += "File Size: " + QString::number(size) + sizeUnit[unitIndex] + "\n";
    fileInfo += "File Created: " + info.birthTime().toString() + "\n";
    fileInfo += "File Modified: " + info.lastModified().toString() + "\n";
    fileInfo += "File Accessed: " + info.lastRead().toString() + "\n";
    fileInfo += "File Type: " + QImageReader::imageFormat(path).toUpper() + "\n";

    QMessageBox::information(this, "Full Image Information", fileInfo);
}

void ImageViewer::updateDisplaydImage() {
    if (imageLabel) {
        imageLabel->setPixmap(QPixmap::fromImage(this->image));
        imageLabel->setScaledContents(true);
    }
}
