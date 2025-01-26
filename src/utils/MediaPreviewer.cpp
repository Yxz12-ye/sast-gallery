#include "MediaPreviewer.h"
#include <QImageReader>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QtConcurrentRun>

MediaPreviewer::MediaPreviewer(QString filepath, QDateTime time, bool isFavorite, QWidget* parent)
    : QLabel(parent)
    , filepath(std::move(filepath))
    , lastModified(std::move(time))
    , isFav(isFavorite) {
    connect(&imageLoadWatcher,
            &QFutureWatcher<QPixmap*>::finished,
            this,
            &MediaPreviewer::loadImageComplete);
    setScaledContents(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    initMedia();
    qDebug() << "load image" << this->filepath;
}

MediaPreviewer::~MediaPreviewer() {}

void MediaPreviewer::paintEvent(QPaintEvent* event) {
    QLabel::paintEvent(event);
    if (requireReloadImage) {
        imageLoadWatcher.setFuture(QtConcurrent::run(&MediaPreviewer::loadImage, this));
        requireReloadImage = false;
    }
}

QSize MediaPreviewer::sizeHint() const {
    // return mediaSize.scaled(1000, 150, Qt::KeepAspectRatio);
    return mediaSize;
}

void MediaPreviewer::setPath(const QString& path) {
    filepath = path;
    initMedia();
}
void MediaPreviewer::setLastModifiedTime(const QDateTime& time) {
    lastModified = time;
    initMedia();
}

void MediaPreviewer::setIsFavorite(bool isFavorite) {
    isFav = isFavorite;
}

QString MediaPreviewer::path() {
    return filepath;
}

QDateTime MediaPreviewer::lastModifiedTime() {
    return lastModified;
}

bool MediaPreviewer::isFavorite() {
    return isFav;
}

void MediaPreviewer::initMedia() {
    mediaSize = QImageReader(filepath).size();
    requireReloadImage = true;
}

QPixmap MediaPreviewer::roundedPixmap(const QPixmap& original, int radius) {
    QPixmap target = QPixmap(original.size());
    target.fill(Qt::transparent);
    QPainter painter(&target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    QPainterPath path = QPainterPath();
    path.addRoundedRect(target.rect(), 4, 4);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, original);
    return target;
}

void MediaPreviewer::loadImageComplete() {
    setPixmap(roundedPixmap(QPixmap(imageLoadWatcher.result()), 4));
}

void MediaPreviewer::mouseDoubleClickEvent(QMouseEvent* event) {
    // TODO: open the image in a ViewingWindow
}

QPixmap MediaPreviewer::loadImage() {
    QImageReader reader(filepath);
    reader.setScaledSize(QSize{0, 180});
    return QPixmap::fromImage(reader.read());
}
