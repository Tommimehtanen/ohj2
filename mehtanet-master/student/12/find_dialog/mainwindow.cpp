
#include "mainwindow.hh"
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QString>
#include <QtGlobal>


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






void MainWindow::on_fileLineEdit_editingFinished()
{
    QString file_name = ui->fileLineEdit->text();
    file_name_ = file_name;
}

void MainWindow::on_keyLineEdit_editingFinished()
{
     QString key_word = ui->keyLineEdit->text();
     key_word_ = key_word;
}

void MainWindow::on_findPushButton_clicked()
{



    QFile file(file_name_);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->textBrowser->setText("File not found");
        return;
    }
    else if(key_word_.isEmpty()){
        ui->textBrowser->setText("File found");
        return;
    }else{
    QTextStream in (&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        if (ui->matchCheckBox->isChecked()){

            if(line.contains(key_word_, Qt::CaseSensitive)){
                ui->textBrowser->setText("Word found");
                return;
            }

        }else{
            QString a = key_word_.toUpper();
            QString b = line.toUpper();

            if (b.contains(a)){
                ui->textBrowser->setText("Word found");
                return;
                }
            }
        }
        ui->textBrowser->setText("Word not found");
        return;
    }


}






