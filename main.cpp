#include "src/mainwindow.h"
#include <QApplication>
#include <QWizard>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QWizard wizard;

//    wizard.setWindowTitle("Trivial Wizard");
//    wizard.show();

    return a.exec();
}
