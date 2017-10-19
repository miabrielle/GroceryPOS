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

    void renderTransactions();
    void renderCustomers();
    void setDBPointer(DBManager* dbPointer);
    void addTransactionsVectorToTable(std::vector<Transaction> transactionsList);

    void calculateRevenue(Item & item);
    std::vector<Customer> calcExecutiveRebates();
    void renderItems();
    void displayItems();

    void addCustomersVectorToTable(std::vector<Customer> customersList);

    ~MainWindow();

private slots:

    void on_transactionsTable_cellClicked(int row);

    void on_editTransactionRowButton_clicked();

    void on_showSalesButton_clicked();

    void on_loadAllTransactionsButton_clicked();

    void on_showSalesByMemberIDButton_clicked();

    void on_addItemButton_clicked();

    void on_deleteItemButton_clicked();

    void on_displayExpiringMembershipsButton_clicked();

    void on_loadAllCustomersButton_clicked();

    void on_searchButton_clicked();

    void on_displayAllButton_clicked();

    void on_sortItemsByButton_clicked();
    
    void on_showChangeMemberStatus_clicked();

private:
    Ui::MainWindow *ui;
    DBManager* dbPointer;
    Transaction transactionSelected;
    int rowSelected;
    std::vector<Item> itemsList;
};

#endif // MAINWINDOW_H
