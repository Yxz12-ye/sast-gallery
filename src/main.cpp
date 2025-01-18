#include "MainWindow.h"
#include <ElaApplication.h>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    MainWindow w;
    w.show();
    return a.exec();
}
