#include <QEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QWidget>

// from: https://stackoverflow.com/questions/19362455/dark-transparent-layer-over-a-qmainwindow-in-qt/19367454#19367454\
// with some changes for ElaWindow

class WindowOverlayWidget : public QWidget {
    void newParent() {
        if (parent() == nullptr) {
            return;
        }
        parent()->installEventFilter(this);
        auto parentWidget = dynamic_cast<QWidget*>(parent());
        move(0, parentWidget->contentsMargins().top());
        raise();
    }

public:
    explicit WindowOverlayWidget(QWidget* parent = nullptr)
        : QWidget{parent} {
        // setAttribute(Qt::WA_NoSystemBackground);
        // setAttribute(Qt::WA_TransparentForMouseEvents);
        newParent();
    }

protected:
    //! Catches resize and child events from the parent widget
    bool eventFilter(QObject* obj, QEvent* ev) override {
        if (obj == parent()) {
            if (ev->type() == QEvent::Resize) {
                auto targetSize = dynamic_cast<QResizeEvent*>(ev)->size();
                auto* parentWidget = dynamic_cast<QWidget*>(parent());
                resize(targetSize.width(),
                       targetSize.height() - parentWidget->contentsMargins().top());
            } else if (ev->type() == QEvent::ChildAdded) {
                raise();
            }
        }
        return QWidget::eventFilter(obj, ev);
    }
    //! Tracks parent widget changes
    bool event(QEvent* ev) override {
        if (ev->type() == QEvent::ParentAboutToChange) {
            if (parent() != nullptr) {
                parent()->removeEventFilter(this);
            }
        } else if (ev->type() == QEvent::ParentChange) {
            newParent();
        }
        return QWidget::event(ev);
    }
};