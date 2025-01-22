#pragma once
#include <QFileInfo>
#include <QMetaType>

struct MediaItem {
    QFileInfo fileInfo;
    bool isFavorite;
};

Q_DECLARE_METATYPE(MediaItem);