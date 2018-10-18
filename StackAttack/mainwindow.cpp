#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_btn_clicked()
{
    Game* game_win = new Game();
    game_win->show();
    this->hide();
}

void MainWindow::on_exit_btn_clicked()
{
    parent()->killTimer(1);
}
