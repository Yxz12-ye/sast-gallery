#include "MediaListModel.h"
#include "MediaItem.h"

MediaListModel::MediaListModel(QList<MediaItem>&& data, QObject* parent)
    : QAbstractListModel(parent)
    , mediaList(std::move(data)) {}

int MediaListModel::rowCount(const QModelIndex& parent) const {
    return mediaList.size();
}

Qt::ItemFlags MediaListModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

QVariant MediaListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= mediaList.size()) {
        return {};
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return QVariant::fromValue(mediaList.value(index.row()));
    }

    return {};
}

bool MediaListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        mediaList.replace(index.row(), value.value<MediaItem>());
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void MediaListModel::reset(QList<MediaItem>&& data) {
    beginResetModel();

    mediaList = std::move(data);

    endResetModel();
}