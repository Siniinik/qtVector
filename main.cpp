#include <mainwindow.h>
#include <QApplication>
#include <ui_mainwindow.h>
#include <QVector>
#include <QDebug>

/**
* ИС «Часы» (фирма, модель, год, страна, цена)
* Автор: А. В. Синицын
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}




