#include <QtWidgets>
#include "data/DbHandler.h"
#include "ui/MainWindow.h"

int main(int argc, char ** argv)
{
    QApplication app (argc, argv);
    DbHandler::getInstance();

    QMainWindow win;
    //win.setWindowFlags(Qt::WindowFlags(Qt::WindowState::WindowMaximized|Qt::WindowType::Window));
    win.setWindowTitle("Finances");
    MainWindow mainArea;
    win.setCentralWidget(&mainArea);

    win.show();
    return app.exec();
}
