#ifndef ADDTRANSACTIONDIALOG_H
#define ADDTRANSACTIONDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "dbmanager.h"
#include "admincp.h"

namespace Ui {
class AddTransactionDialog;
}

class AddTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTransactionDialog(QWidget *parent = 0);

    void setDBPointer(DBManager* dbPointer);

    void setTransactionsTablePointer(QTableWidget* transactionsTable);

    void setMainWindowPointer(MainWindow* mainWindow);
    ~AddTransactionDialog();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddTransactionDialog *ui;
    DBManager* dbPointer;
    QTableWidget* transactionsTablePointer;
    MainWindow* adminCPPointer;
};

#endif // ADDTRANSACTIONDIALOG_H
