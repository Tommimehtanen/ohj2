#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QString>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    QString weight = ui->weightLineEdit->text();
    weight_ = weight.toDouble();
}

void MainWindow::on_heightLineEdit_editingFinished()
{
    QString height = ui->heightLineEdit->text();
    height_ = (height.toDouble())/100;
}

void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    weight_ = arg1.toDouble();
}

void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
     height_ = (arg1.toDouble())/100;
}



void MainWindow::on_countButton_clicked()
{
    double bmi = 0;

    bmi = weight_/(height_*height_);
   // bmi = (int)(bmi * 10000.0)/10000.0;
    QString strbmi = QString::number(bmi);
    ui->resultLabel->setText(strbmi);

    if(bmi < 18.5){
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if(bmi >25){
        ui->infoTextBrowser->setText("You are overweight.");
    }
    else{
        ui->infoTextBrowser->setText("Your weight is normal.");
    }

}
