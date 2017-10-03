#include "admincp.h"
#include "ui_mainwindow.h"
#include "edittransactiondialog.h"
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->customersTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->transactionsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Sets the date format
    ui->salesDateInputField->setDisplayFormat("MM/dd/yyyy");
    ui->salesDateInputField->setCalendarPopup(true);

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
    setUpRevenueTable();  // Creates revenue table

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
    ui->transactionsTable->setColumnCount(6);

    // Table behavior
    ui->transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->transactionsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->transactionsTable->setEditTriggers((QAbstractItemView::NoEditTriggers));

    // Sets the header labels for each column
    ui->transactionsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("CID"));
    ui->transactionsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Purchased"));
    ui->transactionsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Qty"));
    ui->transactionsTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Date"));
    ui->transactionsTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Name"));
    ui->transactionsTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Sale Price"));


    // Makes the customer ID column smaller than the rest.
    ui->transactionsTable->setColumnWidth(0, 70);
    ui->transactionsTable->setColumnWidth(1, 250);
    ui->transactionsTable->setColumnWidth(2, 50);
    ui->transactionsTable->setColumnWidth(3, 80);
    ui->transactionsTable->setColumnWidth(4, 150);
    ui->transactionsTable->setColumnWidth(5, 100);

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

            case 5:
                cell->setData(0, QVariant(dbPointer->getSalesPriceForTransaction(*transIt)));
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
    itemsList = dbPointer->getAllItems();

    //Allows for single row to get selected
    ui->itemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->itemsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //Sets headers to item name and price
    ui->itemsTable->setColumnCount(2);
    ui->itemsTable->setRowCount(itemsList.size());
    ui->itemsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Item Name"));
    ui->itemsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Price"));
    ui->itemsTable->setColumnWidth(0, ui->itemsTable->width() / 2);
    ui->itemsTable->setColumnWidth(1, ui->itemsTable->width() / 2);
}

//Displays any items from list created in renderItems
void MainWindow::displayItems()
{
    //iterates through rows and columns
    for(int row = 0; row < static_cast<int>(itemsList.size()); row++)
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
                cell->setData(0, QVariant(itemsList[row].getItemName()));
                break;
            case 1:
                cell->setData(0, QVariant(itemsList[row].getItemPrice()));
                break;
            }
        }
    }
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
    QString itemName = itemsList[selectedRow].getItemName();
    dbPointer->deleteItem(itemName);

    //Moves all items in the list back one index in the array then erases the last element in the array
    for(int i = selectedRow; i < static_cast<int>(itemsList.size()) - 1; i++)
    {
        itemsList[i].setItemName(itemsList[i + 1].getItemName());
        itemsList[i].setItemPrice(itemsList[i + 1].getItemPrice());
    }
    itemsList.erase(itemsList.begin() + itemsList.size() - 1);
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
        itemsList.push_back(tempItem);

        //Creates new row and adds new item to row
        ui->itemsTable->setRowCount(itemsList.size());

        // Gets the item name and price cell for the new item to be added
        QTableWidgetItem *cellName = ui->itemsTable->item(itemsList.size() - 1, 0);
        QTableWidgetItem *cellPrice = ui->itemsTable->item(itemsList.size() - 1, 1);

        //Adds item to UI page with items table
        if (!cellPrice && !cellName) {
            cellPrice = new QTableWidgetItem;
            cellName = new QTableWidgetItem;
        }
        cellName->setData(0, QVariant(itemsList[itemsList.size() - 1].getItemName() ));
        cellPrice->setData(0, QVariant(itemsList[itemsList.size() - 1].getItemPrice() ));
        ui->itemsTable->setItem(itemsList.size() - 1, 0, cellName);
        ui->itemsTable->setItem(itemsList.size() - 1, 1, cellPrice);

        //clears fields to enter new items
        ui->itemNameField->clear();
        ui->itemPriceField->clear();

        //Adds item to database list
        dbPointer->addItem(tempItem.getItemName(), tempItem.getItemPrice());
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
* Revenue Functions
* ---------------------------------------------------------------------------------------
*   (1) void setUpRevenueTable()
*       x adds columns and a row to the table showing quantity sold and revenue
*
* ---------------------------------------------------------------------------------------
*   (2) void MainWindow::calculateRevenue(Item & item)
*       x takes in an item and searches through the transactions list for items with the same name
*       x sums up the total quantity sold from this list
*       x uses the quantity sold and item price to calculate total revenue
*       x writes those values as members of class object
*
* ---------------------------------------------------------------------------------------
*   (3) void on_searchButton_clicked()
*       x Reads in item name the user is searching for
*       x Determines if item exists in vector
*       x Calls calculateRevenue function if so
*       x Outputs values to screen
*       x will output new values each time button is pressed
*
*****************************************************************************************/
//adds columns and a row to the table showing quantity sold and revenue
void MainWindow::setUpRevenueTable()
{
    ui->revenueTable->setColumnCount(2);
    ui->revenueTable->setRowCount(1);
    ui->revenueTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Quantity Sold"));
    ui->revenueTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Total Revenue"));
    ui->revenueTable->setColumnWidth(0, ui->revenueTable->width()/2.15);
    ui->revenueTable->setColumnWidth(1, ui->revenueTable->width()/2.1);
}


//Calculates total quantity and revenue sold of item class by going through
//transactions class
void MainWindow::calculateRevenue(Item & item)
{
    int quantitySum = 0;
    int revenue;
    std::vector<Transaction> transactionsList = dbPointer->getAllTransactions();

    //Goes through vector to find which items match the name of this item
    for(int i = 0; i < static_cast<int>(transactionsList.size()); i++)
    {
        //Sums up the total quantity of these sold
        if(item.getItemName() == transactionsList[i].getItemName())
        {
            quantitySum += transactionsList[i].getQuantityPurchased();
        }
    }

    //Calculates total revenue based on quantity sold and price of item
    revenue = quantitySum * item.getItemPrice();

    //Changes these numbers in the vector
    item.setQuantitySold(quantitySum);
    item.setTotalRevenue(revenue);

    //Changes values in DBManager class to change database
    dbPointer->updateItemInDB(item);
}

void MainWindow::on_searchButton_clicked()
{
    //Reads in name of item from text box
    QString itemName = ui->searchItemBox->text();
    int index = -1;

    //Prepares program to add info to table, which is done in conditional
    //Gets the item name and price cell for the new item to be added
    QTableWidgetItem *cellQuantity = ui->revenueTable->item(0, 0);
    QTableWidgetItem *cellRevenue = ui->revenueTable->item(0, 1);

    //Checks if cell items created, creates if not
    if (!cellQuantity && !cellRevenue) {
        cellQuantity = new QTableWidgetItem;
        cellRevenue = new QTableWidgetItem;
    }

    //Goes through vector to see if items match the name of this item
    for(int i = 0; i < static_cast<int>(itemsList.size()); i++)
    {
        //Finds index where one transaction of that item occurred
        if(itemName == itemsList[i].getItemName())
        {
            index = i;
        }
    }
    //calculates quantity sold and revenue if so, if not outputs an error message
    if(index != -1)
    {
        calculateRevenue(itemsList[index]);
        cellQuantity->setData(0, QVariant(itemsList[index].getQuantitySold()));
        cellRevenue->setData(0, QVariant(itemsList[index].getTotalRevenue()));
        ui->revenueTable->setItem(0, 0, cellQuantity);
        ui->revenueTable->setItem(0, 1, cellRevenue);
    }
    else
    {
        //populates the text box with an error message
        cellQuantity->setData(0, QVariant("Item not found"));
    }

    //clears fields to enter new items
    ui->searchItemBox->clear();
}

// ============================ END OF REVENUE FUNCTIONS ===============================/


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
    // Gets the sales date from the date input widget

    // 1 = January
    // 2 = February
    // 3 = etc...
    QDate salesDate = ui->salesDateInputField->date();

    // return a vector of all transactions on specified sales date
    std::vector<Transaction> transactionsList = dbPointer->getTransactionsBySalesDate(salesDate);

    // Check to make sure there are transactions for given sales date
    if (transactionsList[0].getCustomerID() == 0)
    {
        QMessageBox errorMsg;
        errorMsg.critical(0,"Error","No transactions found for specified date");
        errorMsg.setFixedSize(500,200);
    }
    else
    {
        // Clears the transactions table before updating it
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
