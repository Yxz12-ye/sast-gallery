#include "AboutPage.h"
#include <ElaIconButton.h>
#include <ElaImageCard.h>
#include <ElaMessageBar.h>
#include <ElaText.h>
#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Version.h>

AboutPage::AboutPage(QWidget* parent)
    : BasePage(parent) {
    setWindowTitle("About");

    auto* pixCard = new ElaImageCard(this);
    pixCard->setFixedSize(100, 100);
    pixCard->setIsPreserveAspectCrop(false);
    pixCard->setCardImage(QImage(":/res/icon/app_icon.svg"));

    auto* pixCardText = new ElaText("SAST Gallery", this);
    pixCardText->setWordWrap(false);
    pixCardText->setTextPixelSize(25);

    auto* pixCardLayout = new QHBoxLayout();
    pixCardLayout->addWidget(pixCard);
    pixCardLayout->addSpacing(20);
    pixCardLayout->addWidget(pixCardText);
    pixCardLayout->setAlignment(Qt::AlignCenter);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("About");
    centralWidget->setSizePolicy(QSizePolicy::Policy::Ignored,
                                 centralWidget->sizePolicy().verticalPolicy());
    auto centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addSpacing(30);
    centerLayout->addLayout(pixCardLayout);
    centerLayout->addSpacing(30);
    centerLayout->addWidget(createTextContent("Version Info", VERSION_FULL));
    centerLayout->addWidget(
        createTextContent("License", "MIT License Copyright (c) 2024 NJUPT-SAST"));
    centerLayout->addWidget(createTextContent("Supported Platforms", "Windows | Linux | macOS"));
    centerLayout->addWidget(
        createLinkContent("Repository", "https://github.com/NJUPT-SAST-CXX/sast-gallery"));
    centerLayout->addWidget(createLinkContent("Visit SAST", "https://sast.fun"));
    centerLayout->addStretch();
    centerLayout->setContentsMargins(0, 0, 0, 0);
    addCentralWidget(centralWidget, true, true, 0);
}

AboutPage::~AboutPage() {}

ElaScrollPageArea* AboutPage::createTextContent(QString label, QString content) {
    auto* area = new ElaScrollPageArea(this);
    auto* layout = new QHBoxLayout(area);
    auto* labelText = new ElaText(label, this);
    auto* contentText = new ElaText(content, this);
    labelText->setWordWrap(false);
    labelText->setTextPixelSize(15);
    contentText->setWordWrap(false);
    contentText->setTextPixelSize(15);
    layout->addWidget(labelText);
    layout->addStretch();
    layout->addWidget(contentText);
    return area;
}

ElaScrollPageArea* AboutPage::createLinkContent(QString label, QString link) {
    auto* area = new ElaScrollPageArea(this);
    auto* layout = new QHBoxLayout(area);
    auto* labelText = new ElaText(label, this);
    auto* linkText = new ElaText(QString("<a style='color: #D0BCFF' href = \"%1\">%1").arg(link),
                                 this);
    auto* copyButton = new ElaIconButton(ElaIconType::Copy, 15, 15, 15, this);
    auto* linkLayout = new QHBoxLayout(area);
    labelText->setWordWrap(false);
    labelText->setTextPixelSize(15);
    linkText->setWordWrap(false);
    linkText->setTextPixelSize(15);
    linkText->setOpenExternalLinks(true);
    linkLayout->addWidget(copyButton);
    linkLayout->addWidget(linkText);
    layout->addWidget(labelText);
    layout->addStretch();
    layout->addLayout(linkLayout);
    connect(copyButton, &QPushButton::clicked, [=]() {
        QApplication::clipboard()->setText(link);
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Copied!", nullptr, 2000);
    });
    return area;
}
