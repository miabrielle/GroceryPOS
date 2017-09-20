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
#include "member.h"
#include <vector>


#include <QSqlTableModel>
#include <vector>
#include "transaction.h"
#include "item.h"
#include "member.h"
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

    // Takes in customerID, finds customerName associated with ID, return it as QString
    QString getCustomerNameFromID(int customerID);

    // Returns true if user authenticates successfully
    // username and password are passed from user input on login screen
    bool authenticateUser(QString username, QString password);

    QSqlDatabase* getDB();
    ~DBManager();



};
#endif // DBMANAGER_H
