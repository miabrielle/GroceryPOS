#include "memberchangestatus.h"
#include "ui_memberchangestatus.h"

MemberChangeStatus::MemberChangeStatus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MemberChangeStatus)
{
    ui->setupUi(this);
}

void MemberChangeStatus::setDBPointer(DBManager* dbPointer)
{
    this->dbPointer = dbPointer;
}

void MemberChangeStatus::renderCustomerStatusTable()
{
    // Gets a vector of all customers in SQL database
    std::vector<Customer> customersList = dbPointer->getAllCustomers();
    customersList = calcMemberChangeStatus();

    // Set the behavior of the customers table
    ui->memberStatusTable->setEditTriggers((QAbstractItemView::NoEditTriggers));
    ui->memberStatusTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->memberStatusTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->memberStatusTable->setColumnCount(3);

    ui->memberStatusTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Customer ID"));
    ui->memberStatusTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->memberStatusTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Member Change Status"));

    ui->memberStatusTable->setColumnWidth(0, 150);
    ui->memberStatusTable->setColumnWidth(1, 200);
    ui->memberStatusTable->setColumnWidth(2, 420);

    // Updates the table with new list of customers obtained from database
    addCustomerVectorToTable(customersList);
}

void MemberChangeStatus::addCustomerVectorToTable(std::vector<Customer> customersList)
{
    int row = 0;
    QString memberType, MemberChangeStatusMessage;
    bool changeStatus;

    // Sets the number of rows in the table to the exact amount of transaction records found in the vector
    ui->memberStatusTable->setRowCount(customersList.size());

    // Loops through all transactions
    // Populates QTableWidget with appropriate data
    std::vector<Customer>::iterator custIt = customersList.begin();

    while (custIt != customersList.end())
    {
        for (int column = 0; column < ui->memberStatusTable->columnCount(); column++)
        {
            QTableWidgetItem *cell = ui->memberStatusTable->item(row,column);
            if (!cell)
            {
                cell = new QTableWidgetItem;
                ui->memberStatusTable->setItem(row,column,cell);
            }
            switch (column)
            {
            // Customer ID column
            case 0:
                cell->setData(0, QVariant(custIt->getCustomerID()));
                break;

                // Customer Name column
            case 1:
                cell->setData(0, QVariant(customersList.at(row).getCustomerName()));
                break;

                // Member Status column
            case 2: memberType = customersList[row].getMemberType();
                    changeStatus = customersList[row].getChangeStatus();

                    if(memberType == "Executive")
                    {
                        if(changeStatus == true)
                        {
                            MemberChangeStatusMessage = "This Executive member should downgrade.";
                        }
                        else
                        {
                            MemberChangeStatusMessage = "This Executive member should not downgrade.";
                        }
                    }
                    else if(memberType == "Standard")
                    {
                        if(changeStatus == true)
                        {
                            MemberChangeStatusMessage = "This Standard member should upgrade.";
                        }
                        else
                        {
                            MemberChangeStatusMessage = "This Standard member should not upgrade.";
                        }
                    }
                cell->setData(0, MemberChangeStatusMessage);
                break;
            }
        }
        row++;      // Updates to the next row in the table
        custIt++;   // Updates the transactionsList iterator to read from the next transaction on next iteration
    }
}

std::vector<Customer> MemberChangeStatus::calcMemberChangeStatus()
{
    std::vector<Customer> allCustomers = dbPointer->getAllCustomers();
    std::vector<Transaction> executiveTransactions;
    QString memberType;
    int memberID, transactionSize, count = 0;
    float amountSpent = 0, rebateAmount;
    Customer p;

    for(std::vector<Customer>::iterator it = allCustomers.begin(); it != allCustomers.end();
            ++it)
    {
        amountSpent  = 0;  //resets amount spent
        rebateAmount = 0;  //resets rebate amount
        memberType = allCustomers[count].getMemberType(); //gets member type of customer

        memberID = allCustomers[count].getCustomerID(); //gets exec members ID then transactions by ID num
        executiveTransactions = dbPointer->getTransactionsByMemberID(memberID);
        transactionSize = executiveTransactions.size();

        for(int i = 0; i < transactionSize; i++) //loops through transactions and sums amount spent
        {
            amountSpent += dbPointer->getSalesPriceTotalFloat(executiveTransactions[i]);
        }


        rebateAmount = amountSpent * .03; //calcs rebate amount

        //sets ALL custumers rebate amount; if the customer is not executive the rebate amount is set to zero
        allCustomers[count].setRebateAmt(rebateAmount);

        //if the member is executive compares amount saved with rebate to sum of regular membership plus
        //transaction sum; sets bool true if the customer should change their status
        if(memberType == "Executive")
        {
            if((120 - rebateAmount) > (60 + amountSpent))
            {
                allCustomers[count].setChangeStatus(true);
            }
            else
            {
                allCustomers[count].setChangeStatus(false);
            }
        }
        //Same as executive but vice versa
        else if(memberType == "Regular")
        {
            if((120 - rebateAmount) < (60 + amountSpent))
            {
                allCustomers[count].setChangeStatus(true);
            }
            else
            {
                allCustomers[count].setChangeStatus(false);
            }
        }

        executiveTransactions.clear(); //clears transaction vector
        count++;                       //adds to count
    }

    return allCustomers;
}

void MemberChangeStatus::on_showMemberChangeStatuses_clicked()
{
    this->renderCustomerStatusTable();
}


void MemberChangeStatus::on_closeMemStatWindow_clicked()
{
    this->close();
}

MemberChangeStatus::~MemberChangeStatus()
{
    delete ui;
}
