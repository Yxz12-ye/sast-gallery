#pragma once

#include <QLabel>
#include <QLayoutItem>
#include <QResizeEvent>

// used for thumbnail, work with ImageFlexLayout
// load image and set image size as size hint
// TODO: implement me
class MediaThumbnail : public QLabel {
public:
    explicit MediaThumbnail(QWidget* parent, const QString& filepath);
    ~MediaThumbnail();

    // load image when show
    void showEvent(QShowEvent* event) override;
    // keep image radio
    void resizeEvent(QResizeEvent* event) override;

    QSize sizeHint() const override;

private:
    QString filepath;
    QSize mediaSize;
    QPixmap img;
};