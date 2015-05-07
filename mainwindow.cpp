#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

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

void MainWindow::updateUIComponents(int r, int g, int b, int a)
{
    ui->horizontalSliderRed->setValue(r);
    ui->horizontalSliderBlue->setValue(b);
    ui->horizontalSliderGreen->setValue(g);
    ui->horizontalSliderAlpha->setValue(a);
}


