#ifndef MEMBERCHANGESTATUS_H
#define MEMBERCHANGESTATUS_H

#include <QMainWindow>
#include <QDialog>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "dbmanager.h"
#include <vector>

namespace Ui {
class MemberChangeStatus;
}

class MemberChangeStatus : public QMainWindow
{
    Q_OBJECT

public:
    void setDBPointer(DBManager* dbPointer);        //sets dbpointer
    void addCustomerVectorToTable(std::vector<Customer> customersList); //adds customers to table
    void renderCustomerStatusTable();               //sets up table and adds customers
    std::vector<Customer> calcMemberChangeStatus(); //runs calcuculations and sets status

    explicit MemberChangeStatus(QWidget *parent = 0);
    ~MemberChangeStatus();

private slots:
    void on_showMemberChangeStatuses_clicked();

    void on_closeMemStatWindow_clicked();

private:
    Ui::MemberChangeStatus *ui;
    DBManager *dbPointer;
};

#endif // MEMBERCHANGESTATUS_H
