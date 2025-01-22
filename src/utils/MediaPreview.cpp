#include "MediaPreview.h"

MediaPreview::MediaPreview(QWidget* parent, const QString& filepath)
    : QLabel(parent)
    , filepath(filepath) {
    setScaledContents(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    img.load(filepath);
    mediaSize = img.size();
    img = img.scaledToHeight(180, Qt::SmoothTransformation);
}

MediaPreview::~MediaPreview() {}

void MediaPreview::showEvent(QShowEvent* event) {
    setPixmap(img);
    // setPixmap(img.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MediaPreview::resizeEvent(QResizeEvent* event) {
    if (!isVisible()) {
        return;
    }
    setPixmap(img);
    // setPixmap(img.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QSize MediaPreview::sizeHint() const {
    return mediaSize.scaled(1000, 150, Qt::KeepAspectRatio);
}