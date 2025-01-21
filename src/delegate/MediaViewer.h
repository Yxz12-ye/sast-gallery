#pragma once
#include "utils/WindowOverlayWidget.h"
#include <QImage>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QVBoxLayout>
// ref: https://doc.qt.io/qt-5/qtwidgets-widgets-MediaViewer-example.html
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

    void wheelEvent(QWheelEvent* event) override {
        if (event->angleDelta().y() > 0) {
            scaleFactor *= 1.1;
        } else {
            scaleFactor /= 1.1;
        }
        update();
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }

    }

private:
    void scroll(const QPoint& delta) {
        // placeholder
    }

    QImage image;
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
    QVBoxLayout* layout;
    QPoint dragPosition;
    double scaleFactor;

};