#pragma once

#include <QLayout>

// ref: https://doc.qt.io/qt-6/qtwidgets-layouts-flowlayout-example.html

// layout media in gallery and favorite

class MediaFlexLayout : public QLayout {
    QList<QLayoutItem*> itemList;

    struct LayoutData {
        double radio; // width/height

        // like item[row][col]
        int row = -1; // line number
        int col = -1; // line offset
    };

    int preferredLineHeight = 180;
    QList<LayoutData> itemLayoutData;
    QList<int> lineHeight;

public:
    explicit MediaFlexLayout(QWidget* parent = nullptr);
    explicit MediaFlexLayout(int preferredLineHeight, QWidget* parent = nullptr);
    ~MediaFlexLayout();

    void setGeometry(const QRect& rect) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    Qt::Orientations expandingDirections() const override;

    void addItem(QLayoutItem* item) override;
    int count() const override;
    QLayoutItem* itemAt(int index) const override;
    QLayoutItem* takeAt(int index) override;

    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;

private:
    int layoutItems(const QRect& rect, bool dryRun = false) const;
};