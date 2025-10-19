#include "logging.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    rfmodel::logging::initializeLogging(argc, argv);

    QApplication a(argc, argv);
    LOG_UI_INFO() << "Starting RF-Model application";
    MainWindow w;
    w.show();
    return a.exec();
}
