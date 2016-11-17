#include <QtWidgets/QApplication>
#include <data/DbHandler.h>
#include "ui/MainWindow.h"

int main(int argc, char ** argv)
{
    QApplication app (argc, argv);
    DbHandler::getInstance();

    QMainWindow win;
    win.resize(800, 600);
    win.move(1920/2-800/2, 1080/2-600/2);
    win.setWindowTitle("Finances");
    MainWindow mainArea;
    win.setCentralWidget(&mainArea);

    win.show();
    return app.exec();
}
