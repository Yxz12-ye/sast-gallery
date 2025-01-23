#pragma once
#include <QFileInfo>
#include <QMetaType>

struct MediaItem {
    QString path;
    QDateTime lastModifiedTime;
    bool isFavorite;
};

Q_DECLARE_METATYPE(MediaItem);