#include <ElaApplication.h>
#include <ElaWindow.h>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    ElaWindow w;
    w.setWindowTitle("SAST Gallery");
    w.show();
    return a.exec();
}
