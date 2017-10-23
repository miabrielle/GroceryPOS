#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "dbmanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void insufficientPriviledgesErrorMessage();
    // Is passed the database pointer, which is initially declared in LoginWindow
    // Needed to access database in the admin panel 'state'
    void setDBPointer(DBManager* dbPointer);


    // Adds a vector of Transaction objects to the data table UI
    void addTransactionsVectorToTable(std::vector<Transaction> transactionsList);

    // Sets up the Transactions data table (column headers, editability behavior, etc)
    void renderTransactions();


    // Calculates the revenue generated for a specified item
    void calculateRevenue(Item & item);

    // Calculates the rebate amount for all Executive members
    std::vector<Customer> calcExecutiveRebates();


    // Sets up the Items data table (column headers, editability behavior, etc)
    void renderItems();

    void displayItems();

    // Adds a vector of Customer objects to the data table in the UI
    void addCustomersVectorToTable(std::vector<Customer> customersList);

    // Sets up the Customers data table (column headers, editability behavior, etc)
    void renderCustomers();

    // Sets the administrator rights to the current logged in user
    void setIsAdmin(bool isAdmin);

    // Copy constructor handles the class pointers
    MainWindow(const MainWindow& mw);

    ~MainWindow();

private slots:

    void on_transactionsTable_cellClicked(int row);

    void on_editTransactionRowButton_clicked();

    void on_showSalesButton_clicked();

    void on_loadAllTransactionsButton_clicked();

    void on_searchByCustomerIDButton_clicked();

    void on_addItemButton_clicked();

    void on_deleteItemButton_clicked();

    void on_displayExpiringMembershipsButton_clicked();

    void on_loadAllCustomersButton_clicked();

    void on_searchButton_clicked();

    void on_displayAllButton_clicked();

    void on_sortItemsByButton_clicked();
    
    void on_showSalesByCustomerName_clicked();

    void on_showChangeMemberStatus_clicked();

    void on_AddCustomerButton_clicked();

    void on_DeleteCustomerButton_clicked();

    void on_addTransactionButton_clicked();

    void on_deleteTransactionButton_clicked();

private:
    Ui::MainWindow *ui;
    DBManager* dbPointer;
    Transaction transactionSelected;
    int rowSelected;
    std::vector<Item> itemsList;
    bool isAdmin;
};

#endif // MAINWINDOW_H
