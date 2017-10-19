#include "dbmanager.h"
#include "customer.h"
#include <QMessageBox>
#include <QDate>

/************************************************************************
 * DBManager Constructor
 * ---------------------------------------------------------------------
 * Sets up the database file to read from
 ***********************************************************************/
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
    query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT, role TEXT)");
    query.exec("CREATE TABLE customers (id INTEGER, name TEXT, type TEXT, expirationDate REAL)");
    query.exec("CREATE TABLE items (id INTEGER PRIMARY KEY, name TEXT, price REAL, quantity INTEGER PRIMARY KEY, revenue REAL)");
    query.exec("CREATE TABLE transactions (id INTEGER PRIMARY KEY, cid INTEGER, customerName TEXT, itemPurchased TEXT, quantityPurchased INTEGER, date REAL, salePrice REAL)");

    if(!query.isActive())
    {
        qWarning() << "DBManager::initDB - Error: " << query.lastError().text();
    }
}

/************************************************************************
 * DBManager::authenticateUser
 * ---------------------------------------------------------------------
 * Passed username and password as strings
 * Checks database 'users' table for any matching entries
 * Returns true if a match is found, false if no match found
 ***********************************************************************/
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
        customerName = "Customer name matches no customers in database!";
    }
    return customerID;
}

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
    return items;
}

std::vector<Transaction> DBManager::getTransactionsBySalesDate(QDate salesDate)
{
    QSqlQuery query;
    std::vector<Transaction> transactionsBySalesDateList;
    int month = salesDate.month();
    int day = salesDate.day();
    int year = salesDate.year();

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
            // We push a blank customer to the vector to let the UI layer know there was an error
            transactionsBySalesDateList.push_back(Transaction(0, "", 0, ""));
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

                qDebug() << "TRANS TOTAL: " << transactionTotalString;
                grandTotal += transactionTotalString.toDouble();
                qDebug() << "GRAND TOTAL: " << grandTotal;
                transactionsQuery.next();
            }
        }
        else
        {
            // returns a fake transaction to the table to inform user that the ID they entered
            // was not found.
            transactions.push_back(Transaction(0, "Customer ID not found", 0, ""));

        }
    }
    return transactions;
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
            // returns a fake transaction to the table to inform user that the ID they entered
            // was not found.
            customers.push_back(Customer(0, "No customers found", "in database with given expiration date." ));

        }
    }
    qDebug() << customersQuery.lastError();
    return customers;
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

std::vector<Customer> DBManager::getAllExecutiveCustomers()
{
    std::vector<Customer> execCustomers;
    QSqlQuery customerQuery;
    QString memberType = "Executive";

    customerQuery.prepare("SELECT id, name, type, expirationdate FROM customers WHERE type=:memberType");
    customerQuery.bindValue(":memberType", memberType);

    if (customerQuery.exec())
    {

        if (customerQuery.first())
        {
            while(customerQuery.isValid())
            {
                Customer tempCustomer;

                tempCustomer.setCustomerID(customerQuery.value(0).toInt());      // Sets customer ID
                tempCustomer.setCustomerName(customerQuery.value(1).toString()); // Sets customer name
                tempCustomer.setMemberType(customerQuery.value(2).toString());   // Sets customer member type
                tempCustomer.setExpDate(customerQuery.value(3).toString());      // Sets customer exp date

                execCustomers.push_back(tempCustomer); // Pushes customer to vector

                customerQuery.next(); // Goes to next query result matching our customersQuery
            }
        }
        else
        {
            // returns a fake transaction to the table to inform user that the ID they entered
            // was not found.
            execCustomers.push_back(Customer(0, "No customers found", "in database with given member type." ));

        }
    }
    qDebug() << customerQuery.lastError();

    return execCustomers;
}

QSqlDatabase* DBManager::getDB()
{
    return &this->db;
}

/************************************************************************
 * DBManager::close()
 * ---------------------------------------------------------------------
 * Closes the database connection (used for when a user clicks quit)
 ***********************************************************************/
void DBManager::close()
{
    db.close();


}

DBManager::~DBManager()
{

}
