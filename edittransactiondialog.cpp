#include "edittransactiondialog.h"
#include "ui_edittransactiondialog.h"
#include "transaction.h"
#include <QDebug>
EditTransactionDialog::EditTransactionDialog(QWidget *parent, Transaction transactionSelected, int rowSelected) :
    QDialog(parent),
    ui(new Ui::EditTransactionDialog)
{
        if (transactionSelected.getItemName().isEmpty())
        {
            throw QString ("Please select a row from the transactions table.");
        }
        ui->setupUi(this);

        this->rowSelected = rowSelected;

        // Sets spin box maximums
        ui->customerIDField->setMaximum(99999);
        ui->quantityPurchasedField->setMaximum(9999);
        ui->customerIDField->setValue(transactionSelected.getCustomerID());
        ui->itemPurchasedField->setText(transactionSelected.getItemName());
        ui->quantityPurchasedField->setValue(transactionSelected.getQuantityPurchased());
        ui->datePurchasedField->setText(transactionSelected.getPurchaseDate());
}

void EditTransactionDialog::setTransactionSelectedPointer(Transaction* transactionSelected)
{
    this->transactionSelectedPointer = transactionSelected;
}


void EditTransactionDialog::setTransactionsTablePointer(QTableWidget* transactionsTable)
{
    // Gives the edit window access to the Transactions table QTableWidget
    this->transactionsTablePointer = transactionsTable;
}

void EditTransactionDialog::on_saveTransactionButton_clicked()
{
    int customerID = ui->customerIDField->value();
    QString itemPurchased = ui->itemPurchasedField->text();
    int quantityPurchased = ui->quantityPurchasedField->value();
    QString purchaseDate = ui->datePurchasedField->text();

    Transaction newTransaction(customerID, itemPurchased, quantityPurchased, purchaseDate);

    // Gets the customerID cell from selected row
    qDebug() << rowSelected;
    QTableWidgetItem* CIDCell = transactionsTablePointer->item(rowSelected, 0);
    CIDCell->setData(0, QVariant(customerID));

    // Item purchased
    QTableWidgetItem* itemNameCell = transactionsTablePointer->item(rowSelected, 1);
    itemNameCell->setData(0, QVariant(itemPurchased));

    // quantity Purchased
    QTableWidgetItem* quantityCell = transactionsTablePointer->item(rowSelected, 2);
    quantityCell->setData(0, QVariant(quantityPurchased));

    // Date purchased
    QTableWidgetItem* dateCell = transactionsTablePointer->item(rowSelected, 3);
    dateCell->setData(0, QVariant(purchaseDate));
    qDebug() << "Edited purchase date: " << purchaseDate;

    dbPointer->updateTransactionInDB(newTransaction, rowSelected + 1);
    QTableWidgetItem* salesPriceCell = transactionsTablePointer->item(rowSelected, 5);

    // Recalculates the sales price of the item
    salesPriceCell->setData(0, QVariant(dbPointer->getSalesPriceForTransaction(newTransaction)));
    this->transactionSelectedPointer->setCustomerID(customerID);
    this->transactionSelectedPointer->setItemName(itemPurchased);
    this->transactionSelectedPointer->setPurchaseDate(purchaseDate);
    this->transactionSelectedPointer->setQuantityPurchased(quantityPurchased);
    this->close();
}

void EditTransactionDialog::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

void EditTransactionDialog::on_cancelEditTransactionButton_clicked()
{
    this->close();
}


EditTransactionDialog::~EditTransactionDialog()
{
    delete ui;
}
