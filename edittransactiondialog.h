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
    explicit EditTransactionDialog(QWidget *parent, int ID, QString itemName, int qtyPurchased, QString date);
    ~EditTransactionDialog();

    void setTransactionsTablePointer(QTableWidget* transactionsTable);
    void setDBPointer(DBManager* dbPointer);
private slots:
    void on_cancelEditTransactionButton_clicked();

    void on_saveTransactionButton_clicked();

private:
    Ui::EditTransactionDialog *ui;
    QTableWidget* transactionsTablePointer;
    DBManager* dbPointer;
};

#endif // EDITTRANSACTIONDIALOG_H
