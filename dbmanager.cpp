#include "dbmanager.h"
#include <QMessageBox>


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
    QSqlQuery query("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT, role TEXT)");
    query.exec("CREATE TABLE customers (id INTEGER, name TEXT, type TEXT, expirationDate REAL)");
    query.exec("CREATE TABLE items (id INTEGER PRIMARY KEY, name TEXT, price REAL)");
    query.exec("CREATE TABLE transactions (id INTEGER PRIMARY KEY, cid INTEGER, customerName TEXT, itemPurchased TEXT, quantityPurchased INTEGER, date REAL)");

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
bool DBManager::authenticateUser(QString username, QString password)
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
    if(query.exec("SELECT username, password FROM users WHERE username='" + username + "' AND PASSWORD='" + password + "'"))
    {
        if (query.next())
        {
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

std::vector<Transaction> DBManager::getAllTransactions()
{
    qDebug() << "Getting all transactions.";
    std::vector<Transaction> transactions;
    QSqlQuery transactionsQuery;

    if(transactionsQuery.exec("SELECT cid, itempurchased, quantitypurchased, date FROM transactions"))
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

std::vector<Transaction> DBManager::getTransactionsBySalesDate(QString salesDate)
{
    std::vector<Transaction> transactionsByIDList;
    QSqlQuery query;
    query.prepare("SELECT cid, itempurchased, quantitypurchased, date FROM transactions WHERE date=:salesDate");
    query.bindValue(":salesDate", salesDate);

    qDebug() << query.lastError();
    // cid = 0
    // itempurchased = 1
    // quantitypurchased = 2
    // date = 3
    if (query.exec())
    {
        qDebug() << "Query executed";
        if(query.first())
        {
            qDebug() << "first result loaded";
            while (query.isValid())
            {
                int customerID, quantityPurchased;
                QString itemName, itemPurchased, datePurchased;

                customerID = query.value(0).toInt();
                itemName = query.value(1).toString();
                quantityPurchased = query.value(2).toInt();
                datePurchased = query.value(3).toString();


                Transaction tempTransaction(customerID, itemName, quantityPurchased, datePurchased); // creates transaction
                transactionsByIDList.push_back(tempTransaction); // Adds transaction to list

                query.next(); // Goes to next query result
            }
        }
    }
    return transactionsByIDList;
}

std::vector<Transaction> DBManager::getTransactionsByMemberID(int memberID)
{
    std::vector<Transaction> transactions;
    QSqlQuery transactionsQuery;

    transactionsQuery.prepare("SELECT cid, itempurchased, quantitypurchased, date FROM transactions WHERE cid=:memberID");
    transactionsQuery.bindValue(":memberID", memberID);

    if (transactionsQuery.exec())
    {
        if (transactionsQuery.first())
        {
            while(transactionsQuery.isValid())
            {
                Transaction tempTransaction;

                tempTransaction.setCustomerID(transactionsQuery.value(0).toInt());
                tempTransaction.setItemName(transactionsQuery.value(1).toString());
                tempTransaction.setQuantityPurchased(transactionsQuery.value(2).toInt());
                tempTransaction.setPurchaseDate(transactionsQuery.value(3).toString());
                qDebug() << "in loop";
                transactions.push_back(tempTransaction);

                transactionsQuery.next();
            }
        }
        else
        {
             transactions.push_back(Transaction(0, "Customer ID not found", 0, ""));

        }
    }
    return transactions;
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
