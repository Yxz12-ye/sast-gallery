#include "MediaViewer.h"

MediaViewer::MediaViewer(QWidget* parent)
    : WindowOverlayWidget(parent),
      mediaPlayer(new QMediaPlayer(this)),
      videoWidget(new QVideoWidget(this)),
      layout(new QVBoxLayout(this)),
      scaleFactor(1.0)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
   //QPainter::setRenderHint() for monitors with high DPI ,to be verified

   //layout to be further implemented
    layout->addWidget(videoWidget);
    videoWidget->hide();
    mediaPlayer->setVideoOutput(videoWidget);
}

bool MediaViewer::loadImage(const QString& path)
{
   //to be implemented
    return false;
}

bool MediaViewer::loadVideo(const QString& path)
{
    //to be implemented
    return false;
}


