#pragma once

#include "MediaItem.h"
#include <QAbstractListModel>
#include <QList>

// model for storing media property on disk, not including the image content

class MediaListModel : public QAbstractListModel {
    Q_OBJECT

    QList<MediaItem> mediaList;

public:
    MediaListModel(QList<MediaItem>&& data, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    // TODO: add item
    // TODO: del item
    void reset(QList<MediaItem>&& data);
};