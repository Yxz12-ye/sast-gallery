#pragma once

#include <QLabel>
#include <QLayoutItem>
#include <QResizeEvent>

// display media in thumbnail, supposed to be work with ImageFlexLayout
class MediaPreview : public QLabel {
    Q_OBJECT
public:
    explicit MediaPreview(QWidget* parent, const QString& filepath);
    ~MediaPreview();

    // load image when show
    void showEvent(QShowEvent* event) override;
    // keep image radio
    void resizeEvent(QResizeEvent* event) override;

    QSize sizeHint() const override;

private:
    QString filepath;
    QSize mediaSize;
    QPixmap img;
};