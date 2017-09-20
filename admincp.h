#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void setDBPointer(DBManager* dbPointer);

    ~MainWindow();

private slots:

    void on_transactionsTable_cellClicked(int row);


    void on_editTransactionRowButton_clicked();

private:
    Ui::MainWindow *ui;
    DBManager* dbPointer;
    Transaction transactionSelected;
};

#endif // MAINWINDOW_H
