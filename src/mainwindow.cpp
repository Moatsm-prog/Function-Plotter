#include "..\headers\mainwindow.h"
#include "ui_mainwindow.h"
#include "..\headers\validate.h"
#include "..\headers\postfix_evaluate.h"
#include <QLineEdit>
#include <QStatusBar>
#include <QMessageBox>
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



void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    QString exp = ui->lineEdit->text();
    QVector<QString> errors = validate(exp);
    if(errors.size() == 0){
        statusBar()->showMessage(tr("Valid"), 2000);
        QVector<double> input;
        QVector<double> output;
        QString post = postfix(exp);
        int start = ui->spinBox->value();
        int end = ui->spinBox_2->value();
        float num = ui->spinBox_3->value();
        float step = (end-start)/num;
        for(float i=start ; i <= end ; i = i + step){
            input.push_back(i);
            float temp = evaluate(post , i);
            output.push_back(temp);
         }

            // create graph and assign data to it:
            ui->widget->addGraph();
            ui->widget->graph(0)->setData(input, output);
            // give the axes some labels:
            ui->widget->xAxis->setLabel("x");
            ui->widget->yAxis->setLabel("F(x)");
            // set axes ranges, so we see all data:
            ui->widget->graph(0)->rescaleAxes();
            ui->widget->replot();
    }
    else{
        statusBar()->showMessage(tr("Invalid"), 2000);
        QString message="";
        for(int i=0 ; i < errors.size() ; i++){
            message = message + errors[i] + "\n";
        }
        QMessageBox msg;
        msg.setText(message);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();



}

}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.size() == 0){
            ui->pushButton->setEnabled(false);
        }
        else{
            ui->pushButton->setEnabled(true);
        }
}





void MainWindow::on_spinBox_valueChanged(double arg1)
{
    ui->spinBox_2->setMinimum(arg1+1);
    ui->pushButton->setEnabled(true);
}


void MainWindow::on_spinBox_2_valueChanged(double arg1)
{
    ui->pushButton->setEnabled(true);
}


void MainWindow::on_spinBox_3_valueChanged(double arg1)
{
    ui->pushButton->setEnabled(true);
}

