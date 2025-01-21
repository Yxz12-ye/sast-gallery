#include "MediaThumbnail.h"

MediaThumbnail::MediaThumbnail(QWidget* parent, const QString& filepath)
    : QLabel(parent)
    , filepath(filepath) {
    setScaledContents(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    img.load(filepath);
    mediaSize = img.size();
    img = img.scaledToHeight(180, Qt::SmoothTransformation);
}

MediaThumbnail::~MediaThumbnail() {}

void MediaThumbnail::showEvent(QShowEvent* event) {
    setPixmap(img);
    // setPixmap(img.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MediaThumbnail::resizeEvent(QResizeEvent* event) {
    if (!isVisible()) {
        return;
    }
    setPixmap(img);
    // setPixmap(img.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QSize MediaThumbnail::sizeHint() const {
    return mediaSize.scaled(1000, 150, Qt::KeepAspectRatio);
}