#ifndef Customer_H
#define Customer_H
#include <QMainWindow>
class Customer
{
private:
    QString customerName;
    QString expDate;
    int CustomerID;
    bool isExecutive;
    float rebateAmt;

public:
 // ================== ACCESSOR FUNCTIONS =============================/
    // Get Functions
    Customer();
    QString getCustomerName();
    QString getExpDate();
    int getCustomerID();
    float getRebateAmt();
    bool IsExecutive();

    // Set functions
    void setCustomerName(QString CustomerName);
    void setExpDate(QString expDate);
    void setCustomerID(int CustomerID);
    void setRebateAmt(float rebateAmt);
    void setIsExecutive(bool isExec);

    ~Customer();
};

#endif // Customer_H
