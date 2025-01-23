#include "MediaFlexLayout.h"
#include <QWidget>
#include <cstdlib>

MediaFlexLayout::MediaFlexLayout(QWidget* parent)
    : QLayout(parent) {}

MediaFlexLayout::MediaFlexLayout(int preferredLineHeight, QWidget* parent)
    : QLayout(parent)
    , preferredLineHeight(preferredLineHeight) {}

MediaFlexLayout::~MediaFlexLayout() {
    QLayoutItem* item;
    while ((item = takeAt(0))) {
        delete item;
    }
}

void MediaFlexLayout::setGeometry(const QRect& rect) {
    QLayout::setGeometry(rect);
    layoutItems(rect);
}

QSize MediaFlexLayout::sizeHint() const {
    return minimumSize();
}

QSize MediaFlexLayout::minimumSize() const {
    QSize size = parentWidget()->size();
    size.setHeight(layoutItems({0, 0, size.width(), 0}, true));
    return size;
}

Qt::Orientations MediaFlexLayout::expandingDirections() const {
    return Qt::Horizontal | Qt::Vertical;
}

void MediaFlexLayout::addItem(QLayoutItem* item) {
    itemList.append(item);

    LayoutData data;
    auto itemSize = item->sizeHint();
    data.radio = double(itemSize.width()) / double(itemSize.height());
    itemLayoutData.append(data);
}

int MediaFlexLayout::count() const {
    return itemList.size();
}

QLayoutItem* MediaFlexLayout::itemAt(int index) const {
    return itemList.value(index);
}

QLayoutItem* MediaFlexLayout::takeAt(int index) {
    if (index >= 0 && index < itemList.size()) {
        itemLayoutData.takeAt(index);
        return itemList.takeAt(index);
    }
    return nullptr;
}

bool MediaFlexLayout::hasHeightForWidth() const {
    return true;
}

int MediaFlexLayout::heightForWidth(int width) const {
    return layoutItems({0, 0, width, 0}, true);
}

int MediaFlexLayout::layoutItems(const QRect& rect, bool dryRun) const {
    // use effectiveRect in account of margin
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);

    if (itemList.size() == 0) {
        return top + bottom;
    }

    int startItem = 0;
    int endItem = -1;
    int y = effectiveRect.y();

    // set oneline onetime
    while (startItem < itemList.size()) {
        // find start and end
        double lineHeight = 1e9;
        double previousLineHeight = 1e9;
        double sumRatio = 0;
        while (abs(lineHeight - preferredLineHeight) <= abs(previousLineHeight - preferredLineHeight)
               || lineHeight == 0) {
            endItem++;
            previousLineHeight = lineHeight;
            if (endItem >= itemList.size()) {
                break;
            }
            sumRatio += itemLayoutData.value(endItem).radio;
            lineHeight = (effectiveRect.width() - spacing() * (endItem - startItem)) / sumRatio;
        }
        lineHeight = previousLineHeight;
        endItem--;
        // now have startItem endItem lineHeight

        if (endItem < startItem) {
            endItem = startItem;
            lineHeight = (effectiveRect.width() - spacing() * (endItem - startItem))
                         / itemLayoutData.value(endItem).radio;
        }

        // set widgets
        int x = effectiveRect.x();
        for (int i = startItem; i <= endItem; i++) {
            auto widget = itemList.value(i)->widget();
            auto width = itemLayoutData.value(i).radio * lineHeight;
            if (!dryRun) {
                widget->setGeometry(x, y, width, lineHeight);
            }
            x += width + spacing();
        }
        y += lineHeight + spacing();
        startItem = endItem + 1;
    }

    // return content height for other function
    return y - spacing() + bottom;
}
