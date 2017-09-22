#include "admincp.h"
#include "ui_mainwindow.h"
#include "edittransactiondialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Number of columns. Usually specific, easily change-able
    ui->transactionsTable->setColumnCount(5);
    ui->memberIDField->setMaximum(99999);

    ui->transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->transactionsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabWidget->setCurrentIndex(0); // sets the tab widget to the first tab (transactions)
    renderTransactions();

    // Makes tabe cells un-editable
    ui->transactionsTable->setEditTriggers((QAbstractItemView::NoEditTriggers));
}

void MainWindow::renderTransactions()
{
    qDebug() << "Rendering transactions..";
    // This line queries the database and returns all Transactions as a vector
    // It is then assigned to our function variable "transactionsList"
    std::vector<Transaction> transactionsList = dbPointer->getAllTransactions();

    // Sets the header labels for each column
    ui->transactionsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->transactionsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Purchased"));
    ui->transactionsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Qty"));
    ui->transactionsTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Date"));
    ui->transactionsTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Name"));
    ui->transactionsTable->setColumnWidth(0, 55);
    ui->transactionsTable->setColumnWidth(1, 175);
    ui->transactionsTable->setColumnWidth(2, 40);
    ui->transactionsTable->setColumnWidth(3, 75);
    ui->transactionsTable->setColumnWidth(4, 170);

    addTransactionsVectorToTable(transactionsList);

}

void MainWindow::addTransactionsVectorToTable(std::vector<Transaction> transactionsList)
{
    int row = 0;
    // Sets the number of rows in the table to the exact amount of transaction records found in the vector
    ui->transactionsTable->setRowCount(transactionsList.size());

    // Loops through all transactions
    // Populates QTableWidget with appropriate data
    std::vector<Transaction>::iterator transIt = transactionsList.begin();

    while (transIt != transactionsList.end())
    {
        for (int column = 0; column < ui->transactionsTable->columnCount(); column++)
        {
            QTableWidgetItem *cell = ui->transactionsTable->item(row,column);
            if (!cell)
            {
                cell = new QTableWidgetItem;
                ui->transactionsTable->setItem(row,column,cell);
            }
            switch (column)
            {
            // Customer ID column
            case 0:
                cell->setData(0, QVariant(transIt->getCustomerID()));
                break;

                // Item Name column
            case 1:
                cell->setData(0, QVariant(transactionsList.at(row).getItemName()));
                break;

                // Quantity purchased column
            case 2:
                cell->setData(0, QVariant(transactionsList.at(row).getQuantityPurchased()));
                break;

                // Purchase Date column
            case 3:
                cell->setData(0, QVariant(transIt->getPurchaseDate()));
                break;

                // **Customer name column
                // TO-DO: create DBManager method to find customer name when passed customerID as argument.
                // Current just has a place holder 'customer name'
            case 4:
                cell->setData(0, QVariant(dbPointer->getCustomerNameFromID(transIt->getCustomerID())));
                break;
            }
        }
        row++;      // Updates to the next row in the table
        transIt++;  // Updates the transactionsList iterator to read from the next transaction on next iteration
    }
}

void MainWindow::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

// Event is fired every single time a cell is clicked on.
void MainWindow::on_transactionsTable_cellClicked(int row)
{
    QString itemPurchased, datePurchased, customerName;
    int customerID, quantityPurchased;

    // 0 = CustomerID
    // 1 = Item Purchased
    // 2 = Quantity
    // 3 = Date Purchased
    // 4 = CustomerName
    for (int col = 0; col < 5; col++)
    {
        switch(col)
        {
        // Customer ID column
        case 0:
            customerID = ui->transactionsTable->item(row, col)->text().toInt();
            break;

            // Item Name column
        case 1:
            itemPurchased = ui->transactionsTable->item(row, col)->text();
            break;

            // Quantity purchased column
        case 2:
            quantityPurchased = ui->transactionsTable->item(row, col)->text().toInt();
            break;

            // Purchase Date column
        case 3:
            datePurchased = ui->transactionsTable->item(row, col)->text();
            break;

            // **Customer name column
            // TO-DO: create DBManager method to find customer name when passed customerID as argument.
            // Current just has a place holder 'customer name'
        case 4:
            customerName = ui->transactionsTable->item(row, col)->text();
            break;
        }
    }
    transactionSelected.setCustomerID(customerID);
    transactionSelected.setItemName(itemPurchased);
    transactionSelected.setPurchaseDate(datePurchased);
    transactionSelected.setQuantityPurchased(quantityPurchased);
    qDebug() << "CID: " << transactionSelected.getCustomerID();
    qDebug() << "Item name: " << transactionSelected.getItemName();
    qDebug() << "Purchase Date: " << transactionSelected.getPurchaseDate();
    qDebug() << "Quantity purchased: " << transactionSelected.getQuantityPurchased();
}



void MainWindow::on_editTransactionRowButton_clicked()
{
    int customerID = transactionSelected.getCustomerID();
    QString itemPurchased = transactionSelected.getItemName();
    QString purchaseDate = transactionSelected.getPurchaseDate();
    int quantityPurchased = transactionSelected.getQuantityPurchased();

    if (customerID == 0)
    {
        ui->invalidRowSelectedMsg->setText("Error: You must select a valid row.");
    }
    else
    { //
    EditTransactionDialog* editTransWindow = new EditTransactionDialog(this, customerID, itemPurchased, quantityPurchased, purchaseDate);

    editTransWindow->show();
    }

}

void MainWindow::on_showSalesButton_clicked()
{
    QString salesDate = ui->salesDayInput->text(); // get the user input sales date

    if (salesDate.isEmpty()) {
        QMessageBox errorMsg;
        errorMsg.setText("Invalid sales date (mm/dd/yyyy)");
        errorMsg.exec();
    }
    else
    {
        // return a vector of all transactions on specified sales date
        std::vector<Transaction> transactionsList = dbPointer->getTransactionsBySalesDate(salesDate);

        // Clear the table
        ui->transactionsTable->setRowCount(0);
        // populate table with new data
        addTransactionsVectorToTable(transactionsList);
    }
}

void MainWindow::on_loadAllTransactionsButton_clicked()
{
    renderTransactions();
}

void MainWindow::on_showSalesByMemberIDButton_clicked()
{
    int memberID = ui->memberIDField->value();

    std::vector<Transaction> membersList = dbPointer->getTransactionsByMemberID(memberID);
    qDebug() << membersList[0].getCustomerID();

    addTransactionsVectorToTable(membersList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

