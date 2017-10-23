#include "addtransactiondialog.h"
#include "ui_addtransactiondialog.h"
#include "transaction.h"
#include <QSqlQueryModel>
#include <QMessageBox>
AddTransactionDialog::AddTransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransactionDialog)
{
    ui->setupUi(this);

    // Fills the item Purchased box with only valid item names (from items table)
    QSqlQuery itemsQuery("select name FROM items");
    QSqlQueryModel* itemsModel = new QSqlQueryModel;
    itemsModel->setQuery(itemsQuery);
    ui->itemPurchasedInput->setModel(itemsModel);


    // Fills the customer ID input box with only valid customer IDs (from customers table)
    QSqlQuery customersQuery("select id FROM customers");
    QSqlQueryModel* customersModel = new QSqlQueryModel;
    customersModel->setQuery(customersQuery);
    ui->customerIDInput->setModel(customersModel);

    ui->quantityPurchasedInput->setMaximum(99999);
}

AddTransactionDialog::~AddTransactionDialog()
{
    delete ui;
}

void AddTransactionDialog::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

void AddTransactionDialog::setTransactionsTablePointer(QTableWidget* transactionsTable)
{
    this->transactionsTablePointer = transactionsTable;
}

void AddTransactionDialog::setMainWindowPointer(MainWindow* mainWindow)
{
    this->adminCPPointer = mainWindow;
}

void AddTransactionDialog::on_addButton_clicked()
{
    Transaction transactionToAdd;
    QString purchaseMonth = ui->monthInput->currentText();
    QString purchaseDay = ui->dayInput->currentText();
    QString purchaseYear = ui->yearInput->currentText();
    QString purchaseDate = purchaseMonth + '/' + purchaseDay + '/' + purchaseYear;


    transactionToAdd.setCustomerID(ui->customerIDInput->currentText().toInt());
    transactionToAdd.setItemName(ui->itemPurchasedInput->currentText());
    transactionToAdd.setPurchaseDate(purchaseDate);
    transactionToAdd.setQuantityPurchased(ui->quantityPurchasedInput->value());

    qDebug() << "QUANTITY: " << transactionToAdd.getQuantityPurchased();
    qDebug() << "CUSTOMER ID TO ADD: " << transactionToAdd.getCustomerID();
    qDebug() << "ITEM TO ADDD: " << transactionToAdd.getItemName();
    // Adds the transaction to the database
    try
    {
        dbPointer->addTransaction(transactionToAdd);
    }
    catch(int customerID)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", "Error adding customer ID:" + QString::number(customerID) + " to database.");
        errorMsgBox.setFixedSize(500,200);
    }

    // Adds the transaction to the data table
    int addRow = transactionsTablePointer->rowCount() + 1;
    this->transactionsTablePointer->setRowCount(addRow);

    //Sets customer ID in tablea
    QTableWidgetItem *cidCell = transactionsTablePointer->item(addRow - 1, 0);
    if(!cidCell)
    {
        cidCell = new QTableWidgetItem;
    }
    cidCell->setData(0, QVariant(transactionToAdd.getCustomerID()));
    transactionsTablePointer->setItem(addRow - 1, 0, cidCell);

    //Sets the item purchased field in table
    QTableWidgetItem *itemPurchasedCell = transactionsTablePointer->item(addRow - 1, 1);
    if(!itemPurchasedCell)
    {
        itemPurchasedCell = new QTableWidgetItem;
    }
    itemPurchasedCell->setData(0, QVariant(transactionToAdd.getItemName()));
    transactionsTablePointer->setItem(addRow - 1, 1, itemPurchasedCell);

    //Sets the quantity purchased field in table
    QTableWidgetItem *quantityPurchasedCell = transactionsTablePointer->item(addRow - 1, 2);
    if(!quantityPurchasedCell)
    {
        quantityPurchasedCell = new QTableWidgetItem;
    }
    quantityPurchasedCell->setData(0, QVariant(ui->quantityPurchasedInput->value()));
    transactionsTablePointer->setItem(addRow - 1, 2, quantityPurchasedCell);

    //Sets purchase date field in table
    QTableWidgetItem *purchaseDateCell = transactionsTablePointer->item(addRow - 1, 3);
    if(!purchaseDateCell)
    {
        purchaseDateCell = new QTableWidgetItem;
    }
    purchaseDateCell->setData(0, QVariant(purchaseDate));
    transactionsTablePointer->setItem(addRow - 1, 3, purchaseDateCell);

    //Sets customer name
    QTableWidgetItem *customerNameCell = transactionsTablePointer->item(addRow - 1, 4);
    if(!customerNameCell)
    {
        customerNameCell = new QTableWidgetItem;
    }
    customerNameCell->setData(0, QVariant(dbPointer->getCustomerNameFromID(ui->customerIDInput->currentText().toInt())));
    transactionsTablePointer->setItem(addRow - 1, 4, customerNameCell);

    //Sets sales price
    QTableWidgetItem *salesPriceCell = transactionsTablePointer->item(addRow - 1, 5);
    if(!salesPriceCell)
    {
        salesPriceCell = new QTableWidgetItem;
    }
    salesPriceCell->setData(0, QVariant(dbPointer->getSalesPriceForTransaction(transactionToAdd)));
    transactionsTablePointer->setItem(addRow - 1, 5, salesPriceCell);
    //closes pop up window


    // This function needs to be called so the program can get the customer name and
    this->close();
}
