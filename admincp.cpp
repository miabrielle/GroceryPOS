#include "admincp.h"
#include "ui_mainwindow.h"
#include "edittransactiondialog.h"
#include "addcustomerdialog.h"
#include "memberchangestatus.h"
#include <iomanip>
#include <vector>
#include <cassert>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->customersTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->transactionsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->itemsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Sets the date format
    ui->salesDateInputField->setDisplayFormat("MM/dd/yyyy");
    ui->salesDateInputField->setCalendarPopup(true);

    // Sets the Admin CP to be non resizable
    this->setFixedSize(this->geometry().width(),this->geometry().height());

    // Sets the tab widget to the first page (transactions)
    ui->tabWidget->setCurrentIndex(0);

    ui->customerIDField->setMaximum(99999); // Sets the maximum number for the search by Customer ID field

    // Renders tables
    renderTransactions(); // Renders all transactions to table
    renderCustomers();    // Renders all customers to table
    renderItems();        // Creates items table
    displayItems();       // Populates items table
}

void MainWindow::insufficientPriviledgesErrorMessage()
{
    QMessageBox errorMsgBox;
    errorMsgBox.critical(0,"Error", "You must have administrator priviledges to access this functionality.");
    errorMsgBox.setFixedSize(500,200);
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
* ---------------------------------------------------------------------------------------
*   (7) void MainWindow::calculateRevenue(Item & item)
*       x takes in an item and searches through the transactions list for items with the same name
*       x sums up the total quantity sold from this list
*       x uses the quantity sold and item price to calculate total revenue
*       x writes those values as members of class object
*
* ---------------------------------------------------------------------------------------
*   (8) void on_searchButton_clicked()
*       x Reads in item name the user is searching for
*       x Determines if item exists in vector
*       x Calls calculateRevenue function if so
*       x Outputs values to screen
*       x will output new values each time button is pressed
* ---------------------------------------------------------------------------------------
*   (9) void MainWindow::on_sortItemsByButton_clicked()
*       x the user can press this button to change the sorting of the list
*       x options include item name, item price, quantity sold, and total revenue
*       x all options can be sorted in ascending or descending order
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
    ui->itemsTable->setColumnCount(4);
    ui->itemsTable->setRowCount(itemsList.size());
    ui->itemsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Item Name"));
    ui->itemsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Price"));
    ui->itemsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("# Sold"));
    ui->itemsTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Revenue"));
    ui->itemsTable->setColumnWidth(0, ui->itemsTable->width() / 2.1);
    ui->itemsTable->setColumnWidth(1, ui->itemsTable->width() / 6.2);
    ui->itemsTable->setColumnWidth(2, ui->itemsTable->width() / 6.2);
    ui->itemsTable->setColumnWidth(3, ui->itemsTable->width() / 6);
}

//Displays any items from list created in renderItems
void MainWindow::displayItems()
{
    qDebug() << "DisplayItems entered";
    //calculates each items revenue and quantity sold
    for(int i = 0; i < static_cast<int>(itemsList.size()); i++)
    {
        calculateRevenue(itemsList[i]);
    }

    ui->itemsTable->setRowCount(itemsList.size());
    //iterates through rows and columns
    for(int row = 0; row < static_cast<int>(itemsList.size()); row++)
    {
        for (int column = 0; column < ui->itemsTable->columnCount(); column++)
        {
            QString priceString = "$" + QString::number(itemsList[row].getItemPrice());
            QString priceRevenue = "$" + QString::number(itemsList[row].getTotalRevenue());


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
                cell->setData(0, QVariant(priceString));
                break;
            case 2:
                cell->setData(0, QVariant(itemsList[row].getQuantitySold()));
                break;
            case 3:
                cell->setData(0, QVariant(priceRevenue));
                break;
            }
        }
    }
}

//When you press the delete item button, this function deletes the item from the UI
//Then finds the correct row in the vector array and erases the entire row from the array
void MainWindow::on_deleteItemButton_clicked()
{
    if (isAdmin)
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

        //Moves all items in the list back one index in the array then erases the last element in the array
        for(int i = selectedRow; i < static_cast<int>(itemsList.size()) - 1; i++)
        {
            itemsList[i].setItemName(itemsList[i + 1].getItemName());
            itemsList[i].setItemPrice(itemsList[i + 1].getItemPrice());
            itemsList[i].setQuantitySold(itemsList[i + 1].getQuantitySold());
            itemsList[i].setTotalRevenue(itemsList[i + 1].getTotalRevenue());
        }
        itemsList.erase(itemsList.begin() + itemsList.size() - 1);
        dbPointer->deleteItem(itemName);
    }
    else
    {
        insufficientPriviledgesErrorMessage();
    }
}

//adds item to inventory on screen
void MainWindow::on_addItemButton_clicked()
{
    if (isAdmin)
    {
        //Gets all items then loads in new item from text boxes in ui and pushes new item onto list
        Item tempItem;
        tempItem.setItemName(ui->itemNameField->text());
        tempItem.setItemPrice(ui->itemPriceField->text().toFloat());
        calculateRevenue(tempItem);

        //Checks that there is an item to enter
        if(tempItem.getItemName() != "" && tempItem.getItemPrice() != 0.0)
        {
            //adds item to vector
            itemsList.push_back(tempItem);

            //Creates new row and adds new item to row
            ui->itemsTable->setRowCount(itemsList.size());

            // Gets the item name and price cell for the new item to be added
            QTableWidgetItem *cellName = ui->itemsTable->item(itemsList.size() - 1, 0);
            QTableWidgetItem *cellPrice = ui->itemsTable->item(itemsList.size() - 1, 1);
            QTableWidgetItem *cellQuantity = ui->itemsTable->item(itemsList.size() - 1, 2);
            QTableWidgetItem *cellRevenue = ui->itemsTable->item(itemsList.size() - 1, 3);

            //Prepares information in string to display values in monetary form
            QString priceString = "$" + QString::number(itemsList[itemsList.size() - 1].getItemPrice());
            QString revenueString = "$" + QString::number(itemsList[itemsList.size() - 1].getTotalRevenue());

            //Adds item to UI page with items table
            if (!cellPrice && !cellName) {
                cellPrice = new QTableWidgetItem;
                cellName = new QTableWidgetItem;
                cellQuantity = new QTableWidgetItem;
                cellRevenue = new QTableWidgetItem;
            }

            //Used to put data into cells in UI
            cellName->setData(0, QVariant(itemsList[itemsList.size() - 1].getItemName() ));
            cellPrice->setData(0, QVariant(priceString));
            cellQuantity->setData(0, QVariant(itemsList[itemsList.size() - 1].getQuantitySold() ));
            cellRevenue->setData(0, QVariant(revenueString));
            ui->itemsTable->setItem(itemsList.size() - 1, 0, cellName);
            ui->itemsTable->setItem(itemsList.size() - 1, 1, cellPrice);
            ui->itemsTable->setItem(itemsList.size() - 1, 2, cellQuantity);
            ui->itemsTable->setItem(itemsList.size() - 1, 3, cellRevenue);

            //clears fields to enter new items
            ui->itemNameField->clear();
            ui->itemPriceField->clear();

            //Adds item to database list
            dbPointer->addItem(tempItem.getItemName(), tempItem.getItemPrice());
        }
        else
        {
            QMessageBox errorMsgBox;
            errorMsgBox.critical(0,"Error", "Item must have a price and name!");
            errorMsgBox.setFixedSize(500,200);
        }
    }
    else
    {
        insufficientPriviledgesErrorMessage();
    }
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
    try
    {
        //Reads in name of item from text box
        QString itemName = ui->searchItemBox->text();
        if (itemName.isEmpty())
        {
            throw QString("Item name cannot be empty!");
        }
        int index = -1;

        ui->itemsTable->clearContents();
        ui->itemsTable->setRowCount(1);

        //Prepares program to add info to table, which is done in conditional
        //Gets the item name and price cell for the new item to be added
        QTableWidgetItem *cellName = ui->itemsTable->item(0, 0);
        QTableWidgetItem *cellPrice = ui->itemsTable->item(0, 1);
        QTableWidgetItem *cellQuantity = ui->itemsTable->item(0, 2);
        QTableWidgetItem *cellRevenue = ui->itemsTable->item(0, 3);

        //Checks if cell items created, creates if not
        if (!cellName && !cellPrice && !cellQuantity && !cellRevenue) {
            cellName = new QTableWidgetItem;
            cellPrice = new QTableWidgetItem;
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
            cellName->setData(0, QVariant(itemsList[index].getItemName()));
            cellPrice->setData(0, QVariant(itemsList[index].getItemPrice()));
            cellQuantity->setData(0, QVariant(itemsList[index].getQuantitySold()));
            cellRevenue->setData(0, QVariant(itemsList[index].getTotalRevenue()));
            ui->itemsTable->setItem(0, 0, cellName);
            ui->itemsTable->setItem(0, 1, cellPrice);
            ui->itemsTable->setItem(0, 2, cellQuantity);
            ui->itemsTable->setItem(0, 3, cellRevenue);
        }
        else
        {
            renderItems();
            displayItems();
            throw QString("Item not found in table!");
        }


        //clears fields to enter new items
        ui->searchItemBox->clear();
    }
    catch (const QString& errorMessage)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", errorMessage);
        errorMsgBox.setFixedSize(500,200);
    }
}

//Sorts the items table based on customer's choice of sort
void MainWindow::on_sortItemsByButton_clicked()
{
    int sortItemIndex = ui->sortItemsByField->currentIndex();

    /*Key:
     * case 0: Name A-Z
     * case 1: Name Z-A
     * case 2: Price low-high
     * case 3: Price high-low
     * case 4: Quantity low-high
     * case 5: Quantity high-low
     * case 6: Revenue low-high
     * case 7: Revenue high-low
     */
    switch(sortItemIndex){
    case(0): ui->itemsTable->sortItems(0, Qt::AscendingOrder);
        break;
    case(1): ui->itemsTable->sortItems(0, Qt::DescendingOrder);
        break;
    case(2): ui->itemsTable->sortItems(1, Qt::AscendingOrder);
        break;
    case(3): ui->itemsTable->sortItems(1, Qt::DescendingOrder);
        break;
    case(4): ui->itemsTable->sortItems(2, Qt::AscendingOrder);
        break;
    case(5): ui->itemsTable->sortItems(2, Qt::DescendingOrder);
        break;
    case(6): ui->itemsTable->sortItems(3, Qt::AscendingOrder);
        break;
    case(7): ui->itemsTable->sortItems(3, Qt::DescendingOrder);
        break;
    }
}

// ============================ END OF ITEM FUNCTIONS ===============================//
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
    customersList = calcExecutiveRebates();

    // Set the behavior of the customers table
    ui->customersTable->setEditTriggers((QAbstractItemView::NoEditTriggers));
    ui->customersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->customersTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->customersTable->setColumnCount(5);

    ui->customersTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Customer ID"));
    ui->customersTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->customersTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Member Type"));
    ui->customersTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Exp. Date"));
    ui->customersTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Rebate Amount"));

    ui->customersTable->setColumnWidth(0, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(1, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(2, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(3, ui->customersTable->width()/4);
    ui->customersTable->setColumnWidth(4, ui->customersTable->width()/4);

    // Updates the table with new list of customers obtained from database
    addCustomersVectorToTable(customersList);
}

std::vector<Customer> MainWindow::calcExecutiveRebates()
{
    std::vector<Customer> allCustomers = dbPointer->getAllCustomers();
    std::vector<Transaction> executiveTransactions;
    QString memberType;
    double grandTotal;
    int memberID, transactionSize, count = 0;
    float amountSpent = 0, rebateAmount;
    Customer p;

    for(std::vector<Customer>::iterator it = allCustomers.begin(); it != allCustomers.end();
        ++it)
    {
        amountSpent  = 0;  //resets amount spent
        rebateAmount = 0;  //resets rebate amount
        memberType = allCustomers[count].getMemberType(); //gets member type of customer

        //Checks if member is executive; if it is, enters loop
        if(memberType == "Executive")
        {
            try
            {
                memberID = allCustomers[count].getCustomerID(); //gets exec members ID then transactions by ID num
                executiveTransactions = dbPointer->getTransactionsByMemberID(memberID, grandTotal);
                transactionSize = executiveTransactions.size();

                for(int i = 0; i < transactionSize; i++) //loops through transactions and sums amount spent
                {
                    amountSpent += dbPointer->getSalesPriceTotalFloat(executiveTransactions[i]);
                }
            }
            catch (const QString& errorMessage)
            {
                QMessageBox errorMsgBox;
                errorMsgBox.critical(0,"Error", errorMessage);
                errorMsgBox.setFixedSize(500,200);
            }
        }

        rebateAmount = amountSpent * .03; //calcs rebate amount

        //sets ALL custumers rebate amount; if the customer is not executive the rebate amount is set to zero
        allCustomers[count].setRebateAmt(rebateAmount);


        executiveTransactions.clear(); //clears transaction vector
        count++;                       //adds to count
    }

    return allCustomers;
}

void MainWindow::addCustomersVectorToTable(std::vector<Customer> customersList)
{
    int row = 0;
    QString rebateQString;

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
            case 4:
                rebateQString = "$" + QString::number(customersList.at(row).getRebateAmt(), 'f', 2);
                cell->setData(0, rebateQString);
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
    this->rowSelected = row;
    QString itemPurchased, datePurchased, customerName;
    int customerID, quantityPurchased;
    float salePrice;

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

        case 5:
            salePrice = ui->transactionsTable->item(row, col)->text().toFloat();

        }
    }
    transactionSelected.setCustomerID(customerID);
    transactionSelected.setItemName(itemPurchased);
    transactionSelected.setPurchaseDate(datePurchased);
    transactionSelected.setQuantityPurchased(quantityPurchased);

}

void MainWindow::on_editTransactionRowButton_clicked()
{
    try
    {
        QString itemPurchased = transactionSelected.getItemName();
        QString purchaseDate = transactionSelected.getPurchaseDate();


        EditTransactionDialog* editTransWindow = new EditTransactionDialog(this, transactionSelected, this->rowSelected);

        editTransWindow->show();
        editTransWindow->setTransactionsTablePointer(ui->transactionsTable);
        editTransWindow->setDBPointer(this->dbPointer);
        editTransWindow->setTransactionSelectedPointer(&transactionSelected);
    }
    catch (const QString& errorMessage)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", errorMessage);
        errorMsgBox.setFixedSize(500,200);
    }


}

void MainWindow::on_showSalesButton_clicked()
{
    try
    {
        // Gets the sales date from the date input widget
        // 1 = January
        // 2 = February
        // 3 = etc...
        QDate salesDate = ui->salesDateInputField->date();

        // return a vector of all transactions on specified sales date
        std::vector<Transaction> transactionsList = dbPointer->getTransactionsBySalesDate(salesDate);

        // Check to make sure there are transactions for given sales date
        // Clears the transactions table before updating it
        ui->transactionsTable->setRowCount(0);

        // populate table with new data
        addTransactionsVectorToTable(transactionsList);
    }
    catch (const QString& errorMessage)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", errorMessage);
        errorMsgBox.setFixedSize(500,200);
    }
}

void MainWindow::on_searchByCustomerIDButton_clicked()
{
    try
    {
        double grandTotal;
        int memberID = ui->customerIDField->value();

        std::vector<Transaction> membersList = dbPointer->getTransactionsByMemberID(memberID, grandTotal);

        if (grandTotal != 0)
        {
            // Update the table
            addTransactionsVectorToTable(membersList);

            // Notify the user of grand total of purchases
            QMessageBox grandTotalInfoBox;
            grandTotalInfoBox.information(0,"Grand Total", "Customer ID '" + QString::number(memberID) + "' has spent: $" + QString::number(grandTotal, 'f', 2) + " dollars.");
            grandTotalInfoBox.setFixedSize(600,100);
        }
        else
        {
            QMessageBox errorMsgBox;
            errorMsgBox.critical(0,"Error!", "No transactions found for specified customer ID");
            errorMsgBox.setFixedSize(500,200);
        }

    }
    catch (const QString& errorMessage)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", errorMessage);
        errorMsgBox.setFixedSize(500,200);
    }
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

    try
    {
        // Queries and returns vector of customers with matching expiraiton dates
        customersList = dbPointer->getExpiringMembershipsForMonth(expirationMonth);

        addCustomersVectorToTable(customersList); // updates the table with the new results
    }
    catch (const QString& errorMessage)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", errorMessage);
        errorMsgBox.setFixedSize(500,200);
    }
}

void MainWindow::on_loadAllCustomersButton_clicked()
{
    renderCustomers();
}

void MainWindow::on_loadAllTransactionsButton_clicked()
{
    renderTransactions();
}

void MainWindow::on_displayAllButton_clicked()
{
    displayItems();
}

void MainWindow::on_showChangeMemberStatus_clicked()
{
    if (isAdmin)
    {
        MemberChangeStatus *memStatWindow = new MemberChangeStatus;
        memStatWindow->setWindowTitle("Member Change Statuses");
        memStatWindow->setDBPointer(this->dbPointer);
        memStatWindow->show();
    }
    else
    {
        insufficientPriviledgesErrorMessage();
    }
}



void MainWindow::on_showSalesByCustomerName_clicked()
{
    try
    {
        // Exception handling displays an error if the customer name is empty or does not exist in database
        QString customerName = ui->searchByCustomerNameInput->text().toLower();
        int customerID;
        double grandTotal;

        customerID = dbPointer->getCustomerIDFromCustomerName(customerName);
        std::vector<Transaction> transactionsList = dbPointer->getTransactionsByMemberID(customerID, grandTotal);

        // Notify the user of grand total of purchases
        addTransactionsVectorToTable(transactionsList);
        QMessageBox grandTotalInfoBox;
        grandTotalInfoBox.information(0,"Grand Total", "Customer " + customerName +" has spent: $" + QString::number(grandTotal, 'f', 2) + " dollars.");
        grandTotalInfoBox.setFixedSize(600,100);
    }
    catch (const QString& errorMessage)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.critical(0,"Error", errorMessage);
        errorMsgBox.setFixedSize(500,200);
    }
}


// This function is passed a boolean, and sets the
// private datamember 'isAdmin' of MainWindow class to whatever boolean is passed.
// 'isAdmin' is data from the SQL database to determine whether a logged in user is
// a 'store manager' or 'administrator' role.
void MainWindow::setIsAdmin(bool isAdmin)
{
    this->isAdmin = isAdmin;
}

// Copy constructor handles the pointers
MainWindow::MainWindow(const MainWindow &mw)
{
    // Shallow copies the pointers
    delete ui;
    delete dbPointer;

    this->ui = mw.ui;
    this->transactionSelected = mw.transactionSelected;
    this->rowSelected = mw.rowSelected;
    this->itemsList = mw.itemsList;
    this->isAdmin = mw.isAdmin;
    this->dbPointer = mw.dbPointer;
}

//In main window when add customer button is clicked, a pop up window appears allowing the user
//to enter information for a new user to be entered into the system
void MainWindow::on_AddCustomerButton_clicked()
{
    if (isAdmin)
    {
        AddCustomerDialog* addCustomerWindow = new AddCustomerDialog(this);

        addCustomerWindow->show();
        addCustomerWindow->setCustomersTablePointer(ui->customersTable);
        addCustomerWindow->setDBPointer(this->dbPointer);
    }
    else
    {
        insufficientPriviledgesErrorMessage();
    }
}

//when the user presses a button in the main window denoting delete user
//a user is deleted from both the main window table and the database
void MainWindow::on_DeleteCustomerButton_clicked()
{
    if (isAdmin)
    {
        //Returns the selected row number and erases row in UI
        int selectedRow;
        QItemSelectionModel* selectionModel = ui->customersTable->selectionModel();
        selectedRow = ui->customersTable->selectionModel()->currentIndex().row();
        QModelIndexList selected = selectionModel->selectedRows();

        for(int i= 0; i< selected.count();i++)
        {
            QModelIndex index = selected.at(i);
            selectedRow = index.row();
        }

        //Erases element in the database
        QString customerName = ui->customersTable->item(selectedRow, 1)->text();
        ui->customersTable->removeRow(selectedRow);
        dbPointer->deleteCustomer(customerName);
    }
    else
    {
        insufficientPriviledgesErrorMessage();
    }
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;

}
