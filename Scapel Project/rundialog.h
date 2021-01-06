#ifndef RUNDIALOG_H
#define RUNDIALOG_H

#include <QDialog>
#include "program/program.h"

namespace Ui {
class RunDialog;
}

class RunDialog : public QDialog
{
    Q_OBJECT
    Program *p;

public:
    explicit RunDialog(QWidget *parent = nullptr);
    ~RunDialog();


private slots:
    void on_pushButton_clicked();

private:
    Ui::RunDialog *ui;
};

#endif // RUNDIALOG_H
