#include "tictatoewindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TicTaToeWindow w;
    w.resize(500,500);
    w.show();

    return a.exec();
}
