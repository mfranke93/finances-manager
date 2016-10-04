#include <QtWidgets/QApplication>
#include "ui/main_window.h"

int main(int argc, char ** argv)
{
    QApplication app (argc, argv);
    if (!ExpenditureView::createConnection())
        return 1;

    QMainWindow win;
    win.resize(800, 600);
    win.move(1920/2-800/2, 1080/2-600/2);
    MainWindow mainArea;
    win.setCentralWidget(&mainArea);

    win.show();
    return app.exec();
}
