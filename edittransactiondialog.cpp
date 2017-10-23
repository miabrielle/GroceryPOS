#include "edittransactiondialog.h"
#include "ui_edittransactiondialog.h"
#include "transaction.h"
#include <QDebug>
EditTransactionDialog::EditTransactionDialog(QWidget *parent, Transaction transactionSelected, int rowSelected) :
    QDialog(parent),
    ui(new Ui::EditTransactionDialog)
{

    // Exception handling
    if (transactionSelected.getItemName().isEmpty())
    {
        throw QString ("Please select a valid row from the transactions table.");
    }
    ui->setupUi(this);

    // Fills the itemPurchasedInput box with valid selections from databasex
    dbPointer->createComboBoxModel("items", "name", ui->itemPurchasedInput);

    // Fills the customer ID input box with only valid customer IDs (from customers table)
    dbPointer->createComboBoxModel("customers", "id", ui->customerIDInput);

    this->rowSelected = rowSelected;

    // Fills in the current data for the transaction that is to be editted
    ui->quantityPurchasedField->setMaximum(9999);
    ui->customerIDInput->setCurrentText(QString::number(transactionSelected.getCustomerID()));
    ui->itemPurchasedInput->setCurrentText(transactionSelected.getItemName());
    ui->quantityPurchasedField->setValue(transactionSelected.getQuantityPurchased());
    ui->datePurchasedField->setText(transactionSelected.getPurchaseDate());
}

void EditTransactionDialog::setTransactionSelectedPointer(Transaction* transactionSelected)
{
    this->transactionSelectedPointer = transactionSelected;
}

void EditTransactionDialog::on_saveTransactionButton_clicked()
{
    int customerID = ui->customerIDInput->currentText().toInt();
    int quantityPurchased = ui->quantityPurchasedField->value();
    QString itemPurchased = ui->itemPurchasedInput->currentText();
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

// Gives access to the DBManager class
void EditTransactionDialog::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

// Gives access to the Transaction table (QTableWidget) inside the MainWindow UI.
void EditTransactionDialog::setTransactionsTablePointer(QTableWidget* transactionsTable)
{
    // Gives the edit window access to the Transactions table QTableWidget
    this->transactionsTablePointer = transactionsTable;
}

void EditTransactionDialog::on_cancelEditTransactionButton_clicked()
{
    this->close();
}

EditTransactionDialog::~EditTransactionDialog()
{
    delete ui;
}
