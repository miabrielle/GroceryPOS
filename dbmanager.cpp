#include "dbmanager.h"
#include "customer.h"
#include <QMessageBox>
#include <QDate>

/**************************************************************************************
 * DBManager Constructor
 *  - Sets up the database file to read from
 * DB initializer
 *  - Initatlizes database with correct table column headers
 **************************************************************************************/
DBManager::DBManager()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName("bulkclub.db");

        if(!db.open())
            qWarning() << "DBManager::DBManager - Error: " << db.lastError().text();
    }
    else
    {
        qWarning() << "DBManager::DBManager - Error: no driver " << DRIVER << " available";
    }
}

void DBManager::initDB()
{
    // Checks to see if the database file exists, if it hasnt been created yet:
    // executes SQL queries on the database 'bulkclub.db' initializing tables with their
    // respective data values
    QSqlQuery query;
    query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT, role INTEGER)");
    query.exec("CREATE TABLE customers (id INTEGER, name TEXT, type TEXT, expirationDate REAL)");
    query.exec("CREATE TABLE items (id INTEGER PRIMARY KEY, name TEXT, price REAL, quantity INTEGER PRIMARY KEY, revenue REAL)");
    query.exec("CREATE TABLE transactions (id INTEGER PRIMARY KEY, cid INTEGER, customerName TEXT, itemPurchased TEXT, quantityPurchased INTEGER, date REAL, salePrice REAL)");

    if(!query.isActive())
    {
        qWarning() << "DBManager::initDB - Error: " << query.lastError().text();
    }
}

/*******************************************************************************************
 * DBManager::authenticateUser
 *  - Passed username and password as strings
 *  - Checks database 'users' table for any matching entries
 *  - Returns true if a match is found, false if no match found
 *******************************************************************************************/
bool DBManager::authenticateUser(QString username, QString password, bool &isAdmin)
{
    bool isAuthed = false;
    if (!db.isOpen())
    {
        qDebug() << "Database connection error.";
        return false;
    }

    QSqlQuery query;

    // Executes a query that attempts to locate username and password that the user entered, if the query executes successfuly,
    // it will enter the if statement and check if there is a matching entry in the database (query.next()).
    if(query.exec("SELECT username, password, role FROM users WHERE username='" + username + "' AND PASSWORD='" + password + "'"))
    {
        if (query.next())
        {
            if (query.value(2) == 1)
            {
                isAdmin = true;
            }
            else
            {
                isAdmin = false;
            }
            // If a result is found in the database matching the username and password entered by user
            isAuthed = true;
        }
        else
        {
            isAuthed = false;
        }
    }
    return isAuthed;
}

/*******************************************************************************************
 * DATA COLLECTION CUSTOMER FUNCTIONS
 *
 * addCustomer
 *  - adds a record to the database with an object parameter
 *
 * deleteCustomer
 *  - uses a customer name passed to find the record in the database and delete the whole record
 * getCustomerNameFromID
 *  - returns the name of a customer if passed the name
 *
 * getCustomerIDFromName
 *  - returns the id of a customer if passed the ID
 *
 * getAllCustomers
 *  - returns a vector containing the information for all of the customers in the database
 *  - called at the beginning of the program
 *  - id, name, type, expirationdate
 *
 * getExpiringMembershipsByMonth
 *  - checks all of the members in the system and checks the month in which their membership
 * will expire
 *******************************************************************************************/

//Adds a customer to the customer table in the database
void DBManager::addCustomer(Customer temp)
{
    //Preps all object values into individual variables
    int id = temp.getCustomerID();
    QString customerName = temp.getCustomerName();
    QString memberType = temp.getMemberType();
    QString expirationDate = temp.getExpDate();

    //Prepares all of the values and updates the database
    QSqlQuery query;
    query.prepare("INSERT INTO customers (id, name, type, expirationdate) VALUES (:id, :customerName, :memberType, :expirationDate)");
    query.bindValue(":id", id);
    query.bindValue(":customerName", customerName);
    query.bindValue(":memberType", memberType);
    query.bindValue(":expirationDate", expirationDate);
    query.exec();
}

//Deletes customer from customer table in database
void DBManager::deleteCustomer(QString customerName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM customers WHERE name = :customerName");
    query.bindValue(":customerName", customerName);
    query.exec();
}

QString DBManager::getCustomerNameFromID(int customerID)
{
    QString customerName;
    QSqlQuery customersQuery;
    customersQuery.prepare("SELECT name FROM customers WHERE id = :customerID");

    customersQuery.bindValue(":customerID", customerID);
    // If the query has a result
    if (customersQuery.exec() && customersQuery.first())
    {
        customerName = customersQuery.value(0).toString();
    }
    else
    {
        customerName = "transaction Customer ID matches no customers in database!";
    }
    return customerName;
}

int DBManager::getCustomerIDFromCustomerName(QString customerName)
{
    if (customerName.isEmpty())
    {
        throw QString("Customer name cannot be empty!");
    }
    int customerID;
    QSqlQuery customersQuery;
    customersQuery.prepare("SELECT id FROM customers WHERE LOWER(name) = :customerName");

    customersQuery.bindValue(":customerName", customerName);

    // If the query has a result
    if (customersQuery.exec() && customersQuery.first())
    {
        customerID = customersQuery.value(0).toInt();
    }
    else
    {
        throw QString("Customer name does not exist in database!");
    }
    return customerID;
}

std::vector<Customer> DBManager::getAllCustomers()
{
    std::vector<Customer> customers;
    QSqlQuery customersQuery;
    customersQuery.prepare("SELECT id, name, type, expirationdate FROM customers"); //<! checks the first two characters of expirationDate column in database

    if (customersQuery.exec())
    {
        if (customersQuery.first())
        {
            while(customersQuery.isValid())
            {
                Customer tempCustomer;

                tempCustomer.setCustomerID(customersQuery.value(0).toInt());      // Sets customer ID
                tempCustomer.setCustomerName(customersQuery.value(1).toString()); // Sets customer name
                tempCustomer.setMemberType(customersQuery.value(2).toString());   // Sets customer member type
                tempCustomer.setExpDate(customersQuery.value(3).toString());      // Sets expiration date

                customers.push_back(tempCustomer); // Pushes customer to vector

                customersQuery.next(); // Goes to next query result matching our customersQuery
            }
        }
        else
        {
            // returns a fake transaction to the table to inform user that the ID they entered
            // was not found.
            customers.push_back(Customer(0, "Error loading customers from database", ""));
        }
    }
    return customers;
}


std::vector<Customer> DBManager::getExpiringMembershipsForMonth(QString month)
{
    QSqlQuery customersQuery;

    customersQuery.prepare("SELECT id, name, type, expirationdate FROM customers WHERE substr(expirationdate, 1, 2)=:month"); //<! checks the first two characters of expirationDate column in database
    customersQuery.bindValue(":month", month);
    std::vector<Customer> customers;

    if (customersQuery.exec())
    {
        if (customersQuery.first())
        {
            while(customersQuery.isValid())
            {
                Customer tempCustomer;

                tempCustomer.setCustomerID(customersQuery.value(0).toInt());      // Sets customer ID
                tempCustomer.setCustomerName(customersQuery.value(1).toString()); // Sets customer name
                tempCustomer.setMemberType(customersQuery.value(2).toString());   // Sets customer member type
                tempCustomer.setExpDate(customersQuery.value(3).toString());      //

                customers.push_back(tempCustomer); // Pushes customer to vector

                customersQuery.next(); // Goes to next query result matching our customersQuery
            }
        }
        else
        {
            throw QString("No memberships are expiring during the specified month!");
        }
    }
    qDebug() << customersQuery.lastError();
    return customers;
}

/*******************************************************************************************
 * DATA COLLECTION TRANSACTION FUNCTIONS
 *
 * getAllTransactions
 *  - puts all of the transactions in the database into a vector with:
 *  - the ID, name, quantity purchased, and purchase date of each item
 *
 * getTransactionsBySalesDate
 *  - returns a vector of all transactions that occured on a particular date
 *
 * getTransactionsByCustomerName
 *  - returns a vector with all of the transactions that a particular customer by a name has made
 *
 * getTransactionsByMemberID
 *  - returns a vector with all of the transactions that a particular customer by an ID has made
 *
 * getSalesPriceTotalFloat
 *  - returns the total sales price of a transaction
 *
 * updateTransactioninDB
 *  - changes the values linked to an item in the database
 *
 * addTransaction
 * - Adds a new transaction to the database
 *******************************************************************************************/
std::vector<Transaction> DBManager::getAllTransactions()
{
    std::vector<Transaction> transactions;
    QSqlQuery transactionsQuery;

    if(transactionsQuery.exec("SELECT cid, itempurchased, quantitypurchased, date, salePrice FROM transactions"))
    {
        // Check if the query has at least one result
        if (transactionsQuery.first())
        {
            while(transactionsQuery.isValid())
            {
                Transaction tempTransaction;

                tempTransaction.setCustomerID(transactionsQuery.value(0).toInt());
                tempTransaction.setItemName(transactionsQuery.value(1).toString());
                tempTransaction.setQuantityPurchased(transactionsQuery.value(2).toInt());
                tempTransaction.setPurchaseDate(transactionsQuery.value(3).toString());

                transactions.push_back(tempTransaction);

                transactionsQuery.next();
            }
        }
    }
    return transactions;
}


std::vector<Transaction> DBManager::getTransactionsBySalesDate(QDate salesDate)
{
    QSqlQuery query;
    std::vector<Transaction> transactionsBySalesDateList;
    int month = salesDate.month();
    int day = salesDate.day();
    int year = salesDate.year();
    if (!salesDate.isValid() || salesDate.isNull())
    {
        throw QString("Invalid date entered! Please try again.");
    }

    // to be documented....
    std::string salesDateString = std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
    QString salesDateQString = QString::fromStdString(salesDateString);

    query.prepare("SELECT cid, itempurchased, quantitypurchased, date, salePrice FROM transactions WHERE date=:salesDateString");
    query.bindValue(":salesDateString", salesDateQString);

    // cid = 0
    // itempurchased = 1
    // quantitypurchased = 2
    // date = 3
    if (query.exec())
    {
        if(query.first())
        {
            while (query.isValid())
            {
                int customerID, quantityPurchased;
                QString itemName, itemPurchased, datePurchased;

                customerID = query.value(0).toInt();
                itemName = query.value(1).toString();
                quantityPurchased = query.value(2).toInt();
                datePurchased = query.value(3).toString();


                Transaction tempTransaction(customerID, itemName, quantityPurchased, datePurchased); // creates transaction
                transactionsBySalesDateList.push_back(tempTransaction); // Adds transaction to list

                query.next(); // Goes to next query result
            }
        }
        else
        {
            throw QString("Error! No transactions found with specified sales date!");
        }
    }
    return transactionsBySalesDateList;
}

std::vector<Transaction> DBManager::getTransactionsByCustomerName(QString customerName)
{
    std::vector<Transaction> transactions;
    QSqlQuery transactionsQuery;
    QSqlQuery customersQuery;
    double grandTotal;

    // Get customer ID associated with name
    customersQuery.prepare("SELECT id FROM customers WHERE name=:customerName");
    customersQuery.bindValue(":customerName", customerName);
    customersQuery.exec();

    // Get the result from query
    customersQuery.first();
    int customerID = customersQuery.value(0).toInt();


    std::vector<Transaction> transactionsList = getTransactionsByMemberID(customerID, grandTotal);

    return transactionsList;
}

std::vector<Transaction> DBManager::getTransactionsByMemberID(int memberID, double& grandTotal)
{
    grandTotal = 0.0;
    // This function also needs to sum up each transaction and display the
    // grand total at the bottom of the window.
    std::vector<Transaction> transactions;
    QSqlQuery transactionsQuery;

    transactionsQuery.prepare("SELECT cid, itempurchased, quantitypurchased, date, salePrice FROM transactions WHERE cid=:memberID");
    transactionsQuery.bindValue(":memberID", memberID);

    if (transactionsQuery.exec())
    {
        if (transactionsQuery.first())
        {
            while(transactionsQuery.isValid())
            {
                Transaction tempTransaction;
                QString transactionTotalString;

                tempTransaction.setCustomerID(transactionsQuery.value(0).toInt());
                tempTransaction.setItemName(transactionsQuery.value(1).toString());
                tempTransaction.setQuantityPurchased(transactionsQuery.value(2).toInt());
                tempTransaction.setPurchaseDate(transactionsQuery.value(3).toString());
                transactions.push_back(tempTransaction);

                transactionTotalString = getSalesPriceForTransaction(tempTransaction);
                transactionTotalString.remove(0, 1); // removes the '$' prefix from the number string

                grandTotal += transactionTotalString.toDouble();
                transactionsQuery.next();
            }
        }
    }
    return transactions;
}

QString DBManager::getSalesPriceForTransaction(Transaction transaction)
{
    QString itemName = transaction.getItemName(); // Gets the item name associated with the transaction
    //int itemQuantityPurchased = transaction.getQuantityPurchased();
    QString salePriceString;
    float salePriceFloat = 0;
    QSqlQuery itemsQuery;
    QSqlQuery transactionsQuery;


    itemsQuery.exec("SELECT name, price FROM items");

    transactionsQuery.prepare("SELECT id, itempurchased, salePrice FROM transactions WHERE itempurchased=:itemName");
    transactionsQuery.bindValue(":itemName", itemName);
    transactionsQuery.exec();

    if (transactionsQuery.first())
    {
        while (itemsQuery.value(0) != transactionsQuery.value(1) && itemsQuery.next())
        {
            if (itemsQuery.value(0) == transactionsQuery.value(1))
            {
                salePriceFloat = itemsQuery.value(1).toFloat() * transaction.getQuantityPurchased();
            }
        }
    }
    salePriceString = "$" + QString::number(salePriceFloat, 'f', 2);
    return salePriceString;
}

float DBManager::getSalesPriceTotalFloat(Transaction transaction)
{
    QString itemName = transaction.getItemName();
    float salePriceFloat;
    QSqlQuery itemsQuery;
    QSqlQuery transactionsQuery;

    itemsQuery.exec("SELECT name, price FROM items");

    transactionsQuery.prepare("SELECT id, itempurchased, salePrice FROM transactions WHERE itempurchased=:itemName");
    transactionsQuery.bindValue(":itemName", itemName);
    transactionsQuery.exec();

    transactionsQuery.first();
    while (itemsQuery.value(0) != transactionsQuery.value(1) && itemsQuery.next())
    {
        if (itemsQuery.value(0) == transactionsQuery.value(1))
        {
            salePriceFloat = itemsQuery.value(1).toFloat() * transaction.getQuantityPurchased();
        }
    }

    return salePriceFloat;
}

void DBManager::updateTransactionInDB(Transaction newTransaction, int transactionID)
{
    // Converts row number to transactionID
    QSqlQuery query;

    QString itemPurchased = newTransaction.getItemName();
    int quantityPurchased = newTransaction.getQuantityPurchased();
    QString datePurchased = newTransaction.getPurchaseDate();


    query.prepare("UPDATE transactions SET itempurchased=:itemPurchased, quantityPurchased=:quantityPurchased, date=:datePurchased WHERE id=:transactionID");
    query.bindValue(":itemPurchased", itemPurchased);
    query.bindValue(":quantityPurchased", quantityPurchased);
    query.bindValue(":datePurchased", datePurchased);
    query.bindValue(":transactionID", transactionID);
    query.exec();

    qDebug() << query.lastError();
}

void DBManager::addTransaction(Transaction transactionToAdd)
{
    QSqlQuery transQuery;
    transQuery.prepare("INSERT INTO transactions (cid, itemPurchased, quantityPurchased, date) VALUES (:customerID, :itemPurchased, :quantityPurchased, :datePurchased)");

    transQuery.bindValue(":customerID", transactionToAdd.getCustomerID());
    transQuery.bindValue(":itemPurchased", transactionToAdd.getItemName());
    transQuery.bindValue(":quantityPurchased", transactionToAdd.getQuantityPurchased());
    transQuery.bindValue(":datePurchased", transactionToAdd.getPurchaseDate());

    if (!transQuery.exec())
    {
        throw transactionToAdd.getCustomerID();
    }
}
void DBManager::deleteTransaction(int transactionID)
{
    QSqlQuery query;
    QSqlQuery updateIndexQuery;
    QSqlQuery reIndexQuery;
    query.prepare("DELETE FROM transactions WHERE id = :transactionID");
    query.bindValue(":transactionID", transactionID);
    query.exec();

    int newIndex = 1;
    if(reIndexQuery.exec("SELECT id FROM transactions"))
    {
        reIndexQuery.first();
        while(reIndexQuery.isValid())
        {
            int currentIndex = reIndexQuery.value(0).toInt();
            updateIndexQuery.prepare("UPDATE transactions SET id=:newIndex WHERE id=:currentIndex");

            updateIndexQuery.bindValue(":currentIndex", currentIndex);
            updateIndexQuery.bindValue(":newIndex", newIndex);

            updateIndexQuery.exec();

            newIndex++;
            reIndexQuery.next();
        }
    }
}
/*******************************************************************************************
 * DATA COLLECTION ITEM FUNCTIONS
 *
 * getAllItems
 *  - puts all of the items in a the database into a vector containing:
 *  - the name, price, quantity purchased, and revenue the item has created
 *
 * addItem
 *  -using passed parameters this function creates a new object and adds it to the database
 *
 * deleteItem
 *  - finds the item in the database and deletes the entire record
 *******************************************************************************************/
//Gets all items from the database and returns them to the program placing them
//inside a vector of items from class Item and returns vector
std::vector<Item> DBManager::getAllItems()
{
    std::vector<Item> items;
    QSqlQuery itemsQuery;
    itemsQuery.exec("SELECT name, price, quantity, revenue FROM items");

    //checks to see if database has values
    if(itemsQuery.first())
    {
        while(itemsQuery.isValid())
        {
            Item tempItem;

            tempItem.setItemName(itemsQuery.value(0).toString());
            tempItem.setItemPrice(itemsQuery.value(1).toFloat());
            tempItem.setQuantitySold(itemsQuery.value(2).toInt());
            tempItem.setTotalRevenue(itemsQuery.value(3).toFloat());

            items.push_back(tempItem);

            itemsQuery.next();
        }
    }
    qDebug() << itemsQuery.lastError();
    return items;
}

//Adds an item to the table in the database
void DBManager::addItem(QString itemName, float itemPrice)
{
    QSqlQuery query;
    query.prepare("INSERT INTO items (name, price, quantity, revenue) VALUES (:itemName, :itemPrice, 0, 0)");
    query.bindValue(":itemName", itemName);
    query.bindValue(":itemPrice", itemPrice);
    query.exec();
}

//Deletes item from table in database
void DBManager::deleteItem(QString itemName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM items WHERE name = :itemName");
    query.bindValue(":itemName", itemName);
    query.exec();
}

void DBManager::updateItemInDB(Item item)
{
    QSqlQuery query;
    QString itemName = item.getItemName();
    float itemPrice = item.getItemPrice();
    int itemQuantity = item.getQuantitySold();
    float itemRevenue = item.getTotalRevenue();

    query.prepare("UPDATE items SET price = :itemPrice, quantity = :itemQuantity, revenue = :itemRevenue WHERE name = :itemName");
    query.bindValue(":itemName", itemName);
    query.bindValue(":itemPrice", itemPrice);
    query.bindValue(":itemQuantity", itemQuantity);
    query.bindValue(":itemRevenue", itemRevenue);

    query.exec();
}

/************************************************************************
 * DATABASE CONNECTION
 *
 * getDB
 *  -opens the database connection
 *
 * close
 *  - Closes the database connection (used for when a user clicks quit)
 *
 * destructor
 ***********************************************************************/

QSqlDatabase* DBManager::getDB()
{
    return &this->db;
}
void DBManager::close()
{
    db.close();
}

DBManager::~DBManager()
{

}
