#pragma once

#include <QDateTime>
#include <QEvent>
#include <QFutureWatcher>
#include <QLabel>

// display media in thumbnail, supposed to be work with ImageFlexLayout
class MediaPreviewer : public QLabel {
    Q_OBJECT
public:
    explicit MediaPreviewer(QString filepath,
                            QDateTime time,
                            bool isFavorite = false,
                            QWidget* parent = nullptr);
    ~MediaPreviewer();

    // load image when show
    void paintEvent(QPaintEvent* event) override;

    QSize sizeHint() const override;

    void setPath(const QString& path);
    void setLastModifiedTime(const QDateTime& time);
    void setIsFavorite(bool isFavorite);
    QString path();
    QDateTime lastModifiedTime();
    bool isFavorite();

public slots:
    void loadImageComplete();

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    QString filepath;
    QDateTime lastModified;
    bool isFav;

    QSize mediaSize;

    bool requireReloadImage = true;
    QFutureWatcher<QPixmap> imageLoadWatcher;

    void initMedia();
    QPixmap loadImage();
};