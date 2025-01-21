#pragma once
#include "utils/WindowOverlayWidget.h"
#include <QImage>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
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

    void mouseMoveEvent(QMouseEvent* mouseEvent)override{
        if (mouseEvent->buttons() & Qt::LeftButton) {
            move(mouseEvent->globalPosition().toPoint() - dragPosition);
            mouseEvent->accept();
        }
    }

private:
    void scroll(const QPoint& delta) {
        // placeholder
    }

    QImage image; //process image in RAM , then cast to QPixmap to QLabel for display
    QLabel* imageLabel;
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
    QVBoxLayout* layout;
    QPoint dragPosition;
    double scaleFactor;

};