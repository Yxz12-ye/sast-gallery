#pragma once

#include <QAbstractItemModel>
#include <QImage>
#include <QObject>
#include <QPersistentModelIndex>
#include <QVBoxLayout>

class MediaViewer;

class MediaViewerDelegate : public QObject {
    Q_OBJECT

public:
    explicit MediaViewerDelegate(QAbstractItemModel* model,
                                 int index,
                                 MediaViewer* window,
                                 QObject* parent = nullptr);

    [[nodiscard]] auto getFilePath() const { return filepath; }
    [[nodiscard]] auto getImage() const { return this->image; }
    void initConnections();

public slots:
    void onModelRowsToBeRemoved(const QModelIndex& parent, int first, int last);
    bool copyImageToClipboard();
    void openImageFileDialog();
    void saveImageFileDialog();
    void readFullInfo();
    void adaptiveResize();
    void deleteImage();
    void prevImage();
    void nextImage();
    void rotateImage();

private:
    QAbstractItemModel* mediaListModel;
    QPersistentModelIndex mediaIndex;
    QImage image;
    QString filepath;
    MediaViewer* view;
    QVBoxLayout* layout;
    double scaleFactor;

    bool loadImagefromDisk(const QString& path);
    bool loadImage(const QImage& image);
};