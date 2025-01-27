#pragma once

#include "utils/WindowOverlayWidget.h"
#include <ElaMessageBar.h>
#include <QApplication>
#include <QClipboard>
#include <QFileDialog>
#include <QImage>
#include <QImageReader>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWheelEvent>

// ref: https://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
// TODO: implement me

class ImageViewer : public WindowOverlayWidget {
    Q_OBJECT
public:
    ImageViewer(QWidget* parent = {});
    bool loadImagefromDisk(const QString& path);
    bool loadImage(const QImage& image);
    const QString& getImagePath();
    bool copyImageToClipboard();
    void openImageFileDialog();
    QImage getImage() const { return this->image; }
    void saveImageFileDialog();
    void readFullInfo(const QString& path);
    void adaptiveResize() {
        // get the resolution of user's monitor
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();
        //get the size of the image

        QImage loadedImage = this->image;
        int imageWidth = loadedImage.width();
        int imageHeight = loadedImage.height();

        //calculate the size of the Window
        int windowWidth = imageWidth;
        int windowHeight = imageHeight;
        if (imageWidth > screenWidth || imageHeight > screenHeight) {
            qreal widthRatio = static_cast<qreal>(screenWidth) / windowWidth;
            qreal heightRatio = static_cast<qreal>(screenHeight) / windowHeight;
            qreal scaleFactor = qMin(widthRatio, heightRatio);
            windowWidth = static_cast<int>(windowWidth * scaleFactor);
            windowHeight = static_cast<int>(windowHeight * scaleFactor);
        }
        this->resize(windowWidth, windowHeight);
    }
    ~ImageViewer() = default;

protected:
    void paintEvent(QPaintEvent*) override {
        // placeholder
        QPainter p{this};
        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::TextAntialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
    }

    /*
    void previousmedia()=0;
    
    void nextmedia()=0;

    void deleteMedia()=0;

    void rotateImage()=0; //only for images

    void scaleImage(double factor)=0;//only for images
  */

private:
    QImage image; //process image in RAM , then cast to QPixmap to QLabel for display
    QLabel* imageLabel;
    QString imagePath;
    QVBoxLayout* layout;
    QPoint dragPosition;
    double scaleFactor;
    void updateDisplaydImage();

    friend class ViewingWindow;
};
