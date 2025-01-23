#pragma once

#include "utils/WindowOverlayWidget.h"
#include <QImage>
#include <QLabel>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QPixmap>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWheelEvent>

// ref: https://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
// TODO: implement me

class MediaViewer : public WindowOverlayWidget {
    Q_OBJECT
public:
    MediaViewer(QWidget* parent = {});
    bool loadImage(const QString& path);
    bool loadVideo(const QString& path);

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

    virtual void play()=0; //only for videos

    virtual void pause()=0; //only for videos

    virtual void setVolume(int volume)=0; //only for videos

    virtual void mute()=0; //only for videos

    virtual void unmute()=0; //only for videos

  */

private:
    QImage image; //process image in RAM , then cast to QPixmap to QLabel for display
    QLabel* imageLabel;
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
    QVBoxLayout* layout;
    QPoint dragPosition;
    double scaleFactor;
};
