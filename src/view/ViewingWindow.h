#pragma once

#include <ElaCustomWidget.h>
#include <ElaIconButton.h>
#include <ElaMenu.h>
#include <ElaMenuBar.h>
#include <ElaPushButton.h>
#include <ElaWidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
class ViewingWindow : public ElaCustomWidget {
    Q_OBJECT

public:
    explicit ViewingWindow(QWidget* parent = nullptr);
    ~ViewingWindow();

    void initWindow();
    void initContent();
};