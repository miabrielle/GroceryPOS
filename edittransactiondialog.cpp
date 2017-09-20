#include "edittransactiondialog.h"
#include "ui_edittransactiondialog.h"
#include <QDebug>
EditTransactionDialog::EditTransactionDialog(QWidget *parent, int ID, QString itemName, int qtyPurchased, QString date) :
    QDialog(parent),
    ui(new Ui::EditTransactionDialog)
{
    ui->setupUi(this);

    // Sets spin box maximums
    ui->customerIDField->setMaximum(99999);
    ui->quantityPurchasedField->setMaximum(9999);

    // Fills in the edit fields with existing data before modification by user
    ui->itemPurchasedField->setText(itemName);
    ui->quantityPurchasedField->setValue(qtyPurchased);
    ui->datePurchasedField->setText(date);
    ui->customerIDField->setValue(ID);
}


void EditTransactionDialog::setTransactionsTablePointer(QTableWidget* transactionsTable)
{
    this->transactionsTablePointer = transactionsTable;
}
void EditTransactionDialog::on_cancelEditTransactionButton_clicked()
{
    this->close();
}



void EditTransactionDialog::on_saveTransactionButton_clicked()
{
    int customerID = ui->customerIDField->value();
    QString itemPurchased = ui->itemPurchasedField->text();
    int quantityPurchased = ui->quantityPurchasedField->value();
    QString purchaseDate = ui->itemPurchasedField->text();


}

void EditTransactionDialog::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

EditTransactionDialog::~EditTransactionDialog()
{

    delete ui;
}
