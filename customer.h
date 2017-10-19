#ifndef Customer_H
#define Customer_H
#include <QMainWindow>

class Customer
{
private:
    int customerID;
    QString customerName;
    QString expDate;
    QString memberType;
    float rebateAmt;
    bool changeStatus;

public:

    // Constructors
    Customer();
    Customer(int customerID, QString customerName, QString memberType);


// ==================== ACCESSOR FUNCTIONS =============================/
    // Get Functions
    QString getCustomerName();
    QString getExpDate();
    QString getMemberType();
    int getCustomerID();
    float getRebateAmt();
    bool getChangeStatus();

    // Set functions
    void setCustomerName(QString customerName);
    void setExpDate(QString expDate);
    void setCustomerID(int ustomerID);
    void setRebateAmt(float rebateAmt);
    void setMemberType(QString memberType);
    void setChangeStatus(bool changeStatus);

    ~Customer();
};

#endif // Customer_H
