#pragma once

#include "utils/WindowOverlayWidget.h"
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
    bool loadImage(const QString& path);

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

    void mousePressEvent(QMouseEvent* mouseEvent) override {
        if (mouseEvent->button() == Qt::LeftButton) {
            dragPosition = mouseEvent->globalPosition().toPoint() - frameGeometry().topLeft();
            mouseEvent->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent* mouseEvent) override {
        if (mouseEvent->buttons() & Qt::LeftButton) {
            move(mouseEvent->globalPosition().toPoint() - dragPosition);
            mouseEvent->accept();
        }
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
};
