#include "mainwindow.h"
#include <QApplication>
#include "dbman.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if (!BdMan::instance().initDatabase("DataBaze_2.db")) {
        qCritical() << "Не удалось запустить приложение без БД!";
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
