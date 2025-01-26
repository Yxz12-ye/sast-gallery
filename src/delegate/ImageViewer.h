#pragma once

#include "utils/WindowOverlayWidget.h"
#include <QFileDialog>
#include <QImage>
#include <QLabel>
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
    bool loadImagefrompath(const QString& path);
    bool loadImage(const QImage& image);
    static inline const QString& getImagePath();
    void openImageFileDialog();
    ~ImageViewer() = default;

protected:
    void paintEvent(QPaintEvent*) override {
        // placeholder
        QPainter p{this};
        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::TextAntialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        p.fillRect(rect(), {100, 100, 100, 128});
        p.setPen({200, 200, 255});
        p.setFont({"arial,helvetica", 48});
        p.drawText(rect(), "IMAGE HERE", Qt::AlignBottom | Qt::AlignRight);
        p.drawText(rect(), "IMAGE HERE", Qt::AlignTop | Qt::AlignLeft);
    }

   

    /*
  
   virtual void displaymedia()=0;
    
    virtual void previousmedia()=0;
    
    virtual void nextmedia()=0;

    virtual void deleteMedia()=0;

    virtual void checkMediaInfo()=0;

    virtual void rotateImage()=0; //only for images

    virtual void scaleImage(double factor)=0;//only for images
  */

private:
    QImage image; //process image in RAM , then cast to QPixmap to QLabel for display
    QLabel* imageLabel;
    QVBoxLayout* layout;
    QPoint dragPosition;
    double scaleFactor;
    void updateDisplaydImage();
};
