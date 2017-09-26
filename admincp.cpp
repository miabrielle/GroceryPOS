#include "admincp.h"
#include "ui_mainwindow.h"
#include "edittransactiondialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sets the Admin CP to be non resizable
    this->setFixedSize(this->geometry().width(),this->geometry().height());

    // Sets the tab widget to the first page (transactions)
    ui->tabWidget->setCurrentIndex(0);

    ui->memberIDField->setMaximum(99999); // Sets the maximum number for the search by Customer ID field

    // Renders tables
    renderTransactions(); // Renders all transactions to table
    renderCustomers();    // Renders all customers to table
    renderItems();        // Creates items table
    displayItems();       // Populates items table

}

/*****************************************************************************************
* Transaction Functions
* ----------------------
*   (1) void renderTransactions();
*       x gets a vector list of all transactions in database.
*       x Sets up columns and header, edit and selection behaviors of the table
*       x Calls addTransactionsVectorToTable and passes it the vector from above.
*
* ---------------------------------------------------------------------------------------
*   (2) void addTransactionsVectorToTable(vector<Transaction> transactionsList)
*       x Takes a vector of transactions, iterates through vector and adds to table.
*
* ---------------------------------------------------------------------------------------
*
*****************************************************************************************/
void MainWindow::renderTransactions()
{
    qDebug() << "Rendering transactions..";

    // This line queries the database and returns all Transactions as a vector
    // It is then assigned to our function variable "transactionsList"
    std::vector<Transaction> transactionsList = dbPointer->getAllTransactions();

    // Number of columns. Usually specific, easily change-able
    ui->transactionsTable->setColumnCount(5);

    // Table behavior
    ui->transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->transactionsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->transactionsTable->setEditTriggers((QAbstractItemView::NoEditTriggers));

    // Sets the header labels for each column
    ui->transactionsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->transactionsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Purchased"));
    ui->transactionsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Qty"));
    ui->transactionsTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Date"));
    ui->transactionsTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Name"));


    // Makes the customer ID column smaller than the rest.
    ui->transactionsTable->setColumnWidth(0, ui->transactionsTable->width()/5.6);
    ui->transactionsTable->setColumnWidth(1, ui->transactionsTable->width()/5);
    ui->transactionsTable->setColumnWidth(2, ui->transactionsTable->width()/5);
    ui->transactionsTable->setColumnWidth(3, ui->transactionsTable->width()/5);
    ui->transactionsTable->setColumnWidth(4, ui->transactionsTable->width()/5);


    // Updates the transactions table with the vector of customers from above
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
// ============================ END OF TRANSACTION FUNCTIONS ===============================/

/*****************************************************************************************
* Item Functions
* ---------------------------------------------------------------------------------------
*   (1) void renderItems();
*       x uses getAllItems function to populate a vector array that is a private data member
*         with information from the database
*       x Allows for single row to be selected
*       x Sets headers
*
* ---------------------------------------------------------------------------------------
*   (2) void displayItems()
*       x fills in information for item table
*
* ---------------------------------------------------------------------------------------
*   (3) void addItem(QString itemName, float itemPrice)
*       x adds row to table in database
*
* ---------------------------------------------------------------------------------------
*   (4) void deleteItem(QString itemName)
*       x deletes row from database
*
* ---------------------------------------------------------------------------------------
*   (5) void on_deleteItemButton_clicked()
*       x when delete button clicked on program
*       x erases row from GUI
*       x erases item in list and moves all items back (gets rid of empty space)
*       x calls deleteItem function
*
* ---------------------------------------------------------------------------------------
*   (6) void on_addItemButton_clicked()
*       x reads info from text box
*       x adds info to new row in GUI
*       x adds info to list
*       x calls addItem function
*
*****************************************************************************************/
//Sets up items table with proper headers and populates a list with items from database
void MainWindow::renderItems()
{
    //create a list for items with 2 columns
    itemList = dbPointer->getAllItems();

    //Allows for single row to get selected
    ui->itemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->itemsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //Sets headers to item name and price
    ui->itemsTable->setColumnCount(2);
    ui->itemsTable->setRowCount(itemList.size());
    ui->itemsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Item Name"));
    ui->itemsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Price"));
    ui->itemsTable->setColumnWidth(0, 175);
    ui->itemsTable->setColumnWidth(1, 175);
}

//Displays any items from list created in renderItems
void MainWindow::displayItems()
{
    //iterates through rows and columns
    for(int row = 0; row < static_cast<int>(itemList.size()); row++)
    {
        for (int column = 0; column < ui->itemsTable->columnCount(); column++)
        {
            //creates a cell if one is not available
            QTableWidgetItem *cell = ui->itemsTable->item(row,column);
            if (!cell)
            {
                cell = new QTableWidgetItem;
                ui->itemsTable->setItem(row,column,cell);
            }
            //switches on column to fill in name and price seperately
            switch (column)
            {

            case 0:
                cell->setData(0, QVariant(itemList[row].getItemName()));
                break;
            case 1:
                cell->setData(0, QVariant(itemList[row].getItemPrice()));
                break;
            }
        }
    }
}

//Adds an item to the table in the database
void MainWindow::addItem(QString itemName, float itemPrice)
{

    QSqlQuery query;
    query.prepare("INSERT INTO items (name, price) VALUES (:itemName, :itemPrice)");
    query.bindValue(":itemName", itemName);
    query.bindValue(":itemPrice", itemPrice);
    query.exec();
}

//Deletes item from table in database
void MainWindow::deleteItem(QString itemName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM items WHERE name = :itemName");
    query.bindValue(":itemName", itemName);
    query.exec();
}

//When you press the delete item button, this function deletes the item from the UI
//Then finds the correct row in the vector array and erases the entire row from the array
void MainWindow::on_deleteItemButton_clicked()
{
    //Returns the selected row number and erases row in UI
    int selectedRow;
    QItemSelectionModel* selectionModel = ui->itemsTable->selectionModel();
    selectedRow = ui->itemsTable->selectionModel()->currentIndex().row();
    QModelIndexList selected = selectionModel->selectedRows();
    for(int i= 0; i< selected.count();i++)
    {
        QModelIndex index = selected.at(i);
        selectedRow = index.row();
    }
    ui->itemsTable->removeRow(selectedRow);

    //Erases element in the database
    QString itemName = itemList[selectedRow].getItemName();
    deleteItem(itemName);

    //Moves all items in the list back one index in the array then erases the last element in the array
    for(int i = selectedRow; i < static_cast<int>(itemList.size()) - 1; i++)
    {
        itemList[i].setItemName(itemList[i + 1].getItemName());
        itemList[i].setItemPrice(itemList[i + 1].getItemPrice());
    }
    itemList.erase(itemList.begin() + itemList.size() - 1);
}

//adds item to inventory on screen
void MainWindow::on_addItemButton_clicked()
{
    //Gets all items then loads in new item from text boxes in ui and pushes new item onto list
    Item tempItem;
    tempItem.setItemName(ui->itemNameField->text());
    tempItem.setItemPrice(ui->itemPriceField->text().toFloat());
    if(tempItem.getItemName() != "")
    {
        itemList.push_back(tempItem);

        //Creates new row and adds new item to row
        ui->itemsTable->setRowCount(itemList.size());

        // Gets the item name and price cell for the new item to be added
        QTableWidgetItem *cellName = ui->itemsTable->item(itemList.size() - 1, 0);
        QTableWidgetItem *cellPrice = ui->itemsTable->item(itemList.size() - 1, 1);

        //Adds item to UI page with items table
        if (!cellPrice && !cellName) {
            cellPrice = new QTableWidgetItem;
            cellName = new QTableWidgetItem;
        }
        cellName->setData(0, QVariant(itemList[itemList.size() - 1].getItemName() ));
        cellPrice->setData(0, QVariant(itemList[itemList.size() - 1].getItemPrice() ));
        ui->itemsTable->setItem(itemList.size() - 1, 0, cellName);
        ui->itemsTable->setItem(itemList.size() - 1, 1, cellPrice);

        //clears fields to enter new items
        ui->itemNameField->clear();
        ui->itemPriceField->clear();

        //Adds item to database list
        addItem(tempItem.getItemName(), tempItem.getItemPrice());
    }
    else
    {
        qDebug() << "No item entered";
    }
}


/*****************************************************************************************
* Customer Functions
* ---------------------------------------------------------------------------------------
*   (1) void renderCustomers();
*       x creates a vector list of all customers from database.
*       x Sets up columns and header, edit and selection behaviors of the table
*       x Calls addCustomersVectorToTable and passes it the vector from above.
*
* ---------------------------------------------------------------------------------------
*   (2) void addCustomersVectorToTable(vector<Customer> customersList)
*       x Takes a vector of customers, iterates through vector and adds to table.
*
* ---------------------------------------------------------------------------------------
*
*****************************************************************************************/
void MainWindow::renderCustomers()
{
    // Gets a vector of all customers in SQL database
    std::vector<Customer> customersList = dbPointer->getAllCustomers();

    // Set the behavior of the customers table
    ui->customersTable->setEditTriggers((QAbstractItemView::NoEditTriggers));
    ui->customersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->customersTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->customersTable->setColumnCount(4);

    ui->customersTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Customer ID"));
    ui->customersTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->customersTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Member Type"));
    ui->customersTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Exp. Date"));

    ui->customersTable->setColumnWidth(0, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(1, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(2, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(3, ui->customersTable->width()/4);

    // Updates the table with new list of customers obtained from database
    addCustomersVectorToTable(customersList);
}
void MainWindow::addCustomersVectorToTable(std::vector<Customer> customersList)
{
    int row = 0;

    // Sets the number of rows in the table to the exact amount of transaction records found in the vector
    ui->customersTable->setRowCount(customersList.size());

    // Loops through all transactions
    // Populates QTableWidget with appropriate data
    std::vector<Customer>::iterator custIt = customersList.begin();

    while (custIt != customersList.end())
    {
        for (int column = 0; column < ui->customersTable->columnCount(); column++)
        {
            QTableWidgetItem *cell = ui->customersTable->item(row,column);
            if (!cell)
            {
                cell = new QTableWidgetItem;
                ui->customersTable->setItem(row,column,cell);
            }
            switch (column)
            {
            // Customer ID column
            case 0:
                cell->setData(0, QVariant(custIt->getCustomerID()));
                break;

                // Customer Name column
            case 1:
                cell->setData(0, QVariant(customersList.at(row).getCustomerName()));
                break;

                // Member Type Column
            case 2:
                cell->setData(0, QVariant(customersList.at(row).getMemberType()));
                break;
                // Member expiration date Column
            case 3:
                cell->setData(0, QVariant(customersList.at(row).getExpDate()));
                break;

            }
        }
        row++;      // Updates to the next row in the table
        custIt++;   // Updates the transactionsList iterator to read from the next transaction on next iteration
    }
}

// ============================ END OF CUSTOMER FUNCTIONS ===============================/

/*****************************************************************************************
* void setDBPointer(DBManager* dbPointer)
*   Used once in the beginning of the program to pass the database manager instance from
*   main into adminCP, editTransactionDialog, and anywhere else database access is needed.
*
*****************************************************************************************/
void MainWindow::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

/*****************************************************************************************
* UI Events
*****************************************************************************************/
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
    qDebug() << "Quantity purchased: " << transactionSelected.getQuantityPurchased() << endl << endl;
}

void MainWindow::on_editTransactionRowButton_clicked()
{
    int customerID = transactionSelected.getCustomerID();
    QString itemPurchased = transactionSelected.getItemName();
    QString purchaseDate = transactionSelected.getPurchaseDate();
    int quantityPurchased = transactionSelected.getQuantityPurchased();

    if (itemPurchased == "")
    {
        ui->invalidRowSelectedMsg->setText("Error: You must select a valid row.");
    }
    else
    {
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

void MainWindow::on_showSalesByMemberIDButton_clicked()
{
    int memberID = ui->memberIDField->value();

    std::vector<Transaction> membersList = dbPointer->getTransactionsByMemberID(memberID);
    qDebug() << membersList[0].getCustomerID();

    addTransactionsVectorToTable(membersList);
}

void MainWindow::on_displayExpiringMembershipsButton_clicked()
{
    // Gets the current index number from the selection box
    // 0 = January
    // 1 = February
    // etc...
    int monthIndex = ui->monthSelectBox->currentIndex();
    QString expirationMonth;
    std::vector<Customer> customersList;

    // This switch statement takes the index number of the option selected,
    // then converts it to its appropriate double-digit month.
    switch (monthIndex)
    {
    case 0: // January
        expirationMonth = "01";
        break;

    case 1: // February
        expirationMonth = "02";
        break;
    case 2: // March
        expirationMonth = "03";
        break;
    case 3: // April
        expirationMonth = "04";
        break;
    case 4: // May
        expirationMonth = "05";
        break;
    case 5: // June
        expirationMonth = "06";
        break;
    case 6: // July
        expirationMonth = "07";
        break;
    case 7: // August
        expirationMonth = "08";
        break;
    case 8: // September
        expirationMonth = "09";
        break;
    case 9: // October
        expirationMonth = "10";
        break;
    case 10: // November
        expirationMonth = "11";
        break;
    case 11: // December
        expirationMonth = "12";
        break;
    }

    // Queries and returns vector of customers with matching expiraiton dates
    customersList = dbPointer->getExpiringMembershipsForMonth(expirationMonth);

    addCustomersVectorToTable(customersList); // updates the table with the new results
}

void MainWindow::on_loadAllCustomersButton_clicked()
{
    renderCustomers();
}

void MainWindow::on_loadAllTransactionsButton_clicked()
{
    renderTransactions();
}

MainWindow::~MainWindow()
{
    delete ui;
}
