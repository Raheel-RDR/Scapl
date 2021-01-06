#include "rundialog.h"
#include "ui_rundialog.h"
#include "./program/program.h"
#include "./operand/operand.h"
#include <QMessageBox>

RunDialog::RunDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunDialog)
{
    ui->setupUi(this);
}

RunDialog::~RunDialog()
{
    delete ui;
}

void RunDialog::on_pushButton_clicked()
{
    QString fileName = ui->lineEdit->text();
    Program* p = new Program();
    this->p = p;
    this->close();
    this->p->start(fileName);
}
