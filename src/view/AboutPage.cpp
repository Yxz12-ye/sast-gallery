#include "AboutPage.h"
#include <ElaText.h>
#include <QVBoxLayout>
#include <Version.h>

AboutPage::AboutPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("About");

    // page root
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("About");
    centralWidget->setSizePolicy(QSizePolicy::Policy::Ignored,
                                 centralWidget->sizePolicy().verticalPolicy());
    addCentralWidget(centralWidget);

    auto layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout->addWidget(createText("Sast-gallery", 25));
    layout->addWidget(createText(QString("版本：%1").arg(VERSION_SEMANTIC), 14));
    layout->addWidget(createText("许可协议：MIT", 14));
    layout->addWidget(createText("支持平台：Windows 和 Linux", 14));
    layout->addStretch();

    centralWidget->setLayout(layout);
}

AboutPage::~AboutPage() {}

ElaText* AboutPage::createText(const QString& text, int size) {
    auto* label = new ElaText(text, this);
    label->setTextPixelSize(size);
    label->setAlignment(Qt::AlignCenter);
    return label;
}
