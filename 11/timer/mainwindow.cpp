#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QLCDNumber>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}

void MainWindow::updateDisplay()
{
    ui->lcdNumberSec->display(time.toString("s"));
    ui->lcdNumberMin->display(time.toString("m"));
}

void MainWindow::onTimeout()
{
    time = time.addSecs(1);
    updateDisplay();
}

void MainWindow::on_resetButton_clicked()
{
    time = QTime(0, 0, 0);
    timer->start(1000);
    time = time.addSecs(0);
    updateDisplay();
}
