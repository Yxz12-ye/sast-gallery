#include "MainWindow.h"
#include <ElaApplication.h>
#include <ElaTheme.h>
#include <QApplication>
#include <QSize>
#include <utils/Settings.hpp>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // Initialize settings
    if (!settings.contains("windowSize")) {
        settings.setValue("windowSize", QSize(1200, 740));
    }
    if (!settings.contains("theme")) {
        settings.setValue("theme", "Light");
    }

    ElaApplication::getInstance()->init();
    ElaTheme::getInstance()->setThemeMode(
        settings.value("theme").toString() == "Light" ? ElaThemeType::Light : ElaThemeType::Dark);
    MainWindow w;
    w.resize(settings.value("windowSize").toSize());
    w.show();

    return a.exec();
}
