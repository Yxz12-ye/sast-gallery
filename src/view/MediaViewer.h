#pragma once

#include "ImageViewer.h"
#include <ElaCustomWidget.h>
#include <ElaIconButton.h>
#include <ElaSlider.h>
#include <ElaText.h>
#include <QAbstractItemModel>
#include <QApplication>
#include <qaction.h>

class MediaViewerDelegate;

class MediaViewer : public ElaCustomWidget {
    Q_OBJECT
    friend class MediaViewerDelegate;

public:
    explicit MediaViewer(QAbstractItemModel* model, int index, QWidget* parent = nullptr);
    ~MediaViewer();
    QSlider* getZoomSlider() const { return zoomSlider; }
    void initWindow();
    void initContent();

private:
    QAction* rotateAction{};
    QAction* deleteAction{};
    QAction* printAction{};
    QAction* editAction{};
    QAction* prevAction{};
    QAction* nextAction{};
    QAction* openFileAction{};
    QAction* copyFileAction{};
    QAction* saveasFileAction{};
    QAction* openInFileExplorerAction{};
    ElaSlider* zoomSlider{};
    ElaIconButton* likeButton{};
    ElaIconButton* fileInfoButton{};
    ElaIconButton* zoomInButton{};
    ElaIconButton* zoomOutButton{};
    ElaIconButton* maximizeButton{};
    ElaIconButton* zoom2originalButton{};
    ElaText* fileInfoBriefText{};
    ImageViewer* imageViewer;

    MediaViewerDelegate* delegate{};
};