#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QList>
#include <QComboBox>
#include <QSqlTableModel>

#include "transaction.h"
#include "item.h"
#include "customer.h"
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

    // Takes in customerName, finds customerID associates with name, returned as integer
    int getCustomerIDFromCustomerName(QString customerName);

    // Returns true if user authenticates successfully
    // username and password are passed from user input on login screen
    bool authenticateUser(QString username, QString password, bool& isAdmin);

    // Used for filling in combo boxes with data from a table
    void createComboBoxModel(QString tableName, QString fieldName, QComboBox* comboBox);

    //When information on an item is updated, this is called to update the database
    void updateItemInDB(Item item);

    // Get transactions by purchase date from database
    std::vector<Transaction> getTransactionsBySalesDate(QDate salesDate);
\
    std::vector<Transaction> getTransactionsByCustomerName(QString customerName);
    // Get transactions by MemberID
    std::vector<Transaction> getTransactionsByMemberID(int memberID, double& grandTotal);

    void addTransaction(Transaction transactionToAdd);

    void deleteTransaction(int transactionID);

    // Get all customers from database
    std::vector<Customer> getAllCustomers();

    // Get customers by expirationDate from database
    std::vector<Customer> getExpiringMembershipsForMonth(QString month);

    QString getSalesPriceForTransaction(Transaction transaction);
    float getSalesPriceTotalFloat(Transaction transaction);

    // Update transaction in database
    void updateTransactionInDB(Transaction newTransaction, int transactionID);

    void deleteItem(QString itemName);
    void addItem(QString itemName, float itemPrice);

    void addCustomer(Customer temp);
    void deleteCustomer(QString customerName);

    // Get all executive customers
    std::vector<Customer> getAllExecutiveCustomers();


    QSqlDatabase* getDB();

    ~DBManager();



};
#endif // DBMANAGER_H
