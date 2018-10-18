#include "mainwindow.h"
#include "game.h"
#include <QApplication>
#include <QtWidgets>

void start_game(){

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* main_win = new MainWindow();
    main_win->show();
    return a.exec();
}
