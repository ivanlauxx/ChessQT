#include <QApplication>
#include "mainwindow.h"
#include "registrationdialog.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return application.exec();
}
