#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QList>

#include "transaction.h"
#include "item.h"
#include "customer.h"
#include <vector>


#include <QSqlTableModel>
#include <vector>
#include "transaction.h"
#include "item.h"
#include "customer.h"
class DBManager
{
private:
    QSqlDatabase db;
public:
    /************************************************************************
     * DBManager Constructor
     * ---------------------------------------------------------------------
     * Sets up the database file to read from
     ***********************************************************************/
    DBManager();
    void initDB();

    // Closes the database connection
    void close();

    // Get and return data functions to UI
    std::vector<Transaction> getAllTransactions();

    //Gets all items from database and returns to program
    std::vector<Item> getAllItems();

    // Takes in customerID, finds customerName associated with ID, return it as QString
    QString getCustomerNameFromID(int customerID);

    // Returns true if user authenticates successfully
    // username and password are passed from user input on login screen
    bool authenticateUser(QString username, QString password);


    // Get transactions by purchase date from database
    std::vector<Transaction> getTransactionsBySalesDate(QString salesDate);

    // Get transactions by MemberID
    std::vector<Transaction> getTransactionsByMemberID(int memberID);

    // Get all customers from database
    std::vector<Customer> getAllCustomers();

    // Get customers by expirationDate from database
    std::vector<Customer> getExpiringMembershipsForMonth(QString month);


    QSqlDatabase* getDB();

    ~DBManager();



};
#endif // DBMANAGER_H
