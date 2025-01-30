#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

class ImageViewer : public QGraphicsView {
    Q_OBJECT

public:
    explicit ImageViewer(QWidget* parent = nullptr);
    explicit ImageViewer(const QPixmap& pixmap, QWidget* parent = nullptr);
    void setContent(const QPixmap& pixmap, bool fadeAnimation = true);
    void setContent(const QImage& image, bool fadeAnimation = true);
    void setWheelZoom(bool enabled);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmapItem;
    QPoint lastMousePos;
    bool zoomEnabled;
    bool dragging;

    void adjustImageToFit();
};