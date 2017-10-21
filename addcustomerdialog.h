#ifndef ADDCUSTOMERDIALOG_H
#define ADDCUSTOMERDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "dbmanager.h"

namespace Ui {
class AddCustomerDialog;
}

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    //constructor
    explicit AddCustomerDialog(QWidget *parent = 0);
    //destructor
    ~AddCustomerDialog();
    //sets the pointer to access database functions
    void setDBPointer(DBManager *dbPointer);
    //sets the pointer to change the table for customers on the main window
    void setCustomersTablePointer(QTableWidget * customersTable);

private slots:
    //two buttons on this UI window for add button and cancel button
    void on_addButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::AddCustomerDialog *ui;
    DBManager * dbPointer;
    QTableWidget * customersTablePointer;

};

#endif // ADDCUSTOMERDIALOG_H
