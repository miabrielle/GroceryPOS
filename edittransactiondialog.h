#ifndef EDITTRANSACTIONDIALOG_H
#define EDITTRANSACTIONDIALOG_H
#include <QModelIndexList>
#include <QDialog>
#include <QTableWidget>
#include "dbmanager.h"
namespace Ui {
class EditTransactionDialog;
}

class EditTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTransactionDialog(QWidget *parent, Transaction transactionSelected, int rowSelected);
    void setTransactionSelectedPointer(Transaction* transactionSelected);

    ~EditTransactionDialog();

    void setTransactionsTablePointer(QTableWidget* transactionsTable);
    void setDBPointer(DBManager* dbPointer);

private slots:
    void on_cancelEditTransactionButton_clicked();

    void on_saveTransactionButton_clicked();

private:
    Ui::EditTransactionDialog *ui;
    int rowSelected;
    Transaction* transactionSelectedPointer;
    QTableWidget* transactionsTablePointer;
    DBManager* dbPointer;
};

#endif // EDITTRANSACTIONDIALOG_H
