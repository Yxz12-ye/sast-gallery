#pragma once

#include <ElaCustomWidget.h>
#include <ElaMenuBar.h>
#include <ElaMenu.h>
class ViewingWindow : public ElaCustomWidget {
    Q_OBJECT

public:
    explicit ViewingWindow(QWidget* parent = nullptr);
    ~ViewingWindow();

    void initWindow();
    void initContent();
};